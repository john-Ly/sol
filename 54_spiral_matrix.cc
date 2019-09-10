#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


/*
  @TODO
  二维矩阵: 主对角线 副对角线 上三角 下三角
 */

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

// https://leetcode.com/problems/spiral-matrix/discuss/20573/A-concise-C%2B%2B-implementation-based-on-Directions
// 顺时针方向移动
vector<int> spiralOrderClockwise(vector<vector<int>>& matrix) {
    // 'right->down->left->up' r  c
    vector<vector<int> > dirs{{0, 1},
                              {1, 0},
                              {0, -1},
                              {-1, 0}};
    vector<int> res;
    int nr = matrix.size();     if (nr == 0) return res;
    int nc = matrix[0].size();  if (nc == 0) return res;

    // horizontal movements, the number of shifts follows:{5, 4, 3}
    // vertical movements follows {2, 1, 0}.
    vector<int> steps{nc, nr-1};

    int iDir = 0;   // index of direction.
    int ir = 0, ic = -1;    // initial position (方便计算)

    // iDir: 表示dirs矩阵 [4][2]  行下标的选择
    // iDir%2 表示是水平方向(0)移动, 还是垂直方向(1)移动
    while (steps[iDir%2]) {
        for (int i = 0; i < steps[iDir%2]; ++i) {
            ir += dirs[iDir][0];
            ic += dirs[iDir][1];
            res.push_back(matrix[ir][ic]);
        }
        steps[iDir%2]--;
        iDir = (iDir + 1) % 4;
    }
    return res;
}

vector<int> spiralOrderCounterClockwise(vector<vector<int>>& matrix) {
    // 'down->right->up->left' r  c
    vector<vector<int> > dirs{{1, 0},
                              {0, 1},
                              {-1, 0},
                              {0, -1}};
    vector<int> res;
    int nr = matrix.size();     if (nr == 0) return res;
    int nc = matrix[0].size();  if (nc == 0) return res;

    // horizontal movements, the number of shifts follows:{5, 4, 3}
    // vertical movements follows {2, 1, 0}.
    vector<int> steps{nr, nc-1};

    int iDir = 0;   // index of direction.
    int ir = -1, ic = 0;    // initial position (方便计算)

    // iDir: 表示dirs矩阵 [4][2]  行下标的选择
    // iDir%2 表示是水平方向(行-0)移动, 还是垂直方向(列-1)移动
    while (steps[iDir%2]) {
        for (int i = 0; i < steps[iDir%2]; ++i) {
            ir += dirs[iDir][0];
            ic += dirs[iDir][1];
            res.push_back(matrix[ir][ic]);
        }
        steps[iDir%2]--;
        iDir = (iDir + 1) % 4;
    }
    return res;
}

// 由内向外 起始座标是(1, 1) 需要处理循环 矩阵的最后一个空可能越界访问
vector<vector<int>> interSpiralOrderClockwise(int n) {
    if(n<1) return {};
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    // 'right->down->left->up' r  c
    vector<vector<int> > dirs{{0, 1},
                              {1, 0},
                              {0, -1},
                              {-1, 0}};
    //                c  r
    vector<int> steps{1, 1};
    int start = 1;
    // initial position 由内向外 从水平向右开始(可以自定义)
    int ir = n%2 ? (n/2): (n/2-1);
    int ic = ir;
    matrix[ir][ic] = start;
    int iDir = 0;   // index of direction.
    /*
        21  22  23  24  25
        20  7   8   9   10
        19  6   1   2   11
        18  5   4   3   12
        17  16  15  14  13
    */
    while (steps[iDir%2] < n+1 ) {
        if(steps[0] == n+1) break;  // 最后一次 steps[0]已经增加到n+1 如果不设置会导致 超级循环

        for (int i = 0; i<steps[iDir%2]; ++i) {
            ir += dirs[iDir][0];
            ic += dirs[iDir][1];
            // cout << ir << " " << ic << endl;
            if(ic==n) break; // 这要针对方向进行调整
            matrix[ir][ic] = ++start;
        }
        steps[iDir%2]++;
        iDir = (iDir + 1) % 4;
    }

    return matrix;
}

// 由外向内 其实座标是(0, -1)/ (-1, 0) 虚拟座标 循环易于控制 不会出现越界现象
vector<vector<int>> outerSpiralOrderClockwise(int n) {
    if(n<1) return {};
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    // 'right->down->left->up' r  c
    vector<vector<int> > dirs{{0, 1},
                              {1, 0},
                              {0, -1},
                              {-1, 0}};
    // horizontal movements, the number of shifts follows:{5, 4, 3}
    // vertical movements follows {2, 1, 0}.
    vector<int> steps{n, n-1};

    int start = 0;
    int iDir = 0;   // index of direction.
    int ir = 0, ic = -1;    // initial position (方便计算)

    // iDir: 表示dirs矩阵 [4][2]  行下标的选择
    // iDir%2 表示是水平方向(0)移动, 还是垂直方向(1)移动
    while (steps[iDir%2]) {
        for (int i = 0; i < steps[iDir%2]; ++i) {
            ir += dirs[iDir][0];
            ic += dirs[iDir][1];
            matrix[ir][ic] = ++start;
        }
        steps[iDir%2]--;
        iDir = (iDir + 1) % 4;
    }
    return matrix;
}

int main() {
    vector<vector<int>> v = { { 1, 2, 3, 4 },
                              { 5, 6, 7, 8 },
                              { 9,10,11,12 } };

    printVector(v);
    for( auto i: spiralOrderClockwise(v) ) cout << i << " ";
    cout << endl;

    for( auto i: spiralOrderCounterClockwise(v) ) cout << i << " ";
    cout << endl;

    auto ma = interSpiralOrderClockwise(5);
    printVector(ma);

    auto m = outerSpiralOrderClockwise(3);
    printVector(m);

    return 0;
}