/*
UserId=Moinul
Password=Moinul909
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define USERNAME "Moinul"
#define PASSWORD "Moinul909"

// Structure to hold student information
typedef struct {
    char name[50];
    float assignment;
    float quiz;
    float exam;
    float final_grade;
} Student;

// Function prototypes
int login();
void input_student_data(Student students[], int count);
void calculate_grades(Student students[], int count);
void display_results(Student students[], int count);
int get_float_input(const char *prompt);

int main() {
    Student students[MAX_STUDENTS];
    int student_count = 0;

    // User login
    if (login() == -1) {
        printf("Login failed!\n");
        return 1;
    }

    printf("Enter the number of students: ");
    scanf("%d", &student_count);
    input_student_data(students, student_count);
    calculate_grades(students, student_count);
    display_results(students, student_count);

    return 0;
}

// Login function
int login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 0; // Successful login
    }
    return -1; // Failed login
}

// Function to input student data
void input_student_data(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter name for student %d: ", i + 1);
        scanf(" %[^\n]", students[i].name);

        students[i].assignment = get_float_input("Enter assignment grade: ");
        students[i].quiz = get_float_input("Enter quiz grade: ");
        students[i].exam = get_float_input("Enter exam grade: ");
    }
}

// Function to get float input with validation
int get_float_input(const char *prompt) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            return value;
        } else {
            printf("Invalid input. Please enter a numeric value.\n");
            // Clear invalid input from buffer
            while (getchar() != '\n');
        }
    }
}

// Function to calculate final grades
void calculate_grades(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        // Assuming weights: Assignments 30%, Quizzes 30%, Exams 40%
        students[i].final_grade = (students[i].assignment * 0.3) +
                                   (students[i].quiz * 0.3) +
                                   (students[i].exam * 0.4);
    }
}

// Function to display results and ranks
void display_results(Student students[], int count) {
    printf("\nStudent Grades:\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Name", "Assignment", "Quiz", "Exam", "Final Grade");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10.2f %-10.2f %-10.2f %-10.2f\n",
               students[i].name,
               students[i].assignment,
               students[i].quiz,
               students[i].exam,
               students[i].final_grade);
    }

    // Ranking students based on final grades
    // Simple bubble sort for ranking
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].final_grade < students[j + 1].final_grade) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nClass Rank:\n");
    for (int i = 0; i < count; i++) {
        printf("Rank %d: %s with final grade %.2f\n", i + 1, students[i].name, students[i].final_grade);
    }
}
