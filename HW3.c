#include <stdio.h>
#include <stdlib.h>

#define PASSWORD 2025
#define MAX_TRIES 3

// ��ܭӤH����e���]20 ��^
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
    getchar(); // ���� Enter ��
}

// ��ܥD���
void showMainMenu() {
    // �M���ù��]Windows �ϥ� cls�ALinux/Mac �ϥ� clear�^
    system("cls"); // �Y�ϥ� macOS/Linux �Чאּ system("clear");

    printf("----------[Booking System]----------\n");
    printf("| a. Available seats                |\n");
    printf("| b. Arrange for you               |\n");
    printf("| c. Choose by yourself            |\n");
    printf("| d. Exit                          |\n");
    printf("------------------------------------\n");
}

int main() {
    int input, tries = 0;

    displayIntro(); // ��ܭӤH����e��

    // �K�X��J�̦h�T��
    while (tries < MAX_TRIES) {
        printf("�п�J4��ƱK�X�G");
        scanf("%d", &input);

        if (input == PASSWORD) {
            printf("\n�n�J���\�I�w��i�J�t�ΡC\n");
            getchar(); // �Y������Ÿ�
            getchar(); // ���ݨϥΪ̫� Enter �A�M���e��
            showMainMenu(); // ��ܥD���
            return 0;
        } else {
            tries++;
            printf("�K�X���~�A�z�٦� %d �����|�C\n", MAX_TRIES - tries);
        }
    }

    // �K�X���~�T��
    printf("\n���~���ƹL�h�A�t�ΧY�N�����C\n");
    return 1;
}
