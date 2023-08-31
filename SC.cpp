// #include <SC.h>
// #include <t2sdk_interface.h>
#include <sc_interface.h>
#include <LogFunc.h>
// #include <dbg.h>
// #include <LoadDllBase.h>

#include <iostream>
#include <string>
using std::string;
#include <Windows.h>
#include <direct.h>

#define DLL_EXPORT extern "C" __declspec(dllexport)
// using DLL_EXPORT = extern "C" __declspec(dllexport);

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

#if 0  // Test dll path
    LOG("Dll name: %s", dll_name);

    char dll_absolute_path[250];
    char curr_path[250];
    sprintf(dll_absolute_path, _getcwd(curr_path, 250), dll_path);
    LOG("Current path = %s", curr_path);

    dll_path_m = dll_absolute_path;
#endif // Comment

    // dll_handle_m = ::LoadLibraryA("C:\\Users\\yty\\testhssdk.dll");
    dll_handle_m = ::LoadLibraryA(dll_name);
    if (!dll_handle_m)
    {
        LOG("Failed to get library, dll path = %s", dll_path_m);

        char curr_path[250];
        LOG("Current path: %s", _getcwd(curr_path, 250));
        return;
    }
    LOG("Success to get library: %s", dll_path_m);
    char curr_path[250];
    LOG("Current path: %s", _getcwd(curr_path, 250));
    // Sleep(1000);
}

Module::~Module()
{
    LOG("In");
    // Sleep(3000);
    if (dll_handle_m)
    {
        LOG("In");
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

// Initialize dll library
Module t2sdk("t2sdk.dll");

/**
 * T2SDK functions that have to be rewritten
 */

CConfigInterface *FUNCTION_CALL_MODE NewConfig()
{
    LOG("In");
#if 1
    return t2sdk.get_fun<CConfigInterface *(FUNCTION_CALL_MODE *)()>("NewConfig")();
#else
    return nullptr;
#endif // Comment to debug
}

CConnectionInterface *FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig)
{
    LOG("In");
#if 0
    return t2sdk.get_fun<CConnectionInterface *(FUNCTION_CALL_MODE *)(CConfigInterface *)>("NewConnection")(lpConfig);
#else
    // return nullptr;
    SCConnectionInterface *p = new SCConnectionInterface();
    return p;
#endif // Comment to debug
}

#pragma region // Connection
unsigned long FUNCTION_CALL_MODE SCConnectionInterface::QueryInterface(const char *iid, IKnown **ppv)
{
    LOG("In");
    return 1;
}

unsigned long FUNCTION_CALL_MODE SCConnectionInterface::AddRef()
{
    LOG("In");
    return 1;
}

unsigned long FUNCTION_CALL_MODE SCConnectionInterface::Release()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE SCConnectionInterface::Create(CCallbackInterface *lpCallback)
{
    LOG("In");
    // lpCallback = nullptr;
    return 1;
}

int FUNCTION_CALL_MODE SCConnectionInterface::Connect(unsigned int uiTimeout)
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE SCConnectionInterface::Close()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved1()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved2()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved3()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved4()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved5()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved6()
{
    LOG("In");
    return 1;
}

const char *FUNCTION_CALL_MODE GetServerAddress(int *lpPort)
{
    LOG("In");
    return nullptr;
}

int FUNCTION_CALL_MODE GetStatus()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE GetServerLoad()
{
    LOG("In");
    return 1;
}

const char *FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode)
{
    LOG("In");
    return NULL;
}

int FUNCTION_CALL_MODE GetConnectError()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1)
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0)
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE SendBizEx(int iFunID, IF2Packer *lpPacker, char *svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1, int branchNo = 0, LPREQ_DATA lpRequest = NULL)
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE RecvBizEx(int hSend, void **lppUnpackerOrStr, LPRET_DATA *lpRetData, unsigned uiTimeout = 1000, unsigned uiFlag = 0)
{
    LOG("In");
    return 1;
}
int FUNCTION_CALL_MODE CreateEx(CCallbackInterface *lpCallback)
{
    LOG("In");
    return 1;
}

const char *FUNCTION_CALL_MODE GetRealAddress()
{
    LOG("In");
    return nullptr;
}

int FUNCTION_CALL_MODE Reserved8()
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE Reserved9()
{
    LOG("In");
    return 1;
}

const char *FUNCTION_CALL_MODE GetSelfAddress()
{
    LOG("In");
    return nullptr;
}

const char *FUNCTION_CALL_MODE GetSelfMac()
{
    LOG("In");
    return nullptr;
}

CSubscribeInterface *FUNCTION_CALL_MODE NewSubscriber(CSubCallbackInterface *lpCallback, char *SubScribeName, int iTimeOut,
                                                      int iInitRecvQLen = INIT_RECVQ_LEN, int iStepRecvQLen = STEP_RECVQ_LEN)
{
    LOG("In");
    return nullptr;
}

CPublishInterface *FUNCTION_CALL_MODE NewPublisher(char *PublishName, int msgCount, int iTimeOut, bool bResetNo = false)
{
    LOG("In");
    return nullptr;
}

IF2UnPacker *FUNCTION_CALL_MODE GetTopic(bool byForce, int iTimeOut)
{
    LOG("In");
    return nullptr;
}

const char *FUNCTION_CALL_MODE GetMCLastError()
{
    LOG("In");
    return nullptr;
}

int FUNCTION_CALL_MODE Create2BizMsg(CCallbackInterface *lpCallback)
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE SendBizMsg(IBizMessage *lpMsg, int nAsy = 0)
{
    LOG("In");
    return 1;
}

int FUNCTION_CALL_MODE RecvBizMsg(int hSend, IBizMessage **lpMsg, unsigned uiTimeout = 1000, unsigned uiFlag = 0)
{
    LOG("In");
    return 1;
}

CFileUpdateInterface *FUNCTION_CALL_MODE NewFileUpdate(const char *szTopicName, CFileUpdateCallbackInterface *lpCallBack, const char *szScanDir, const char *szUpdateDir, unsigned int uiTimeOut = 5000, const char *szDirFilter = NULL)
{
    LOG("In");
    return nullptr;
}

const char *FUNCTION_CALL_MODE GetFileUpdateLastError()
{
    LOG("In");
    return nullptr;
}

const char *FUNCTION_CALL_MODE GetLastAnsError(bool bAsyError = 0)
{
    LOG("In");
    return nullptr;
}

#pragma endregion // Connection

/**
 * T2SDK functions that can be reused
 */
// auto myFunction = t2sdk.GetProcAddress<int(*)(int)>("MyFunction");
// auto MyFunction = myLibrary["MyFunction"];

// auto NewConfig = t2sdk["NewConfig"];

IF2Packer *FUNCTION_CALL_MODE NewPacker(int iVersion)
{
    LOG("In");
    return t2sdk.get_fun<IF2Packer *(FUNCTION_CALL_MODE *)(int)>("NewPacker")(iVersion);
}

int FUNCTION_CALL_MODE GetPackVersion(const void *lpBuffer)
{
    LOG("In");
    return t2sdk.get_fun<int(FUNCTION_CALL_MODE *)(const void *)>("GetPackVersion")(lpBuffer);
}

#if 0  // Useless
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
#endif // Comment