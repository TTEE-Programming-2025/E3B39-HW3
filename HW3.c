#include <stdio.h>
#include <stdlib.h>

#define PASSWORD 2025
#define MAX_TRIES 3

void displayIntro() {
    // ��ܭӤH����e���]��n 20 ��^
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

int main() {
    int input, tries = 0;

    displayIntro(); // ��ܵe��

    while (tries < MAX_TRIES) {
        printf("�п�J 4 ��ƱK�X�G");
        scanf("%d", &input);

        if (input == PASSWORD) {
            printf("\n�n�J���\�I�w��i�J�t�ΡC\n");
            // �U�@�B�i�I�s�D���禡
            // showMainMenu();
            return 0;
        } else {
            tries++;
            printf("�K�X���~�A�z�٦� %d �����|�C\n", MAX_TRIES - tries);
        }
    }

    printf("\n���~���ƹL�h�A�t�ΧY�N�����C\n");
    return 1;
}
