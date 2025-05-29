#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD 2025
#define MAX_TRIES 3
#define SIZE 9
#define BOOKED_SEATS 10

char seats[SIZE][SIZE]; // 9x9 �y���

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
    printf("�Ы� Enter ���~��...\n");
    getchar(); // ���ݨϥΪ̫� Enter
}

// ��l�Ʈy��A���H���аO 10 �Ӥw�w�q�y��]'*'�^
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

// ��ܥD���
void showMainMenu() {
    printf("----------[Booking System]----------\n");
    printf("| a. Available seats               |\n");
    printf("| b. Arrange for you              |\n");
    printf("| c. Choose by yourself           |\n");
    printf("| d. Exit                         |\n");
    printf("------------------------------------\n");
}

// ��ܮy���
void showSeats() {
    int i, j;
    printf(" \\123456789\n"); // �W�Ʈy�츹
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", i + 1); // �����C��
        for (j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
    printf("�����N���^�D���...\n");
    getchar(); // �M���W����J�� Enter
    getchar(); // ���ݫ���
    system("cls"); // Windows�AMac/Linux �Чאּ system("clear")
}

int main() {
    int input, tries = 0;
    char choice;

    displayIntro();

    while (tries < MAX_TRIES) {
        printf("�п�J 4 ��ƱK�X�G");
        scanf("%d", &input);

        if (input == PASSWORD) {
            break;
        } else {
            tries++;
            printf("�K�X���~�A�٦� %d �����|�C\n", MAX_TRIES - tries);
        }
    }

    if (tries == MAX_TRIES) {
        printf("���~���ƹL�h�A�t�ε����C\n");
        return 1;
    }

    // �K�X���T
    system("cls");
    initSeats();

    while (1) {
        showMainMenu();
        printf("�п�ܥ\�� (a/b/c/d)�G");
        scanf(" %c", &choice); // �e�����Ů�H�����e����J�� Enter

        switch (choice) {
            case 'a':
                showSeats();
                break;
            case 'b':
                printf("�|����@�۰ʤ��t�\��C\n");
                break;
            case 'c':
                printf("�|����@��ʿ�ܥ\��C\n");
                break;
            case 'd':
                printf("�P�¨ϥΡA�A���I\n");
                return 0;
            default:
                printf("�L�Ī��ﶵ�A�Э��s��J�C\n");
        }
    }

    return 0;
}
