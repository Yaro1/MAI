#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
using std::cin;
using std::cout;
using std::map;
using std::string;

#include "TSTree.h"

int main(int argc, char* argv[]){
#ifdef TEST
    std::string str;
    std::cin >> str;

    TSTree tree(str + "$");
#else
    std::string str1, str2;
    std::cin >> str1 >> str2;
    str1 += "#";
    str2+= "$";
    str1 += str2;
    TSTree tree(str1);
#endif

    return 0;
}