#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 9

char seats[SIZE][SIZE];  // 9x9�y���

// �M���ù� (�̥��x�Ӳ�)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ��ܮy���
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

// �ˬd�y��O�_�w�Q���
int isOccupied(int row, int col) {
    return seats[row][col] == '*' || seats[row][col] == '@';
}

// �B�z��ʿ��
void chooseSeats() {
    char input[100];
    int row, col;
    int done = 0;

    while (!done) {
        clearScreen();
        showSeats('@');
        printf("�п�J�y�� (�Ҧp 1-2 ��ܲ�1�C��2��)�A��J done ������ܡG\n");
        printf("=> ");
        scanf("%s", input);

        if (strcmp(input, "done") == 0) {
            done = 1;
        } else if (sscanf(input, "%d-%d", &row, &col) == 2 &&
                   row >= 1 && row <= SIZE &&
                   col >= 1 && col <= SIZE) {
            row--; col--;
            if (isOccupied(row, col)) {
                printf("���~�G�y�� %d-%d �w�Q����I�Э��s��J�C\n", row + 1, col + 1);
                system("pause");
            } else {
                seats[row][col] = '@';
            }
        } else {
            printf("�榡���~�A�п�J�p 1-2 �o�˪��榡�C\n");
            system("pause");
        }
    }

    clearScreen();
    printf("�z��ܪ��y��p�U�G\n");
    showSeats('@');
    printf("�нT�{�H�W�y��L�~�A�����N���~��...\n");
    getchar(); getchar();

    // �T�{���ର�w�q��
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (seats[i][j] == '@') {
                seats[i][j] = '*';
            }
        }
    }

    clearScreen();
}
