#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int id;
    int class;
    int grade;
} student;

typedef struct{
    int id;
    int class;
} teacher;

int create_stu(student **arr, int *studentnum);
int create_tea(teacher **arr, int *teachernum);

int print_stu(student *arr, int studentnum);
int print_tea(teacher *arr, int teachernum);

void free_all(student **stu, teacher **tea);

int main(void){
    // UI and logic vars
    int option;
    int result;

    // Struct data
    int studentnum = 0;
    int teachernum = 0;

    student *stu_arr = NULL;
    teacher *tea_arr = NULL;

    while (true){
        printf("Would you like to:\n1. See students\n2. See teachers\n3. Create Student\n4. Create teacher\n5. Exit\n");
        scanf("%d", &option);

        if (option == 1){
            result = print_stu(stu_arr, studentnum);
        } else if (option == 2)
        {
            result = print_tea(tea_arr, teachernum);
        } else if (option == 3)
        {
            result = create_stu(&stu_arr, &studentnum);
        } else if (option == 4)
        {
            result = create_tea(&tea_arr, &teachernum);
        } else if (option == 5){
            free_all(&stu_arr, &tea_arr);
            return 0;
        }
        else {printf("Error, that is not an option\n"); result = 0;}
        if (result != 0){
            free_all(&stu_arr, &tea_arr);
            return 1;
        }
    }
}

int create_stu(student **arr, int *studentnum){
    (*studentnum)++;
    student *tmp;
    tmp = realloc(*arr, *studentnum * sizeof(student));
    if (tmp == NULL){
        printf("Failed memory allocation\n");
        return -1;
    } 
    *arr = tmp;

    int id = *studentnum;
    int grade;
    printf("Enter student's grade: ");
    scanf("%d", &grade);

    int class;
    printf("Enter student's class: ");
    scanf("%d", &class);
    
    student stu = {id, grade, class};
    (*arr)[*studentnum - 1] = stu;
    return 0;
}

int create_tea(teacher **arr, int *teachernum){
    (*teachernum)++;
    teacher *tmp;
    tmp = realloc(*arr, *teachernum * sizeof(teacher));
    if (tmp == NULL){
        printf("Failed memory allocation\n");
        return -1;
    } 

    *arr = tmp;

    int id = *teachernum;
    int class;
    printf("Enter teacher's class: ");
    scanf("%d", &class);
    
    teacher tea = {id, class};
    (*arr)[*teachernum - 1] = tea;
    return 0;
}

int print_stu(student *arr, int studentnum){
    if (studentnum == 0) {printf("No students\n");return 0;}
    printf("--- Student List ---\n");
    for (int i = 0; i < studentnum; i++){
        printf("%i. Grade: %i, Class: %i\n", arr[i].id, arr[i].grade, arr[i].class);
    }
    printf("--------------------\n");
    return 0;
}

int print_tea(teacher *arr, int teachernum){
    if (teachernum == 0) {printf("No teachers\n");return 0;}
    printf("--- Teacher List ---\n");
    for (int i = 0; i < teachernum; i++){
        printf("%i. Class: %i\n", arr[i].id, arr[i].class);
    }
    printf("--------------------\n");
    return 0;
}

void free_all(student **stu, teacher **tea){
    if (*tea != NULL){
        free(*tea);
    }
    if (*stu !=  NULL){
        free(*stu);
    }
}