#ifndef CHIBIUTIL_DIRECTORYENTRY_H
#define CHIBIUTIL_DIRECTORYENTRY_H

#include <cstdint>

enum EntryType {
    Empty = 0,
    File = 1,
    Directory = 2
};

struct DirectoryEntry {
    uint8_t type;
    char name[128];
    uint32_t position;
    uint32_t size;
    uint32_t modifyDate;
    uint32_t createDate;
    uint16_t ownerId;
    uint16_t groupId;
    uint16_t perms;
}

#endif //CHIBIUTIL_DIRECTORYENTRY_H
