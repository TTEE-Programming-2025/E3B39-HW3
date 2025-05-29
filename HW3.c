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
    printf("\n�Ы� Enter ���~��...");
    getchar();
    getchar();
}

void printWelcomeScreen() {
    clearScreen();
    for (int i = 0; i < 10; i++) printf("********************************************\n");
    printf("*                                          *\n");
    printf("*     ( ^_^ )  �w��ϥέq���t��             *\n");
    printf("*     ( o_o )  �п�J�|��ƱK�X�n�J         *\n");
    printf("*     ( owo )                                *\n");
    printf("*                                          *\n");
    for (int i = 0; i < 10; i++) printf("********************************************\n");
    printf("\n");
}

int login() {
    int password;
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        printf("�п�J�|��ƱK�X: ");
        scanf("%d", &password);
        if (password == 2025) {
            printf("\n�n�J���\�I\n");
            waitForEnter();
            return 1;
        } else {
            printf("�K�X���~�I\n");
            attempts++;
        }
    }
    printf("�s����~�T���A�t�ε����I\n");
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
    printf("�{���y���p�U�G\n");
    showSeats();
    waitForEnter();
}

void arrangeSeats() {
    int n;
    printf("�п�J�ݭn���y��� (1~4): ");
    scanf("%d", &n);
    if (n < 1 || n > 4) {
        printf("��J���~\n");
        return;
    }
    // ²�ƪ���: ���Ĥ@�ӥi�񪺮y��A�Хܬ� @
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
        printf("�O�_���N�w�ơH(y/n): ");
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
        printf("�ثe�䤣��X�A���y��w�ơC\n");
    }
    waitForEnter();
}

void chooseByYourself() {
    char input[10];
    int row, col;
    while (1) {
        clearScreen();
        showSeats();
        printf("�п�J�y�� (�p 1-2)�A��J done �����G");
        scanf("%s", input);
        if (strcmp(input, "done") == 0) break;
        if (sscanf(input, "%d-%d", &row, &col) == 2 && row >= 1 && row <= 9 && col >= 1 && col <= 9) {
            row--; col--;
            if (seats[row][col] == '-') {
                seats[row][col] = '@';
            } else {
                printf("�Ӯy��w�Q�w�q�I\n");
                waitForEnter();
            }
        } else {
            printf("�榡���~�A�Э��s��J�I\n");
            waitForEnter();
        }
    }
    clearScreen();
    showSeats();
    printf("�O�_�T�w�o�Ǯy��H�����N���~��...");
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
        printf("�п��: ");
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
                    else printf("��J���~�A�Э��s��J�C\n");
                } while (1);
                break;
            }
            default:
                printf("�ﶵ���~�I\n");
                waitForEnter();
        }
    }
    return 0;
}
