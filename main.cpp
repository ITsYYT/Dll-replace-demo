// #include <SC.h>
#include <t2sdk_interface.h>

#include <map>
#include <string>

#if 0
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
#endif // ע��

void test_t2sdk()
{
    printf("-------------test t2sdk-----------------");
    // ����һ�� CConfig ���󣬻�ȡ�����ļ��е� IP ��ַ����ȫģʽ������
    CConfigInterface *lpConfig = NewConfig();
    // ��Ӧ Release()
    lpConfig->AddRef();
    lpConfig->Load("./config/Hsconfig.ini");

    // ����һ������ʵ��
    CConnectionInterface *lpConnection = NewConnection(lpConfig);
    // printf("Connecting to: %s\n", lpConfig->GetString("t2sdk", "servers", "DEFAULT_SERVERS"));
    // lpConnection->AddRef();

    // �쳣����ֵ
    int ret = 0;

    if (0 == (ret = lpConnection->Create(NULL)))
    {
        if (ret = lpConnection->Connect(1000))
        {
            // printf("%s\n", lpConnection->GetErrorMsg(ret));
            printf("[main: %d] Connect return value", __LINE__);
        }
        else
        {
            printf("[main: %d] Connect return 0", __LINE__);
        }
    }
}

void test_packer()
{
    printf("-------------test packer-----------------");
    std::map<std::string, std::string> params{
        {"op_branch_no", "100"}, {"op_entrust_way", "1"}, {"op_station", ""}};

    // ��ȡ�����
    IF2Packer *pack = NewPacker(2);
    pack->AddRef();

    // ����һ��ҵ���
    pack->BeginPack();
    for (const auto &kv : params)
    {
        pack->AddField(kv.first.c_str());
        pack->AddStr(kv.second.c_str());
    }
    pack->EndPack();

    void *Pointer = NULL;
}

int main(int argc, char const *argv[])
{
    // test0();
    test_t2sdk();
    test_packer();

    return 0;
}
