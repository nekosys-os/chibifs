//
// Created by Twometer on 8 Jun 2021.
//

#include <cstring>
#include "ChibiFS.h"

ChibiFS::ChibiFS(Partition *partition, BlockDevice *blockDevice) : partition(partition), blockDevice(blockDevice) {
    uint8_t identitySector[512];
    blockDevice->readSectors(partition->startSector, 1, identitySector);
    memcpy(&identityBlock, identitySector, sizeof(identityBlock));
}

const DescriptorBlock &ChibiFS::getIdentityBlock() const {
    return identityBlock;
}
