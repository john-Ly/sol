// 00-99 范围内共有20个 1
// 000-999 范围共有280个 1


// O(nlogn)
int NumberOf1Between1AndN_Solution(int n) {
    int count=0;
    for(int i=0; i <= n; ++i) {
        int temp = i;
        while(temp) {
            if(temp % 10 == 1)  ++count;
            temp /= 10;
        }
    }
    return count;
}

// 彻底放弃 这纯粹智力题
int NumberOf1Between1AndN_Solution(int n) {
    // 统计次数
    int count = 0;
    for(int i = 1; i <= n; i *= 10){
        // 计算高位和低位
        int a = n / i, b = n % i;
        count += (a + 8) / 10 * i + (a % 10 == 1) * (b + 1);
    }
    return count;
}