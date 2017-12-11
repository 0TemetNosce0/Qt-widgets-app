#include <ShlObj.h>
#include <string>
#include <iostream>

#pragma comment(lib,"Shell32.lib")

std::string getLogDir()
{
    char szBuffer[256] = { 0 };
    SHGetSpecialFolderPathA(0, szBuffer, CSIDL_COMMON_DOCUMENTS, FALSE);
    return szBuffer;
}

int main()
{
    std::string str = getLogDir();

    std::cout << str << std::endl;

    system("pause");

    return 0;
}

