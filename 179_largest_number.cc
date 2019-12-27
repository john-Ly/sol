// Given a list of non negative integers, arrange them such that they form the largest number.

// Example 1:

// Input: [10,2]
// Output: "210"
// Example 2:

// Input: [3,30,34,5,9]
// Output: "9534330"
// Note: The result may be very large, so you need to return a string instead of an integer.


// 自定义比较器可以 但是(直接按照首位大小进行比较  对于第二个例子 无法解释)
// 9 5 34 (34是组合出来最大的值)
    // 3
    // 30

// https://www.cnblogs.com/grandyang/p/4225047.html
string largestNumber(vector<int>& nums) {
    vector<string> arr;
    for(auto i : nums)
        arr.push_back(to_string(i));

    // 9和34，由于 934>349，所以9排在前面
    // 30 和3，由于 303<330，所以3排在 30 的前面
    sort(begin(arr), end(arr), [](string &s1, string &s2){ return s1+s2>s2+s1; });

    string res;
    for(auto s: arr)
        res+=s;
    return res[0] == '0' ? "0" : res;
    // while(res[0]=='0' && res.length()>1)
    //     res.erase(0,1);
    // return  res;
}