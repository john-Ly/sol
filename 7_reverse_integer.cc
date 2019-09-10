#include <stdio.h>
#include <stdlib.h> // atoi
#include <limits.h> // INT_MAX

//        min         max
// int -2147483648	2147483647
// @NOTE leetcode上的答案很经典
//
/*
// Reversing an integer can be done similarly to reversing a string.
// We want to repeatedly "pop" the last digit off of xx and "push" it to the back of the \text{rev}rev. In the end, \text{rev}rev will be the reverse of the xx.
// To "pop" and "push" digits without the help of some auxiliary stack/array, we can use math.
    //pop operation:
    pop = x % 10;
    x /= 10;

    //push operation:
    temp = rev * 10 + pop;
    rev = temp;

*/

int reverse(int x) {
    int y = 0;
    while (x != 0) {
        int n = x % 10;
        // Checking the over/underflow.
        // Actually, it should be y>(INT_MAX-n)/10, but n/10 is 0, so omit it.
        //
        // INT_MAX: 214748364 7
        // 2147483642  ==> 0   因为21..42 前一个条件就满足类这种不可能(数学上可能严谨 但是int计算机实现还是有限制)
        if (y > INT_MAX/10 /* || (y == INT_MAX/10 && n > 7)*/) return 0;
        if (y < INT_MIN/10 /* || (y == INT_MIN/10 && n < -8)*/) return 0;

        y = y * 10 + n;
        x /= 10;
    }
    return y;
}

#define TEST(n, e)  printf("%12d  =>  %-12d  %s!\n",  n, reverse(n),  e == reverse(n)?"passed":"failed")

int main(int argc, char**argv)
{
    //basic cases
    TEST(  123,  321);
    TEST( -123, -321);
    TEST( -100,   -1);
    TEST( 1002, 2001);
    //big integer
    TEST( 1463847412,  2147483641);
    TEST(-2147447412, -2147447412);
    TEST( 2147447412,  2147447412);
    //overflow
    TEST( 1000000003, 0);
    TEST( 2147483647, 0);
    // TEST( 2147483648, 0);  int无法表示
    TEST(-2147483648, 0);
    // TEST(-2147483649, 0);
    //customized cases

	char s[100] = "123";
    printf("\n");
    int n = atoi(s);
    printf("%12d  =>  %-12d  %s!\n",  n, reverse(n), reverse(reverse(n))==n ? "passed":"failed");
    printf("%12d  =>  %-12d \n", 2147483642, reverse(2147483642));
    return 0;
}
