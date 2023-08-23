#include <HS.h>

// #pragma comment(linker, "/EXPORT:fun=b.fun")

extern "C" __declspec(dllexport) void fun()
{
    printf("This is fun function in HS.dll\n");
}

extern "C" __declspec(dllexport) void duplicate_name_test()
{
    printf("This is duplicate_name_test function in HS.dll\n");
}
