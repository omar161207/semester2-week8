
#define NAME_LENGTH 50
#define NUM_MODULES 3

/**
 * Structure to represent a student
 */
typedef struct student_record {
    char name[NAME_LENGTH];  // Student's name
    int id;                  // Student's ID number
    float marks[NUM_MODULES]; // Marks for three modules
}Student;

/*
 * function headers
 */
float calculate_average(struct student_record student);
void display_student(struct student_record student);

// this header file is js to be on the safe side that u have your functions defined before the main function in the .c file 
// so no errors happen if u have one function declared after the main function 
