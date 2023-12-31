﻿// #include <SC.h>
// #include <t2sdk_interface.h>
#include <sc_interface.h>
#include <LogFunc.h>
// #include <dbg.h>

#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <stdarg.h>

// template <typename... Args>
// static void print(const char *func_name, int line, const char *content, Args... args)
// {
//     printf("[%s: %d] %s\n", func_name, line, content, args...);
// }

#if 1 // ShowPacket function
// Display the fields within the package
void ShowPacket(IF2UnPacker *lpUnPacker)
{
    LOG("--------------------START--------------------");
    int i = 0, t = 0, j = 0, k = 0;

    for (i = 0; i < lpUnPacker->GetDatasetCount(); ++i)
    {
        // LOG("Debug in for(i)");
        // Set current result set
        lpUnPacker->SetCurrentDatasetByIndex(i);

        // Print Fields
        for (t = 0; t < lpUnPacker->GetColCount(); ++t)
        {
            // LOG("Debug in for(t)");
            printf("%20s", lpUnPacker->GetColName(t));
        }

        putchar('\n');

        // Print all records
        for (j = 0; j < (int)lpUnPacker->GetRowCount(); ++j)
        {
            // LOG("Debug in for(j)");
            // Print each record
            for (k = 0; k < lpUnPacker->GetColCount(); ++k)
            {
                // LOG("Debug in for(k)");
                switch (lpUnPacker->GetColType(k))
                {
                case 'I':
                    printf("%20d", lpUnPacker->GetIntByIndex(k));
                    break;

                case 'C':
                    printf("%20c", lpUnPacker->GetCharByIndex(k));
                    break;

                case 'S':
                    printf("%20s", lpUnPacker->GetStrByIndex(k));
                    break;

                case 'F':
                    printf("%20f", lpUnPacker->GetDoubleByIndex(k));
                    break;

                case 'R':
                {
                    int nLength = 0;
                    void *lpData = lpUnPacker->GetRawByIndex(k, &nLength);

                    // Process binary data
                    break;
                }

                default:
                    // Unknown data type
                    printf("Unknown data type");
                    break;
                }
            }

            putchar('\n');

            lpUnPacker->Next();
        }

        putchar('\n');
    }

    LOG("--------------------END--------------------");
}
#endif // Comment

#if 0  // Test Module class
void test0()
{
    Module HSDll("HS.dll");
    auto path = HSDll.get_dll_path();
    printf("main:%d, path = %s\n", __LINE__, path);

    typedef void (*FunPtr)();
    auto HSfun = HSDll.get_fun<FunPtr>("fun");
    if (HSfun)
    {
        HSfun();
    }
    else
    {
        printf("main:%d, empty pointer\n", __LINE__);
    }

    printf("-------------------------------------\n");
    fun();
    duplicate_name_test();

    // getchar();
}
#endif // Comment

// Test initial connection
void test_t2sdk()
{
    LOG("--------------------START--------------------");
#if 1
    // Create a CConfig object to obtain attributes
    // such as "IP address" and "security mode" in the configuration file
    CConfigInterface *lpConfig = NewConfig();
    // Corresponding to the Release()
    lpConfig->AddRef();
    lpConfig->Load("./config/Hsconfig.ini");
#endif // Comment

    // Create a connection instance
    CConnectionInterface *lpConnection = NewConnection(lpConfig);
    // printf("Connecting to: %s\n", lpConfig->GetString("t2sdk", "servers", "DEFAULT_SERVERS"));
    // lpConnection->AddRef();

    LOG("Debug");

    // Exception return value
    int ret = 0;

    if (0 == (ret = lpConnection->Create(NULL)))
    {
        LOG("Debug in if");

        // Start connection
        if (ret = lpConnection->Connect(1000))
        {
            // printf("%s\n", lpConnection->GetErrorMsg(ret));
            LOG("Connect return value");
        }
        else
        {
            LOG("Connect return 0");
        }
    }
    else
    {
        LOG("Create return value");
    }

    LOG("--------------------END--------------------");
}

// Test packer and unpacker related interfaces
void test_packer()
{
    LOG("--------------------START--------------------");
    // std::map<std::string, std::string> params{
    //     {"op_branch_no", "100"}, {"op_entrust_way", "1"}, {"op_station", " "}};
    std::map<std::string, std::string> params{{"op_branch_no", "0"},
                                              {"op_entrust_way", "5"},
                                              {"op_station", " "},
                                              {"branch_no", "0"},
                                              {"password", "600000"},
                                              {"password_type", "2"},
                                              {"input_content", "6"},
                                              {"account_content", "3519012"},
                                              {"content_type", "0"},
                                              {"asset_prop", "0"}};

    // dbg(params);

    // Get the packager
    IF2Packer *pack = NewPacker(2);
    if (!pack)
    {
        LOG("Error: Empty pointer pack");
        return;
    }
    pack->AddRef();

    // Create a business package
    LOG("Begin pack");
    pack->BeginPack();

    /**
     * WARNING: AddStr ONLY CAN USE AFTER AddField FINESHED
     */
    for (const auto &kv : params)
    {
        LOG("Current add field: %s", kv.first.c_str());
        // pack->AddField(kv.first.c_str(), 'S');
        pack->AddField(kv.first.c_str());
    }
    for (const auto &kv : params)
    {
        LOG("Current add str: %s", kv.second.c_str());
        pack->AddStr(kv.second.c_str());
    }

    pack->EndPack();
    LOG("End pack");
    LOG("Pack version = %d", GetPackVersion(pack->GetPackBuf()));
    LOG("Pack length = %d", pack->GetPackLen());

    // void *Pointer = NULL;
    IF2UnPacker *un_pack = pack->UnPack();
    LOG("Turn to unpacker");

    LOG("Begin showpack");
    ShowPacket(un_pack);
    LOG("End showpack");

    LOG("Packbuf size = %d", pack->GetPackBufSize());
    pack->FreeMem(pack->GetPackBuf());
    LOG("Package memory has been freed");
    pack->Release();
    LOG("Package has been released");

    LOG("--------------------END--------------------");
}

// Test connection
void test_connection()
{
    LOG("--------------------START--------------------");

    CConfigInterface *lpConfig = NewConfig();
    lpConfig->AddRef();
    if (!lpConfig)
    {
        LOG("\033[0;31mEmpty pointer lpConfig\033[0m");
        lpConfig->Release();
        return;
    }
    else
    {
        LOG("Config has been created");
    }

    lpConfig->Load("Hsconfig.ini");
    LOG("Config has been loaded");

    CConnectionInterface *lpConnection = NewConnection(lpConfig);
    lpConnection->AddRef();

#if 0
    if (!lpConnection)
    {
        LOG("\033[0;31mEmpty pointer loConnection\033[0m");
        lpConnection->Release();
        return;
    }
    else
    {
        /**
         * Q: What does GetString do?
         *    The current test results are simply returning the third parameter
         *    : "DEFAULT_SERVERS"
         *    When third parameter is empty, return ""
         *
         * virtual const char * FUNCTION_CALL_MODE
         * GetString(
         *  const char *szSection, const char *szEntry, const char *szDefault
         * ) = 0;
         *
         *      const char *szSection 节名
         *      const char *szEntry 变量名
         *      const char *szDefault 默认值
         */
        LOG("\033[0;32mConnecting to: %s\033[0m", lpConfig->GetString("t2sdk", "servers", "DEFAULT_SERVERS"));
    }
#endif // Comment

    int ret = 0;
    LOG("Error return value = %d", ret);

#if 0
    if (0 == (ret = lpConnection->Create(NULL)))
    {
        LOG("Created");
        // Start connect
        if (ret = lpConnection->Connect(1000))
        {
            LOG("\033[0;31mError message: %s\033[0m", lpConnection->GetErrorMsg(ret));

            ret = lpConnection->GetConnectError();
            LOG("\033[0;31mGetConnectError message: %s\033[0m", lpConnection->GetErrorMsg(ret));

            lpConfig->Release();
            LOG("Released: lpConfig");
            lpConnection->Release();
            LOG("Released: lpConnection");
        }
        else
        {
            LOG("Connected");
            while (true)
            {
                LOG("Sleeping");
                Sleep(3000);
            }
        }
    }
    else
    {
        LOG("\033[0;31mError message: %s\033[0m", lpConnection->GetErrorMsg(ret));
        lpConfig->Release();
        LOG("Released: lpConfig");
        lpConnection->Release();
        LOG("Released: lpConnection");
        // return;
    }
#else
    if (0 != (ret = lpConnection->Create(NULL)))
    {
        LOG("\033[0;31mError message: %s\033[0m", lpConnection->GetErrorMsg(ret));
        // lpConfig->Release();
        // LOG("Released: lpConfig");
        // lpConnection->Release();
        // LOG("Released: lpConnection");
        // return;

        goto end;
    }
    LOG("Created");

    if (0 != (ret = lpConnection->Connect(1000)))
    {
        LOG("\033[0;31mError message: %s\033[0m", lpConnection->GetErrorMsg(ret));

        ret = lpConnection->GetConnectError();
        LOG("\033[0;31mGetConnectError message: %s\033[0m", lpConnection->GetErrorMsg(ret));

        // lpConfig->Release();
        // LOG("Released: lpConfig");
        // lpConnection->Release();
        // LOG("Released: lpConnection");
        // return;

        goto end;
    }
    LOG("Connected");

    while (true)
    {

        LOG("Sleeping");
        Sleep(3000);
    }

#endif // Comment to debug

end:
    lpConfig->Release();
    LOG("Released: lpConfig");
    lpConnection->Release();
    LOG("Released: lpConnection");
    // ret = lpConnection->Close();
    // LOG("\033[0;31mError message: %s\033[0m", lpConnection->GetErrorMsg(ret));

    LOG("--------------------END--------------------");
}

int main(int argc, char const *argv[])
{
    LOG("--------------------START--------------------");

    // test0();
    // test_t2sdk();
    // test_packer();
    test_connection();

    // debug

    LOG("--------------------END--------------------");
    return 0;
}
