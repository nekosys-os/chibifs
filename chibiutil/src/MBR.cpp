//
// Created by Twometer on 8 Jun 2021.
//

#include "MBR.h"

std::vector<Partition *> MBR::read(BlockDevice *blockDevice) {
    uint8_t data[512];
    blockDevice->readSectors(0, 1, data);

    std::vector<Partition *> partitions;
    for (uint32_t i = 0x1BE; i < 510; i += 16) {
        bool bootable = data[i] == 0x80;
        uint8_t partitionType = data[i + 0x04];
        uint32_t startSector = *(uint32_t *) &data[i + 0x08];
        uint32_t numSectors = *(uint32_t *) &data[i + 0x0C];

        if (numSectors != 0)
            partitions.push_back(new Partition(bootable, partitionType, startSector, numSectors));
    }

    return partitions;
}

void MBR::write(BlockDevice *blockDevice, const std::vector<Partition *> &partitions) {
    uint8_t data[512];
    memset(data, 0, 512);

    uint32_t offset = 0x1BE;
    for (auto partition : partitions) {
        data[offset + 0x00] = partition->bootable ? 0x80 : 0x00;
        data[offset + 0x04] = partition->partitionType;
        *(uint32_t *) &data[offset + 0x08] = partition->startSector;
        *(uint32_t *) &data[offset + 0x0C] = partition->numSectors;
        offset += 16;
    }

    // Boot signature
    data[510] = 0x55;
    data[511] = 0xAA;

    blockDevice->writeSectors(data, 512, 0);
}
