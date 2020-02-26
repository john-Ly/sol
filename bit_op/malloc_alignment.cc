#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// @NOTE 任意字节对齐的动态内存分配函数
// https://zhou-yuxin.github.io/articles/2017/%E4%BB%BB%E6%84%8F%E5%AD%97%E8%8A%82%E5%AF%B9%E9%BD%90%E7%9A%84%E5%8A%A8%E6%80%81%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E5%87%BD%E6%95%B0/index.html

// ref: leveldb
char* Arena::AllocateAligned(size_t bytes /*,int align*/) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  static_assert((align & (align - 1)) == 0,
                "Pointer size should be a power of 2");
  // 取模 (& mask)
  size_t current_mod = reinterpret_cast<uintptr_t>(alloc_ptr_) & (align - 1);
  size_t slop = (current_mod == 0 ? 0 : align - current_mod);
  size_t needed = bytes + slop;
  char* result;
  if (needed <= alloc_bytes_remaining_) {
    result = alloc_ptr_ + slop;
    alloc_ptr_ += needed;
    alloc_bytes_remaining_ -= needed;
  } else {
    // AllocateFallback always returned aligned memory
    result = AllocateFallback(bytes);
  }
  assert((reinterpret_cast<uintptr_t>(result) & (align - 1)) == 0);
  return result;
}

#define PTR_ADDR(p) ((unsigned long)p)

void* malloc_aligned(uint32_t size,uint8_t alignment) {
    // 因为alignment 会对地址进行取模 所以需要多余的alignment
    assert(alignment>0);
    // uint8_t  一个字节的地址
    uint8_t* bytes = (uint8_t*)malloc(size+alignment);
    if (!bytes) return nullptr;
    uint8_t offset = alignment-PTR_ADDR(bytes)%alignment;
    bytes += offset;
    bytes[-1] = offset;
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
