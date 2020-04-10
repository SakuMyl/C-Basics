#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projekti.h"

int main()
{
    Schedule *s = init_schedule(); 
    if (!s) return 1;

    char cmd[100];
    char params[100];
    char option;
    while (1) {
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            release_all(s);
            return 0;
        }
        sscanf(cmd, "%c %100[^\n]s", &option, params);
        switch (option) {
            case 'A': {
                char desc[20];
                int month, day, hour;
                if (sscanf(params, "%20s %d %d %d", desc, &month, &day, &hour) < 4) {
                    printf("Invalid parameters\n");
                    break;
                }
                if (add_appointment(s, desc, month, day, hour)) {
                    printf("Appointment %s added\n", desc);
                }
                break;
            }
            case 'D': {
                int month, day, hour;
                if (sscanf(params, "%d %d %d", &month, &day, &hour) < 3) {
                    printf("Invalid parameters\n");
                    break;
                }
                if (delete_appointment(s, month, day, hour)) {
                    printf("Appointment deleted\n");
                }
                break;
            }
            case 'L':
                print_schedule(s);
                break;
            case 'W': {
                char filename[100];
                if (sscanf(params, "%100s", filename) < 1) {
                    printf("Invalid parameters: file name not specified\n");
                    break;
                }
                if (write_to_file(s, filename)) {
                    printf("Schedule saved to %s\n", filename);
                }
                break;
            }
            case 'O': {
                char filename[100];
                if (sscanf(params, "%100s", filename) < 1) {
                    printf("Invalid parameters: file name not specified\n");
                    break;
                }
                Schedule *new_s = load_from_file(filename);
                if (new_s) {
                    release_all(s);
                    s = new_s;
                    printf("Schedule loaded from %s\n", filename);
                }
                break;
            }
            case 'Q':
                release_all(s);
                return 0;
            default:
                printf("Invalid command\n");
                break;
        }
    }
    return 0;
}

int is_valid_time(int month, int day, int hour)
{
    if (month > 12 || month < 1 || day > 31 || day < 1 || hour > 23 || hour < 0) {
        return 0;
    }
    return 1;
}

int appointment_exists(Schedule *s, int month, int day, int hour)
{
    for (int i = 0; i < s->numAppointments; i++) {
        Appointment a = s->appointments[i];
        if (a.month == month && a.day == day && a.hour == hour) {
            return 1;
        }
    }
    return 0;
}

int add_appointment(Schedule *s, char *desc, int month, int day, int hour)
{
    if (!is_valid_time(month, day, hour)) {
        printf("Adding appointment %s failed: invalid time\n", desc);
        return 0;
    } 
    if (appointment_exists(s, month, day, hour)) {
        printf("Adding appointment %s failed: an appointment already exists at given time\n", desc);
        return 0;
    }
    
    s->numAppointments++;
    s->appointments = realloc(s->appointments, s->numAppointments * sizeof(Appointment));
    if (!s->appointments) {
        perror("realloc failed");
        release_all(s);
        exit(1);
    }
    Appointment a;
    strcpy(a.desc, desc);
    a.month = month;
    a.day = day;
    a.hour = hour;
    s->appointments[s->numAppointments - 1] = a; 
    return 1;
}

int delete_appointment(Schedule *s, int month, int day, int hour)
{
    if (!is_valid_time(month, day, hour)) {
        printf("Deleting appointment failed: invalid time\n");
        return 0;
    }
    if (!appointment_exists(s, month, day, hour)) {
        printf("Deleting appointment failed: no appointment exists at given time\n");
        return 0;
    }
    s->numAppointments--;
    if (s->numAppointments == 0) {
        return 1;
    }
    Appointment *appointments = malloc(s->numAppointments * sizeof(Appointment));
    if (!appointments) {
        perror("malloc failed");
        release_all(s);
        exit(1);
    }
    // Two pointers, one for the old array and one for the new
    for (int i = 0, j = 0; i < s->numAppointments; j++) {
        Appointment a = s->appointments[j];
        // Don't copy the deleted appointment
        if (!(a.month == month && a.day == day && a.hour == hour)) {
            appointments[i] = a;
            i++;
        }
    }
    free(s->appointments);
    s->appointments = appointments;
    return 1;
}

Schedule *init_schedule()
{
    Schedule *s = malloc(sizeof(Schedule));
    if (!s) {
        perror("malloc failed");
        return NULL;
    }
    // Initialize empty array
    s->appointments = NULL;
    s->numAppointments = 0;
    return s;
}

Schedule *load_from_file(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("error opening file");
        return NULL;
    }
    // Count the number of rows in the file
    int n = 0;
    char c, last = '\n';
    while ((c = fgetc(f)) != EOF) {
        // To handle empty files with line breaks properly
        if (c == '\n' && last != '\n') n++;
        last = c;
    }
    rewind(f);
    Schedule *s = init_schedule();
    if (!s) {
        fclose(f);
        exit(1);
    }
    char line[50];
    for (int i = 0; i < n; i++) {
        Appointment a;
        fgets(line, sizeof(line), f);
        if (sscanf(line, " %s %d %d %d", a.desc, &a.month, &a.day, &a.hour) < 4) {
            printf("Error: malformatted file\n");
            fclose(f);
            release_all(s);
            return NULL;
        }
        add_appointment(s, a.desc, a.month, a.day, a.hour);
    }
    fclose(f);
    return s;
}

int write_to_file(Schedule *s, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("error opening file");
        return 0;
    }
    Appointment *a = s->appointments;
    for (int i = 0; i < s->numAppointments; i++) {
        if (fprintf(f, "%s %d %d %d\n", a[i].desc, a[i].month, a[i].day, a[i].hour) < 4) {
            perror("error writing to file");
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

void print_appointment(Appointment a)
{
    printf("%s %d.%d. klo %d\n", a.desc, a.day, a.month, a.hour);
}

int cmp_appointment(const void *a, const void *b)
{
    const Appointment *a_ = (Appointment *)a;
    const Appointment *b_ = (Appointment *)b;
    int ret = a_->month - b_->month;
    if (ret) return ret;
    ret = a_->day - b_->day;
    if (ret) return ret;
    ret = a_->hour - b_->hour;
    return ret;
}

void print_schedule(Schedule *s)
{
    Appointment *sorted = malloc(s->numAppointments * sizeof(Appointment));
    if (!sorted) {
        perror("malloc failed");
        release_all(s);
        exit(1);
    }
    memcpy(sorted, s->appointments, s->numAppointments * sizeof(Appointment));
    qsort(sorted, s->numAppointments, sizeof(Appointment), cmp_appointment);
    for (int i = 0; i < s->numAppointments; i++) {
        print_appointment(sorted[i]);
    }
    free(sorted);
}

void release_all(Schedule *s)
{
    free(s->appointments);
    free(s);
}
