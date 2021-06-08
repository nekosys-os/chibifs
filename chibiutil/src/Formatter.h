//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_FORMATTER_H
#define CHIBIUTIL_FORMATTER_H


#include <xstring>
#include "IdentityBlock.h"

class Formatter {
public:
    static void createImage(const std::string &path, const IdentityBlock &identityBlock);
};


#endif //CHIBIUTIL_FORMATTER_H
