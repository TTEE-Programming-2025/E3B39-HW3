#include <stdio.h>
#include <stdlib.h>

#define PASSWORD 2025
#define MAX_TRIES 3

// 顯示個人風格畫面（20 行）
void displayIntro() {
    printf("********************************************\n");
    printf("1     .----------.                         \n");
    printf("2   .'            `.                       \n");
    printf("3  /   .--------. r  \\                    \n");
    printf("4 ;   /          \\   ;                   \n");
    printf("5 |  ;            ;  |                   \n");
    printf("6 ;   \\          /   ;                   \n");
    printf("7  \\   `--------'   /                    \n");
    printf("8   `.            .'                     \n");
    printf("9     `-........-'                       \n");
    printf("10                                         \n");
    printf("11       ( o.o )                          \n");
    printf("12                                         \n");
    printf("13       ( owo )                          \n");
    printf("14                                         \n");
    printf("15       ( ^_^ )                          \n");
    printf("16                                         \n");
    printf("17                                         \n");
    printf("18                                         \n");
    printf("19                                         \n");
    printf("20*****************************************\n");
    printf("請按 Enter 鍵繼續...\n");
    getchar(); // 等待 Enter 鍵
}

// 顯示主選單
void showMainMenu() {
    // 清除螢幕（Windows 使用 cls，Linux/Mac 使用 clear）
    system("cls"); // 若使用 macOS/Linux 請改為 system("clear");

    printf("----------[Booking System]----------\n");
    printf("| a. Available seats                |\n");
    printf("| b. Arrange for you               |\n");
    printf("| c. Choose by yourself            |\n");
    printf("| d. Exit                          |\n");
    printf("------------------------------------\n");
}

int main() {
    int input, tries = 0;

    displayIntro(); // 顯示個人風格畫面

    // 密碼輸入最多三次
    while (tries < MAX_TRIES) {
        printf("請輸入4位數密碼：");
        scanf("%d", &input);

        if (input == PASSWORD) {
            printf("\n登入成功！歡迎進入系統。\n");
            getchar(); // 吃掉換行符號
            getchar(); // 等待使用者按 Enter 再清除畫面
            showMainMenu(); // 顯示主選單
            return 0;
        } else {
            tries++;
            printf("密碼錯誤，您還有 %d 次機會。\n", MAX_TRIES - tries);
        }
    }

    // 密碼錯誤三次
    printf("\n錯誤次數過多，系統即將結束。\n");
    return 1;
}
