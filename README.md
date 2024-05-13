# Part 1 VVSFS

## Building

Command line:

* `make` to build the image, block, and test files.
* `make clean` to clean object files.
* `make pristine` to remove all build files

## Files
* `inode.c` allocates an inode
* `free.c` file freeing and setting a specific bit index
* `testfs.c` this file tests the functionality of the image opening and the blocks read&write.
* `ctest.h` lightweight testing framework made by Beej
* `image.c` this file opens the image 
* `image.h` header file for image.c
* `block.c` the block file reads/writes a block of data passed in (example in test)
* `block.h` header file for `block.c`
* `testfs.c` testing file for functionality of the VVSFS

## Data
Reading and writing blocks of 4096 bytes to disk. 

## Functions

* All executed in main testing environment
* `find_free` finds a bit set to 0 and returns the index of the assigned block number
* `set_free` sets a passed in block's bit to the specific  `set` value specified
* `find_clear_low_bit` helper function from Beej to find the lowest clear bit
* `ialloc` allocates a previously-free inode in the inode map
* `test_bread` test to read a test block of data
* `test_bwrite` test to write data block 
* `test_open_img` opens a new image and then tests to see whether it is open with fd 4
* `test_img_close` test to assert if image is closed == 0
* `test_img_fd_init` test to ensure initial image_fd is set to -1
* `test_image_fd_gets_set` test to test to see if image_fd is set to valid (open) fd

## Notes
# project6_cs444
