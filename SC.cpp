// #include <SC.h>
#include <t2sdk_interface.h>
// #include <dbg.h>
// #include <LoadDllBase.h>

#include <iostream>
#include <string>
using std::string;
#include <Windows.h>
#include <direct.h>

#define DLL_EXPORT extern "C" __declspec(dllexport)
// using DLL_EXPORT = extern "C" __declspec(dllexport);

// Log function
#ifndef __LOG_FUNCTION__
#define __LOG_FUNCTION__

#define LOG(...) Log(__FUNCTION__, __LINE__, __VA_ARGS__)

void Log(const char *functionName, int lineNumber, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    printf("[%s: %d] ", functionName, lineNumber);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

#endif // __LOG_FUNCTION__

// class Module : public LoadBase
class Module
{
public:
    // string readLine(const string &str) override;
    //  Module(const char *);
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
#endif // Comment

private:
    const char *dll_path_m;
    HMODULE dll_handle_m;
};

// string Module::readLine(const string &str)
// {
// }

Module::Module(const char *dll_name)
    : dll_path_m(dll_name)
{

#if 0
    LOG("Dll name: %s", dll_name);

    char dll_absolute_path[250];
    char curr_path[250];
    sprintf(dll_absolute_path, _getcwd(curr_path, 250), dll_path);
    LOG("Current path = %s", curr_path);

    dll_path_m = dll_absolute_path;
#endif // 0

    // dll_handle_m = ::LoadLibraryA("C:\\Users\\yty\\testhssdk.dll");
    dll_handle_m = ::LoadLibraryA(dll_name);
    if (!dll_handle_m)
    {
        LOG("Failed to get library, dll path = %s", dll_path_m);

        return;
    }
    LOG("Success to get library: %s", dll_path_m);
}

Module::~Module()
{
    if (dll_handle_m)
    {
        ::FreeLibrary(dll_handle_m);
        LOG("Success to free library: %s", dll_path_m);
    }
    LOG("Released module: %s", dll_path_m);
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
 * T2SDK functions that need to be rewritten
 */

// CConfigInterface *FUNCTION_CALL_MODE NewConfig()
// {
// }

CConnectionInterface *FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig)
{
    LOG("In");
    return nullptr;
}

int FUNCTION_CALL_MODE CConnectionInterface::Create(CCallbackInterface *lpCallback)
{
    LOG("In");
    return 0;
}

int FUNCTION_CALL_MODE CConnectionInterface::Connect(unsigned int uiTimeout)
{
    LOG("In");
    return 0;
}

/**
 * T2SDK functions that can be reused
 */
// auto myFunction = t2sdk.GetProcAddress<int(*)(int)>("MyFunction");
// auto MyFunction = myLibrary["MyFunction"];

// Initialize
Module t2sdk("t2sdk.dll");

// auto NewConfig = t2sdk["NewConfig"];
CConfigInterface *FUNCTION_CALL_MODE NewConfig()
{
    // auto NewConfig = t2sdk.get_fun<CConfigInterface *(*)()>("NewConfig");
    LOG("In");
    return t2sdk.get_fun<CConfigInterface *(FUNCTION_CALL_MODE *)()>("NewConfig")();
}

int FUNCTION_CALL_MODE CConfigInterface::Load(const char *szFileName)
{
    LOG("In");
    return t2sdk.get_fun<int(FUNCTION_CALL_MODE *)(const char *)>("Load")(szFileName);
}

IF2Packer *FUNCTION_CALL_MODE NewPacker(int iVersion)
{
    LOG("In");
    return t2sdk.get_fun<IF2Packer *(FUNCTION_CALL_MODE *)(int)>("NewPacker")(iVersion);
}

void FUNCTION_CALL_MODE BeginPack(void)
{
    LOG("In");
    return t2sdk.get_fun<void(FUNCTION_CALL_MODE *)(void)>("BeginPack")();
}

int FUNCTION_CALL_MODE AddField(const char *szFieldName, char cFieldType = 'S', int iFieldWidth = 255, int iFieldScale = 4)
{
    LOG("In");
    return t2sdk.get_fun<int(FUNCTION_CALL_MODE *)(const char *, char, int, int)>("AddField")(szFieldName, cFieldType, iFieldWidth, iFieldScale);
}

int FUNCTION_CALL_MODE AddStr(const char *szValue)
{
    LOG("In");
    return t2sdk.get_fun<int(FUNCTION_CALL_MODE *)(const char *)>("AddStr")(szValue);
}

void FUNCTION_CALL_MODE EndPack()
{
    LOG("In");
    return t2sdk.get_fun<void(FUNCTION_CALL_MODE *)()>("EndPack")();
}
