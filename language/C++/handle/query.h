#ifndef __QUERY_H__
#define __QUERY_H__

#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include "TextQuery.h"
using namespace std;

/* Query_base */
class Query_base{
  friend class Query;
  
  protected:
    typedef TextQuery::line_no line_no;
    virtual ~Query_base() {}
  
  private:
    virtual set<line_no> eval(const TextQuery&) const = 0;
    virtual ostream& display(ostream& = cout) const = 0;
};

class WordQuery: public Query_base {
  friend class Query;

  WordQuery(const string &s): query_word(s) { cout << "WordQuery()" << s << endl; }
  set<line_no> eval(const TextQuery &t) const
    {
      cout << "WordQuery::eval()" << endl; 
      return t.run_query(query_word); 
    }
  ostream& display (ostream& os) const
    { 
      cout << "WordQuery::display()" << endl;
      return os << query_word;
    }

  string query_word;
};

/* Query */
class Query {
  friend Query operator~ (const Query&);
  friend Query operator| (const Query&, const Query&);
  friend Query operator& (const Query&, const Query&);

  private:
    Query(Query_base *query): q(query), use(new size_t(1)) {  }
  public:
    Query(const string& s): q(new WordQuery(s)), use(new size_t(1)) {  }  
    Query(const Query &c): q(c.q), use(c.use) { ++*use; }
    Query& operator= (const Query&);
    ~Query(){ decr_use(); }

    set<TextQuery::line_no> eval(const TextQuery &t) const
      { 
        cout << "Query::eval()" << endl;
        return q->eval(t);
      }
    ostream &display(ostream &os) const
      { cout << "Query::display()" << endl; return q->display(os); }

  private:
    void decr_use();

  private:
    Query_base *q;
    size_t *use;
};

void Query::decr_use()
{
  if ( --*use == 0 ) 
  {
    delete q;
    delete use;
  }
}

Query& Query::operator=(const Query& rhs)
{
  ++*rhs.use;
  decr_use();
  q = rhs.q;
  use = rhs.use;
  return *this;
}

inline ostream& operator<<(ostream& os, const Query q)
{
  cout << "opertor<< Query.display()" << endl;
  return q.display(os);
}

class NotQuery: public Query_base {
  friend Query operator~(const Query&); 
  NotQuery(const Query &q): query(q) { cout << "NotQuery()" << endl; }

  set<line_no> eval(const TextQuery&) const;
  ostream& display(ostream &os) const
   { 
     cout << "NotQuery::display()" << endl;
     return os << "~(" << query << ")"; 
   }

  const Query query;
};

set<TextQuery::line_no> NotQuery::eval(const TextQuery& file) const
{
  cout << "NotQuery::eval()" << endl;
  set<TextQuery::line_no> has_val = query.eval(file);
  set<line_no> ret_lines;
  for (TextQuery::line_no n = 0; n != file.size(); n++) 
  {
    if (has_val.find(n) == has_val.end()) 
    {
      ret_lines.insert(n);
    }
  }
  return ret_lines;
}

class BinaryQuery: public Query_base {
  protected:
    BinaryQuery(const Query &left, const Query &right, string op):
      lhs(left),rhs(right),oper(op) { cout << "Binary()" << endl; }
    ostream& display(ostream &os) const
      { 
        cout << "BinaryQuery::display()_" << oper << endl;
        os << "(" << lhs << " " << oper << " " << rhs << ")"; 
      }
    const Query lhs, rhs;
    const string oper;
};

class AndQuery: public BinaryQuery{
  friend Query operator&(const Query&, const Query&);
  AndQuery(const Query &left,const Query &right): 
      BinaryQuery(left, right, "&") { cout << "And()" << endl; }  
  set<TextQuery::line_no> eval(const TextQuery& ) const;
};

set<TextQuery::line_no> AndQuery::eval(const TextQuery& file) const
{
  cout << "AndQuery::eval()" << endl;
  set<TextQuery::line_no> right = rhs.eval(file);
  set<TextQuery::line_no> ret_lines = lhs.eval(file);
  ret_lines.insert(right.begin(), right.end());
  return ret_lines;
}

class OrQuery: public BinaryQuery{
  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query &left, const Query &right): 
      BinaryQuery(left, right, "|") { cout << "Or()" << endl; }  
  set<line_no> eval(const TextQuery& ) const;
};

set<TextQuery::line_no> OrQuery::eval(const TextQuery& file) const
{
  cout << "OrQuery::eval()" << endl;
  set<line_no> left = lhs.eval(file);
  set<line_no>::const_iterator it;
  for(it = left.begin(); it != left.end(); it++)
  {
    cout << (*it)+1 << ":" << file.text_line(*it) << endl;
  }

  set<line_no> right = rhs.eval(file);
  for(it = right.begin(); it != right.end(); it++)
  {
    cout << (*it)+1 << ":" << file.text_line(*it) << endl;
  }

  set<line_no> ret_lines;
  set_intersection(left.begin(), left.end(),
                  right.begin(), right.end(),
                  inserter(ret_lines, ret_lines.begin()));
  for(it = ret_lines.begin(); it != ret_lines.end(); it++)
  {
    cout << (*it)+1 << ":" << file.text_line(*it) << endl;
  }
}

inline Query operator&(const Query &lhs, const Query &rhs)
{
  cout << "Start &" << endl;
  return new AndQuery(lhs, rhs);
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
  cout << "Start |" << endl;
  return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query &oper)
{
  cout << "Start ~" << endl; 
  return new NotQuery(oper);
}

#endif
