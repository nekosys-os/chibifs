//
// Created by Twometer on 8 Jun 2021.
//

#include <stdexcept>
#include <vector>
#include "Formatter.h"
#include "ChibiFS.h"
#include "MBR.h"

void Formatter::createImage(const std::string &path, const IdentityBlock &identityBlock) {
    uint32_t partitionSize = identityBlock.numBlocks * identityBlock.blockSize;
    if (partitionSize == 0) {
        throw std::runtime_error("partition size must not be 0");
    }
    if (identityBlock.blockSize % 512 != 0) {
        throw std::runtime_error("block size must be multiple of 512");
    }

    auto mbrOffset = 512;
    auto *data = new uint8_t[partitionSize + mbrOffset];
    memset(data, 0, partitionSize + mbrOffset);
    memcpy(data + mbrOffset, &identityBlock, sizeof(IdentityBlock));

    // Write master boot record
    BlockDevice device(data, partitionSize + mbrOffset);
    std::vector<Partition *> partitions;
    partitions.push_back(new Partition(true, 0x00, 1, partitionSize / 512));
    MBR::write(&device, partitions);

    // Initialize file table
    auto fileTableIdx = identityBlock.blockSize * (identityBlock.reservedBlocks + 1);
    auto *fileTable = (uint32_t *) &data[fileTableIdx + mbrOffset];

    // Mark reserved sectors in file table
    for (int i = 0; i < identityBlock.reservedBlocks + 1; i++) {
        fileTable[i] = FILE_TABLE_RESERVED;
    }

    // Mark the end of the empty root directory chain
    fileTable[identityBlock.reservedBlocks + 1] = FILE_TABLE_CHAIN_END;

    // Write image to file
    FILE *file = fopen(path.c_str(), "wb");
    fwrite(data, 1, partitionSize + mbrOffset, file);
}
