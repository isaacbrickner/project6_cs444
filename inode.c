#include "inode.h"
#include "free.h"
#include "block.h"
#include "image.h"


int ialloc(unsigned char *inode_map)
{
    bread(1, inode_map);
    int i = find_free(inode_map);
    if (i == -1)
    {
        return -1;
    }
    set_free(inode_map, i, 1);
    bwrite(1, inode_map);
    return i;
}