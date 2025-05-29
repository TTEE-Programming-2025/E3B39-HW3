#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 座位表大小
#define ROWS 9
#define COLS 9

// 密碼設定
#define PASSWORD 2025

// 函式宣告
void showIntro();
int verifyPassword();
void clearScreen();
void showMenu();
void initSeats(char seats[ROWS][COLS]);
void showSeats(char seats[ROWS][COLS]);
void pauseForKey();
void arrangeSeats(char seats[ROWS][COLS]);
void userChooseSeats(char seats[ROWS][COLS]);
int askContinue();
int isValidSeatFormat(const char *input);
int seatTaken(char seats[ROWS][COLS], int row, int col);
int tryArrangeSeats(char seats[ROWS][COLS], int need, int pos[4][2]);

int main() {
    char seats[ROWS][COLS];
    srand((unsigned int)time(NULL));

    // 顯示個人風格畫面，並驗證密碼
    showIntro();
    if (!verifyPassword()) {
        printf("錯誤超過三次，系統結束。\n");
        return 0;
    }
    printf("密碼正確，歡迎進入訂票系統！\n");
    printf("請按 Enter 繼續...");
    getchar();

    // 初始化座位表(隨機10個訂位 '*')
    initSeats(seats);

    while (1) {
        clearScreen();
        showMenu();

        char choice;
        printf("請輸入選項(a/b/c/d): ");
        scanf(" %c", &choice);
        getchar(); // 吃掉換行

        if (choice == 'a') {
            clearScreen();
            showSeats(seats);
            pauseForKey();
        }
        else if (choice == 'b') {
            clearScreen();
            arrangeSeats(seats);
        }
        else if (choice == 'c') {
            clearScreen();
            userChooseSeats(seats);
        }
        else if (choice == 'd') {
            // 詢問是否重啟
            if (askContinue()) {
                continue; // 回主選單
            }
            else {
                printf("系統結束，感謝使用！\n");
                break; // 離開程式
            }
        }
        else {
            printf("無效選項，請重新輸入。\n");
            printf("請按 Enter 繼續...");
            getchar();
        }
    }

    return 0;
}

// 顯示個人風格畫面(至少20行)
void showIntro() {
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*        Welcome to Booking System         *\n");
    printf("*                                          *\n");
    printf("*      ----------------------------        *\n");
    printf("*     |   Seat Booking Management   |      *\n");
    printf("*      ----------------------------        *\n");
    printf("*                                          *\n");
    printf("*           Designed by YourName           *\n");
    printf("*                                          *\n");
    printf("*    Please enter your 4-digit password    *\n");
    printf("*                                          *\n");
    printf("*           (default password: 2025)       *\n");
    printf("*                                          *\n");
    printf("*                                          *\n");
    printf("*    **********************************    *\n");
    printf("*    *                                *    *\n");
    printf("*    *        [Press Enter to start]  *    *\n");
    printf("*    **********************************    *\n");
    printf("*                                          *\n");
    printf("********************************************\n");
    getchar();
}

// 密碼驗證，錯三次結束回傳0，正確回傳1
int verifyPassword() {
    int attempt = 0;
    int input;
    while (attempt < 3) {
        printf("請輸入4位數密碼: ");
        if (scanf("%d", &input) != 1) {
            // 非數字輸入處理
            while (getchar() != '\n'); // 清除緩衝
            printf("輸入錯誤，請輸入數字！\n");
            attempt++;
            continue;
        }
        if (input == PASSWORD) {
            return 1;
        } else {
            printf("密碼錯誤！\n");
            attempt++;
        }
    }
    return 0;
}

// 清螢幕（簡單版）
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 顯示主選單
void showMenu() {
    printf("----------[Booking System]----------\n");
    printf("| a. Available seats                |\n");
    printf("| b. Arrange for you                |\n");
    printf("| c. Choose by yourself             |\n");
    printf("| d. Exit                         |\n");
    printf("------------------------------------\n");
}

// 初始化座位表，隨機產生10個已被訂座 '*'
void initSeats(char seats[ROWS][COLS]) {
    // 全部初始化為'-'
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            seats[r][c] = '-';

    int booked = 0;
    while (booked < 10) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (seats[r][c] == '-') {
            seats[r][c] = '*';
            booked++;
        }
    }
}

// 顯示座位表，格式符合題目要求
void showSeats(char seats[ROWS][COLS]) {
    printf("\\123456789\n");
    for (int r = ROWS - 1; r >= 0; r--) {
        printf("%d", r + 1);
        for (int c = 0; c < COLS; c++) {
            printf("%c", seats[r][c]);
        }
        printf("\n");
    }
}

// 等待使用者按任意鍵繼續
void pauseForKey() {
    printf("請按任意鍵繼續...");
    getchar();
}

// 電腦自動安排座位，並顯示'@'標示建議座位
void arrangeSeats(char seats[ROWS][COLS]) {
    int need;
    printf("請輸入需要幾個座位（1~4）: ");
    if (scanf("%d", &need) != 1 || need < 1 || need > 4) {
        while (getchar() != '\n');
        printf("輸入錯誤，必須是1~4的數字！\n");
        printf("請按 Enter 返回主選單...");
        getchar();
        return;
    }
    getchar();

    // 複製目前座位狀態，方便標示@座位
    char tempSeats[ROWS][COLS];
    memcpy(tempSeats, seats, sizeof(tempSeats));

    int pos[4][2] = {0}; // 紀錄安排座位位置
    int arranged = 0;

    // 1~3位: 尋找連續座位
    if (need >= 1 && need <= 3) {
        // 找連續座位
        for (int r = 0; r < ROWS && !arranged; r++) {
            for (int c = 0; c <= COLS - need; c++) {
                int can = 1;
                for (int k = 0; k < need; k++) {
                    if (tempSeats[r][c+k] != '-') {
                        can = 0;
                        break;
                    }
                }
                if (can) {
                    for (int k = 0; k < need; k++) {
                        tempSeats[r][c+k] = '@';
                        pos[k][0] = r;
                        pos[k][1] = c + k;
                    }
                    arranged = 1;
                    break;
                }
            }
        }
    }
    else if (need == 4) {
        // 4位: 先找同列4連座
        for (int r = 0; r < ROWS && !arranged; r++) {
            for (int c = 0; c <= COLS - 4; c++) {
                int can = 1;
                for (int k = 0; k < 4; k++) {
                    if (tempSeats[r][c+k] != '-') {
                        can = 0;
                        break;
                    }
                }
                if (can) {
                    for (int k = 0; k < 4; k++) {
                        tempSeats[r][c+k] = '@';
                        pos[k][0] = r;
                        pos[k][1] = c + k;
                    }
                    arranged = 1;
                    break;
                }
            }
        }
        // 若找不到，找前後兩列各兩位
        if (!arranged) {
            for (int r = 0; r < ROWS - 1 && !arranged; r++) {
                for (int c = 0; c <= COLS - 2; c++) {
                    if (tempSeats[r][c] == '-' && tempSeats[r][c + 1] == '-' &&
                        tempSeats[r + 1][c] == '-' && tempSeats[r + 1][c + 1] == '-') {
                        tempSeats[r][c] = '@'; tempSeats[r][c + 1] = '@';
                        tempSeats[r + 1][c] = '@'; tempSeats[r + 1][c + 1] = '@';
                        pos[0][0] = r; pos[0][1] = c;
                        pos[1][0] = r; pos[1][1] = c + 1;
                        pos[2][0] = r + 1; pos[2][1] = c;
                        pos[3][0] = r + 1; pos[3][1] = c + 1;
                        arranged = 1;
                        break;
                    }
                }
            }
        }
    }

    if (!arranged) {
        printf("抱歉，無法找到連續可用的座位。\n");
        printf("請按 Enter 返回主選單...");
        getchar();
        return;
    }

    // 顯示建議座位表
    showSeats(tempSeats);

    // 詢問是否滿意
    printf("您滿意此安排嗎？(y/n): ");
    char ans = getchar();
    getchar();
    if (ans == 'y' || ans == 'Y') {
        // 紀錄座位，把'@'轉'*'
        for (int i = 0; i < need; i++) {
            seats[pos[i][0]][pos[i][1]] = '*';
        }
        printf("座位已確認，返回主選單。\n");
        printf("請按 Enter 繼續...");
        getchar();
    } else {
        printf("已取消安排，返回主選單。\n");
        printf("請按 Enter 繼續...");
        getchar();
    }
}

// 使用者手動選位
void userChooseSeats(char seats[ROWS][COLS]) {
    int chosenCount = 0;
    char tempSeats[ROWS][COLS];
    memcpy(tempSeats, seats, sizeof(tempSeats));

    printf("請依序輸入座位 (格式: row-col, 範例1-2)，輸入空行結束:\n");

    while (1) {
        char input[10];
        printf("輸入座位 %d: ", chosenCount + 1);
        fgets(input, sizeof(input), stdin);

        // 去除換行
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            if (chosenCount == 0) {
                printf("至少需輸入一個座位！\n");
                continue;
            } else {
                break;
            }
        }

        // 驗證格式
        if (!isValidSeatFormat(input)) {
            printf("格式錯誤，請輸入row-col，例如1-2\n");
            continue;
        }

        // 解析 row 和 col
        int row, col;
        sscanf(input, "%d-%d", &row, &col);

        // 轉成索引
        row -= 1;
        col -= 1;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("座位超出範圍，請重新輸入！\n");
            continue;
        }

        // 檢查座位是否已被訂或重複選
        if (tempSeats[row][col] == '*' || tempSeats[row][col] == '@') {
            printf("該座位已被佔用或已選擇，請重新輸入！\n");
            continue;
        }

        // 標示為@，並記錄
        tempSeats[row][col] = '@';
        chosenCount++;
    }

    // 顯示座位表讓使用者確認
    showSeats(tempSeats);
    printf("請按任意鍵確認選擇...");
    getchar();

    // 確認後，將@改成*
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (tempSeats[r][c] == '@') {
                seats[r][c] = '*';
            }
        }
    }
}

// 詢問使用者是否要重新輸入(繼續執行主選單)，輸入'y'回傳1，'n'回傳0，其他重試
int askContinue() {
    while (1) {
        printf("Continue? (y/n): ");
        char ch = getchar();
        getchar(); // 吃掉換行
        if (ch == 'y' || ch == 'Y') return 1;
        else if (ch == 'n' || ch == 'N') return 0;
        else {
            printf("輸入錯誤，請輸入'y'或'n'。\n");
        }
    }
}

// 檢查座位輸入格式 (row-col，row跟col皆為1位數到2位數的正整數)
int isValidSeatFormat(const char *input) {
    int len = strlen(input);
    int dashCount = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '-') dashCount++;
        else if ((input[i] < '0' || input[i] > '9')) return 0;
    }
    if (dashCount != 1) return 0;
    return 1;
}
/*
心得分享：

這個訂票系統讓我練習了陣列操作、字串處理和使用者輸入驗證。尤其是在安排連續座位和手動選位的部分，讓我更理解座位排位的邏輯和細節。隨機產生已訂座位的設計增加了真實感。整個流程也讓我體會到良好使用者介面的重要性，像是錯誤提示和重試機制。寫完後，我對C語言的控制流程和資料結構應用有更深的認識，覺得收穫很大！
*/
