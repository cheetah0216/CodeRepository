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

void query_test(ifstream &infile)
{
  TextQuery tq;
  tq.read_file(infile);
  Query andq = Query("hair") & Query("Alice");
  //Query andq = ~Query("hair");
  string ands = "hair | Alice";
  cout << "Query for: " << andq << endl;
  set<TextQuery::line_no> result = andq.eval(tq);
  print_result(result, ands, tq);
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
  query_test(infile);
  return 0;
}

