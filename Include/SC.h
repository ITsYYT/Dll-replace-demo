#include "LoadDllBase.h"

#include <string>
using std::string;
#include <Windows.h>

#ifndef __SC_H__
#define __SC_H__

// class Module : public LoadBase
class Module
{
public:
    // string readLine(const string &str) override;
    __declspec(dllexport) Module(const char *);
    __declspec(dllexport) ~Module();

public:
    __declspec(dllexport) const char *get_dll_path() const;
    __declspec(dllexport) HMODULE get_dll() const;

    template <typename T>
    __declspec(dllexport) T get_fun(const char *fun_name)
    {
        if (dll_handle_m)
        {
            return reinterpret_cast<T>(GetProcAddress(dll_handle_m, fun_name));
        }
        return nullptr;
    }

private:
    const char *dll_path_m;
    HMODULE dll_handle_m;
};

// extern "C" __declspec(dllexport) void fun()
// {
//     printf("This is fun function in SC.dll\n");
// }

// extern "C" __declspec(dllexport) void duplicate_name_test()
// {
//     printf("This is duplicate_name_test function in SC.dll\n");
// }

#endif // __SC_H__
