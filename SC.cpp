// #include <SC.h>
#include <t2sdk_interface.h>
// #include <dbg.h>
// #include <LoadDllBase.h>

#include <iostream>
#include <string>
using std::string;
#include <Windows.h>

// class Module : public LoadBase
class Module
{
public:
    // string readLine(const string &str) override;
    // __declspec(dllexport) Module(const char *);
    Module(const char *);
    ~Module();

public:
    const char *get_dll_path() const;
    HMODULE get_dll() const;

    template <typename T>
    T get_fun(const char *fun_name)
    {
        if (dll_handle_m)
        {
            return reinterpret_cast<T>(GetProcAddress(dll_handle_m, fun_name));
        }
        return nullptr;
    }

#if 0
    template <typename FuncType>
    struct FunctionWrapper
    {
        FuncType function_ptr;

        FunctionWrapper(FuncType ptr) : function_ptr(ptr) {}

        template <typename... Args>
        auto operator()(Args &&...args) -> decltype(function_ptr(std::forward<Args>(args)...))
        {
            return function_ptr(std::forward<Args>(args)...);
        }
    };

    template <typename FuncType>
    FunctionWrapper<FuncType> operator[](const char *function_name)
    {
        if (dll_handle_m != nullptr)
        {
            auto function_ptr = reinterpret_cast<FuncType>(::GetProcAddress(dll_handle_m, function_name));
            return FunctionWrapper<FuncType>(function_ptr);
        }
        return nullptr;
    }
#endif // 0

private:
    const char *dll_path_m;
    HMODULE dll_handle_m;
};

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

/**
 * T2SDK 函数重写
 */

// CConfigInterface *FUNCTION_CALL_MODE NewConfig()
// {
// }

CConnectionInterface *FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig)
{
    // dbg("This is NewConnection");
    printf("This is NewConnection");
    return nullptr;
}

int FUNCTION_CALL_MODE CConnectionInterface::Create(CCallbackInterface *lpCallback)
{
    // dbg("This is Create");
    printf("This is Create");
    return 0;
}

int FUNCTION_CALL_MODE CConnectionInterface::Connect(unsigned int uiTimeout)
{
    // dbg("This is Connect");
    printf("This is Connect");
    return 0;
}

/**
 * T2SDK 函数复用
 */
// auto myFunction = t2sdk.GetProcAddress<int(*)(int)>("MyFunction");
// auto MyFunction = myLibrary["MyFunction"];

// 初始化
Module t2sdk("t2sdk.dll");

// auto NewConfig = t2sdk["NewConfig"];

CConfigInterface *FUNCTION_CALL_MODE NewConfig()
{
    // auto NewConfig = t2sdk.get_fun<CConfigInterface *(*)()>("NewConfig");
    t2sdk.get_fun<CConfigInterface *(*)()>("NewConfig")();
    return nullptr;
}

int FUNCTION_CALL_MODE CConfigInterface::Load(const char *szFileName)
{
    t2sdk.get_fun<int (*)(const char *)>("Load")(szFileName);
    return 0;
}
