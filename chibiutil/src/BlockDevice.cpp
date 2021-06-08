//
// Created by Twometer on 8 Jun 2021.
//

#include <cstring>
#include "BlockDevice.h"

BlockDevice::BlockDevice(uint8_t *data, uint32_t size) : data(data), size(size) {}

void BlockDevice::readSectors(uint32_t block, uint32_t numBlocks, uint8_t *dst) {
    memcpy(dst, &data[block * BYTES_PER_SECTOR], numBlocks * BYTES_PER_SECTOR);
}

void BlockDevice::writeSectors(uint8_t *src, uint32_t numBytes, uint32_t block) {
    memcpy(&data[block * BYTES_PER_SECTOR], src, numBytes / BYTES_PER_SECTOR * BYTES_PER_SECTOR);
}
