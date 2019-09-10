
// 思想是快慢指针(不过数组的下标比较方便)
// @NOTE 前提是已经拍好序
//
// https://www.cnblogs.com/grandyang/p/4329128.html
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int pre = 0, cur = 0, n = nums.size();
    while (cur < n) {
        if (nums[pre] == nums[cur]) ++cur;
        else nums[++pre] = nums[cur++];
    }
    return pre + 1;
}
