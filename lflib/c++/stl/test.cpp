#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

void stl_test1()
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
}

void test_set_difference()
{
    set<unsigned> list1;
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);

    set<unsigned> list2;
    list2.insert(3);
    list2.insert(4);
    list2.insert(5);
    list2.insert(6);
    list2.insert(7);

    set<unsigned> result;
    set<unsigned>::iterator iter;    

    std::set_difference(
            list1.begin(), list1.end(),
            list2.begin(), list2.end(),
            inserter(result, result.begin())
            );

    for(iter = result.begin(); iter != result.end(); iter++){
        cout << *iter << endl; 
    }
}

void test_reverse_iterator()
{
    map<unsigned, unsigned> numlist;
    numlist.insert(make_pair(1, 10000));
    numlist.insert(make_pair(2, 20000));
    numlist.insert(make_pair(3, 30000));
    numlist.insert(make_pair(4, 40000));

    //不能这样使用
    map<unsigned, unsigned>::reverse_iterator iter =  numlist.find(3);
    for(; iter != numlist.rend(); iter++){
        cout << iter->second << endl;
    }
}

int main()
{
    //test_set_difference();
    test_reverse_iterator();
    return 0;
}
