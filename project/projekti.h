typedef struct {
    char desc[20];
    int month;
    int day;
    int hour;
} Appointment;

typedef struct {
    int numAppointments;
    Appointment *appointments;
} Schedule;

int add_appointment(Schedule *s, char *desc, int month, int day, int hour);
int delete_appointment(Schedule *s, int month, int day, int hour);
Schedule *init_schedule();
Schedule *load_from_file(char *filename);
int write_to_file(Schedule *s, char *filename);
void print_appointment(Appointment a);
void print_schedule(Schedule *s);
void release_all(Schedule *s);
int is_valid_time(int month, int day, int hour);
int appointment_exists(Schedule *s, int month, int day, int hour);
