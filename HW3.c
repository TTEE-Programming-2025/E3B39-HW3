#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD 2025
#define MAX_TRIES 3
#define SIZE 9
#define BOOKED_SEATS 10

char seats[SIZE][SIZE];  // '-'�G�Ŧ�A'*'�G�w�w�q�A'@'�G��ĳ��

void displayIntro() {
    printf("********************************************\n");
    printf("*              �w��ϥέq���t��            *\n");
    for (int i = 0; i < 18; i++)
        printf("*                                          *\n");
    printf("********************************************\n");
    printf("�Ы� Enter ���~��...\n");
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
    system("cls"); // Windows �� cls�AMac/Linux �� clear
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
        // �չϧ�@�Ƴs��Ŧ�
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
        // �u����@�Ƴs��4��
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
        // �䦸���ƦU���۾F�]�����s��^
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
    printf("�п�J�ݭn���y��ƶq (1~4)�G");
    scanf("%d", &people);

    if (people < 1 || people > 4) {
        printf("�H�Ƥ��X�k�A�Э��s��ܥ\��C\n");
        return;
    }

    if (!suggestSeats(people)) {
        printf("�䤣��i�w�ƪ��s��y��A�еy��A�աC\n");
        return;
    }

    showSeats();
    printf("�z�O�_���N�o�Ǯy��w�ơH(y/n)�G");
    char response;
    scanf(" %c", &response);
    if (response == 'y' || response == 'Y') {
        // �N @ �ܦ� *
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (seats[i][j] == '@')
                    seats[i][j] = '*';
        printf("�y��w���z�O�d�I�����N���^�D���...\n");
    } else {
        clearSuggestedSeats();
        printf("�w�����w�ơA�����N���^�D���...\n");
    }
    getchar(); // �M������
    getchar(); // ������J
    clearScreen();
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

    clearScreen();
    initSeats();

    while (1) {
        showMainMenu();
        printf("�п�ܥ\�� (a/b/c/d)�G");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                showSeats();
                printf("�����N���^�D���...\n");
                getchar(); getchar();
                clearScreen();
                break;
            case 'b':
                arrangeForUser();
                break;
            case 'c':
                printf("��ʿ��|����@�C\n");
                break;
            case 'd':
                printf("�P�¨ϥΡA�A���I\n");
                return 0;
            default:
                printf("�ﶵ���~�A�Э��s��J�C\n");
        }
    }
}
