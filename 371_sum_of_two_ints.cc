// https://www.cnblogs.com/grandyang/p/5451942.html
// 使用位运算进行 两个数字的相加

// https://www.cnblogs.com/grandyang/p/5631814.html

// 没有进位 就可以直接退出
int add(int a, int b) {
    if (b == 0) return a;
    int sum = a ^ b;
    int carry = (a & b) << 1;
    return add(sum, carry);
}

int getSum(int a, int b) {
    if (b == 0) return a;
    int sum = a ^ b;
    // INT_MIN负数不能够进行左移  因为符号位的问题
    // @TODO 左移和右移的区别(负数 右移符号位会扩展)
    int carry = (a & b & 0x7fffffff) << 1;
    return getSum(sum, carry);
}