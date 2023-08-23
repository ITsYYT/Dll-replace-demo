#include <SC.h>

// string Module::readLine(const string &str)
// {
// }

Module::Module(const char *dll_path)
    : dll_path_m(dll_path)
{
    dll_handle_m = ::LoadLibraryA(dll_path);
    if (!dll_handle_m)
    {
        printf("Failed to get library, empty pointer: %s\n", dll_path);
    }
    printf("Success to get library: %s\n", dll_path);
}

Module::~Module()
{
    if (dll_handle_m)
    {
        ::FreeLibrary(dll_handle_m);
        printf("Success to free library: %s\n", dll_path_m);
    }
    printf("Released module: %s\n", dll_path_m);
}

const char *Module::get_dll_path() const
{
    return dll_path_m;
}

HMODULE Module::get_dll() const
{
    return dll_handle_m;
}
