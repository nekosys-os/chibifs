#include <iostream>
#include "Formatter.h"

void createImage() {
    DescriptorBlock identityBlock{};
    identityBlock.numBlocks = 16 * 1024 * 1024 / identityBlock.blockSize;
    identityBlock.reservedBlocks = 3;
    Formatter::createImage("test.img", identityBlock);
}

int main() {
    createImage();
    return 0;
}
