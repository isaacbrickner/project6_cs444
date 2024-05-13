#include "image.h"
#include "block.h"
#include "ctest.h"
#include "free.h"
#include "inode.h"

void test_set_free(void)
{
    unsigned char block[4096] = {0, 0, 0, 0, 0, 0};
    set_free(block, 1, 1);
    CTEST_ASSERT(block[0] == 1, "test setting a 0 bit to 1");
}

void test_find_free(void)
{
    unsigned char block[4096] = {1, 1, 0, 0, 0, 0};
    CTEST_ASSERT(find_free(block) == 2, "test finding a 0 bit and returning its index");
}

void test_ialloc(void)
{
    unsigned char inode_map[4096] = {0, 0, 0, 0, 0, 0};
    CTEST_ASSERT(ialloc(inode_map) == 0, "test allocating inode in inode map");
}

void test_alloc(void)
{
    unsigned char data_block[4096] ={0, 0, 0, 0, 0, 0};
    CTEST_ASSERT(alloc(data_block) == 0, "test allocating block from blockmap");
}

void test_bread(void){
    unsigned char testBlock[4096]={1,1,1,1,1,1};
    CTEST_ASSERT(bread(2,testBlock)==testBlock, "test for block read");
}
void test_bwrite(void){
    unsigned char testBlock[4096] = {1,1,1,1,1,0};
    bwrite(1,testBlock);
    CTEST_ASSERT(bread(1,testBlock)==testBlock, "test  for block write(write, then assert read)");
}

void test_open_img(void){
    CTEST_ASSERT(image_open("test_open_img.txt",1) == 4, "test for image_open to be open fd #4");
}

void test_img_close(void){
    CTEST_ASSERT(image_close()==0, "test for image_close");
}

void test_img_fd_init(void){
    CTEST_ASSERT(image_fd==-1, "test for image_fd to be set to -1");
}

void test_img_fd_gets_set(void){
    CTEST_ASSERT(image_fd!=-1, "test to see if image_fd is set");
}

#ifdef CTEST_ENABLE
int main(){
    CTEST_VERBOSE(1);

    test_img_fd_init();
    image_open("test_open_img.txt",0);
    test_img_fd_gets_set();
    test_open_img();
    test_img_close();
    test_bread();
    test_bwrite();
    test_alloc();
    test_ialloc();
    test_set_free();
    test_find_free();

    CTEST_RESULTS();
    CTEST_EXIT();

    return 0;
}

#else
int main(){
    printf("If im here its not testing i think?");
}
#endif