//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_IDENTITYBLOCK_H
#define CHIBIUTIL_IDENTITYBLOCK_H

#include <cstdint>

struct IdentityBlock {
    uint8_t reserved[4];
    char signature[8];
    uint32_t blockSize;
    uint32_t numBlocks;
    uint32_t reservedBlocks;

    IdentityBlock() {
        const char *signatureData = "CHIBIFS0";
        memcpy(signature, signatureData, 8);
        memset(reserved, 0, 4);
        blockSize = 512;
    }
};

#endif //CHIBIUTIL_IDENTITYBLOCK_H
