//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_PARTITION_H
#define CHIBIUTIL_PARTITION_H

#include <cstdint>

struct Partition {
    bool bootable;
    uint8_t partitionType;
    uint32_t startSector;
    uint32_t numSectors;

    Partition(bool bootable, uint8_t partitionType, uint32_t startSector, uint32_t numSectors)
            : bootable(bootable), partitionType(partitionType), startSector(startSector), numSectors(numSectors) {}
};

#endif //CHIBIUTIL_PARTITION_H
