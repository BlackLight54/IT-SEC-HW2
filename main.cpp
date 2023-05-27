#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

#include "Parser.h"

using namespace std;
int main(int argc, char *argv[]) {
    if (argc != 3 || (strcmp(argv[1], "-ciff") != 0 && strcmp(argv[1], "-caff") != 0))
    {
       cout << "Usage: %s <-ciff|-caff> <[path-to-caff].ciff|[path-to-ciff].caff>\n" << argv[0] << endl;
        return -1;
    }

    bool caff = (strcmp(argv[1], "-caff") == 0) ;
    string relpath = argv[2];
    string path = std::filesystem::absolute(relpath.substr(2, relpath.size()));
    string jpegPath = path.substr(0, path.size()-5) + ".jpeg";


    cout << "reading file: " << path << endl;
    ifstream file;
    file.open(path);
    if (!file || !file.is_open()) {
        cout << "File not found" << endl;
        return -1;
    }
    try {
        // parse blocks
        Caff caffFile(file);
        for (auto &block : caffFile.blocks) {
            cout << *block << endl;
        }
    }
    catch (exception &e) {
        cout << e.what() << endl;
        return -1;
    }
//    CaffBlock firstBlock = CaffBlock::parseBlock(file);
//    cout << dynamic_cast<CaffHeader&>(firstBlock);
//    auto header  = dynamic_cast<CaffHeader&>(firstBlock);
//    cout << header;
//    CaffBlock secondBlock = CaffBlock::parseBlock(file);
//    auto credits  = dynamic_cast<CaffCredits&>(secondBlock);
//    cout << credits;

//    Caff caffFile(file);
//    cout << dynamic_cast<CaffHeader&>(caffFile.blocks.at(0));

    file.close();
    return 0;
}