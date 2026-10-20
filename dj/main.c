#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include "timing.h"

int main() {
    setlocale(LC_CTYPE, "RUS");
    char code;
    int start_sec, end_sec, age_group;
    int current_best = 999999;
    while (1) {
        printf("\n¬ведите код спортсмена ('!' дл€ выхода): ");
        scanf(" %c", &code);
        if (code == '!') {
            printf("—оревновани€ завершены.\n");
            break;
        }
        printf("¬ведите врем€ старта и финиша (в сек.): ");
        scanf("%d %d", &start_sec, &end_sec);
        printf("¬ведите возрастную группу (1 - дети, 2 - взрослые, 3 - ветераны): ");
        scanf("%d", &age_group);
        printf("—портсмен %c -> ", code);
        process_stage(start_sec, end_sec, age_group, &current_best);
    }
    return 0;
}