//
// Created by black on 5/24/2023.
//

#include "Ciff.h"



using namespace std;

Ciff::Ciff(const std::string &path) {

    // open file in path as binary
    ifstream file(path, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("File not found");
    }

    file.read(&magic[0], 4);
    if (strcmp(magic.c_str(), "CIFF") != 0) {
        throw runtime_error("Invalid magic");
    }
    file.read((char *) &header_size, 8);
    file.read((char *) &content_size, 8);
    file.read((char *) &width, 8);
    file.read((char *) &height, 8);

    // validate content size with height and width
    if (content_size != width * height * 3) {
        throw runtime_error("Invalid content size");
    }


    int header_size_check = 36;
    // read caption
    char c;
    do {
        file.read(&c, 1);
        caption += c;
        header_size_check++;
        if (header_size_check > header_size) {
            throw runtime_error("Invalid header size");
        }
    } while (c != '\n');

    // read tags
    do {
        string tag;
        do {
            file.read(&c, 1);
            tag += c;
            header_size_check++;
            if (header_size_check > header_size) {
                throw runtime_error("Invalid header size");
            }
            if (c == '\n'){
                throw runtime_error("Invalid character in tags");
            }
        } while (c != '\0');
        if (tag != "\0") {
            tags.push_back(tag);
        }
    } while (header_size_check < header_size);
    if (c == '\0') {
        throw runtime_error("Invalid header size");
    }

    int content_size_check = 0;
    // read pixels
    for (int i = 0; i < width * height; i++) {
        Pixel pixel;
        file.read((char *) &pixel.r, 1);
        file.read((char *) &pixel.g, 1);
        file.read((char *) &pixel.b, 1);
        content_size_check += 3;
        if (content_size_check > content_size) {
            throw runtime_error("Invalid content size");
        }
        pixels.push_back(pixel);
    }

    // validate pixel count



}