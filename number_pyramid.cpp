#include <iostream>
//number pyramid
int main()
{
    int n = 5;  // total layers

    for (int i = 1; i <= n; ++i) {

        // 前導空白
        for (int space = 0; space < n - i; ++space) {
            std::cout << ' ';
        }

        // 遞增數字
        for (int num = 1; num <= i; ++num) {
            std::cout << num;
        }

        // 遞減數字
        for (int num = i - 1; num >= 1; --num) {
            std::cout << num;
        }

        std::cout << '\n';
    }

    return 0;
}
