#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// �y���j�p
#define ROWS 9
#define COLS 9

// �K�X�]�w
#define PASSWORD 2025

// �禡�ŧi
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

    // ��ܭӤH����e���A�����ұK�X
    showIntro();
    if (!verifyPassword()) {
        printf("���~�W�L�T���A�t�ε����C\n");
        return 0;
    }
    printf("�K�X���T�A�w��i�J�q���t�ΡI\n");
    printf("�Ы� Enter �~��...");
    getchar();

    // ��l�Ʈy���(�H��10�ӭq�� '*')
    initSeats(seats);

    while (1) {
        clearScreen();
        showMenu();

        char choice;
        printf("�п�J�ﶵ(a/b/c/d): ");
        scanf(" %c", &choice);
        getchar(); // �Y������

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
            // �߰ݬO�_����
            if (askContinue()) {
                continue; // �^�D���
            }
            else {
                printf("�t�ε����A�P�¨ϥΡI\n");
                break; // ���}�{��
            }
        }
        else {
            printf("�L�Ŀﶵ�A�Э��s��J�C\n");
            printf("�Ы� Enter �~��...");
            getchar();
        }
    }

    return 0;
}

// ��ܭӤH����e��(�ܤ�20��)
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

// �K�X���ҡA���T�������^��0�A���T�^��1
int verifyPassword() {
    int attempt = 0;
    int input;
    while (attempt < 3) {
        printf("�п�J4��ƱK�X: ");
        if (scanf("%d", &input) != 1) {
            // �D�Ʀr��J�B�z
            while (getchar() != '\n'); // �M���w��
            printf("��J���~�A�п�J�Ʀr�I\n");
            attempt++;
            continue;
        }
        if (input == PASSWORD) {
            return 1;
        } else {
            printf("�K�X���~�I\n");
            attempt++;
        }
    }
    return 0;
}

// �M�ù��]²�檩�^
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ��ܥD���
void showMenu() {
    printf("----------[Booking System]----------\n");
    printf("| a. Available seats                |\n");
    printf("| b. Arrange for you                |\n");
    printf("| c. Choose by yourself             |\n");
    printf("| d. Exit                         |\n");
    printf("------------------------------------\n");
}

// ��l�Ʈy���A�H������10�Ӥw�Q�q�y '*'
void initSeats(char seats[ROWS][COLS]) {
    // ������l�Ƭ�'-'
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

// ��ܮy���A�榡�ŦX�D�حn�D
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

// ���ݨϥΪ̫����N���~��
void pauseForKey() {
    printf("�Ы����N���~��...");
    getchar();
}

// �q���۰ʦw�Ʈy��A�����'@'�Хܫ�ĳ�y��
void arrangeSeats(char seats[ROWS][COLS]) {
    int need;
    printf("�п�J�ݭn�X�Ӯy��]1~4�^: ");
    if (scanf("%d", &need) != 1 || need < 1 || need > 4) {
        while (getchar() != '\n');
        printf("��J���~�A�����O1~4���Ʀr�I\n");
        printf("�Ы� Enter ��^�D���...");
        getchar();
        return;
    }
    getchar();

    // �ƻs�ثe�y�쪬�A�A��K�Х�@�y��
    char tempSeats[ROWS][COLS];
    memcpy(tempSeats, seats, sizeof(tempSeats));

    int pos[4][2] = {0}; // �����w�Ʈy���m
    int arranged = 0;

    // 1~3��: �M��s��y��
    if (need >= 1 && need <= 3) {
        // ��s��y��
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
        // 4��: ����P�C4�s�y
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
        // �Y�䤣��A��e���C�U���
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
        printf("��p�A�L�k���s��i�Ϊ��y��C\n");
        printf("�Ы� Enter ��^�D���...");
        getchar();
        return;
    }

    // ��ܫ�ĳ�y���
    showSeats(tempSeats);

    // �߰ݬO�_���N
    printf("�z���N���w�ƶܡH(y/n): ");
    char ans = getchar();
    getchar();
    if (ans == 'y' || ans == 'Y') {
        // �����y��A��'@'��'*'
        for (int i = 0; i < need; i++) {
            seats[pos[i][0]][pos[i][1]] = '*';
        }
        printf("�y��w�T�{�A��^�D���C\n");
        printf("�Ы� Enter �~��...");
        getchar();
    } else {
        printf("�w�����w�ơA��^�D���C\n");
        printf("�Ы� Enter �~��...");
        getchar();
    }
}

// �ϥΪ̤�ʿ��
void userChooseSeats(char seats[ROWS][COLS]) {
    int chosenCount = 0;
    char tempSeats[ROWS][COLS];
    memcpy(tempSeats, seats, sizeof(tempSeats));

    printf("�Ш̧ǿ�J�y�� (�榡: row-col, �d��1-2)�A��J�Ŧ浲��:\n");

    while (1) {
        char input[10];
        printf("��J�y�� %d: ", chosenCount + 1);
        fgets(input, sizeof(input), stdin);

        // �h������
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            if (chosenCount == 0) {
                printf("�ܤֻݿ�J�@�Ӯy��I\n");
                continue;
            } else {
                break;
            }
        }

        // ���Ү榡
        if (!isValidSeatFormat(input)) {
            printf("�榡���~�A�п�Jrow-col�A�Ҧp1-2\n");
            continue;
        }

        // �ѪR row �M col
        int row, col;
        sscanf(input, "%d-%d", &row, &col);

        // �ন����
        row -= 1;
        col -= 1;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("�y��W�X�d��A�Э��s��J�I\n");
            continue;
        }

        // �ˬd�y��O�_�w�Q�q�έ��ƿ�
        if (tempSeats[row][col] == '*' || tempSeats[row][col] == '@') {
            printf("�Ӯy��w�Q���ΩΤw��ܡA�Э��s��J�I\n");
            continue;
        }

        // �Хܬ�@�A�ðO��
        tempSeats[row][col] = '@';
        chosenCount++;
    }

    // ��ܮy������ϥΪ̽T�{
    showSeats(tempSeats);
    printf("�Ы����N��T�{���...");
    getchar();

    // �T�{��A�N@�令*
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (tempSeats[r][c] == '@') {
                seats[r][c] = '*';
            }
        }
    }
}

// �߰ݨϥΪ̬O�_�n���s��J(�~�����D���)�A��J'y'�^��1�A'n'�^��0�A��L����
int askContinue() {
    while (1) {
        printf("Continue? (y/n): ");
        char ch = getchar();
        getchar(); // �Y������
        if (ch == 'y' || ch == 'Y') return 1;
        else if (ch == 'n' || ch == 'N') return 0;
        else {
            printf("��J���~�A�п�J'y'��'n'�C\n");
        }
    }
}

// �ˬd�y���J�榡 (row-col�Arow��col�Ҭ�1��ƨ�2��ƪ������)
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
�߱o���ɡG

�o�ӭq���t�����ڽm�ߤF�}�C�ާ@�B�r��B�z�M�ϥΪ̿�J���ҡC�ר�O�b�w�Ƴs��y��M��ʿ�쪺�����A���ڧ�z�Ѯy��Ʀ쪺�޿�M�Ӹ`�C�H�����ͤw�q�y�쪺�]�p�W�[�F�u��P�C��Ӭy�{�]������|��}�n�ϥΪ̤��������n�ʡA���O���~���ܩM���վ���C�g����A�ڹ�C�y��������y�{�M��Ƶ��c���Φ���`���{�ѡAı�o��ì�ܤj�I
*/
