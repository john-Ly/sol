#include <iostream>
#include <cstdint>

bool Check(uint32_t, uint32_t) {
    return true;
}

// utf-8(最长4个字节 uint32_t)
// 1. 0xxx.xxxx 单字节
// 2. 110x.xxxx 10xx.xxxx  首字节前半部分表示该cp占用多少个字节
// 3. 1110.xxxx 10xx.xxxx 10xx.xxxx
// 4. 1111.0xxx 10xx.xxxx 10xx.xxxx 10xx.xxxx
bool ReadCodePoint(const uint8_t* pSrc, uint32_t& cp) {
    uint32_t u1, u2, u3, u4, nu = 0;
    if ((u1 = *pSrc++) <= 0x7F) {
        cp = u1; nu = 1;
    } else if ((u1 & 0xE0) == 0xC0) {
        u2 = *pSrc++; nu = 2;
        cp = ((u1 & 0x1F) << 6) | (u2 & 0x3F);
    } else if ((u1 & 0xF0) == 0xE0) {
        u2 = *pSrc++;
        u3 = *pSrc++; nu = 3;
        cp = ((u1 & 0x0F) << 12) | ((u2 & 0x3F) << 6) | (u3 & 0x3F);
    } else if ((u1 & 0xF8) == 0xF0) {
        u2 = *pSrc++;
        u3 = *pSrc++;
        u4 = *pSrc++; nu = 4;
        cp = ((u1 & 0x07) << 18) | ((u2 & 0x3F) << 12) | ((u3 & 0x3F) << 6) | (u4 & 0x3F);
    }
    // cp 存储codepoint代表的值; nu 代表使用几个字节
    return Check(cp, nu);
}