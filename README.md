# ChibiFS Specification
ChibiFS (short: chifs) is a small and simple 32-bit FAT-like file system, designed as the native file system for nekosys. It's not designed to be a new and amazing file system with groundbreaking new technology, but rather a fun project as well as a simple and clean solution for a hobby operating system.

## Specs 

- Simple to implement for hobby operating systems
- Theoretical partition size limit: 2^32 bytes per block * 2^32 blocks = 18.4 Exabyte
- File size limit: 2^32 bytes = 4 Gigabyte
- File name limit: 127 characters
- POSIX-compliant permissions
- Dynamic main directory
- Little-endian integers

## Descriptor Block

The first block on disk is the descriptor block, which contains basic information about the file system. This block is **always** reserved. Note that the block size **must** always be divisible by 512.

The descriptor block takes up the first 24 bytes of the first block. The rest of the first block is reserved.

```c
struct DescriptorBlock {
    uint8_t     reserved[4];    // May be used for jump instructions etc.
    char        signature[8];   // File System signature, must be "CHIBIFS0"
    uint32_t    blockSize;      // Size of a single block, in bytes
    uint32_t    numBlocks;      // Size of the file system, in blocks
    uint32_t    reservedBlocks; // Number of reserved blocks after block 0
}
```

## File Table

After the descriptor block and all the reserved blocks comes the file table. For each block in the partition, there is an entry here which contains the index of the next block, or a marker for the end of the chain. The first entry in the file table correspondents to the first block on the disk.

### Table size

For each block on disk, there is a 32-bit integer in the File Table. Therefore, the size of the file table (in blocks) can be calculated as follows

```c
ceil(numBlocks * sizeof(uint32_t) / blockSize)
```

### Possible values

- `0x00000000`: Available block
- `0xFFFFFFFE`: Reserved block
- `0xFFFFFFFF`: End of a chain
- `0x00000000 ... 0xFFFFFFFD`: Reference to the next block in the chain

## Directory structure

A directory is basically just a file on the disk that contains a sequential list of directory entries (see below). Just like a file, it can span multiple blocks, and follows the File Table.

The root directory begins right after the File Table, and behaves just like any other directory except that its position is fixed.

## Directory entry

Files and directories are represented in their parent directory using directory entries. Non-existent or deleted directories are marked with type 0. A single directory entry is 158 bytes in size.

```c
struct DirectoryEntry {
    uint8_t     type;       // Type of the directory entry (0 = empty, 1 = file, 2 = dir)
    char        name[128];  // Null-terminated string with 127 usable bytes
    uint32_t    position;   // Disk block where the file is located
    uint32_t    size;       // Size of the file. Is 0 for anything but type #1
    uint32_t    modifyDate; // 32-bit unsigned unix time of last mofification
    uint32_t    createDate; // 32-bit unsigned unix time of file creation
    uint16_t    ownerId;    // User ID of the file owner
    uint16_t    groupId;    // Group ID of the file owner
    uint16_t	perms;      // Unix permissions
}
```

## Implementation

You can find the reference implementation (written in C++) of ChibiFS in the `chibiutil` folder
