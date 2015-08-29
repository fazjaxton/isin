/* Define to get basename function from string.h */
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


static void *xmap (const char *name, size_t *size)
{
    void *addr;
    struct stat buf;
    int res;
    int fd;

    fd = open(name, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Opening %s: %s\n", name, strerror(errno));
        exit(255);
    }

    res = fstat(fd, &buf);
    if (res < 0) {
        fprintf(stderr, "Error getting %s stats: %s\n",
                name, strerror(errno));
        exit(255);
    }

    addr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        fprintf(stderr, "Could not map %s: %s\n", name, strerror(errno));
        exit(255);
    }

    *size = buf.st_size;

    return addr;
}


int main(int argc, char **argv)
{
    size_t size1;
    size_t size2;
    size_t offset;

    uint8_t *file1;
    uint8_t *file2;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <outer_file> <inner_file>\n",
                basename(argv[0]));
        exit(255);
    }

    file1 = xmap(argv[1], &size1);
    file2 = xmap(argv[2], &size2);

    if (size2 > size1) {
        fprintf(stderr, "%s larger than %s\n", argv[2], argv[1]);
        exit(255);
    }

    offset = 0;

    for (offset = 0; offset < size1 - size2 + 1; offset++) {
        if (file1[offset] == file2[0]) {
            if (memcmp (&file1[offset], file2, size2) == 0) {
                printf ("Match at offset %ld\n", offset);
                return 0;
            }
        }
    }

    return 1;
}
