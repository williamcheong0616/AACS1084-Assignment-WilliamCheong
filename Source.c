#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define MAX_STAFF 100

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char staffID[15];
    char name[50];
    Date dob;
    float salary;
    char password[20];
    char recovery[20];
    char position[20];
} Staff;

void add_staff(Staff staff[], int* num_staff);
void search_staff(Staff staff[]);
void modify_staff(Staff staff[], int num_staff);
void display_staff(Staff staff[], int num_staff);
void display_staff_annual_report(Staff staff[]);
void delete_staff(Staff staff[], int* num_staff);

int staffmain() {
    Staff staff[MAX_STAFF];
    int num_staff = 0;
    char username[50];
    char password[50];
    char staffID[15];
    int choice;

    printf("Please enter your staff ID (SXXX): ");
    scanf("%s", staffID);

    FILE* fp;
    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Unable to open file staff.txt.\n");
        return 0;
    }

    int found = 0;
    while (fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", staff[num_staff].staffID, staff[num_staff].name, &staff[num_staff].dob.day, &staff[num_staff].dob.month, &staff[num_staff].dob.year, &staff[num_staff].salary, staff[num_staff].password, staff[num_staff].recovery, staff[num_staff].position) == 9) {
        if (strcmp(staffID, staff[num_staff].staffID) == 0) {
            found = 1;
            strcpy(username, staff[num_staff].staffID);
            printf("Please enter your password or recovery password: ");
            scanf("%s", password);
            if (strcmp(password, staff[num_staff].password) == 0 || strcmp(password, staff[num_staff].recovery) == 0) {
                printf("Login successful.\n");
                break;
            }
            else {
                printf("Invalid password or recovery password.\n");
                return 0;
            }
        }
        num_staff++;
    }
    system("pause");
    fclose(fp);

    if (!found) {
        printf("Staff ID not found.\n");
        return 0;
    }

    while (1) {
        system("cls");

        printf("\nStaff Information Module\n");
        printf("1. Add new staff account\n");
        printf("2. Search for staff account\n");
        printf("3. Modify staff account\n");
        printf("4. Display all staff accounts\n");
        printf("5. Display staff login report\n");
        printf("6. Delete staff account\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add_staff(staff, &num_staff);
            break;
        case 2:
            search_staff(staff, num_staff);
            break;
        case 3:
            modify_staff(staff, num_staff);
            break;
        case 4:
            display_staff(staff, num_staff);
            break;
        case 5:
            display_staff_annual_report(staff, num_staff);
            break;
        case 6:
            delete_staff(staff, &num_staff);
            break;
        case 7:
            printf("Exiting Staff Information Module. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_staff(Staff staff[], int* num_staff) {
    system("cls");
    if (*num_staff >= MAX_STAFF) {
        printf("Error: Maximum number of staff accounts reached.\n");
        return;
    }
    rewind(stdin);
    printf("\nEnter Staff ID (SXXX)           : ");
    scanf("%s", staff[*num_staff].staffID);
    rewind(stdin);
    printf("Enter staff name                : ");
    scanf("%[^\n]", staff[*num_staff].name);
    rewind(stdin);
    printf("Enter date of birth (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &staff[*num_staff].dob.day, &staff[*num_staff].dob.month, &staff[*num_staff].dob.year);
    rewind(stdin);
    printf("Enter staff salary              : ");
    scanf("%f", &staff[*num_staff].salary);
    rewind(stdin);
    printf("Enter staff password            : ");
    scanf("%s", staff[*num_staff].password);
    rewind(stdin);
    printf("Enter staff password recovery   : ");
    scanf("%s", staff[*num_staff].recovery);
    rewind(stdin);
    printf("Enter staff position            : ");
    scanf("%s", staff[*num_staff].position);

    (*num_staff)++;

    FILE* fp;
    fp = fopen("staff.txt", "a");
    fprintf(fp, "%s,%s,%d/%d/%d,%.2f,%s,%s,%s\n", staff[*num_staff - 1].staffID,staff[*num_staff - 1].name , staff[*num_staff - 1].dob.day, staff[*num_staff - 1].dob.month, staff[*num_staff - 1].dob.year, staff[*num_staff - 1].salary, staff[*num_staff - 1].password, staff[*num_staff - 1].recovery, staff[*num_staff - 1].position);
    fclose(fp);

    printf("======================================================\n");
    printf("New staff account added successfully.\n");

    system("pause");    
}

void search_staff(Staff staff[]) {
    system("cls");
    char staffLogID[50];
    int i;
    int found = 0;
    FILE* fp = fopen("staff.txt", "r");
    printf("\nEnter Staff ID to search for: ");
    scanf("%s", staffLogID);

    for (i = 0; i < MAX_STAFF;i++) {
   
           fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", staff[i].staffID, staff[i].name, &staff[i].dob.day, &staff[i].dob.month, &staff[i].dob.year, &staff[i].salary, staff[i].password, staff[i].recovery, staff[i].position);
          
           if (strcmp(staffLogID, staff[i].staffID) == 0) {
               printf("Name             : %s\n", staff[i].name);
               printf("Date of Birth    : %d/%d/%d\n", staff[i].dob.day, staff[i].dob.month, staff[i].dob.year);
               printf("Salary           : %.2f\n", staff[i].salary);
               printf("Password         : %s\n", staff[i].password);
               printf("Password Recovery: %s\n", staff[i].recovery);
               printf("Position         : %s\n", staff[i].position);
               found = 1;
               break;
           }
    }


    if (!found) {
        printf("Staff account not found.\n");
    }
    fclose(fp);

    printf("======================================================\n");
    printf("Staff account found\n");

    system("pause");
}

void modify_staff(Staff staff[], int num_staff) {
    system("cls");
 
    char staffID[50];
    int i=0,a;
    int found = 0;
    Staff temp[MAX_STAFF];
    FILE* fp = fopen("staff.txt", "r");
    
    while (!feof(fp)) {
        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", temp[i].staffID, temp[i].name, &temp[i].dob.day, &temp[i].dob.month, &temp[i].dob.year, &temp[i].salary, temp[i].password, temp[i].recovery, temp[i].position);
        i++;
    }
    
    printf("\nEnter Staff ID to Modify for: ");
    scanf("%s", staffID);

    

    for (a = 0; a<i; a++) {
        
        //scan the staff data from text file
        if (strcmp(temp[a].staffID,staffID) == 0) {
            printf("Staff account found\n");
            printf("Name             : %s\n", temp[a].name);
            printf("Date of Birth    : %d/%d/%d\n", temp[a].dob.day, temp[a].dob.month, temp[a].dob.year);
            printf("Salary           : %.2f\n", temp[a].salary);
            printf("Password         : %s\n", temp[a].password);
            printf("Password Recovery: %s\n", temp[a].recovery);
            printf("Position         : %s\n", temp[a].position);
            rewind(stdin);
            printf("\nEnter new staff name: ");
            scanf("%[^\n]", temp[a].name);
            rewind(stdin);
            printf("Enter new date of birth (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &temp[a].dob.day, &temp[a].dob.month, &temp[a].dob.year);
            rewind(stdin);
            printf("Enter new staff salary: ");
            scanf("%f", &temp[a].salary);
            rewind(stdin);
            printf("Enter new staff password: ");
            scanf("%s", temp[a].password);
            rewind(stdin);
            printf("Enter new staff password recovery: ");
            scanf("%s", temp[a].recovery);
            rewind(stdin);
            printf("Enter new staff position: ");
            scanf("%s", temp[a].position);

            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("Staff account not found.\n");
    }
    else {
        FILE* fp;


        fp = fopen("staff.txt", "w");
        for (a= 0; a <i; a++) {
            fprintf(fp, "%s,%s,%d/%d/%d,%.2f,%s,%s,%s\n", temp[a].staffID, temp[a].name, temp[a].dob.day, temp[a].dob.month, temp[a].dob.year, temp[a].salary, temp[a].password, temp[a].recovery, temp[a].position);
        }
        fclose(fp);

        printf("======================================================\n");
        printf("Staff account modified successfully.\n");
    }
}

void display_staff(Staff staff[], int num_staff) {
    system("cls");
    Staff stf;

    printf("\n%-10s %-30s %-10s %-10s %-20s %-20s %-20s\n","Staff ID","Name", "Birth Date", "Salary", "Password", "Password Recovery", "Position");
    printf("========================================================================================================================\n");

    FILE *fp = fopen("staff.txt" ,"r");

while(!feof(fp)){
        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", stf.staffID, stf.name, &stf.dob.day, &stf.dob.month, &stf.dob.year, &stf.salary, stf.password, stf.recovery, stf.position);
        printf("%-10s %-30s %02d/%02d/%04d %-10.2f %-20s %-20s %-20s\n", stf.staffID,stf.name, stf.dob.day, stf.dob.month, stf.dob.year, stf.salary, stf.password, stf.recovery, stf.position);
    }
    fclose(fp);

    system("pause");
}

void display_staff_annual_report(Staff staff[]) {
    system("cls");

    char staffLogID[50];
    int i;
    int found = 0;
    double salary_monthly;
    double ePF_monthly;
    double sOCSO_monthly;

    FILE* fp = fopen("staff.txt", "r");
    printf("\nEnter Staff ID to Display Login Report for: ");
    scanf("%s", staffLogID);

    for (i = 0; i < MAX_STAFF; i++) {

        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", staff[i].staffID, staff[i].name, &staff[i].dob.day, &staff[i].dob.month, &staff[i].dob.year, &staff[i].salary, staff[i].password, staff[i].recovery, staff[i].position);

        salary_monthly = staff[i].salary / 12;
        ePF_monthly = salary_monthly * 0.11;
        sOCSO_monthly = salary_monthly * 0.02;

        if (strcmp(staffLogID, staff[i].staffID) == 0) {
            printf("=========================================\n");
            printf("||         Staff account found         ||\n");
            printf("=========================================\n");
            printf("||Name          || %-20s||\n", staff[i].name);
            printf("||Position      || %-20s||\n", staff[i].position);
            printf("||Salary        || %-20.2f||\n", staff[i].salary);
            printf("||Salary Monthly|| %-20.2f||\n", salary_monthly);
            printf("||EPF Monthly   || %-20.2f||\n", ePF_monthly);
            printf("||SOCSO Monthly || %-20.2f||\n", sOCSO_monthly);
            printf("=========================================\n");
            found = 1;
            break;
        }
    }


    if (!found) {
        printf("Staff account not found.\n");
    }

    fclose(fp);
    system("pause");
}

void delete_staff(Staff staff[], int* num_staff) {
    char staffID[50];
    int i = 0, j = 0;
    int found = 0;
    Staff tempStf[100];

    printf("\nEnter Staff ID to delete: ");
    scanf("%s", staffID);

    FILE* fp = fopen("staff.txt", "r");
    while (!feof(fp)) {

        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%lf,%[^,],%[^,],%[^\n]\n", tempStf[i].staffID, tempStf[i].name, &tempStf[i].dob.day, &tempStf[i].dob.month, &tempStf[i].dob.year, &tempStf[i].salary, tempStf[i].password, tempStf[i].recovery, tempStf[i].position);

        if (strcmp(staffID, tempStf[i].staffID) == 0) {
            printf("Staff account found:\n");
            printf("Staff ID: %s\n", tempStf[i].staffID);
            printf("Name: %s\n", tempStf[i].name);
            printf("Date of Birth: %d/%d/%d\n", tempStf[i].dob.day, tempStf[i].dob.month, tempStf[i].dob.year);
            printf("Salary: %.2f\n", tempStf[i].salary);
            printf("Password: %s\n", tempStf[i].password);
            printf("Password Recovery: %s\n", tempStf[i].recovery);
            printf("Position: %s\n", tempStf[i].position);

            printf("Are you sure you want to delete this staff account? (y/n): ");
            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                found = 1;
                fclose(fp);
                FILE* fp = fopen("staff.txt", "w");
                for (j = 0; j < i; j++) {

                    if (strcmp(tempStf[j].staffID, staffID) != 0)
                    {
                        fprintf(fp, "%s,%s,%d/%d/%d,%.2f,%s,%s,%s\n", tempStf[j].staffID, tempStf[j].name, tempStf[j].dob.day, tempStf[j].dob.month, tempStf[j].dob.year, tempStf[j].salary, tempStf[j].password, tempStf[j].recovery, tempStf[j].position);
                    }

                }
                printf("The Staff account has been delete");
                break;
                fclose(fp);
            }

        }
        i++;

    }

    if (!found) {
        printf("Staff account cancel delete.\n");
    }
    fclose(fp);
    system("pause");
}