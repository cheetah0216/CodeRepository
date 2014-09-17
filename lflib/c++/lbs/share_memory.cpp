#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

#include <boost/foreach.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <vector>
#include <string>
#include <cstdlib> //std::system

using namespace std;

//For parent process argc == 1, for child process argc > 1
int main(int argc, char *argv[])
{
    using namespace boost::interprocess;
    namespace bg = boost::geometry;
    namespace bgm = bg::model;
    namespace bgi = bg::index;

    typedef bgm::point<float, 2, bg::cs::cartesian> P;
    typedef bgm::box<P> B;
    typedef std::pair<P, std::string> V;

    typedef bgi::linear<32, 8> Par;
    typedef bgi::indexable<V> I;
    typedef bgi::equal_to<V> E;
    typedef allocator<V, managed_shared_memory::segment_manager> Alloc;
    typedef bgi::rtree<V, Par, I, E, Alloc> Rtree;

    //Parent process
    if ( argc == 1 )
    {
        struct shm_remove
        {
            shm_remove() { shared_memory_object::remove("MySharedMemory"); }
            ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
        } remover;

        managed_shared_memory segment(create_only, "MySharedMemory", 65536);

        std::cout << "Parent: Constructing container\n";

        Rtree * tree = segment.construct<Rtree>("Rtree")(Par(), I(), E(), Alloc(segment.get_segment_manager()));

        std::cout << "Parent: Filling container with 100 boxes\n";

        string str = "hello";
        for ( float i = 0 ; i < 100 ; i += 1 )
            tree->insert(make_pair(P(i, i), str));

        std::cout << "Parent: Tree content\n";
        std::cout << "Parent: Running child process\n";

        std::string s(argv[0]); s += " child ";
        if ( 0 != std::system(s.c_str()) )
            return 1;

        if ( segment.find<Rtree>("Rtree").first )
            return 1;

        std::cout << "Parent: Container was properly destroyed by the child process\n";
   }
   //Child process
   else
   {
      managed_shared_memory segment(open_only, "MySharedMemory");

      std::cout << "Child: Searching of the container in shared memory\n";

      Rtree * tree = segment.find<Rtree>("Rtree").first;

      std::cout << "Child: Querying for objects intersecting box = [(45, 45)(55, 55)]\n";

      std::vector<B> result;
      unsigned k = tree->query(bgi::intersects(B(P(45, 45), P(55, 55))), std::back_inserter(result));

      std::cout << "Child: Destroying container\n";

      segment.destroy<Rtree>("Rtree");
   }

   return 0;
};
