// https://www.cnblogs.com/grandyang/p/4284205.html
// 思想非常巧妙(DNA 里面重复字符串较多)  可以用来进行压缩

// 返回原始字符串中 子串(10个连续字符)出现超过1次的候选者

// 后三位不同 可以用来区分字符
// A: 0100 0 001
// C: 0100 0 011
// G: 0100 0 111
// T: 0101 0 100
vector<string> findRepeatedDnaSequences1(string s) {
    vector<string> res;
    if (s.size() <= 10) return res;
    // mast提取出 后27为位
    int mask = 0x7ffffff, cur = 0;
    // 10个字符 后三位 组装成 30位 作为一个整数: key
    //                                 出现次数: value
    unordered_map<int, int> m;

    for (int i = 0; i < 9; ++i) {
        // 每次左移 腾出三个位给下一个字符
        cur = (cur << 3) | (s[i] & 7);
    }

    for (int i = 9; i < s.size(); ++i) {
        // 滑动窗口的作用
        cur = ((cur & mask) << 3) | (s[i] & 7);
        if (m.count(cur)) {
            if (m[cur] == 1) res.push_back(s.substr(i - 9, 10));
            ++m[cur];
        } else {
            m[cur] = 1;
        }
    }
    return res;
}


// hash_set 利用无重复特性
vector<string> findRepeatedDnaSequences2(string s) {
    unordered_set<string> res;
    unordered_set<int> st;
    int cur = 0;
    for (int i = 0; i < 9; ++i) cur = cur << 3 | (s[i] & 7);
    for (int i = 9; i < s.size(); ++i) {
        cur = ((cur & 0x7ffffff) << 3) | (s[i] & 7);
        if (st.count(cur)) res.insert(s.substr(i - 9, 10));
        else st.insert(cur);
    }
    return vector<string>(res.begin(), res.end());
}

vector<string> findRepeatedDnaSequences3(string s) {
    unordered_set<string> res, st;

    // 最原始的方法
    for (int i = 0; i + 9 < s.size(); ++i) {
        string t = s.substr(i, 10);
        if (st.count(t)) res.insert(t);
        else st.insert(t);
    }
    return vector<string>{res.begin(), res.end()};
}

// 4个字符 可以编码成 00, 01, 10, 11
vector<string> findRepeatedDnaSequences(string s) {
    unordered_set<string> res;
    unordered_set<int> st;
    static unordered_map<int, int> m{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    int cur = 0;
    for (int i = 0; i < 9; ++i) cur = cur << 2 | m[s[i]];
    for (int i = 9; i < s.size(); ++i) {
        //        窗口: 9*2 = 18 bit
        cur = ((cur & 0x3ffff) << 2) | (m[s[i]]);
        if (st.count(cur)) res.insert(s.substr(i - 9, 10));
        else st.insert(cur);
    }
    return vector<string>(res.begin(), res.end());
}