/**************************************************************************************************
 Name         : Student Management System
 Submitted by : Abdulrahman Adel
 Group        : 96
 Submiited to : Mohamed Tarek ❤❤❤❤
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define a structure
typedef struct student {
    int id;                     // Student's ID
    char name[50];              // Student's name
    int age;                    // Student's age
    float gpa;                  // Student's GPA
    struct student* next;       // Pointer to the next student
} Student;

// This pointer will always point to the head of the student list
Student* head = NULL;

// Functions used in the code
void addStudent();
void displayStudents();
void searchStudentByID(int id);
void updateStudent(int id);
void deleteStudent(int id);
float calculateAverageGPA();
void searchHighestGPA();

int main() {
    int choice, id;

    // Infinite loop to keep showing the menu
    while (1) {
        printf("\n====== Student Management System ======\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for Student by ID\n");
        printf("4. Update Student Information\n");
        printf("5. Delete Student\n");
        printf("6. Calculate Average GPA\n");
        printf("7. Find Student with Highest GPA\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        fflush(stdout);  // Ensures The prints shown immediately
        scanf("%d", &choice);

        // Take action based on user choice
        switch (choice) {
            case 1:
                addStudent();  // Add a new student
                break;
            case 2:
                displayStudents();  // Show all students
                break;
            case 3:
                printf("Enter student ID to search: ");
                fflush(stdout);
                scanf("%d", &id);
                searchStudentByID(id);  // Search student by ID
                break;
            case 4:
                printf("Enter student ID to update: ");
                fflush(stdout);
                scanf("%d", &id);
                updateStudent(id);  // Update student info
                break;
            case 5:
                printf("Enter student ID to delete: ");
                fflush(stdout);
                scanf("%d", &id);
                deleteStudent(id);  // Delete student
                break;
            case 6:
                // Show average GPA
                printf("Average GPA: %.2f\n", calculateAverageGPA());
                break;
            case 7:
                searchHighestGPA();  // Find student with highest GPA
                break;
            case 8:
                printf("Exiting program.\n");
                return 0;  // Exit the program
            default:
                printf("Invalid choice.\n");
        }
    }
}

// Function to add a new student
void addStudent() {
    int id;
    Student* temp = head;

    printf("Enter student ID: ");
    fflush(stdout);
    scanf("%d", &id);

    // Check if the ID already exists
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Error: Student ID already exists.\n");
            return;
        }
        temp = temp->next;
    }

    // Allocate memory for new student
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Fill in the student's information
    newStudent->id = id;
    printf("Enter name: ");
    fflush(stdout);
    scanf(" %[^\n]s", newStudent->name);  // Read full name
    printf("Enter age: ");
    fflush(stdout);
    scanf("%d", &newStudent->age);
    printf("Enter GPA: ");
    fflush(stdout);
    scanf("%f", &newStudent->gpa);
    newStudent->next = NULL;

    // Add the new student to the end of the linked list
    if (head == NULL) {
        head = newStudent;  // First student in the list
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newStudent;
    }

    printf("Student added successfully.\n");
}

// Function to display all students in the list
void displayStudents() {
    if (head == NULL) {
        printf("No students found.\n");
        return;
    }

    Student* temp = head;
    printf("\n--- Student List ---\n");
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
               temp->id, temp->name, temp->age, temp->gpa);
        temp = temp->next;  // Move to the next student
    }
}

// Function to search for a student by their ID
void searchStudentByID(int id) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Student found: ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
                   temp->id, temp->name, temp->age, temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}

// Function to update a student's information
void updateStudent(int id) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            // Update name, age, and GPA
            printf("Enter new name: ");
            fflush(stdout);
            scanf(" %[^\n]s", temp->name);
            printf("Enter new age: ");
            fflush(stdout);
            scanf("%d", &temp->age);
            printf("Enter new GPA: ");
            fflush(stdout);
            scanf("%f", &temp->gpa);
            printf("Student updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}

// Function to delete a student from the list
void deleteStudent(int id) {
    Student *temp = head, *prev = NULL;

    // Search for the student to delete
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If student not found
    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    // If student is the first in the list
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;  // Skip the student to remove
    }

    free(temp);  // Free memory
    printf("Student deleted successfully.\n");
}

// Function to calculate the average GPA of all students
float calculateAverageGPA() {
    if (head == NULL)
        return 0.0;

    float total = 0.0;
    int count = 0;
    Student* temp = head;

    // Sum all GPAs and count the students
    while (temp != NULL) {
        total += temp->gpa;
        count++;
        temp = temp->next;
    }

    // Return the average GPA
    return (count > 0) ? (total / count) : 0.0;
}

// Function to find the student with the highest GPA
void searchHighestGPA() {
    if (head == NULL) {
        printf("No students in the list.\n");
        return;
    }

    Student* temp = head;
    Student* topStudent = head;

    // Go through the list and find the highest GPA
    while (temp != NULL) {
        if (temp->gpa > topStudent->gpa)
            topStudent = temp;
        temp = temp->next;
    }

    printf("Top student: ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
           topStudent->id, topStudent->name, topStudent->age, topStudent->gpa);
}
/**************************************************************************************************
 "I am truly grateful for the guidance, preparation, and support you have consistently
  offered. Your steadfast confidence in my abilities enabled me to achieve goals
  I once believed were unattainable."
 **************************************************************************************************/
