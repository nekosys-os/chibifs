//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_CHIBIFS_H
#define CHIBIUTIL_CHIBIFS_H

#define FILE_TABLE_AVAILABLE 0x00000000
#define FILE_TABLE_CHAIN_END 0xFFFFFFFF
#define FILE_TABLE_RESERVED  0xFFFFFFFE

#include "BlockDevice.h"
#include "DescriptorBlock.h"
#include "Partition.h"

class ChibiFS {
private:
    Partition *partition;
    BlockDevice *blockDevice;
    DescriptorBlock identityBlock{};

public:
    ChibiFS(Partition *partition, BlockDevice *blockDevice);

    const DescriptorBlock &getIdentityBlock() const;

};


#endif //CHIBIUTIL_CHIBIFS_H
