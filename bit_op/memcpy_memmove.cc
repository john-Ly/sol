#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cassert>

// memcpy函数，如果内存重叠则报错  --> src指向内容 不能修改
void* memcpy(void* dst, const void* src, size_t count) {
    assert(dst!= nullptr && src != nullptr);  // non-ptr
    uint8_t* pdst = (uint8_t*)dst;
    uint8_t* psrc = (uint8_t*)src;

    // 两个区间不重合overlap 全在左边 或者 右边
    assert(pdst >= psrc+count || psrc >= pdst + count);
    while (count-- > 0) {
        *pdst++ = *psrc++;
    }
    return dst;
}

// memmove函数，考虑了内存重叠的情况(src可能被覆盖)
// const void* src 虽然src不能修改内存, 但是指针还是泄漏给了psrc
void* memmove(void* dst, const void* src, size_t count) {
    assert(dst!= nullptr && src != nullptr);  // non-ptr
    uint8_t* pdst = (uint8_t*)dst;
    uint8_t* psrc = (uint8_t*)src;

    //  dst在小端(或重叠)       在大端(非重叠)
    if (dst <= src || pdst >= psrc + count) {
        while (count-- > 0) {
            *pdst++ = *psrc++; // 按递增拷贝
        }
    } else { // 大端(重叠)    从高位地址向低位拷贝(copy_backward)
        pdst += count-1;
        psrc += count-1;
        while (count-- > 0) {
            *pdst-- = *psrc--; //按递减拷贝
        }
    }
    return dst;
}