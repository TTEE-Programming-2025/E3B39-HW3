#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 9
#define MAX_ATTEMPTS 3

char seats[SIZE][SIZE];

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    printf("\n請按 Enter 鍵繼續...");
    getchar();
    getchar();
}

void printWelcomeScreen() {
    clearScreen();
    for (int i = 0; i < 10; i++) printf("********************************************\n");
    printf("*                                          *\n");
    printf("*     ( ^_^ )  歡迎使用訂票系統             *\n");
    printf("*     ( o_o )  請輸入四位數密碼登入         *\n");
    printf("*     ( owo )                                *\n");
    printf("*                                          *\n");
    for (int i = 0; i < 10; i++) printf("********************************************\n");
    printf("\n");
}

int login() {
    int password;
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        printf("請輸入四位數密碼: ");
        scanf("%d", &password);
        if (password == 2025) {
            printf("\n登入成功！\n");
            waitForEnter();
            return 1;
        } else {
            printf("密碼錯誤！\n");
            attempts++;
        }
    }
    printf("連續錯誤三次，系統結束！\n");
    return 0;
}

void initSeats() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            seats[i][j] = '-';

    srand(time(NULL));
    int count = 0;
    while (count < 10) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (seats[r][c] == '-') {
            seats[r][c] = '*';
            count++;
        }
    }
}

void showSeats() {
    printf("\\123456789\n");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
}

void availableSeats() {
    clearScreen();
    printf("現有座位表如下：\n");
    showSeats();
    waitForEnter();
}

void arrangeSeats() {
    int n;
    printf("請輸入需要的座位數 (1~4): ");
    scanf("%d", &n);
    if (n < 1 || n > 4) {
        printf("輸入錯誤\n");
        return;
    }
    // 簡化版本: 找到第一個可放的座位，標示為 @
    int placed = 0;
    for (int i = 0; i < SIZE && !placed; i++) {
        for (int j = 0; j <= SIZE - n; j++) {
            int ok = 1;
            for (int k = 0; k < n; k++) {
                if (seats[i][j + k] != '-') {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                for (int k = 0; k < n; k++)
                    seats[i][j + k] = '@';
                placed = 1;
                break;
            }
        }
    }
    if (placed) {
        clearScreen();
        showSeats();
        char confirm;
        printf("是否滿意安排？(y/n): ");
        scanf(" %c", &confirm);
        if (confirm == 'y' || confirm == 'Y') {
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    if (seats[i][j] == '@') seats[i][j] = '*';
        } else {
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    if (seats[i][j] == '@') seats[i][j] = '-';
        }
    } else {
        printf("目前找不到合適的座位安排。\n");
    }
    waitForEnter();
}

void chooseByYourself() {
    char input[10];
    int row, col;
    while (1) {
        clearScreen();
        showSeats();
        printf("請輸入座位 (如 1-2)，輸入 done 完成：");
        scanf("%s", input);
        if (strcmp(input, "done") == 0) break;
        if (sscanf(input, "%d-%d", &row, &col) == 2 && row >= 1 && row <= 9 && col >= 1 && col <= 9) {
            row--; col--;
            if (seats[row][col] == '-') {
                seats[row][col] = '@';
            } else {
                printf("該座位已被預訂！\n");
                waitForEnter();
            }
        } else {
            printf("格式錯誤，請重新輸入！\n");
            waitForEnter();
        }
    }
    clearScreen();
    showSeats();
    printf("是否確定這些座位？按任意鍵繼續...");
    getchar(); getchar();
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (seats[i][j] == '@') seats[i][j] = '*';
    clearScreen();
}

int main() {
    printWelcomeScreen();
    if (!login()) return 0;
    initSeats();
    char choice;
    while (1) {
        clearScreen();
        printf("----------[Booking System]----------\n");
        printf("| a. Available seats               |\n");
        printf("| b. Arrange for you              |\n");
        printf("| c. Choose by yourself           |\n");
        printf("| d. Exit                         |\n");
        printf("------------------------------------\n");
        printf("請選擇: ");
        scanf(" %c", &choice);
        switch (choice) {
            case 'a':
                availableSeats();
                break;
            case 'b':
                arrangeSeats();
                break;
            case 'c':
                chooseByYourself();
                break;
            case 'd': {
                char confirm;
                do {
                    printf("Continue? (y/n): ");
                    scanf(" %c", &confirm);
                    if (confirm == 'y' || confirm == 'Y') break;
                    else if (confirm == 'n' || confirm == 'N') return 0;
                    else printf("輸入錯誤，請重新輸入。\n");
                } while (1);
                break;
            }
            default:
                printf("選項錯誤！\n");
                waitForEnter();
        }
    }
    return 0;
}
