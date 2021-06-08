#include <iostream>
#include "Formatter.h"
#include "BlockDevice.h"
#include "MBR.h"
#include "ChibiFS.h"

void createImage(const std::string &image) {
    DescriptorBlock identityBlock{};
    identityBlock.numBlocks = 16 * 1024 * 1024 / identityBlock.blockSize;
    identityBlock.reservedBlocks = 3;
    Formatter::createImage(image, identityBlock);
}

void importFolder(const std::string &image, const std::string &folder) {
    FILE *file = fopen(image.c_str(), "rb");
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    auto *data = new uint8_t[size];
    fread(data, 1, size, file);
    fclose(file);

    BlockDevice blockDevice(data, size);
    auto partitions = MBR::read(&blockDevice);
    auto chibiFS = new ChibiFS(partitions[0], &blockDevice);
    std::cout << chibiFS->getIdentityBlock().signature << std::endl;

    delete[] data;
    delete chibiFS;
}

int main() {
    importFolder("test.img", "imgdir");
    return 0;
}
