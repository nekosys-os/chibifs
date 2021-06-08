cmake_minimum_required(VERSION 3.19)
project(chibiutil)

set(CMAKE_CXX_STANDARD 14)

add_executable(chibiutil src/main.cpp src/IdentityBlock.h src/DirectoryEntry.h src/BlockDevice.cpp src/BlockDevice.h src/ChibiFS.cpp src/ChibiFS.h src/Partition.h src/Formatter.cpp src/Formatter.h src/MBR.cpp src/MBR.h)