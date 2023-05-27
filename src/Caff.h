//
// Created by black on 5/24/2023.
//

#ifndef PARSER_CAFF_H
#define PARSER_CAFF_H

#include "Ciff.h"

using namespace std;

class CaffBlock {
protected:
    char type_;
    unsigned long int length_;
public:
    virtual ~CaffBlock() = default;

    auto &type() const { return type_; }

    auto &length() const { return length_; }

    static CaffBlock &parseBlock(std::ifstream &file);

    friend ostream &operator<<(ostream &os, const CaffBlock &block) {
        os << "TYPE: " << to_string(block.type_) << endl;
        os << "DATA_LENGTH: " << block.length_ << endl;
        return os;
    }
};

class CaffHeader : public CaffBlock {
    std::string magic_;
    unsigned long int headerSize_;
    unsigned long int numAnim_;
public:
    CaffHeader(unsigned long dataLength,
               std::string magic,
               unsigned long int headerSize,
               unsigned long int numAnim) : magic_(std::move(magic)),
                                            headerSize_(headerSize),
                                            numAnim_(numAnim) {
        type_ = 0x1;
        length_ = dataLength;

        if (magic != "CAFF") { throw runtime_error("Invalid CAFF magic"); }
        if (dataLength <= 9) { throw runtime_error("CAFF block length too short"); }
        if (headerSize != dataLength) { throw runtime_error("Invalid CAFF header size"); }

    }

    //getters
    [[nodiscard]] auto magic() const -> const string & { return magic_; }

    [[nodiscard]] auto headerSize() const -> const unsigned long & { return headerSize_; }

    [[nodiscard]] auto numAnim() const -> const unsigned long & { return numAnim_; }

    static CaffHeader &parseData(ifstream &file, unsigned long int length);

    friend ostream &operator<<(ostream &os, const CaffHeader &header);


};

class CaffCredits : public CaffBlock {
    unsigned short year_;
    unsigned char month_;
    unsigned char day_;
    unsigned char hour_;
    unsigned char minute_;
    unsigned long creator_length_;
    std::string creator_;
public:
    CaffCredits(unsigned long dataLength,
                unsigned short year,
                unsigned char month,
                unsigned char day,
                unsigned char hour,
                unsigned char minute,
                unsigned long creator_length,
                std::string creator) : year_(year),
                                       month_(month),
                                       day_(day),
                                       hour_(hour),
                                       minute_(minute),
                                       creator_length_(creator_length),
                                       creator_(std::move(creator)) {
        type_ = 0x2;
        length_ = dataLength;

        //data validation
        if (month < 1 || month > 12) throw runtime_error("Invalid CAFF month");
        if (day < 1 || day > 31) throw runtime_error("Invalid CAFF day");
        if (hour < 0 || hour > 23) throw runtime_error("Invalid CAFF hour");
        if (minute < 0 || minute > 59) throw runtime_error("Invalid CAFF minute");
        if (creator_length > dataLength - 14) throw runtime_error("Invalid CAFF creator length");
    }

    auto &year() const { return year_; }

    auto &month() const { return month_; }

    auto &day() const { return day_; }

    auto &hour() const { return hour_; }

    auto &minute() const { return minute_; }

    auto &creator_length() const { return creator_length_; }

    auto &creator() const { return creator_; }


    static CaffCredits &parseData(ifstream &file, unsigned long int length);

    friend ostream &operator<<(ostream &os, const CaffCredits &credits);
};

class CaffAnimation : public CaffBlock {
    unsigned long int duration;
    vector<Ciff> ciffs;
public:
    CaffAnimation(unsigned long dataLength,
                  unsigned long duration,
                  vector<Ciff> ciffs) : duration(duration),
                                        ciffs(std::move(ciffs)) {
        type_ = 0x3;
        length_ = dataLength;
    }
    static CaffAnimation parseData(ifstream &file, unsigned long int length, unsigned long num_anim);

    // << operator
friend ostream &operator<<(ostream &os, const CaffAnimation &animation) {
        os << "-----ANIMATION-----" << endl;
        os << (CaffBlock &) animation;
        os << "DURATION: " << animation.duration << endl;
//        os << "CIFFS: " << endl;
//        for (auto &ciff : animation.ciffs) {
//            os << ciff;
//        }
        return os;
    }
};

class Caff {
public:
    std::vector<std::reference_wrapper<CaffBlock>> blocks;

    explicit Caff(ifstream &file) {
        for (int i = 0; i < 3; i++) {
            blocks.push_back(CaffBlock::parseBlock(file));
        }

    }
};


#endif //PARSER_CAFF_H
