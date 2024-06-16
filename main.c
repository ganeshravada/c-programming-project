#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();

int main() {
    int choice;
    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add a student record
void addStudent() {
    FILE *file = fopen("students.dat", "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;

    printf("Enter roll number: ");
    scanf("%d", &s.rollNumber);
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, file);
    fclose(file);

    printf("Student record added successfully.\n");
}

// Function to view all student records
void viewStudents() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;

    printf("\nAll Student Records:\n");
    while (fread(&s, sizeof(s), 1, file)) {
        printf("Roll Number: %d\n", s.rollNumber);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n\n", s.marks);
    }
    fclose(file);
}

// Function to search for a student record by roll number
void searchStudent() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    int rollNumber, found = 0;

    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);

    while (fread(&s, sizeof(s), 1, file)) {
        if (s.rollNumber == rollNumber) {
            printf("Roll Number: %d\n", s.rollNumber);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No student found with roll number %d\n", rollNumber);
    }
}

// Function to delete a student record by roll number
void deleteStudent() {
    FILE *file = fopen("students.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    int rollNumber, found = 0;

    printf("Enter roll number to delete: ");
    scanf("%d", &rollNumber);

    while (fread(&s, sizeof(s), 1, file)) {
        if (s.rollNumber == rollNumber) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student record deleted successfully.\n");
    } else {
        printf("No student found with roll number %d\n", rollNumber);
    }
}
