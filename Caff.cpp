//
// Created by black on 5/24/2023.
//

#include "Caff.h"
#include "Parser.h"

CaffBlock * CaffBlock::parseBlock(std::ifstream &file) {
    return Parser::parseCaffBlock(file);
}

CaffHeader CaffHeader::parseData(ifstream &file, unsigned long int dataLength) {
    return Parser::parseCaffHeader(file, dataLength);
}

CaffCredits CaffCredits::parseData(ifstream &file, unsigned long length) {
    return Parser::parseCaffCredits(file, length);
}

CaffAnimation CaffAnimation::parseData(ifstream &file, unsigned long length, unsigned long num_anim) {
    return Parser::parseCaffAnimation(file, length); //TODO: Enfornce num_anim constraint?
}

void CaffBlock::print(ostream &os) const {
    os << "TYPE: " << to_string(type_) << endl;
    os << "DATA_LENGTH: " << length_ << endl;
}

void CaffHeader::print(ostream &os) const {
    os << "-----HEADER-----" << endl;
    CaffBlock::print(os);
    os << "MAGIC: \"" << magic() << "\"" << endl;
    os << "HEADER SIZE: " << headerSize() << endl;
    os << "NUM ANIM: " << numAnim() << endl;
}

void CaffCredits::print(ostream &os) const {
    os << "-----CREDITS-----" << endl;
    CaffBlock::print(os);
    os << "YEAR: " << to_string(year()) << endl;
    os << "MONTH: " << to_string(month()) << endl;
    os << "DAY: " << to_string(day()) << endl;
    os << "HOUR: " << to_string(hour()) << endl;
    os << "MINUTE: " << to_string(month()) << endl;
    os << "CREATOR_L:" << to_string(creator_length()) << endl;
    os << "CREATOR: " << creator() << endl;
}

void CaffAnimation::print(ostream &os) const {
    os << "-----ANIMATION-----" << endl;
    CaffBlock::print(os);
    os << "DURATION: " << duration << endl;
        os << "CIFFS: " << endl;
        for (auto &ciff : ciffs) {
            os << ciff;
        }
}


