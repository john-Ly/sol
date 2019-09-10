#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define PTR_ADDR(p) ((unsigned long)p)

void* malloc_aligned(uint32_t size,uint8_t alignment) {
    // 因为alignment 会对地址进行取模 所以需要多余的alignment
    assert(alignment>0);
    // uint8_t  一个字节的地址
    uint8_t* bytes=(uint8_t*)malloc(size+alignment);
    if (!bytes)
	    return NULL;
    uint8_t offset=alignment-PTR_ADDR(bytes)%alignment;
    bytes+=offset;
    bytes[-1]=offset;
    return bytes;
}

void free_aligned(void* ptr) {
    assert(ptr!=0);
    uint8_t* bytes=(uint8_t*)ptr;
    uint8_t offset=bytes[-1];
    bytes-=offset;
    free(bytes);
}

int main() {
    //对齐内存分配
    uint32_t size = 1234; //需要分配的内存大小（byte）
    uint8_t alignment = 128; //2^n byte地址对齐

    void* p = malloc_aligned(size, alignment); //  对齐后的
    uint8_t* tmp = (uint8_t*)p;
    uint8_t* q = tmp-tmp[-1]; // 未处理过对齐的
    printf("p = %p, %d\n", p, (size_t)p % alignment);
    printf("q = %p, %d\n", q, (size_t)q % alignment);
    free_aligned(p);

    return 0;
}
