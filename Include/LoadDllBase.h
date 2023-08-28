#include <string>
using std::string;

#ifndef __LOAD_DLL_BASE_H__
#define __LOAD_DLL_BASE_H__

class LoadBase
{
public:
    virtual string readLine(const string &) = 0;

    virtual ~LoadBase() = default;
};

#endif // __LOAD_DLL_BASE_H__
