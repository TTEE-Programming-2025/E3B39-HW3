#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD 2025
#define MAX_TRIES 3
#define SIZE 9
#define BOOKED_SEATS 10

char seats[SIZE][SIZE];  // '-'：空位，'*'：已預訂，'@'：建議位

void displayIntro() {
    printf("********************************************\n");
    printf("*              歡迎使用訂票系統            *\n");
    for (int i = 0; i < 18; i++)
        printf("*                                          *\n");
    printf("********************************************\n");
    printf("請按 Enter 鍵繼續...\n");
    getchar();
}

void initSeats() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            seats[i][j] = '-';

    int count = 0;
    while (count < BOOKED_SEATS) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (seats[r][c] == '-') {
            seats[r][c] = '*';
            count++;
        }
    }
}

void showMainMenu() {
    printf("----------[Booking System]----------\n");
    printf("| a. Available seats               |\n");
    printf("| b. Arrange for you              |\n");
    printf("| c. Choose by yourself           |\n");
    printf("| d. Exit                         |\n");
    printf("------------------------------------\n");
}

void showSeats() {
    printf(" \\123456789\n");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
}

void clearScreen() {
    system("cls"); // Windows 用 cls，Mac/Linux 用 clear
}

void clearSuggestedSeats() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (seats[i][j] == '@')
                seats[i][j] = '-';
}

int suggestSeats(int people) {
    clearSuggestedSeats();
    if (people >= 1 && people <= 3) {
        // 試圖找一排連續空位
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j <= SIZE - people; j++) {
                int found = 1;
                for (int k = 0; k < people; k++) {
                    if (seats[i][j + k] != '-') {
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    for (int k = 0; k < people; k++)
                        seats[i][j + k] = '@';
                    return 1;
                }
            }
        }
    } else if (people == 4) {
        // 優先找一排連續4位
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j <= SIZE - 4; j++) {
                if (seats[i][j] == '-' && seats[i][j + 1] == '-' &&
                    seats[i][j + 2] == '-' && seats[i][j + 3] == '-') {
                    for (int k = 0; k < 4; k++)
                        seats[i][j + k] = '@';
                    return 1;
                }
            }
        }
        // 其次找兩排各兩位相鄰（垂直連續）
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j <= SIZE - 2; j++) {
                if (seats[i][j] == '-' && seats[i][j + 1] == '-' &&
                    seats[i + 1][j] == '-' && seats[i + 1][j + 1] == '-') {
                    seats[i][j] = '@';
                    seats[i][j + 1] = '@';
                    seats[i + 1][j] = '@';
                    seats[i + 1][j + 1] = '@';
                    return 1;
                }
            }
        }
    }
    return 0;
}

void arrangeForUser() {
    int people;
    printf("請輸入需要的座位數量 (1~4)：");
    scanf("%d", &people);

    if (people < 1 || people > 4) {
        printf("人數不合法，請重新選擇功能。\n");
        return;
    }

    if (!suggestSeats(people)) {
        printf("找不到可安排的連續座位，請稍後再試。\n");
        return;
    }

    showSeats();
    printf("您是否滿意這些座位安排？(y/n)：");
    char response;
    scanf(" %c", &response);
    if (response == 'y' || response == 'Y') {
        // 將 @ 變成 *
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (seats[i][j] == '@')
                    seats[i][j] = '*';
        printf("座位已為您保留！按任意鍵返回主選單...\n");
    } else {
        clearSuggestedSeats();
        printf("已取消安排，按任意鍵返回主選單...\n");
    }
    getchar(); // 清掉換行
    getchar(); // 等待鍵入
    clearScreen();
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

    clearScreen();
    initSeats();

    while (1) {
        showMainMenu();
        printf("請選擇功能 (a/b/c/d)：");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                showSeats();
                printf("按任意鍵返回主選單...\n");
                getchar(); getchar();
                clearScreen();
                break;
            case 'b':
                arrangeForUser();
                break;
            case 'c':
                printf("手動選位尚未實作。\n");
                break;
            case 'd':
                printf("感謝使用，再見！\n");
                return 0;
            default:
                printf("選項錯誤，請重新輸入。\n");
        }
    }
}
