#include <stdio.h>
#include <stdlib.h>

#define PASSWORD 2025
#define MAX_TRIES 3

void displayIntro() {
    // 顯示個人風格畫面（恰好 20 行）
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
    getchar(); // 等待使用者按 Enter
}

int main() {
    int input, tries = 0;

    displayIntro(); // 顯示畫面

    while (tries < MAX_TRIES) {
        printf("請輸入 4 位數密碼：");
        scanf("%d", &input);

        if (input == PASSWORD) {
            printf("\n登入成功！歡迎進入系統。\n");
            // 下一步可呼叫主選單函式
            // showMainMenu();
            return 0;
        } else {
            tries++;
            printf("密碼錯誤，您還有 %d 次機會。\n", MAX_TRIES - tries);
        }
    }

    printf("\n錯誤次數過多，系統即將結束。\n");
    return 1;
}
