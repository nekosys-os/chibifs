//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_DESCRIPTORBLOCK_H
#define CHIBIUTIL_DESCRIPTORBLOCK_H

#include <cstdint>

struct DescriptorBlock {
    uint8_t reserved[4];
    char signature[8];
    uint32_t blockSize;
    uint32_t numBlocks;
    uint32_t reservedBlocks;

    DescriptorBlock() {
        const char *signatureData = "CHIBIFS0";
        memcpy(signature, signatureData, 8);
        memset(reserved, 0, 4);
        blockSize = 512;
    }
};

#endif //CHIBIUTIL_DESCRIPTORBLOCK_H
