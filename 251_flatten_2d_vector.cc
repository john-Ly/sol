#include <vector>

// https://www.cnblogs.com/grandyang/p/5209621.html
namespace sol1 {
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for (auto a : vec2d) {
            v.insert(v.end(), a.begin(), a.end());
        }
    }

    // next 函数即为取出当前位置元素，坐标后移一位
    int next() { return v[i++];}
    bool hasNext() { return i < v.size(); }

private:
    vector<int> v;
    int i = 0;
};
}

namespace sol2 {
class Vector2D {
public:
    explicit Vector2D(vector<vector<int>>& vec2d)
        : v(vec2d), x(0), y(0) { }

    // next 函数即为取出当前位置元素，坐标后移一位
    int next() {
        hasNext();
        return v[x][y++];
    }

    bool hasNext() {
        // 可能存在一个为 empty rows 所以要使用while 而不是if
        while (x < v.size() && y == v[x].size()) {
            ++x;
            y = 0;
        }
        return x < v.size();
    }

private:
    vector<vector<int>> v;
    int x, y;
};
}