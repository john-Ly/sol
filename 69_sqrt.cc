
// https://www.cnblogs.com/grandyang/p/4346413.html
//
// 二分法
//

// 还有一种牛顿迭代法  刷题角度 还是忽略吧
int mySqrt(int x) {
    if (x <= 1) return x;  // x=0无效 x=1直接返回1
    int left = 0, right = x;
    // 因为8的平方根 不是整数 所以 只能采用upper_bound
    while (left < right) {
        int mid = left + (right - left) / 2;
        // if (mid*mid <= x) left = mid + 1;  @NOTE mid*mid可能超出范围
        if (mid <= x/mid) left = mid + 1;
        else right = mid;
    }
    return right - 1;
}
