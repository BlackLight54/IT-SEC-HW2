#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

#include "Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3 || (strcmp(argv[1], "-ciff") != 0 && strcmp(argv[1], "-caff") != 0)) {
        cout << "Usage: %s <-ciff|-caff> <[path-to-caff].ciff|[path-to-ciff].caff>\n" << argv[0] << endl;
        return -1;
    }

    bool caff = (strcmp(argv[1], "-caff") == 0);
    string relpath = argv[2];
    string path = std::filesystem::absolute(relpath);
    string jpegPath = path.substr(0, path.size() - 5) + ".jpeg";


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
        for (auto &block: caffFile.blocks) {

            cout << *block;

            if (block->type() == 0x3) {
                cout << "writing jpeg to: " << jpegPath << endl;
                auto animation = dynamic_cast<CaffAnimation &>(*block);
                if (animation.getCiffs().at(0).writeJpeg(jpegPath)) return 0;
                else return -1;
            }

        }
    }
    catch (exception &e) {
        file.close();
        cout << e.what() << endl;
        return -1;
    }


    file.close();
    return 0;
}