//
// Created by Twometer on 8 Jun 2021.
//

#ifndef CHIBIUTIL_MBR_H
#define CHIBIUTIL_MBR_H

#include <vector>
#include "BlockDevice.h"
#include "Partition.h"

class MBR {
public:
    static std::vector<Partition *> read(BlockDevice *blockDevice);

    static void write(BlockDevice *blockDevice, const std::vector<Partition *> &partitions);
};


#endif //CHIBIUTIL_MBR_H
