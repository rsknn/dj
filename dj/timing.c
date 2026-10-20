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