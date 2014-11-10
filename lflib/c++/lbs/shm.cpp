#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <vector>

#include <iostream>
#include <boost/foreach.hpp>

#include <sys/time.h>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
namespace bi = boost::interprocess;

typedef bg::model::point<int, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<point, std::string> value;
typedef bgi::indexable<value> idx;
typedef bgi::equal_to<value> eq;
typedef bi::allocator<value, bi::managed_mapped_file::segment_manager> alloc;
typedef bgi::quadratic<32> qu;
typedef bgi::linear<32, 8> par;
typedef bgi::rtree< value, par, idx, eq, alloc > Rtree;

bi::managed_mapped_file *_file;
alloc *_ac;
Rtree *rtree; 

uint64_t get_microstamp()
{
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    return (((uint64_t)tv1.tv_sec) * 1000) + ((uint64_t)tv1.tv_usec) / 1000;
}

unsigned int get_seed()
{
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    return (unsigned int)(tv1.tv_usec);
}

int get_flag()
{
    srand(get_seed());
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    if(rand() % 2 == 0){
        return 1;
    }else{
        return -1;
    }
}

int get_randnum(const unsigned int randmax)
{
    int flag = get_flag();
    srand(get_seed());
    int num = (int)((unsigned int)(rand())% randmax) * flag;
    return num;
}

void create_rtree()
{
    std::cout << "create:" << std::endl;
    int posx = 0;
    int posy = 0;
    uint64_t starttime;
    starttime = get_microstamp();

    for(int i = 0; i < 1; i++){
        //posx = get_randnum(9000001);
        //posy = get_randnum(18000001); 
        posx = 1;
        posy = 2;
        //std::cout << i << ": " << posx << "," << posy << std::endl;
        //std::cout << i << ": " << posx - 1 << "," << posy - 1 << std::endl;

        point b(posx,posy);

        try{
            std::cout << rtree->size() << std::endl;
            std::string str1 = "hello";
            std::string str2 = "luxy";
            rtree->insert(std::make_pair(point(posx, posy), str1));
            rtree->insert(std::make_pair(point(posx, posy), str2));
        }catch(...){
            std::cout << "failed!" << std::endl;
            //_file->grow("data.bin", 1024 * 1024);
        }

    }

    uint64_t endtime = get_microstamp();
    std::cout << "create rtree time:" << (endtime - starttime) << "ms" << std::endl;
}

void test_point(int x, int y)
{
    uint64_t starttime;
    starttime = get_microstamp();
 
    point p(x, y);
    std::vector<value> result_s;
    rtree->query(bgi::within(p), std::back_inserter(result_s));

    uint64_t endtime = get_microstamp();
    std::cout << "time:" << (endtime - starttime) << "ms" << std::endl;
    std::cout << "spatial query result:" << std::endl;
    std::cout << "total: " << result_s.size() << std::endl;
    BOOST_FOREACH(value const& v, result_s)
        std::cout << bg::wkt<point>(v.first) << " - " << v.second << std::endl;

}

void test_del(int x, int y)
{
    std::string val = "hello";
    if(rtree->remove(std::make_pair(point(x, y), val))){
        std::cout << "remove success!" << std::endl;
    }else{
        std::cout << "recome failed!" << std::endl;
    }
}

void test_remove(int x, int y)
{
    point p(x, y);
    std::vector<value> result_s;
    rtree->query(bgi::within(p), std::back_inserter(result_s));
    unsigned num1 = result_s.size();
    BOOST_FOREACH(value const& v, result_s)
    {
        std::cout << bg::wkt<point>(v.first) << " - " << v.second << std::endl;
        rtree->remove(std::make_pair(v.first, v.second));
    }

    result_s.clear();
    rtree->query(bgi::within(p), std::back_inserter(result_s));
    unsigned num2 = result_s.size();

    if(num1 == 2 && num2==0){
        std::cout << "delete success" << std::endl;
    }
}



void test_range()
{
    uint64_t starttime;
    starttime = get_microstamp();
 
    box query_box(point(-90000, -180000), point(90000, 180000));
    std::vector<value> result_s;
    rtree->query(bgi::intersects(query_box), std::back_inserter(result_s));

    uint64_t endtime = get_microstamp();
    std::cout << "time:" << (endtime - starttime) << "ms" << std::endl;
    std::cout << "spatial query box:" << std::endl;
    std::cout << bg::wkt<box>(query_box) << std::endl;
    std::cout << "spatial query result:" << std::endl;
    std::cout << "total: " << result_s.size() << std::endl;
    BOOST_FOREACH(value const& v, result_s)
        std::cout << bg::wkt<point>(v.first) << " - " << v.second << std::endl;

}

void test_near()
{
    uint64_t starttime = get_microstamp();
    std::vector<value> result_n;
    rtree->query(bgi::nearest(point(0, 0), 100), std::back_inserter(result_n));

    uint64_t endtime = get_microstamp();
    std::cout << "time:" << (endtime - starttime) << "ms" << std::endl;
    std::cout << "knn query point:" << std::endl;
    std::cout << bg::wkt<point>(point(1000, 1000)) << std::endl;
    std::cout << "knn query result:" << std::endl;
    std::cout << "total: " << result_n.size() << std::endl;
    BOOST_FOREACH(value const& v, result_n)
        std::cout << bg::wkt<point>(v.first) << " - " << v.second << std::endl;
}

int main()
{
    _file = new bi::managed_mapped_file(bi::open_or_create, "data.bin", 100*1024*1024);
    _ac = new alloc(_file->get_segment_manager());
    rtree = _file->find_or_construct<Rtree>("rtree")(par(), idx(), eq(), *_ac);
	create_rtree();    
    //test_range();
    test_near();
    //test_point(-5867798, -14867835);
    //test_remove(1, 2);
    test_del(1, 2);
    test_near();
    //test_remove(2,2);
    test_del(1, 2);
    test_near();

    return 0;
}

