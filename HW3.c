#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD 2025
#define MAX_TRIES 3
#define SIZE 9
#define BOOKED_SEATS 10

char seats[SIZE][SIZE]; // 9x9 座位表

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
    getchar(); // 等待使用者按 Enter
}

// 初始化座位，並隨機標記 10 個已預訂座位（'*'）
void initSeats() {
    int i, j, count = 0;
    srand(time(NULL));
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            seats[i][j] = '-';

    while (count < BOOKED_SEATS) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (seats[r][c] != '*') {
            seats[r][c] = '*';
            count++;
        }
    }
}

// 顯示主選單
void showMainMenu() {
    printf("----------[Booking System]----------\n");
    printf("| a. Available seats               |\n");
    printf("| b. Arrange for you              |\n");
    printf("| c. Choose by yourself           |\n");
    printf("| d. Exit                         |\n");
    printf("------------------------------------\n");
}

// 顯示座位圖
void showSeats() {
    int i, j;
    printf(" \\123456789\n"); // 上排座位號
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", i + 1); // 左側列號
        for (j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
    printf("按任意鍵返回主選單...\n");
    getchar(); // 清掉上次輸入的 Enter
    getchar(); // 等待按鍵
    system("cls"); // Windows，Mac/Linux 請改為 system("clear")
}

int main() {
    int input, tries = 0;
    char choice;

    displayIntro();

    while (tries < MAX_TRIES) {
        printf("請輸入 4 位數密碼：");
        scanf("%d", &input);

        if (input == PASSWORD) {
            break;
        } else {
            tries++;
            printf("密碼錯誤，還有 %d 次機會。\n", MAX_TRIES - tries);
        }
    }

    if (tries == MAX_TRIES) {
        printf("錯誤次數過多，系統結束。\n");
        return 1;
    }

    // 密碼正確
    system("cls");
    initSeats();

    while (1) {
        showMainMenu();
        printf("請選擇功能 (a/b/c/d)：");
        scanf(" %c", &choice); // 前面有空格以忽略前次輸入的 Enter

        switch (choice) {
            case 'a':
                showSeats();
                break;
            case 'b':
                printf("尚未實作自動分配功能。\n");
                break;
            case 'c':
                printf("尚未實作手動選擇功能。\n");
                break;
            case 'd':
                printf("感謝使用，再見！\n");
                return 0;
            default:
                printf("無效的選項，請重新輸入。\n");
        }
    }

    return 0;
}
