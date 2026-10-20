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