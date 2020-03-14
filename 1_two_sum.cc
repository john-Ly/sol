#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "  [";
		for (T val: row) {
			cout << val << ',';
		}
        cout << "],\n";
	}
    cout << "}\n";
}

// topic: n_sum, array, 双指针

namespace two_sum {
// 给定target 求数组中和满足的两个数的下标(下标不能相同)(无序)
// https://www.cnblogs.com/grandyang/p/4130379.html
vector<int> twoSum(vector<int> &numbers, int target) {
	unordered_map<int, int> hash;   // num -> idx
	vector<int> result;
    // 按顺序遍历, 所以不可能返回相同的i
	for (int i = 0; i < numbers.size(); i++) {
        if (hash.count(target - numbers[i])) {
            // push的顺序
			result.push_back(hash[target - numbers[i]]);
			result.push_back(i);
			return result;
		}

		hash[numbers[i]] = i;
	}
	return result;
}

int twoSumSmaller(vector<int>& nums, int target) {
    if (nums.size()<2) return 0;
    int res = 0;
    sort(nums.begin(), nums.end());
    int left = 0, right = nums.size()-1;
    while (left < right) {
        if (nums[left] + nums[right] < target) {
            // e.g.:  1 2 3
            //       (1 3) + (1 2)
            //       2 3
            // 所以left 只增加1
            res += right - left;
            ++left;
        } else {
            --right;
        }
    }
    return res;
}

// 设计two_sum类
class TwoSum {
public:
    // 不存在 m[number] = 0;  ++  -->  m[number] == 1
    void add(int number) {
        ++m[number];
    }

    bool find(int value) {
        for (auto pa : m) {
            int t = value - pa.first;
            if ((t != pa.first && m.count(t)) ||
                (t == pa.first && pa.second > 1)) {
                return true;
            }
        }
        return false;
    }
private:
    // 存储无序的数组
    unordered_map<int, int> m;
};

// 升序数组 twoSum 如果有多对数字的和等于S，输出两个数的乘积最小的
// 双指针 - 保证乘积最小
vector<int> FindNumbersWithSum(vector<int>& array, int sum) {
    vector<int> result;
    int length = array.size();
    if(length < 1) { return result; }
    int pleft = 0, pright = length - 1;

    while(pleft > pright){
        int curSum = array[pleft] + array[pright];
        if (curSum == sum) {
            result.push_back(array[pleft]);
            result.push_back(array[pright]);
            break;
        }
        else if(curSum < sum) { pleft++;}
        else { pright--; }
    }
    return result;
}

// 输入是BST 找出two_sum是否存在 (中序得到有序数组 然后快慢指针)
class bst_two_sum {
public:
    bool findTarget(TreeNode* root, int target) {
        vector<int> nums;
        inorder(root, nums);
        for (int i=0, j=(int)nums.size()-1; i<j;) {
            if (nums[i] + nums[j] == target) return true;
            (nums[i] + nums[j] < target) ? ++i : --j;
        }
        return false;
    }

    void inorder(TreeNode* node, vector<int>& nums) {
        if (!node) return;
        inorder(node->left, nums);
        nums.push_back(node->val);
        inorder(node->right, nums);
    }
};
}

// 固定一个数 快慢指针
namespace three_sum {
// https://www.cnblogs.com/grandyang/p/4481576.html
// 无序数组(可能包含重复)  找出可能的三个数和为0
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    // 排序 方便确定相反数
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.back()<0 || nums.front()>0) return res;

    // 三个数全为0 或者 TwoSum>0, 后一个数<0
    // leetcode: num.size()-2 报错 @TODO但是感觉不会存在heap memory泄露
    // 1. 每次固定一个数(sorted, 如果fixed > 0 直接break)
    //    从固定数之后的范围 查找另外两个数
    for (int k = 0; k < nums.size()-2; ++k) {
        // 剪枝优化(固定第一位 负数)
        if (nums[k] > 0) break;
        // 重复 与之前的数字(运行下面会得到与之前相同的结果)
        if (k > 0 && nums[k] == nums[k - 1]) continue;

        int target = 0 - nums[k];
        // 快慢指针 -- 数组有序可以线性时间O(n), 否则O(n^2)
        // i指针指向小数   j指针指向大数
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                res.push_back({nums[k], nums[i], nums[j]});
                // 重复的出现 会造成最终结果重复
                while (i < j && nums[i] == nums[i + 1]) ++i;
                while (i < j && nums[j] == nums[j - 1]) --j;
                ++i; --j;
            } else if (nums[i] + nums[j] < target) ++i;
            else --j;
        }
    }
    return res;
}

// https://www.cnblogs.com/grandyang/p/4481576.html
int threeSumClosest(vector<int>& nums, int target) {
    int closest = nums[0] + nums[1] + nums[2];
    int diff = std::abs(closest - target);
    sort(nums.begin(), nums.end());

    for (int k = 0; k < nums.size()-2; ++k) {
        if (nums[i] * 3 > target) // 数组排序 后面的数字很大
            return min(closest, nums[i] + nums[i+1] + nums[i+2]);
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            int sum = nums[k] + nums[i] + nums[j];
            int newDiff = std::abs(target-sum);
            if (newDiff < diff) {
                diff = newDiff;
                closest = sum;
            }

            if (sum < target) ++i;
            // sum >= target
            else --j;
        }
    }
    return closest;
}

// https://www.cnblogs.com/grandyang/p/5235086.html
//  求出三个数的和小于 target的所有个数
// O(n^2)
int threeSumSmaller_brute(vector<int>& nums, int target) {
    int res = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 2); ++i) {
        int left = i+1, right = nums.size()-1;
        int sum = target - nums[i];

        for (int j = left; j <= right; ++j) {
            for (int k = j + 1; k <= right; ++k) {
                if (nums[j] + nums[k] < sum) ++res;
            }
        }
    }
    return res;
}

// 快慢指针
int threeSumSmaller_slow_fast(vector<int>& nums, int target) {
    if (nums.size()<3) return 0;
    int res = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 2); ++i) {
        int left = i+1, right = nums.size()-1;
        int sum = target - nums[i];

        while (left < right) {
            if (nums[i] + nums[left] + nums[right] < target) {
                // e.g.:  1 2 3
                //       1 3 + 1 k2
                //       2 3
                // 所以left 只增加1
                res += right - left;
                ++left;
            } else {
                --right;
            }
        }
    }
    return res;
}

}

namespace four_sum {
// https://www.cnblogs.com/grandyang/p/4515925.html
// three_sum的模板(去除有重复的)
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n-3; ++i) {
        // 重复 与之前的数字 -- 从第二次遍历开始
        if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i+1; j < n-2; ++j) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            int lo = j + 1, hi = n - 1;
            while (lo < hi) {
                int sum = nums[i] + nums[j] + nums[lo] + nums[hi];
                if (sum == target) {
                    res.push_back({nums[i], nums[j], nums[lo], nums[hi]});
                    while (lo < hi && nums[lo] == nums[lo + 1]) ++lo;
                    while (lo < hi && nums[hi] == nums[hi - 1]) --hi;
                    ++lo; --hi;
                } else if (sum < target) ++lo;
                else --hi;
            }
        }
    }
    return res;
}

// 四个等长度的数组 各挑一个数其和为0    two_sum思路
// https://www.cnblogs.com/grandyang/p/6073317.html
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    int res = 0;
    //           a+b   次数
    unordered_map<int, int> m;
    // A B 两两之和 求出
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            ++m[A[i] + B[j]];
        }
    }

    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < D.size(); ++j) {
            int target = -1 * (C[i] + D[j]);
            // 存在相反数  即证明存在
            res += m[target];
        }
    }
    return res;
}
}

// @NOTE 累加数组和
namespace range_sum {
// 连续子数组 和为k 的个数
// https://www.cnblogs.com/grandyang/p/6810361.html
int subarraySum(vector<int>& nums, int k) {
    int res = 0, n = nums.size();
    vector<int> sums = nums;
    for (int i=1; i<n; ++i) {
        sums[i] = sums[i-1] + nums[i];
    }
    for (int i = 0; i < n; ++i) {
        if (sums[i] == k) ++res;
        for (int j = i - 1; j >= 0; --j) {
            if (sums[i] - sums[j] == k) ++res;
        }
    }
    return res;
}

// 思路相似
// 求连续子数组 最大的和
// @SEE dp/maximum_subarray

// 非负数组
// 连续子数组之和是k的倍数(除法 判断分母不为0)
bool checkSubarraySum(vector<int>& nums, int k) {
    for (int i = 0; i < nums.size(); ++i) {
        int sum = nums[i];
        for (int j = i + 1; j < nums.size(); ++j) {
            sum += nums[j];
            if (sum == k) return true;
            if (k != 0 && sum % k == 0) return true;
        }
    }
    return false;
}

// @TODO
// https://www.cnblogs.com/grandyang/p/7753959.html

// https://www.cnblogs.com/grandyang/p/7865693.html
// 找到一个中枢点 左右两边的和相同
int pivotIndex(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int curSum = 0, n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (sum - nums[i] == 2 * curSum) return i;
        curSum += nums[i];
    }
    return -1;
}
}

int main () {
    using namespace two_sum;
    vector<int> v {2, 7, 11, 15};
    int target = 9;
    auto tmp = twoSum(v, target);

    for(auto i: tmp)
        cout << i << " ";
    cout << endl;


    {
        using namespace three_sum;
        vector<int> v {-4, -1, -1, 0, 1, 2};
        auto tmp = threeSum(v);

        printVector(tmp);

    }
    {
        using namespace three_sum;
        vector<int> v {-4, -1, 1, 2};
        auto tmp = threeSumClosest(v, 1);
        cout << tmp << endl;

        return 0;
    }

    {
        using namespace four_sum;
        vector<int> v {1, 0, -1, 0, -2, 2};
        auto tmp = fourSum (v, 0);
        printVector(tmp);
        return 0;
    }

    return 0;
}