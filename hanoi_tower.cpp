#include <iostream>
using namespace std;

// n: 盤子數量
// from: 起始柱子
// buffer: 輔助柱子
// to: 目標柱子
void hanoi(int n, char from, char buffer, char to) {
    // 終止條件：只剩下一個盤子時，直接搬移
    if (n == 1) {
        cout << "盤子 1 從 " << from << " 搬到 " << to << endl;
        return;
    }

    // 步驟一：將 n-1 個盤子從 from 搬到 buffer
    hanoi(n - 1, from, to, buffer);

    // 步驟二：將第 n 個盤子從 from 搬到 to
    cout << "盤子 " << n << " 從 " << from << " 搬到 " << to << endl;

    // 步驟三：將 n-1 個盤子從 buffer 搬到 to
    hanoi(n - 1, buffer, from, to);
}

int main() {
    int n;
    cout << "請輸入盤子數量: ";
    cin >> n;

    // 呼叫函式，假設柱子名稱為 A, B, C
    hanoi(n, 'A', 'B', 'C');

    return 0;
}
