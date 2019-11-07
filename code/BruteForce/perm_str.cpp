#include <stdio.h>
#include <cstring>

//交换两个字符
void Swap(char *a ,char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

//递归全排列，start 为全排列开始的下标， length 为str数组的长度
void AllRange(char* str,int start,int length) {
	if(start == length-1) {
		printf("%s\n",str);
	}
	else {
		for(int i=start;i<=length-1;i++) {
			//从下标为start的数开始，分别与它后面的数字交换
			Swap(&str[start],&str[i]);
			AllRange(str,start+1,length);
			Swap(&str[start],&str[i]);
		}
	}
}

void Permutation(char* str) {
	if(str == NULL)
		return;

	AllRange(str,0,strlen(str));
}

int main() {
	char str[] = "abc";
	Permutation(str);

	return 0;
}
