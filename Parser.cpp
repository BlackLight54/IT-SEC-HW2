//
// Created by black on 5/27/2023.
//

#include "Parser.h"

CaffBlock *Parser::parseCaffBlock(ifstream &file) {
    if (!file || !file.is_open()) { throw runtime_error("File not found"); }
    char type;
    file.read(&type, sizeof type);

    unsigned long int length;
    file.read((char *) &length, 8);

    int dataStart = file.tellg();
    CaffBlock *block = nullptr;
    if (type == 0x1) {
        auto header = parseCaffHeader(file, length);
        block = new CaffHeader(header);
    } else if (type == 0x2) {
        auto credits = parseCaffCredits(file, length);
        block = new CaffCredits(credits);
    } else if (type == 0x3) {
        auto anim = parseCaffAnimation(file, length);
        block = new CaffAnimation(anim);
    } else { throw runtime_error("Invalid CAFF block type"); }
    cout << *block << endl;


    int dataEnd = file.tellg();
    if (dataEnd - dataStart != length) { throw runtime_error("CAFF block length too long"); }


    return block;
}

CaffHeader Parser::parseCaffHeader(ifstream &file, unsigned long dataLength) {
    if (!file || !file.is_open()) {
        throw runtime_error("File not found");
    }

    string magic;
    unsigned long header_size;
    unsigned long num_anim;

    // Read magic
    for (int i = 0; i < 4; i++) {
        char c;
        file.read(&c, sizeof c);
        magic += c;
    }

    // Read header size
    file.read((char *) &header_size, 8);

    // Read num anim
    file.read((char *) &num_anim, 8);




    // return header
    return {dataLength, magic, header_size, num_anim};
}

CaffCredits Parser::parseCaffCredits(ifstream &file, unsigned long length) {
    if (!file || !file.is_open()) {
        throw runtime_error("File not found");
    }

    // declaration
    auto type = 0x2;
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned long creator_length;
    std::string creator;

    // read data
    file.read((char *) &year, 2);
    file.read((char *) &month, 1);
    file.read((char *) &day, 1);
    file.read((char *) &hour, 1);
    file.read((char *) &minute, 1);
    file.read((char *) &creator_length, 8);


    // read creator
    for (int i = 0; i < creator_length; i++) {
        char c;
        file.read(&c, sizeof c);
        creator += c;
    }

    // return credits
    return {
            length,
            year,
            month,
            day,
            hour,
            minute,
            creator_length,
            creator
    };
}

CaffAnimation Parser::parseCaffAnimation(ifstream &file, unsigned long length) {
    //check file
    if (!file || !file.is_open()) {
        throw runtime_error("File not found");
    }
    //read duration
    unsigned long duration;
    file.read((char *) &duration, 8);

    // read elements
    vector<Ciff> frames;
    long blockStart = file.tellg();
    while (file.tellg() - blockStart < length - 8) {
        auto ciff = parseCiff(file);
        frames.push_back(ciff);
    }


    // return animation
    return {
            length,
            duration,
            frames
    };
}

Ciff Parser::parseCiff(ifstream &file) {
    if (!file.is_open()) {
        throw runtime_error("File not found");
    }
    std::string magic;
    unsigned long long int header_size;
    unsigned long long int content_size;
    unsigned long long int width;
    unsigned long long int height;
    std::string caption;
    std::vector<std::string> tags;
    std::vector<Pixel> pixels;

    for (int i = 0; i < 4; i++) {
        char c;
        file.read(&c, sizeof c);
        magic += c;
    }
    file.read((char *) &header_size, 8);
    file.read((char *) &content_size, 8);
    file.read((char *) &width, 8);
    file.read((char *) &height, 8);

    int bytesRead = 4 + 8 + 8 + 8 + 8;

    // read caption
    char cc;
    while (cc != '\n') {
        file.read(&cc, 1);
        bytesRead++;
        caption += cc;
        if (bytesRead > header_size) { throw runtime_error("Invalid header size"); }
    }

    //read tags
    char c;
    do {
        string tag;
        do {
            file.read(&c, 1);
            bytesRead++;
            tag += c;
            if (c == '\n') { throw runtime_error("Invalid character in tags"); }
        } while (c != '\0');
        if (tag != "") { tags.push_back(tag); }
        if (bytesRead > header_size) { throw runtime_error("Invalid header size"); }
    } while (bytesRead < header_size);
    if (c != '\0') {
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

    return {
            magic,
            header_size,
            content_size,
            width,
            height,
            caption,
            tags,
            pixels
    };

}
