#ifndef __TEXT_QUERY_H__
#define __TEXT_QUERY_H__

#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class TextQuery{
  public:
    typedef vector<string>::size_type line_no;
    void read_file(ifstream &is);
    set<line_no> run_query(const string&) const;
    string text_line(line_no) const;
    line_no size() const { return lines_of_text.size(); }

  private:
    void store_file(ifstream&);
    void build_map();
    vector<string> lines_of_text;
    map< string, set<line_no> > word_map;
};

void TextQuery::read_file(ifstream &is)
{
  store_file(is);
  build_map();
}

void TextQuery::store_file(ifstream &is)
{
  string textline;
  while(getline(is, textline))
    lines_of_text.push_back(textline);
}

void TextQuery::build_map()
{
  for (line_no line_num = 0; line_num != lines_of_text.size(); line_num++) 
  {
    istringstream line(lines_of_text[line_num]);
    string word;
    while (line >> word) 
    {
      //cout << word << endl;
      word_map[word].insert(line_num);
    }
  }
}

set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const
{
  map<string, set<line_no> >::const_iterator loc = word_map.find(query_word);
  if (loc == word_map.end()) 
  {
    return set<line_no>();
  }
  else 
  {
    return loc->second;
  }
}

string TextQuery::text_line(line_no line) const
{
  //cout << line << " " << lines_of_text.size() << endl;
  if (line < lines_of_text.size()) 
  {
    return lines_of_text[line];
  }
  throw out_of_range("line number out of range");
}

#endif
