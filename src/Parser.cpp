//
// Created by black on 5/27/2023.
//

#include "Parser.h"

CaffBlock* Parser::parseCaffBlock(ifstream &file) {
    if (!file || !file.is_open()) { throw runtime_error("File not found"); }
    char type;
    file.read(&type, sizeof type);

    unsigned long int length;
    file.read((char *) &length, 8);

    int dataStart = file.tellg();
    CaffBlock* block = nullptr;
    if (type == 0x1) {
        auto header = parseCaffHeader(file, length);
        cout << header << endl;

        int dataEnd = file.tellg();
        if (dataEnd - dataStart != length) { throw runtime_error("CAFF block length too long"); }

        return &header;
    } else if (type == 0x2) {
        auto credits = parseCaffCredits(file, length);
        cout << credits << endl;

        int dataEnd = file.tellg();
        if (dataEnd - dataStart != length) { throw runtime_error("CAFF block length too long"); }

        return &credits;
    } else if (type == 0x3) {
        auto anim = parseCaffAnimation(file, length);
        cout << anim << endl;

        int dataEnd = file.tellg();
        if (dataEnd - dataStart != length) { throw runtime_error("CAFF block length too long"); }

        return &anim;
    } else {
        throw runtime_error("Invalid CAFF block type");
    }


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
        if (i > length - 14) throw runtime_error("Invalid CAFF creator length");
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
    const auto start = file.tellg();
    while (file.tellg() - start < length) {
        frames.push_back(parseCiff(file));
    }

    // return animation
    return {
            length,
            duration,
            frames
    };

}

Ciff Parser::parseCiff(ifstream &file) {


}
