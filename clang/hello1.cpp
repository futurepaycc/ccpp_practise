#include <iostream>
#include <clang-c/Index.h>
using namespace std;

/*GCC: g++ -g -lclang -lstdc++ -o hello1 hello1.cpp */

/* 来源: https://shaharmike.com/cpp/libclang/ */

//对cout重写，之接收CXString参数
ostream& operator<<(ostream& stream,const CXString& str){
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

int main(int argc, char const *argv[]) {
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(index, "header.hpp", nullptr, 0, nullptr, 0, CXTranslationUnit_None);

    if(unit == nullptr){
        cerr<<"unable to parse translition unit"<<endl;
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor,[](CXCursor c,CXCursor parent, CXClientData client_data){
        // cout << "Cursor kind:"<< clang_getCursorKind(c) << endl;
        cout <<"Cursor: " << clang_getCursorSpelling(c) <<"\tkind: " << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "\n" << endl;
        return CXChildVisit_Recurse;
    },nullptr);

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
    return 0;
}
