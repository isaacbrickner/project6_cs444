#include "image.h"
#include "block.h"
#include "ctest.h"
#include "free.h"
#include "inode.h"
#include <stdlib.h>

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
    struct inode *in = ialloc(inode_map);
    CTEST_ASSERT(in->size == 0, "test allocating inode in inode map");
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

void test_incore_find_free(void)
{
    struct inode *node = incore_find_free();
    CTEST_ASSERT(node != NULL && node->ref_count==0, "test a free inode exists w/o a ref");
}
void test_incore_find(void)
{
    
    struct inode *node = incore_find(0);
    CTEST_ASSERT(node != NULL, "test to find an inode");
}

void test_incore_free_all(void)
{
    struct inode *node = incore_find(0);
    node->ref_count = 1;
    incore_free_all();
    CTEST_ASSERT(node->ref_count == 0, "test freeing incore inodes(s)");
}

void test_read_inode(void)
{

    struct inode inode;
    unsigned int inode_num = 0;
    read_inode(&inode, inode_num);
    CTEST_ASSERT(inode.ref_count==1 && inode.inode_num==inode_num, "test reading inode by inode number.");
}

void test_write_inode(void)
{

    struct inode in;
    struct inode in2;
    write_inode(&in);
    CTEST_ASSERT(in.size!=in2.size, "test write_inode");
    read_inode(&in2, in.inode_num);
    CTEST_ASSERT(in.size==in2.size, "test write_inode");
}

void test_iget(void)
{
    incore_free_all();
    CTEST_ASSERT(iget(0)->ref_count == 1, "test to find first ref count before it  finds a free incore inode");
    CTEST_ASSERT(iget(0)->ref_count == 2, "test to see if iget increments ref count");
}

void test_iput(void)
{ 
    struct inode in;
    in.ref_count = 0;
    CTEST_ASSERT(iput(&in) == NULL, "test null check iput");
    in.ref_count = 1;
    CTEST_ASSERT(iput(&in) == &in, "test that iput returns `in` after writing");
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
    test_set_free();
    test_find_free();
    test_ialloc();
    test_alloc();
    test_incore_find_free();
    test_incore_find();
    test_incore_free_all();
    test_read_inode();
    test_write_inode();
    test_iget();
    test_iput();
    CTEST_RESULTS();
    CTEST_EXIT();
    return 0;
}

#else
int main(){
    printf("If im here its not testing i think?");
}
#endif