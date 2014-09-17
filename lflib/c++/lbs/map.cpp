#include <iostream>

#include </usr/local/include/boost/interprocess/managed_mapped_file.hpp>

#include </usr/local/include/boost/geometry.hpp>
#include </usr/local/include/boost/geometry/geometries/point.hpp>
#include </usr/local/include/boost/geometry/index/rtree.hpp>

namespace bi = boost::interprocess;
namespace bg = boost::geometry;
namespace bgm = bg::model;
namespace bgi = bg::index;

int main()
{
    typedef bgm::point<float, 2, bg::cs::cartesian> point_t;

    typedef std::pair<point_t, std::string> value_t;
    typedef bgi::linear<32, 8> params_t;
    typedef bgi::indexable<value_t> indexable_t;
    typedef bgi::equal_to<value_t> equal_to_t;
    typedef bi::allocator<value_t, bi::managed_mapped_file::segment_manager> allocator_t;
    typedef bgi::rtree<value_t, params_t, indexable_t, equal_to_t, allocator_t> rtree_t;

    {
        bi::managed_mapped_file file(bi::open_or_create, "data.bin", 1024*1024);
        allocator_t alloc(file.get_segment_manager());
        rtree_t * rtree_ptr = file.find_or_construct<rtree_t>("rtree")(params_t(), indexable_t(), equal_to_t(), alloc);

        std:: cout << "first size()" << std::endl;
        std::cout << rtree_ptr->size() << std::endl;

        std::string str = "hello";
        rtree_ptr->insert(std::make_pair(point_t(1.0, 1.0), str));
        rtree_ptr->insert(std::make_pair(point_t(2.0, 2.0), str));

        std:: cout << "second size()" << std::endl;
        std::cout << rtree_ptr->size() << std::endl;
    }

    {
        bi::managed_mapped_file file(bi::open_or_create, "data.bin", 1024*1024);
        allocator_t alloc(file.get_segment_manager());
        rtree_t * rtree_ptr = file.find_or_construct<rtree_t>("rtree")(params_t(), indexable_t(), equal_to_t(), alloc);

        std:: cout << "first size()" << std::endl;
        std::cout << rtree_ptr->size() << std::endl;

        std::string str = "world";
        rtree_ptr->insert(std::make_pair(point_t(3.0, 3.0), str));
        rtree_ptr->insert(std::make_pair(point_t(4.0, 4.0), str));

        std:: cout << "second size()" << std::endl;
        std::cout << rtree_ptr->size() << std::endl;
    }

    return 0;
}
