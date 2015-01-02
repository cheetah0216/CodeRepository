#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<unsigned, unsigned> list;

    list.insert(make_pair(1,1));
    //list.insert(make_pair(2,2));
    //list.insert(make_pair(3,3));

    map<unsigned, unsigned>::iterator it = list.begin();
    map<unsigned, unsigned>::iterator it2;

    for(; it != list.end(); it++){
        cout << it->first << " " << it->second << endl;
    }

    if(it == list.end()){
        cout << "end1" << endl;
    }

    it2 = it;
    if(it2 == list.end()){
        cout << "end2" << endl;
    }

    it++;
    if(it != list.end()){
        cout << "end2" << endl;
    }

    it++;
    if(it != list.end()){
        cout << "end3" << endl;
    }

    return 0;
}
