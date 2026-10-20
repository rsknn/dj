# Условие задачи

Создать мини-проект, реализующий программу системы хронометража на спортивных соревнованиях (например, лыжные гонки или биатлон). Программа должна принимать временные метки прохождения контрольных этапов в секундах, рассчитывать чистый результат, проверять его на соответствие правилам и выводить данные на экран. Программу необходимо разделить на несколько файлов и создать заголовочный файл для объявлений собственных функций.

Дополнительный функционал:
* **Расчет скорости:** принимает фиксированную длину трассы в метрах и время в секундах, возвращает скорость спортсмена в км/ч.
* **Динамический рекорд:** вместо фиксированного рекорда в 45 секунд сравнивает время спортсмена с лучшим временем дня (`current_best`).
* **Возрастной коэффициент:** корректирует чистое время в зависимости от возрастной группы (`1` — дети: бонус -15 сек, `2` — взрослые: без изменений, `3` — ветераны: бонус -10 сек).

# 1. Алгоритм и блок-схема

### Алгоритм

1. **Начало**.
2. **Инициализация:** задание начального рекорда дня `current_best = 999999`.
3. **Цикл ввода данных:**
   * Ввод однобуквенного кода спортсмена `code` (если введён символ `'!'`, цикл завершается).
   * Ввод времени старта `start_sec`, времени финиша `end_sec` и кода возрастной группы `age_group`.
4. **Обработка этапа (`process_stage`):**
   * Вычисление чистой длительности: `raw_duration = get_duration(start_sec, end_sec)`.
   * Применение возрастного бонуса: `final_duration = apply_age_coeff(raw_duration, age_group)`.
   * Проверка на нарушение правил (`check_status`): если время меньше 30 секунд — код `-1` (дисквалификация).
   * Выделение полных минут (`get_full_minutes`) и остатка секунд (`% 60`), вывод времени в формате `ММ:СС` (`print_time_mm_ss`).
   * Вывод текстового вердикта: `[Дисквалификация]`, `[Рекорд!]` (если побит `current_best` через `check_dynamic_record`) или `[Норма]`.
   * Расчёт и вывод скорости спортсмена в км/ч (`calc_speed`).
5. **Конец**.

### Блок-схема

<img width="782" height="1652" alt="image" src="https://github.com/user-attachments/assets/30555d53-ffcc-4eb8-8e55-9a987dd8e729" />

[Ссылка на изображение блок-схемы](https://clck.ru/3WaRne)


# 2. Реализация программы

### Заголовочный файл (`timing.h`)

```c
#ifndef TIMING_H
#define TIMING_H
int get_duration(int start_sec, int end_sec);
int check_status(int duration_sec);
int get_full_minutes(int total_sec);
void print_time_mm_ss(int minutes, int seconds);
double calc_speed(double distance_m, int duration_sec);
int check_dynamic_record(int duration_sec, int current_best);
int apply_age_coeff(int duration_sec, int age_group);
void process_stage(int start_sec, int end_sec, int age_group, int* current_best);
#endif
```

### Файл реализации функций (`timing.c`)

```c
#include <stdio.h>
#include "timing.h"

#define TRACK_LENGTH_M 500.0

int get_duration(int start_sec, int end_sec) {
    return end_sec - start_sec;
}
int check_status(int duration_sec) {
    if (duration_sec < 30) {
        return -1;
    }
    else if (duration_sec < 45) {
        return 1;
    }
    else {
        return 0;
    }
}
int get_full_minutes(int total_sec) {
    return total_sec / 60;
}
void print_time_mm_ss(int minutes, int seconds) {
    printf("%02d:%02d", minutes, seconds);
}
double calc_speed(double distance_m, int duration_sec) {
    if (duration_sec <= 0) return 0.0;
    return (distance_m / duration_sec) * 3.6;
}
int check_dynamic_record(int duration_sec, int current_best) {
    if (duration_sec < current_best) {
        return 1;
    }
    return 0;
}
int apply_age_coeff(int duration_sec, int age_group) {
    if (age_group == 1) {
        return duration_sec - 15;
    }
    else if (age_group == 3) {
        return duration_sec - 10;
    }
    return duration_sec;
}
void process_stage(int start_sec, int end_sec, int age_group, int* current_best) {
    int raw_duration = get_duration(start_sec, end_sec);
    int final_duration = apply_age_coeff(raw_duration, age_group);
    int status = check_status(final_duration);
    int minutes = get_full_minutes(final_duration);
    int seconds = final_duration % 60;
    printf("Итоговое время: ");
    print_time_mm_ss(minutes, seconds);
    if (status == -1) {
        printf(" [Дисквалификация]");
    }
    else if (check_dynamic_record(final_duration, *current_best) == 1) {
        printf(" [Рекорд!]");
        *current_best = final_duration;
    }
    else {
        printf(" [Норма]");
    }
    double speed = calc_speed(TRACK_LENGTH_M, final_duration);
    printf(" | Скорость: %.1f км/ч\n", speed);
}
```

### Главный файл (`main.c`)

```c
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
        printf("\nВведите код спортсмена ('!' для выхода): ");
        scanf(" %c", &code);
        if (code == '!') {
            printf("Соревнования завершены.\n");
            break;
        }
        printf("Введите время старта и финиша (в сек.): ");
        scanf("%d %d", &start_sec, &end_sec);
        printf("Введите возрастную группу (1 - дети, 2 - взрослые, 3 - ветераны): ");
        scanf("%d", &age_group);
        printf("Спортсмен %c -> ", code);
        process_stage(start_sec, end_sec, age_group, &current_best);
    }
    return 0;
}
```

# 3. Результат работы программы

1. **Первый заезд (установка рекорда дня, взрослая группа)**
```text
Введите код спортсмена ('!' для выхода): A
Введите время старта и финиша (в сек.): 10 75
Введите возрастную группу (1 - дети, 2 - взрослые, 3 - ветераны): 2
Спортсмен A -> Результат: 01:05 [Рекорд!] | Скорость: 27.7 км/ч
```

2. **Второй заезд (обычное время, группа ветеранов с бонусом -10 сек)**
```text
Введите код спортсмена ('!' для выхода): B
Введите время старта и финиша (в сек.): 20 100
Введите возрастную группу (1 - дети, 2 - взрослые, 3 - ветераны): 3
Спортсмен B -> Результат: 01:10 [Норма] | Скорость: 25.7 км/ч
```

3. **Третий заезд (новый рекорд дня, детская группа с бонусом -15 сек)**
```text
Введите код спортсмена ('!' для выхода): C
Введите время старта и финиша (в сек.): 0 65
Введите возрастную группу (1 - дети, 2 - взрослые, 3 - ветераны): 1
Спортсмен C -> Результат: 00:50 [Рекорд!] | Скорость: 36.0 км/ч
```

4. **Четвёртый заезд (дисквалификация и выход)**
```text
Введите код спортсмена ('!' для выхода): D
Введите время старта и финиша (в сек.): 10 30
Введите возрастную группу (1 - дети, 2 - взрослые, 3 - ветераны): 2
Спортсмен D -> Результат: 00:20 [Дисквалификация] | Скорость: 90.0 км/ч

Введите код спортсмена ('!' для выхода): !
Ввод завершён.
```

# 4. Информация

Енгалычев Руслан бОТИ-261
