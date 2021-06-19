## About `class`
C++是一個物件導向的程式語言，一般的寫程式是給電腦下達一個一個指令，然而當程式碼越來越長時就會造成閱讀困難。
物件導向程式中加入「物件」這個概念，每個物件有自己的「功能」，例如今天你要煮飯：
+ 如果只有鍋子，你就得一步一步把煮飯的步驟寫下來。
+ 如果有「電鍋」這個**物件**，電鍋有一個「煮飯」的**功能**，你只要呼叫 `電鍋.煮飯()` 這個function，飯就會煮好了

你不需要知道電鍋是怎麼煮飯的，僅僅需要會操作電鍋就好。

<br><br/>
## 遊戲基本流程
我們都知道遊戲基本流程是：偵測使用者輸入→根據輸入變更物件→繪出畫面
<br><br/>
我把程式碼分成 `Screen` 與 `Snake` 兩個 class，
`Screen`負責畫面輸出、控制每一個像素的內容；`Snake`負責接收玩家輸入、改變蛇的狀態

## 重要函式簡介
```cpp
typedef pair<int, int> POS;          //這裡用pair容器儲存畫面上的座標XY，定義為POS

class Screen{
    void print();                    //輸出畫面到終端

    void setXYC();                   //更改XY座標的字元

    char getXYChar();                //返回XY座標的字元，用於蛇的碰撞判斷
};
class Snake{
    bool move();                     //蛇移動的主程式，包含偵測使用者輸入、更改蛇的位置

    bool isAlive();                  //判斷蛇頭是否撞牆、撞身體

    POS GenFood();                   //生成一個食物，並返回食物的位置
};
```
<br><br/>


## 蛇的主程式 `Snake::move();`
這邊我參考了 [這篇文章](https://www.programmersought.com/article/92824465319/) 的概念，使用 **LinkedList** 儲存蛇的XY座標

![1](https://github.com/SoySauceGGD/greedy-snake/blob/main/Pictures/1.PNG?raw=true)

當蛇往右移動一格移動後

![2](https://github.com/SoySauceGGD/greedy-snake/blob/main/Pictures/2.PNG?raw=true)

會產生新的蛇頭，且舊蛇尾刪掉，蛇就完成一次移動
<br><br/>
仔細會發現觀察蛇的XY座標在 **LinkedList** 裡面儲存時只會頭進尾出，剛好符合 `std::queue()`先進先出的特性，
因此我嘗試使用 `std::queue()`來儲存蛇的資料

## 遊戲流程圖

![3](https://github.com/SoySauceGGD/greedy-snake/blob/main/Pictures/3.PNG?raw=true)


## 註
+ 程式碼放在 `main.cpp` ，直接編譯後即可遊玩
+ 輸入法記得切成英文
+ 程式有使用`<conio.h>` , `<windows.h>` 標頭檔，所以只能在 **Windows** 平台運行
+ 已測試可以成功編譯運行的編譯器：
  + **MinGW-W64 7.3.0 (x86_64-posix-seh-rev0)**
  + **Code::Blocks 20.03-mingw** 自帶的MinGW編譯器 **(version 8.1.0, 32/64 bit, SEH)**


## Plan
+ 學習Linked list　✔
+ 創建一張地圖　✔
+ 基本遊戲架構 ✔
+ 持續偵測輸入(不須按Enter) ✔
+ 簡易菜單✔


## Problemes / Glitches
| Problems | Solution | Solved ? |
| -------- | -------- | -------- |
| 畫面閃爍 | 使用`std::flush` , `ios::sync_with_stdio(false)` 手動清除緩衝區 | ✔ |
| 玩到後面卡死 | `genFood()`函式邏輯錯誤 | ✔ |


## 參考資料
1. [Class](https://ithelp.ithome.com.tw/articles/10230401)
1. [Number generator](https://blog.gtwang.org/programming/cpp-random-number-generator-and-probability-distribution-tutorial/)
1. [Set](http://c.biancheng.net/view/538.html)
1. [Queue](https://shengyu7697.github.io/std-queue/)
1. [Snake](https://www.programmersought.com/article/92824465319/)
1. [持續輸入](https://blog.csdn.net/gggg_ggg/article/details/45956719)
