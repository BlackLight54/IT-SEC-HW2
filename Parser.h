//
// Created by black on 5/27/2023.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>

#include "Caff.h"

using namespace std;
namespace Parser {

    CaffBlock *parseCaffBlock(ifstream &file);

    CaffHeader parseCaffHeader(ifstream &file, unsigned long dataLength);

    CaffCredits parseCaffCredits(ifstream &file, unsigned long length);

    CaffAnimation parseCaffAnimation(ifstream &file, unsigned long length);

    Ciff parseCiff(ifstream &file);

}
#endif //PARSER_PARSER_H
