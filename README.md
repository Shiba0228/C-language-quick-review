# C / C++ 快速複習

這份筆記整理 junior 軟體／韌體工程師面試常見的 C、C++ 觀念題與 coding 題。建議每題先口頭說明思路、時間與空間複雜度，再開始寫程式；完成後主動補充邊界條件與測試案例。

> 韌體職缺通常更重視 C、記憶體、位元操作、`volatile`、中斷與硬體介面；軟體職缺則常問 C++、資料結構、演算法、物件生命週期與標準函式庫。

## 一、C 語言核心問題

1. **指標與陣列有什麼不同？**
   - 陣列是一段連續儲存空間，指標是存放位址的變數。
   - 陣列在多數運算式中會退化（decay）成首元素指標，但 `sizeof(array)` 與 `&array` 是常見例外。
   - 說明 `int *p`、`int a[10]`、`int (*p)[10]` 的差異。

2. **Stack、Heap、靜態儲存區有什麼不同？**
   - 比較生命週期、容量、配置方式與常見錯誤。
   - 延伸：區域變數、`static` 變數、字串常值通常放在哪裡？

3. **`malloc`、`calloc`、`realloc` 與 `free` 的差異？**
   - `malloc` 不初始化；`calloc` 會將配置的 bytes 清零。
   - `realloc` 可能搬移記憶體；失敗時原區塊仍有效，因此不要直接覆蓋原指標。
   - 延伸：memory leak、double free、use-after-free、dangling pointer。

4. **以下宣告分別代表什麼？**

   ```c
   const int *p;        // 指向唯讀 int 的指標
   int *const p2 = &x;  // 不可改指向的指標
   const int *const p3 = &x;
   ```

5. **`sizeof` 常見陷阱有哪些？**
   - `sizeof(array)` 是整個陣列的 byte 數；陣列傳入函式後，參數實際是指標。
   - `sizeof(char)` 保證為 1，但 1 byte 不一定固定為 8 bits，可查 `CHAR_BIT`。
   - 不應假設 `int`、`long` 或指標在所有平台上的大小。

6. **Structure padding 與 alignment 是什麼？**
   - 編譯器可能在成員間或尾端插入 padding，以符合 CPU 對齊需求。
   - 延伸：如何排列成員以節省空間？為何直接把 struct 當網路封包或硬體暫存器可能有問題？

7. **Undefined、unspecified、implementation-defined behavior 有何不同？**
   - 例：越界存取、signed integer overflow、修改字串常值、使用已釋放記憶體。
   - 經典題：`printf("%d %d", i++, ++i);` 為什麼不能依賴結果？

8. **`static` 與 `extern` 的用途？**
   - 函式內 `static` 改變生命週期；檔案層級 `static` 限制 linkage。
   - `extern` 宣告由其他位置定義的物件或函式。

9. **前置遞增 `++i` 與後置遞增 `i++` 的差異？**
   - 說明回傳值與副作用；對 class iterator，後置版本通常還需保留舊值。

10. **巨集（macro）有哪些陷阱？**

    ```c
    #define SQUARE(x) ((x) * (x))
    ```

    即使加括號，`SQUARE(i++)` 仍會重複計算參數。可比較 `inline` 函式、型別安全與除錯性。

更多基礎輸出判讀題見 [c_basic_skill.md](./c_basic_skill.md)。

## 二、C++ 核心問題

1. **Reference 與 pointer 有何不同？**
   - reference 宣告時通常必須綁定物件，不能重新綁定；pointer 可以是 `nullptr` 並改變指向。

2. **RAII 是什麼？為何重要？**
   - 將資源生命週期綁定物件生命週期，constructor 取得資源、destructor 釋放資源。
   - 可舉 `std::vector`、`std::string`、lock guard 與 smart pointer 為例。

3. **Rule of Three / Five / Zero 是什麼？**
   - 若類別自行管理資源，需思考 destructor、copy constructor、copy assignment，以及 C++11 的 move constructor、move assignment。
   - 最佳情況是使用標準容器與 RAII 類別達成 Rule of Zero。

4. **`unique_ptr`、`shared_ptr`、`weak_ptr` 如何選擇？**
   - 預設優先單一所有權 `unique_ptr`；確實需要共享所有權才用 `shared_ptr`。
   - `weak_ptr` 不增加引用計數，可觀察物件並協助打破循環引用。

5. **Overloading、overriding 與 name hiding 有何不同？**
   - 說明同作用域多載、衍生類別覆寫 virtual function，以及同名函式隱藏。
   - 使用 `override` 讓編譯器檢查函式簽章。

6. **為何 polymorphic base class 的 destructor 通常要是 `virtual`？**
   - 若透過 base pointer 刪除 derived object，而 base destructor 非 virtual，行為未定義。

7. **`std::vector` 與 linked list 的取捨？**
   - vector 連續、快取友善、支援 O(1) 隨機存取；擴容可能使 iterator/reference 失效。
   - 不要只背 Big-O，也要談記憶體區域性與實際情境。

8. **Copy 與 move semantics 的差異？**
   - move 可轉移資源，降低不必要的深複製；被 move 的物件仍須有效，但狀態通常未指定。

9. **Template 的用途與代價？**
   - 可建立型別安全的泛型程式；可能增加編譯時間、錯誤訊息複雜度與 binary size。

10. **Exception safety 有哪些基本保證？**
    - no-throw、strong guarantee、basic guarantee；韌體環境也可能禁用 exception，需能說明替代的錯誤處理方式。

## 三、韌體與嵌入式常見問題

1. **`volatile` 是什麼？它能保證 thread safety 或 atomicity 嗎？**
   - 告知編譯器每次都要真正讀寫該物件，常用於 memory-mapped I/O、ISR 與主程式共享的旗標。
   - 它不保證操作具原子性、執行順序或執行緒同步；多執行緒應使用 atomic 或同步機制。

2. **中斷服務常式（ISR）應注意什麼？**
   - 儘量短、不可阻塞、避免動態配置與耗時工作；正確處理共享資料、競態與中斷旗標。

3. **Polling 與 interrupt 的取捨？**
   - polling 簡單、延遲可預測但耗 CPU；interrupt 效率較高，但增加同步、優先序與除錯複雜度。

4. **Memory-mapped I/O 如何存取？**

   ```c
   #include <stdint.h>
   #define STATUS_REG (*(volatile uint32_t *)0x40000000u)
   ```

   位址與 register 寬度由晶片文件決定，並需留意 `volatile`、對齊與位元遮罩。

5. **Endianness 是什麼？**
   - little-endian 將最低有效 byte 放在低位址；big-endian 相反。
   - 網路協定、檔案格式與跨平台傳輸時不可直接假設 byte order。

6. **Bit manipulation 基本操作怎麼寫？**

   ```c
   reg |=  (1u << n);   // set bit
   reg &= ~(1u << n);   // clear bit
   reg ^=  (1u << n);   // toggle bit
   bit = (reg >> n) & 1u;
   ```

   延伸：避免移位量超出型別寬度，以及對 signed value 位移造成的可攜性問題。

7. **Race condition、critical section 與 deadlock 是什麼？**
   - 能說明 mutex、semaphore、atomic、關中斷等方法的適用範圍和代價。

8. **Watchdog timer 的用途？**
   - 系統必須定期餵狗；若程式卡死，watchdog 可觸發 reset。餵狗位置應能反映系統真的健康。

9. **UART、SPI、I2C 的差異？**
   - 比較線數、同步／非同步、全雙工／半雙工、位址、速度與常見應用。

10. **Button debounce 如何處理？**
    - 可用 RC/Schmitt trigger 等硬體方法，或以週期採樣、計時器與 state machine 做軟體去彈跳。

11. **Bootloader 通常負責什麼？**
    - 初始化最小硬體、驗證／載入 application、韌體更新、映像完整性與失敗回復。

12. **如何在資源受限環境改善可靠性？**
    - 避免不受控的動態配置、檢查長度與回傳值、使用固定寬度型別、設定 timeout、設計錯誤恢復路徑。

## 四、Coding 題清單

目前已完成的一題一檔 C++ 範例（全部放在專案根目錄）：

- [reverse_string.cpp](./reverse_string.cpp)：反轉字串
- [binary_search.cpp](./binary_search.cpp)：二分搜尋
- [two_sum.cpp](./two_sum.cpp)：Two Sum
- [valid_brackets.cpp](./valid_brackets.cpp)：括號配對
- [reverse_linked_list.cpp](./reverse_linked_list.cpp)：反轉 linked list
- [linked_list_cycle.cpp](./linked_list_cycle.cpp)：偵測 linked list cycle
- [count_set_bits.cpp](./count_set_bits.cpp)：計算 set bits
- [ring_buffer.cpp](./ring_buffer.cpp)：固定容量 circular buffer（C++17）
- [lru_cache.cpp](./lru_cache.cpp)：LRU cache（C++17）

### 基礎字串與陣列

1. 不用函式庫反轉字串，並處理空字串與 `NULL`。
2. 實作安全版 `strlen`、`strcpy` 或 `memcpy`，說明 API 如何傳入 buffer capacity。
3. 判斷字串是否為 palindrome。
4. 找出陣列的最大值、次大值；定義重複值如何處理。
5. 移除 sorted array 中的重複元素，回傳新長度。
6. 合併兩個 sorted arrays。
7. 使用 two pointers 解 Two Sum（先說明排序是否允許改變輸入）。
8. 實作 binary search，留意中點 overflow：`left + (right - left) / 2`。
9. 實作字串轉整數，處理正負號、非法字元與 overflow。
10. 實作 circular buffer / ring buffer 的 enqueue、dequeue、full、empty。

### Linked list、stack 與 queue

1. 反轉 singly linked list（iterative 與 recursive）。
2. 找 linked list 中點（slow/fast pointers）。
3. 判斷 linked list 是否有環，並找出環的入口。
4. 合併兩條 sorted linked lists。
5. 用兩個 stacks 實作 queue，或用兩個 queues 實作 stack。
6. 檢查括號 `()[]{}` 是否正確配對。

### 位元與韌體風格題

1. 計算 unsigned integer 中有幾個 1 bits（Brian Kernighan 方法）。
2. 判斷整數是否為 2 的次方。
3. 反轉 8-bit 或 32-bit 整數的 bit order。
4. 擷取或更新暫存器的某段 bit field。
5. 實作 8-bit checksum、XOR checksum；進階可問 CRC 概念。
6. 實作按鍵 debounce state machine。
7. 設計 non-blocking LED blinker，不使用 busy wait 或長時間 delay。
8. 設計 UART receive ring buffer，討論 ISR 與 main loop 的共享狀態。

### 遞迴與基本演算法

1. Fibonacci：先寫遞迴，再分析重複計算並改成 iterative / dynamic programming。
2. 河內塔：解釋 base case、遞迴關係及 O(2^n) 複雜度。範例見 [hanoi_tower.cpp](./hanoi_tower.cpp)。
3. 實作 insertion sort、selection sort、bubble sort，說明穩定性與複雜度。
4. 解釋並實作 quicksort 或 mergesort。
5. 印出對稱數字金字塔，測試 loop 與輸出控制。範例見 [number_pyramid.cpp](./number_pyramid.cpp)。

## 五、代表題與參考解法

### 1. 反轉 singly linked list

```c
typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *reverse_list(Node *head)
{
    Node *prev = NULL;

    while (head != NULL) {
        Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}
```

- 時間 O(n)，額外空間 O(1)。
- 測試：空 list、單一節點、兩個節點、多個節點。

### 2. 計算 set bits

```c
unsigned int count_set_bits(unsigned int value)
{
    unsigned int count = 0;

    while (value != 0u) {
        value &= value - 1u; // 每次清除最低位的 1
        ++count;
    }

    return count;
}
```

- 若共有 k 個 1 bits，迴圈執行 k 次。
- 使用 unsigned type 可避免 signed 位元運算的陷阱。

### 3. Circular buffer API 設計

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 16u

typedef struct {
    uint8_t data[BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t count;
} RingBuffer;

bool ring_push(RingBuffer *buffer, uint8_t value)
{
    if (buffer == NULL || buffer->count == BUFFER_SIZE) {
        return false;
    }

    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1u) % BUFFER_SIZE;
    ++buffer->count;
    return true;
}

bool ring_pop(RingBuffer *buffer, uint8_t *value)
{
    if (buffer == NULL || value == NULL || buffer->count == 0u) {
        return false;
    }

    *value = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1u) % BUFFER_SIZE;
    --buffer->count;
    return true;
}
```

- 所有操作皆為 O(1)。
- 若 ISR 與 main loop 同時操作，還需依平台處理 atomicity、memory ordering 與 critical section；只加 `volatile` 並不足夠。

## 六、面試官常見追問

寫完程式後，通常還會被問：

- 輸入是 `NULL`、空集合、極大值或重複值時會怎樣？
- 時間與額外空間複雜度是多少？能否換取不同的 time-space tradeoff？
- 是否有 integer overflow、buffer overflow、off-by-one 或資源洩漏？
- API 是否清楚表達 ownership、buffer size 與錯誤？
- 程式若跑在 8/16/32/64-bit 平台是否仍正確？
- 若函式會被多執行緒或 ISR 呼叫，是否安全？
- 你會如何測試？哪些案例最可能抓出 bug？

## 七、建議複習方式

1. 每題先在 1 分鐘內釐清輸入、輸出與限制。
2. 先說出簡單正確的解法，再談最佳化。
3. 寫 code 時持續說明 invariant、邊界條件與錯誤處理。
4. 寫完用 2～3 個案例手動 trace，包括至少一個極端案例。
5. 用 compiler warnings 與 sanitizer 練習找錯，例如 GCC/Clang 的 `-Wall -Wextra -Wpedantic`、AddressSanitizer 與 UndefinedBehaviorSanitizer。

面試不只看是否寫出答案，也會看你是否能把假設講清楚、發現風險，並寫出容易維護與測試的程式。
