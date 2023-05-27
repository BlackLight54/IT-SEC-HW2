//
// Created by black on 5/24/2023.
//

#include "Caff.h"

CaffBlock &CaffBlock::parseBlock(std::ifstream &file) {



}

CaffHeader &CaffHeader::parseData(ifstream &file, unsigned long int dataLength) {

}

CaffCredits &CaffCredits::parseData(ifstream &file, unsigned long length) {

}


ostream &operator<<(ostream &os, const CaffHeader &header) {
    os << "-----HEADER-----" << endl;
    os << (CaffBlock &) header;
    os << "MAGIC: " << header.magic() << endl;
    os << "HEADER SIZE: " << header.headerSize() << endl;
    os << "NUM ANIM: " << header.numAnim() << endl;

    return os;
}

ostream &operator<<(ostream &os, const CaffCredits &credits) {
    os << "-----CREDITS-----" << endl;
    os << (CaffBlock &) credits;

    os << "YEAR: " << to_string(credits.year()) << endl;
    os << "MONTH: " << to_string(credits.month()) << endl;
    os << "DAY: " << to_string(credits.day()) << endl;
    os << "HOUR: " << to_string(credits.hour()) << endl;
    os << "MINUTE: " << to_string(credits.month()) << endl;
    os << "CREATOR_L:" << to_string(credits.creator_length()) << endl;
    os << "CREATOR: " << credits.creator() << endl;

    return os;
}

CaffAnimation CaffAnimation::parseData(ifstream &file, unsigned long length, unsigned long num_anim) {

}
