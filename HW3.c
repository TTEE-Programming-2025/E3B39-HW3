#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 9

char seats[SIZE][SIZE];  // 9x9座位表

// 清除螢幕 (依平台而異)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// 顯示座位表
void showSeats(char mark) {
    printf("\\123456789\n");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
}

// 檢查座位是否已被選取
int isOccupied(int row, int col) {
    return seats[row][col] == '*' || seats[row][col] == '@';
}

// 處理手動選位
void chooseSeats() {
    char input[100];
    int row, col;
    int done = 0;

    while (!done) {
        clearScreen();
        showSeats('@');
        printf("請輸入座位 (例如 1-2 表示第1列第2行)，輸入 done 結束選擇：\n");
        printf("=> ");
        scanf("%s", input);

        if (strcmp(input, "done") == 0) {
            done = 1;
        } else if (sscanf(input, "%d-%d", &row, &col) == 2 &&
                   row >= 1 && row <= SIZE &&
                   col >= 1 && col <= SIZE) {
            row--; col--;
            if (isOccupied(row, col)) {
                printf("錯誤：座位 %d-%d 已被選取！請重新輸入。\n", row + 1, col + 1);
                system("pause");
            } else {
                seats[row][col] = '@';
            }
        } else {
            printf("格式錯誤，請輸入如 1-2 這樣的格式。\n");
            system("pause");
        }
    }

    clearScreen();
    printf("您選擇的座位如下：\n");
    showSeats('@');
    printf("請確認以上座位無誤，按任意鍵繼續...\n");
    getchar(); getchar();

    // 確認後轉為已訂位
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (seats[i][j] == '@') {
                seats[i][j] = '*';
            }
        }
    }

    clearScreen();
}
