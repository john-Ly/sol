#include <stdio.h>
#include <stdlib.h>  // malloc + int atio(char *)
#include <string.h>  // memset
#include <ctype.h>   // isspace
#include <limits.h>  // INT_MAX INT_MIN

#include <stdlib.h>
#include <string>
#include <iostream>

// 补码可以表示  8位带符号整数: [ -128, 127 ]  @TODO 出现warning
// #define MAX_INT ((1 << 31) - 1)
// #define MIN_INT (-(1 << 31))
#define STR_ELEM_NUM 20
using namespace std;
// atoi()  字符串整数
// 1. 字符串前的空白
// 2. 字符串所表示数值的正负号
// 3. 结束条件，遇到非数字或者字符'\0'结束
// 4. 考虑溢出，分别与int值所能表示的最大(0x7fffffff)和最小值(0x8000000)进行比较  32位机与64位机的区别。
// 5. 考虑异常输入情况下，用全局变量valid来标识，对于"+/-" "0" "+abc"需要进行区分。

// 推荐做法 思路清晰
// @TODO 科学计数法 就太复杂了
int myatoi2(string str) {
    if(str.empty()) return 0;
    int sign = 1, base = 0, i = 0, n = str.size();
    while (i < n && str[i] == ' ') ++i;
    if (i < n && (str[i] == '+' || str[i] == '-')) {
        sign = (str[i++] == '+') ? 1 : -1;
    }
    while (i < n && str[i] >= '0' && str[i] <= '9') {
        // int -2147483648	2147483647
        // 1. 如果正数 >=7 都是直接返回 INT_MAX
        // 2. 如果负数 7合法 8是上限 9溢出 但是直接返回 INT_MIN 所以一个条件统一
        // 3. @NOTE 由于带符号 由补码 对称 所以这种方法都是适用的
        if (base > INT_MAX/10
            || (base == INT_MAX/10 && str[i] - '0' > INT_MAX%10 ))
            return (sign == 1) ? INT_MAX : INT_MIN;
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

// int -2147483648	2147483647
string itos(int value) {
  static const char digits[] = "9876543210123456789";
  static const char* zero = digits + 9;
  int i = value;
  string res;

  do {
    int lsd = i%10;
    i /= 10;
    res += zero[lsd];
  } while (i != 0);
  if (value < 0) res += '-';
  std::reverse(res.begin(), res.end());

  return res;
}

/*
1. scanf 针对 字符串指针 数组
  stackoverflow 方法:

   char arrays[12];
   char *pointers= arrays;
   scanf("%s",pointers);
   printf("%s",pointers);

  或者 本文件中的 malloc 的方法
2. scanf:                          接受引用变量(&n) 因为函数名参数是 void *
   %[*] [域长度] [长度修饰符] [转换修饰符]
   * scanf所读入的所有都丢弃
   [转换修饰符]:
   d 整数 十进制
   c 一个字符    %7c 放入有个字符串指针
      - @ NOTE  没有'\0' 终止字符
      - 会读入 空白字符
   s 一个字符串
      - 遇到 第一个空白字符  --- 停止读取
	  - 自带 '\0'
   [...] 扫描集
      - 只匹配 扫描集 中的字符
	     [abc]
      - 取反操作
        *[^0123456789] 取出来不是数字的字符 并且丢弃
		%[...]  类似 %d 一样 都是转换修饰符
		    double x, y;
		    char op[16] = "";
			scanf("%15s%lf%*[^0123456789]%lf", op, &x, &y);

			puts(op);
			printf("%lf %lf\n", x, y);

=======================
c in a nutshell P552
fscan 文件
=======================

fscanf  @NOTE SEE 真正高手的使用   ---  感觉没有正则表达式 完全不能处理字符串啊
    results = fscanf( fp, "%31[^:]:%31[^:]:%u:%u:",
                      recptr->user, recptr->pw, &recptr->uid, &recptr->gid );

    fscanf( fp, "%*[^\n]\n" ); // 读错了 就全部丢弃

    results = fscanf( fp, "%127[^:]:%127[^:\n]\n", recptr->home, recptr->shell );
    %[^:]: 冒号前所有的字符都读

@NOTE scanf 利用数据流 实际上就是内存流


3. while(~scanf("%d",&n))   <=>  while(scanf("%d",&n)!=EOF)
   不要这样做
4. 使用scanf(“%*[^\n]%*c”)，
   用扫描集将缓冲区中的字符全部读取来实现清除输入缓冲区的动作

   http://blog.csdn.net/veniversum/article/details/62048870
   fflush(stdin);
   不规范的做法
*/


int myatoi3(const char* str) {
    int sign = 1, base = 0, i = 0;
    while (str[i] == ' ') { i++; }
    if (str[i] == '-' || str[i] == '+') {
        sign = 1 - 2 * (str[i++] == '-');
    }
    while (str[i] >= '0' && str[i] <= '9') {
        if (base >  INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }
        base  = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

int myatoi1(const char* str) {
    int n = 0;
    char sign;
    int c;

    while (isspace(*str))
        ++str;

	//第一个字符不是数字
    if(*str != '-' && *str != '+' && (*str < '0' || *str > '9'))
        return 0;

    sign = *str;
    if (sign == '+' || sign == '-')
        ++str;
    while (isdigit(*str)) {
        c = *str - '0';  // 字符串 --->  整数

		//先用n与MAX/10进行比较: 若n>MAX/10(还要考虑n=MAX/10的情况), 说明将要溢出了
		//提高溢出处理的健壮性,除法代替乘法
		// 上溢 和 下溢
        if (sign != '-' && (n > INT_MAX/10 || (n == INT_MAX/10 && c >= INT_MAX%10)))
            return INT_MAX;
        else if (sign == '-' && (n > (unsigned)INT_MIN/10
                              || (n == (unsigned)INT_MIN/10 && c >= (unsigned)INT_MIN%10)))
            return INT_MIN;
        n = n * 10 + c;  // 字符串 --> 整数 先从高位 每次进一位即可
        ++str;
    }

    return sign == '-' ? -n : n;
}

int main(){
    /*
    int N,i;
    char *str[STR_ELEM_NUM];
    memset(str,0,sizeof(str));

    printf("测试数据个数N:\n");
    scanf("%d",&N);
    for(i=0;i<N;i++) {
        str[i] = (char*) malloc(STR_ELEM_NUM);
        // 如果不清缓冲区，scanf会把"\n"吃进，导致str[0] = "",少输入一个数据.
        //fflush(stdin);
        scanf("%*c");  // 把 '\n' 丢弃掉

        // str[i]是一个字符型指针，定义时指向不可用的地址，需要字符指针配内存空间
        scanf("%[^\n]",str[i]);
        // 换行符之前的都读进来 算是读入一行
        //fflush(stdin);
    }
    printf("\n***************Result**************************\n");
    for(i =0;i<N;i++){
        printf("%d\n",myatoi(str[i]));
        free(str[i]);
    }
*/
/*   1+sd   --- 输出结果应该是  1
    if ('0' <= *pstr && *pstr <= '9') {}
    else break;
*/
    cout << INT_MAX/10 << " " << INT_MAX%10 << endl;
    // 把负号编程正号输出
    cout << (unsigned) INT_MIN/10 << " " << (unsigned)INT_MIN%10 << endl;

    return 0;
}
