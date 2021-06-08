//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_BLOCKDEVICE_H
#define CHIBIUTIL_BLOCKDEVICE_H

#include <cstdint>
#include <cstddef>

#define BYTES_PER_SECTOR 512

class BlockDevice {
private:
    uint8_t *data;
    uint32_t size;

public:
    BlockDevice(uint8_t *data, uint32_t size);

    void readSectors(uint32_t block, uint32_t numBlocks, uint8_t *dst);

    void writeSectors(uint8_t *src, uint32_t numBytes, uint32_t block);
};


#endif //CHIBIUTIL_BLOCKDEVICE_H
