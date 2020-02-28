// @SEE dijstra + bfs
// bfs 搜索 找到最短距离
// https://leetcode.com/problems/word-ladder/solution/
// https://www.cnblogs.com/grandyang/p/4539768.html

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // 加快查找速度
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord)) return 0;

    unordered_map<string, int> pathCnt {{beginWord, 1}};
    queue<string> q {{beginWord}};
    while (!q.empty()) {
        string word = q.front(); q.pop();
        for (int i = 0; i < word.size(); ++i) {   // 针对每一位进行替换
            string newWord = word;
            for (char ch = 'a'; ch <= 'z'; ++ch) {// 26字母
                newWord[i] = ch;
                if (wordSet.count(newWord) && newWord == endWord) return pathCnt[word] + 1;
                if (wordSet.count(newWord) && !pathCnt.count(newWord)) {
                    q.push(newWord);
                    pathCnt[newWord] = pathCnt[word] + 1;
                }
            }
        }
    }
    return 0;
}