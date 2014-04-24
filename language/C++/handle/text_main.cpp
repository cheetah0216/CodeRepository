#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include "TextQuery.h"
#include "query.h"
using namespace std;

ifstream& open_file(ifstream &in, const string &file)
{
  in.close();
  in.clear();
  in.open(file.c_str());
  return in;
}
string make_plural(size_t ctr, 
                  const string& word,
                  const string& ending)
{
  return (ctr == 1) ? word : word + ending;
}

void print_result(const set<TextQuery::line_no> &locs,
                  const string& sought,
                  const TextQuery &file)
{
  typedef set<TextQuery::line_no> line_nums;
  line_nums::size_type size = locs.size();
  cout << "\n" << sought << " occurs " << size << " " 
    << make_plural(size, "time", "s") << endl;

  for (line_nums::const_iterator it = locs.begin(); it != locs.end(); it++) 
  {
    cout << "\t(line "
      << (*it) + 1 << ") "
      << file.text_line(*it) << endl;
  }
}

void textquery_test(ifstream &infile)
{
  TextQuery tq;
  tq.read_file(infile);
  while (true) 
  {
    cout << "enter word to look for,or q to quit: ";
    string s;
    cin >> s;
    if (!cin || s == "q") 
      break;
    set<TextQuery::line_no> locs = tq.run_query(s);
    print_result(locs,s,tq);
  }
}

void query_word_test(TextQuery &tq, string s)
{
  Query q1 = Query(s);
  string s1 = s;
  set<TextQuery::line_no> result1 = q1.eval(tq);
  print_result(result1, s1, tq);
  cout << "Query for: " << q1 << endl;
}

void query_not_test(TextQuery &tq, string s)
{
  Query q1 = ~Query(s);
  string s1 = "~"+s;
  set<TextQuery::line_no> result1 = q1.eval(tq);
  print_result(result1, s1, tq);
  cout << "Query for: " << q1 << endl;
}

void query_binary_test(TextQuery &tq, string oper)
{

  Query q1 = Query("hair");
  string s1 = "hair";
  //set<TextQuery::line_no> result1 = q1.eval(tq);
  //print_result(result1, s1, tq);

  Query q2 = Query("Alice");
  string s2 = "Alice";
  //set<TextQuery::line_no> result2 = q2.eval(tq);
  //print_result(result2, s2, tq);

  if( oper == "&")
  {
    Query andq = q1 & q2;
    string ands = "hair & Alice";
    set<TextQuery::line_no> result = andq.eval(tq);
    print_result(result, ands, tq);
    cout << "Query for: " << andq << endl;
  }
  if( oper == "|")
  {
    Query orq = q1 | q2;
    string ors = "hair | Alice";
    set<TextQuery::line_no> result = orq.eval(tq);
    print_result(result, ors, tq);
    cout << "Query for: " << orq << endl;
  }
}

void query_mul_test(TextQuery &tq)
{
  Query q1 = Query("fiery");
  string s1 = "hair";
  //set<TextQuery::line_no> result1 = q1.eval(tq);
  //print_result(result1, s1, tq);

  Query q2 = Query("bird");
  string s2 = "bird";
  //set<TextQuery::line_no> result2 = q2.eval(tq);
  //print_result(result2, s2, tq);
  
  Query q3 = Query("wind");
  string s3 = "wind";
  //set<TextQuery::line_no> result3 = q3.eval(tq);
  //print_result(result3, s3, tq);

  Query mulq = (q1 & q2) | q3;
  string muls = "(fiery & bird) | wind";
  set<TextQuery::line_no> result = mulq.eval(tq);
  print_result(result, muls, tq);
  cout << "Query for: " << mulq << endl;
}

int main(int argc, char **argv)
{
  ifstream infile;
  if (argc < 2 || !open_file(infile,argv[1]))
  {
    cerr << "No input file!" << endl;
    return EXIT_FAILURE;
  }

  //textquery_test(infile);
  TextQuery tq;
  tq.read_file(infile);

  cout << "================================================" << endl;
  cout << "Query(\"Daddy\"):" << endl;
  query_word_test(tq,"Daddy");

  cout << "================================================" << endl;
  cout << "~Query(\"Alice\"):" << endl;
  query_not_test(tq,"Alice");

  cout << "================================================" << endl;
  cout << "Query(\"hair\") | Query(\"Alice\"):" << endl;
  query_binary_test(tq,"|");

  cout << "================================================" << endl;
  cout << "Query(\"hair\") & Query(\"Alice\"):" << endl;
  query_binary_test(tq,"&");

  cout << "================================================" << endl;
  cout << "(Query(\"fiery\") & Query(\"bird\")) | Query(\"wind\"):" << endl;
  query_mul_test(tq);
  return 0;
}

