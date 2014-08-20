#include <string>
#include <cstdlib>
using namespace std;

int main()
{
    string cmd = "./test ";
    string argv = "\"this is the this\"";
    cmd = cmd + argv;
    system(cmd.c_str());

    return 0;
}
