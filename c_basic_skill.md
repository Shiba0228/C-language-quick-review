# C Language Basics skills– README

本文件整理常見「最基本C語言技巧」，涵蓋語法、指標、記憶體、Undefined Behavior 等核心觀念。  
適用對象：臨時抱佛腳的大學生，剛退伍的可撥仔。

---

題目 1：基本輸出

```c
int a = 5;
printf("%d\n", a);
ans:5, %d 會以十進位整數格式輸出 int a 的值。

題目 2：遞增運算子與 Undefined Behavior|
int a = 3;
printf("%d %d\n", a++, ++a);
ans: Undefined Behavior
說明:
在同一個 expression中，a被多次修改，且沒有 sequence point（C11 之後稱為 unsequenced）

題目 3：for 迴圈陷阱
ans: 3
說明:
for 後面多了一個分號，形成空迴圈；i 會遞增到 3 才結束。

題目 4：sizeof 與陣列
int arr[10];
printf("%zu\n", sizeof(arr));
ans:10 * sizeof(int)（在常見 32/64-bit 平台上通常為 40）
說明:
sizeof(arr) 取得的是整個陣列所佔的位元組數，而非指標大小。

題目 5：指標與陣列關係
int arr[] = {1, 2, 3};
int *p = arr;
問題與答案
問題:arr == &arr[0]是否成立?
ans:成立（true，非 0）
問題:*(p + 1)的值?
ans:2
說明:
陣列在此情境會 decay 成指向第一個元素的指標。

題目 6：Pass by Value
void foo(int x)
{
    x = 100;
}

int main(void)
{
    int a = 10;
    foo(a);
    printf("%d\n", a);
}
問題:a的值為何?
ans:10
說明:
C 語言只有 pass by value，x 是 a 的複本。

題目 7：修改字串常值
char *s = "hello";
s[0] = 'H';

ans:Undefined Behavior
說明:
"hello" 是 string literal，通常位於唯讀記憶體，修改其內容屬於未定義行為。

題目 8：回傳區域變數位址
int *func(void)
{
    int x = 10;
    return &x;
}
ans:Undefined Behavior
說明:
x 是 stack 變數，function return 後生命週期結束，回傳其位址是未定義行為。

題目 9：const 宣告差異
const int *p;
int *const q;

ans:
const int *p:不能透過 p 修改值，p 本身可以改指向
int *const q:q 指向固定，可以修改 *q

題目 10：陣列作為函式參數
void foo(int arr[])
{
    printf("%zu\n", sizeof(arr));
}

ans: 32bit：4, 64bit：8
說明:
函式參數中的陣列會被調整為指標，sizeof(arr) 等於指標大小。

題目 11：字串複製與 buffer overflow
char buf[5];
strcpy(buf, "hello");

ans:有問題（buffer overflow）
說明:
"hello" 需要 6 bytes（含 \0），buf 空間不足，造成 overflow，屬於 Undefined Behavior。

題目 12：if 與 assignment
int a = 0;
if (a = 1) {
    printf("yes\n");
} else {
    printf("no\n");
}

ans:yes
說明:
a = 1 是指定運算，結果為 1（非 0），條件成立。
