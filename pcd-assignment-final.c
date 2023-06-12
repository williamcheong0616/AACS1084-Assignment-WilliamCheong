#include<stdio.h>       
#include<stdlib.h>
#include<string.h>       //strcmp ,strcpy
#pragma warning(disable:4996)
#define MAX_STAFF 100

#pragma region Structures
//struct for day/month/year
typedef struct {
    int day, month, year;
}Date;

//struct for applydate and expiredate
typedef struct {
    Date date;
}MemDate;                    

// Member Information Module
typedef struct
{
    char memberID[6];
    char name[50];
    char gender[2];
    char IC[15];
    char contactNum[20];
    char uplineID[6];
    MemDate applydate, expdate;
} Member;

// Sales Information Module
typedef struct
{
    char salesOrderID[6];
    char itemCode[7];
    int quantityOrdered;
    double price;
    char memberID[6];

} Sales;


typedef struct {
    char staffID[15];
    char name[50];
    Date dob;
    float salary;
    char password[20];
    char recovery[20];
    char position[20];
} Staff;


typedef struct
{
    char itemCode[7];
    char itemDesc[50];
    float price;
    int quantityInStock;
    int minLevel;
    int reorderQty;
} Stock;
#pragma endregion

#pragma region Functions
int staffmain();
void membermain();
void salesmain();
int stockmain();

#pragma region Staff functions
void add_staff(Staff staff[], int* num_staff);
void search_staff(Staff staff[]);
void modify_staff(Staff staff[], int num_staff);
void display_staff(Staff staff[], int num_staff);
void display_staff_annual_report(Staff staff[]);
void delete_staff(Staff staff[], int* num_staff);
#pragma endregion

#pragma region Member functions
//function declaration
void addMember(FILE* fp);
void searchMember(FILE* fp);
void modifyMember(FILE* fp);
void displayMember(FILE* fp);
void reportMember(FILE* fp);
void deleteMember(FILE* fp);
#pragma endregion

#pragma region Sales functions
void addSales(FILE* file);
void searchSales(FILE* file, FILE* fp);
void modifySales(FILE* file, FILE* fp);         //file = binary file for sales
void displayAllSales(FILE* file, FILE* fp); //fp= text file of member
void reportSales(FILE* file, FILE* fp);
void deleteSales(FILE* file);
double commissionSales();
#pragma endregion

#pragma region Stock functions
void addStock(Stock tempStock[], int* i);
void searchStock(Stock tempStock[], int* i);
void modifyStock(Stock tempStock[], int* i);
void displayAllStock(Stock tempStock[], int* i);
void deleteStock(Stock tempStock[], int* size);
void displayReport(Stock tempStock[], int* i, int reportType);
void reportTypeSelection(Stock tempStock[], int* i);
#pragma endregion
#pragma endregion


int main()
{
    int choice;
    system("cls");
    printf("\t\t\t .----------------.  .----------------.  .----------------.   \n");
    printf("\t\t\t| .--------------. || .--------------. || .--------------. |  \n");
    printf("\t\t\t| | _____  _____ | || | ____    ____ | || |  _________   | |  \n");
    printf("\t\t\t| ||_   _||_   _|| || ||_   \\  /   _|| || | |  _   _  |  | |  \n");
    printf("\t\t\t| |  | |    | |  | || |  |   \\/   |  | || | |_/ | | \\_|  | |  \n");
    printf("\t\t\t| |  | '    ' |  | || |  | |\\  /| |  | || |     | |      | |  \n");
    printf("\t\t\t| |   \\ `--' /   | || | _| |_\\/_| |_ | || |    _| |_     | |  \n");
    printf("\t\t\t| |    `.__.'    | || ||_____||_____|| || |   |_____|    | |  \n");
    printf("\t\t\t| |              | || |              | || |              | |  \n");
    printf("\t\t\t| '--------------' || '--------------' || '--------------' |  \n");
    printf("\t\t\t '----------------'  '----------------'  '----------------'   \n");
    printf("\n\n");
    printf("\t\t\t .----------------.  .----------------.  .----------------.   \n");
    printf("\t\t\t| .--------------. || .--------------. || .--------------. |  \n");
    printf("\t\t\t| | ____    ____ | || |   _____      | || | ____    ____ | |  \n");
    printf("\t\t\t| ||_   \\  /   _|| || |  |_   _|     | || ||_   \\  /   _|| |  \n");
    printf("\t\t\t| |  |   \\/   |  | || |    | |       | || |  |   \\/   |  | |  \n");
    printf("\t\t\t| |  | |\\  /| |  | || |    | |   _   | || |  | |\\  /| |  | |  \n");
    printf("\t\t\t| | _| |_\\/_| |_ | || |   _| |__/ |  | || | _| |_\\/_| |_ | |  \n");
    printf("\t\t\t| ||_____||_____|| || |  |________|  | || ||_____||_____|| |  \n");
    printf("\t\t\t| |              | || |              | || |              | |  \n");
    printf("\t\t\t| '--------------' || '--------------' || '--------------' |  \n");
    printf("\t\t\t '----------------'  '----------------'  '----------------'   \n");


    system("pause");
    system("cls");

    do
    {
        system("cls");
        printf("\nMenu\n");
        printf("================================\n");
        printf("|1. Staff Information Module   |\n");
        printf("|2. Member Information Module  |\n");
        printf("|3. Sales Information Module   |\n");
        printf("|4. Stock Information Module   |\n");
        printf("|5. Exit                       |\n");
        printf("================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            staffmain();
            break;
        case 2:
            membermain();
            break;

        case 3:
            salesmain();
            break;

        case 4:
            stockmain();
            break;

        case 5:
            // Exit the program
            printf("Exiting the program... Goodbye!\n");
            break;

        default:
            printf("\nInvalid choice\n");
            system("pause");
            break;
        }

    } while (choice != 5);

    return 0;
}

#pragma region Staff management
int staffmain() {
    Staff staff[MAX_STAFF];
    int num_staff = 0;
    char username[50];
    char password[50];
    char staffID[15];
    int choice;

    system("cls");

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
        printf("================================\n");
        printf("|1. Add new staff account      |\n");
        printf("|2. Search for staff account   |\n");
        printf("|3. Modify staff account       |\n");
        printf("|4. Display all staff accounts |\n");
        printf("|5. Display staff login report |\n");
        printf("|6. Delete staff account       |\n");
        printf("|7. Exit                       |\n");
        printf("================================\n");
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
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_staff(Staff staff[], int* num_staff) {

    char staffID[15];
    int i = 0;

    system("cls");
    if (*num_staff >= MAX_STAFF) {
        printf("Error: Maximum number of staff accounts reached.\n");
        return;
    }

    rewind(stdin);
    printf("\nEnter Staff ID (SXXX)          : ");
    scanf("%s", staffID);
    rewind(stdin);

    int a = 0;
    FILE* fstf = fopen("staff.txt", "r");
    if (fstf == NULL) {
        printf("File unable to open");
        return;
    }
    while (!feof(fstf)) {

        fscanf(fstf, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", staff[i].staffID, staff[i].name, &staff[i].dob.day, &staff[i].dob.month, &staff[i].dob.year, &staff[i].salary, staff[i].password, staff[i].recovery, staff[i].position);
        i++;
    }

    for (a = 0; a < i; a++) {
        if (strcmp(staff[a].staffID, staffID) == 0) {
            printf("Staff already exist!\n");
            system("pause");
            return;
        }
        
    }

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
    fprintf(fp, "%s,%s,%d/%d/%d,%.2f,%s,%s,%s\n", staff[*num_staff - 1].staffID, staff[*num_staff - 1].name, staff[*num_staff - 1].dob.day, staff[*num_staff - 1].dob.month, staff[*num_staff - 1].dob.year, staff[*num_staff - 1].salary, staff[*num_staff - 1].password, staff[*num_staff - 1].recovery, staff[*num_staff - 1].position);
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

    for (i = 0; i < MAX_STAFF; i++) {

        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", staff[i].staffID, staff[i].name, &staff[i].dob.day, &staff[i].dob.month, &staff[i].dob.year, &staff[i].salary, staff[i].password, staff[i].recovery, staff[i].position);

        if (strcmp(staffLogID, staff[i].staffID) == 0) {
            printf("=========================================================\n");
            printf("Name             : %s\t\t\t|\n", staff[i].name);
            printf("Date of Birth    : %d/%d/%d\t\t\t\t|\n", staff[i].dob.day, staff[i].dob.month, staff[i].dob.year);
            printf("Salary           : %.2f\t\t\t\t|\n", staff[i].salary);
            printf("Password         : %s\t\t\t\t|\n", staff[i].password);
            printf("Password Recovery: %s\t\t\t\t|\n", staff[i].recovery);
            printf("Position         : %s\t\t\t\t|\n", staff[i].position);
            found = 1;
            break;
        }
    }


    if (!found) {
        printf("Staff account not found.\n");
    }
    fclose(fp);

    printf("=========================================================\n");
    printf("Staff account found\n");

    system("pause");
}

void modify_staff(Staff staff[], int num_staff) {
    system("cls");

    char staffID[50];
    int i = 0, a;
    int found = 0;
    Staff temp[MAX_STAFF];
    FILE* fp = fopen("staff.txt", "r");

    while (!feof(fp)) {
        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", temp[i].staffID, temp[i].name, &temp[i].dob.day, &temp[i].dob.month, &temp[i].dob.year, &temp[i].salary, temp[i].password, temp[i].recovery, temp[i].position);
        i++;
    }

    printf("\nEnter Staff ID to Modify for: ");
    scanf("%s", staffID);



    for (a = 0; a < i; a++) {

        //scan the staff data from text file
        if (strcmp(temp[a].staffID, staffID) == 0) {

            printf("Staff account found\n");
            printf("=========================================================\n");
            printf("Name             : %s\t\t\t|\n", temp[a].name);
            printf("Date of Birth    : %d/%d/%d\t\t\t\t|\n", temp[a].dob.day, temp[a].dob.month, temp[a].dob.year);
            printf("Salary           : %.2f\t\t\t\t|\n", temp[a].salary);
            printf("Password         : %s\t\t\t\t|\n", temp[a].password);
            printf("Password Recovery: %s\t\t\t\t|\n", temp[a].recovery);
            printf("Position         : %s\t\t\t\t|\n", temp[a].position);
            printf("=========================================================\n");
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
        for (a = 0; a < i; a++) {
            fprintf(fp, "%s,%s,%d/%d/%d,%.2f,%s,%s,%s\n", temp[a].staffID, temp[a].name, temp[a].dob.day, temp[a].dob.month, temp[a].dob.year, temp[a].salary, temp[a].password, temp[a].recovery, temp[a].position);
        }
        fclose(fp);

        printf("======================================================\n");
        printf("Staff account modified successfully.\n");
        system("pause");
    }
}

void display_staff(Staff staff[], int num_staff) {
    system("cls");
    Staff stf;
    printf("=================================================================================================================================\n");
    printf("|%-10s %-30s %-10s %-10s %-20s %-20s %-20s\t|\n", "Staff ID", "Name", "Birth Date", "Salary", "Password", "Password Recovery", "Position");
    printf("=================================================================================================================================\n");

    FILE* fp = fopen("staff.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", stf.staffID, stf.name, &stf.dob.day, &stf.dob.month, &stf.dob.year, &stf.salary, stf.password, stf.recovery, stf.position);
        printf("|%-10s %-30s %02d/%02d/%04d %-10.2f %-20s %-20s %-20s\t|\n", stf.staffID, stf.name, stf.dob.day, stf.dob.month, stf.dob.year, stf.salary, stf.password, stf.recovery, stf.position);
    }
    fclose(fp);
    printf("=================================================================================================================================\n\n");
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

        fscanf(fp, "%[^,],%[^,],%d/%d/%d,%f,%[^,],%[^,],%[^\n]\n", tempStf[i].staffID, tempStf[i].name, &tempStf[i].dob.day, &tempStf[i].dob.month, &tempStf[i].dob.year, &tempStf[i].salary, tempStf[i].password, tempStf[i].recovery, tempStf[i].position);

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
                printf("======================================================\n");
                printf("The Staff account has been delete.\n");
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
#pragma endregion

#pragma region Member management
void membermain() {
    Date date;
    MemDate applydate, expdate;

    int slct, exit = 1;
    char cont;
    Member member;
    FILE* fp;

    do {
        //to make every looping can reopen the file
        fp = fopen("member.txt", "a");
        if (fp == NULL) {
            printf("Error\n");

        }
        //member's module menu
        system("cls");
       
        printf("Member's Menu\n"
            "=========================================\n"
            "||1.Add the new members                ||\n"
            "||2.Search member information          ||\n"
            "||3.Modify member information          ||\n"
            "||4.Display all the member information ||\n"
            "||5.Display member report              ||\n"
            "||6.Delete member                      ||\n"
            "||7.Return to main menu                ||\n"
            "=========================================\n"
            "Enter your selection:");
        //loop when invalid selection
        do {
            scanf("%d", &slct);
            switch (slct) {
            case 1:
                addMember(fp);
                exit = 1;
                break;
            case 2:
                searchMember(fp);
                exit = 1;
                break;
            case 3:
                modifyMember(fp);
                exit = 1;
                break;
            case 4:
                displayMember(fp);
                exit = 1;
                break;
            case 5:
                reportMember(fp);
                exit = 1;
                break;
            case 6:
                deleteMember(fp);
                exit = 1;
                break;
            case 7:
                exit = 10;  //set the value to exit the program
                break;
            default:
                printf("Invalid selection,try again\n"); //tell user invalid code for selection
                exit = 0;
            }
        } while (exit == 0); //when user type invalid code , loop the selection

        if (exit != 10) { //avoid EXIT selection to ask the user go to menu or not
            printf("Return to member's menu? (Y/N)"); //if 'Y' loop again , 'N' end the member's module
            scanf(" %c", &cont);
        }
        else { cont = 'n'; } //direct quit the system
    } while (cont == 'Y' || cont == 'y');
}

void addMember(FILE* fp) {
    Member member, mem[100];
    int i = 0, a, exist = 0;
    char cont;
    fclose(fp);
    fp = fopen("member.txt", "r"); if (fp == NULL) { printf("Error\n"); exit(-1); }

    while (!feof(fp)) { //read the text file
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            mem[i].memberID, mem[i].name, mem[i].gender, mem[i].IC,
            mem[i].contactNum, mem[i].uplineID,
            &mem[i].applydate.date.day, &mem[i].applydate.date.month,
            &mem[i].applydate.date.year,
            &mem[i].expdate.date.day, &mem[i].expdate.date.month, &mem[i].expdate.date.year);
        i++;
    }
    do {

        system("cls");
        do {
            exist = 0;
            printf("Enter ID (AXXXX):");
            scanf(" %s", member.memberID);
            for (a = 0; a < i; a++) {
                if (strcmp(mem[a].memberID, member.memberID) == 0)  //if ID exist
                {
                    printf("This member already exist!\n");
                    exist = 1;
                }
            }
        } while (exist == 1); //end the loop when no member ID not exist

        rewind(stdin);
        printf("Enter Name:");
        scanf(" %[^\n]", member.name);

        rewind(stdin);
        printf("Enter Gender(M/F):");
        scanf("%s", member.gender);

        printf("Enter IC:");
        scanf(" %s", member.IC);

        printf("Enter Contact number:");
        scanf(" %s", member.contactNum);

        printf("Enter uplineID (UXXXX):");
        scanf(" %s", member.uplineID);

        printf("Enter Apply's day (DD):");
        scanf("%d", &member.applydate.date.day);

        printf("Enter Apply's month (MM):");
        scanf("%d", &member.applydate.date.month);

        printf("Enter Apply's year (YYYY):");
        scanf("%d", &member.applydate.date.year);

        printf("Sure to add? (Y/N)");
        scanf(" %c", &cont);
        if (cont == 'y' || cont == 'Y') { //ask user to confirm the process
            fclose(fp); fp = fopen("member.txt", "a"); //open for append mode
            //exp date is apply date after 2 year, day and month same as apply date
            member.expdate.date.day = member.applydate.date.day;
            member.expdate.date.month = member.applydate.date.month;
            member.expdate.date.year = member.applydate.date.year + 2;

            fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                member.memberID, member.name, member.gender, member.IC, member.contactNum, member.uplineID,
                member.applydate.date.day, member.applydate.date.month, member.applydate.date.year,
                member.expdate.date.day, member.expdate.date.month, member.expdate.date.year);

            printf("Successful to add member.\n");
        }
        else printf("Unsuccessful to add member.\n"); //cancel addition of member
        printf("Continue to add another member? (Y/N)");
        scanf(" %c", &cont);

        fclose(fp);   //re open the read mode for check the member ID exist or not
        fp = fopen("member.txt", "r"); if (fp == NULL) { printf("Error\n"); exit(-1); }
    } while (cont == 'y' || cont == 'Y');
}

void searchMember(FILE* fp) {
    Member member;
    char searchID[15];
    char cont;
    int record = 0, i = 0;
    fclose(fp);


    do {
        fp = fopen("member.txt", "r");      //because main program opened append mode 
        system("cls");
        printf("Enter ID to search:");
        scanf(" %s", searchID);



        while (!feof(fp)) {

            fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
                member.memberID, member.name, member.gender, member.IC,
                member.contactNum, member.uplineID,
                &member.applydate.date.day, &member.applydate.date.month,
                &member.applydate.date.year,
                &member.expdate.date.day, &member.expdate.date.month, &member.expdate.date.year);
            if (strcmp(member.memberID, searchID) == 0) {

                printf("member information:\n"
                    "=================================================================================================================\n"
                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                    "=================================================================================================================\n"
                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                    member.memberID, member.name, member.gender, member.IC,
                    member.contactNum, member.uplineID,
                    member.applydate.date.day, member.applydate.date.month, member.applydate.date.year,
                    member.expdate.date.day, member.expdate.date.month, member.expdate.date.year);
                record++;

            }

        }
        if (record == 0) { printf("Record not found\n"); }
        printf("=================================================================================================================\n");
        printf("Continue to search? (Y/N)");
        scanf(" %c", &cont);
        fclose(fp);
        record = 0;  //reset the value
    } while (cont == 'y' || cont == 'Y');

}

void modifyMember(FILE* fp) {
    fclose(fp);
    fp = fopen("member.txt", "r");

    char searchID[6], modifyContactNum[20], modifyName[50], modifyGender[2], modifyIC[15];
    char cont;
    int i = 0, a, slct, exit = 1, record = 0;
    Member member, tem[100];

    while (!feof(fp)) {
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
            tem[i].contactNum, tem[i].uplineID,
            &tem[i].applydate.date.day, &tem[i].applydate.date.month,
            &tem[i].applydate.date.year,
            &tem[i].expdate.date.day, &tem[i].expdate.date.month, &tem[i].expdate.date.year);
        i++;
    }
    system("cls");
    printf("Enter the member's ID want to modify:");
    scanf(" %[^\n]", &searchID);
    for (a = 0; a < i; a++) {
        if (strcmp(tem[a].memberID, searchID) == 0) {
            record++;
            system("cls");
            do {
                printf("Modify's Menu\n"
                    "================================\n");
                printf(
                    "|1.Member's name               |\n"
                    "|2.Member's gender (if needed) |\n"
                    "|3.Member's IC                 |\n"
                    "|4.Member's contact number     |\n"
                    "|5.Return to menu              |\n"
                    "================================\n"
                    "Select: ");
                //loop when invalid selection
                do {
                    scanf("%d", &slct);
                    switch (slct) {
                    case 1:  //for name
                        system("cls");
                        printf("Enter member's name to modify:");
                        scanf(" %[^\n]", &modifyName);


                        for (a = 0; a < i; a++) {
                            if (strcmp(tem[a].memberID, searchID) == 0) {

                                printf("BEFORE MODIFY member information:\n\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("=================================================================================================================\n");
                                printf("\nAFTER MODIFY member information:\n\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, modifyName, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("=================================================================================================================\n");

                                printf("Sure to Modify? (Y/N)");
                                scanf(" %c", &cont);
                                if (cont == 'y' || cont == 'Y') {
                                    strcpy(tem[a].name, modifyName);
                                    printf("Modify Successful\n");
                                    system("pause");
                                }
                                else { 
                                    printf("Modify Unsuccessful\n");
                                    system("pause");
                                }
                            }
                            else { continue; } //quit the for loop when modify has been fulfilled

                        }

                        // modify the information of searched ID
                        fclose(fp);
                        fp = fopen("member.txt", "w");
                        for (a = 0; a < i; a++) {
                            fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                                tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC, tem[a].contactNum, tem[a].uplineID,
                                tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                        }
                        fclose(fp);
                        exit = 1;
                        break;
                    case 2: //for gender

                        printf("Enter member's gender to modify:");
                        scanf(" %[^\n]", &modifyGender);


                        for (a = 0; a < i; a++) {
                            if (strcmp(tem[a].memberID, searchID) == 0) {

                                printf("\nBEFORE MODIFY member information:\n\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("=================================================================================================================\n");
                                printf("\nAFTER MODIFY member information:\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, modifyGender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("=================================================================================================================\n");
                                printf("Sure to Modify? (Y/N)");
                                scanf(" %c", &cont);
                                if (cont == 'y' || cont == 'Y') {
                                    strcpy(tem[a].gender, modifyGender);
                                    printf("Modify Successful\n");
                                }
                                else { printf("Modify Unsuccessful\n"); }
                            }
                            else { continue; } //quit the for loop when modify has been fulfilled
                        }

                        // modify the information of searched ID
                        fclose(fp);
                        fp = fopen("member.txt", "w");
                        for (a = 0; a < i; a++) {
                            fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                                tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC, tem[a].contactNum, tem[a].uplineID,
                                tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                        }
                        fclose(fp);
                        exit = 1;
                        break;
                    case 3: //for IC
                        printf("Enter member's IC to modify:");
                        scanf(" %[^\n]", &modifyIC);


                        for (a = 0; a < i; a++) {
                            if (strcmp(tem[a].memberID, searchID) == 0) {

                                printf("\nBEFORE MODIFY member information:\n\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("=================================================================================================================\n");
                                printf("\nAFTER MODIFY member information:\n\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, modifyIC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("=================================================================================================================\n");
                                printf("Sure to Modify? (Y/N)");
                                scanf(" %c", &cont);
                                if (cont == 'y' || cont == 'Y') {
                                    strcpy(tem[a].IC, modifyIC);
                                    printf("Modify Successful\n");
                                }
                                else { printf("Modify Unsuccessful\n"); }
                            }
                            else { continue; } //quit the for loop when modify has been fulfilled

                        }

                        // modify the information of searched ID
                        fclose(fp);
                        fp = fopen("member.txt", "w");
                        for (a = 0; a < i; a++) {
                            fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                                tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC, tem[a].contactNum, tem[a].uplineID,
                                tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                        }
                        fclose(fp);
                        exit = 1;
                        break;
                    case 4: //for contact number
                        printf("Enter member's contact number to modify:");
                        scanf(" %[^\n]", &modifyContactNum);


                        for (a = 0; a < i; a++) {
                            if (strcmp(tem[a].memberID, searchID) == 0) {

                                printf("\nBEFORE MODIFY member information:\n\n"                                    
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("\n=================================================================================================================\n");
                                printf("AFTER MODIFY member information:\n"
                                    "=================================================================================================================\n"
                                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                                    "=================================================================================================================\n"
                                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    modifyContactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("=================================================================================================================\n");
                                printf("Sure to Modify? (Y/N)");
                                scanf(" %c", &cont);
                                if (cont == 'y' || cont == 'Y') {
                                    strcpy(tem[a].contactNum, modifyContactNum);
                                    printf("Modify Successful\n");
                                }
                                else { printf("Modify Unsuccessful\n"); }
                            }
                            else { continue; } //quit the for loop when modify has been fulfilled

                        }

                        // modify the information of searched ID
                        fclose(fp);
                        fp = fopen("member.txt", "w");
                        for (a = 0; a < i; a++) {
                            fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                                tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC, tem[a].contactNum, tem[a].uplineID,
                                tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                        }
                        fclose(fp);
                        exit = 1;
                        break;
                    case 5:
                        exit = 10;  //set the value to exit the program
                        break;
                    default:
                        printf("Invalid selection,try again\n"); //tell user invalid code for selection
                        exit = 0;
                    }
                } while (exit == 0); //when user type invalid code , loop the selection
                system("cls");
            } while (exit != 10);

        }
        else if (exit != 10 && exit != 1) { //to fillter the exit selection and modify selection
            printf("Invalid member's ID.\n");
            break;
        }

    }
    if (record <= 0) {
        printf("Invalid member's ID\n");
    }
}

void displayMember(FILE* fp) {
    system("cls");
    Member member;
    fclose(fp);
    fp = fopen("member.txt", "r");
    printf("member information:\n\n"
        "=================================================================================================================\n"
        "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
        "=================================================================================================================\n");
    while (!feof(fp)) {
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            member.memberID, member.name, member.gender, member.IC,
            member.contactNum, member.uplineID,
            &member.applydate.date.day, &member.applydate.date.month,
            &member.applydate.date.year,
            &member.expdate.date.day, &member.expdate.date.month, &member.expdate.date.year);
        printf(
            "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
            member.memberID, member.name, member.gender, member.IC,
            member.contactNum, member.uplineID,
            member.applydate.date.day, member.applydate.date.month, member.applydate.date.year,
            member.expdate.date.day, member.expdate.date.month, member.expdate.date.year);
    }
    printf("=================================================================================================================\n");
    fclose(fp);
}

void reportMember(FILE* fp) {
    
    Member member, tem[100];
    int reportyear, i = 0, invalid = 0;
    char cont;

    fclose(fp);

    do {
        system("cls");
        printf("Enter the member's year to show report:");
        scanf("%d", &reportyear);


        fp = fopen("member.txt", "r");

        while (!feof(fp)) {
            fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
                tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
                tem[i].contactNum, tem[i].uplineID,
                &tem[i].applydate.date.day, &tem[i].applydate.date.month,
                &tem[i].applydate.date.year,
                &tem[i].expdate.date.day, &tem[i].expdate.date.month, &tem[i].expdate.date.year);

            if (reportyear == tem[i].expdate.date.year) {
                printf("This report shown the member who membership almost expire base on following year:\n\n"
                    "=================================================================================================================\n"
                    "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                    "=================================================================================================================\n"
                    "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                    tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
                    tem[i].contactNum, tem[i].uplineID,
                    tem[i].applydate.date.day, tem[i].applydate.date.month, tem[i].applydate.date.year,
                    tem[i].expdate.date.day, tem[i].expdate.date.month, tem[i].expdate.date.year);
                invalid++;
            }


        }
        if (invalid == 0) {
            printf("invalid year\n");
        }
        printf("=================================================================================================================\n");
        printf("Continue to search? (Y/N)");
        scanf(" %c", &cont);
        fclose(fp);

        
    } while (cont == 'Y' || cont == 'y');
    
}

void deleteMember(FILE* fp) {
    system("cls");
    int i = 0, a, dlt = 0;
    char searchID[6], deleteContactNum[20];
    char cont;
    Member member, tem[100];


    fclose(fp);
    fp = fopen("member.txt", "r");

    printf("Enter the member's ID want to Delete:");
    scanf(" %[^\n]", &searchID);


    while (!feof(fp)) {
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
            tem[i].contactNum, tem[i].uplineID,
            &tem[i].applydate.date.day, &tem[i].applydate.date.month,
            &tem[i].applydate.date.year,
            &tem[i].expdate.date.day, &tem[i].expdate.date.month, &tem[i].expdate.date.year);
        if (strcmp(tem[i].memberID, searchID) == 0) {

            printf("\nmember information:\n"
                "=================================================================================================================\n"
                "|ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\t|\n"
                "=================================================================================================================\n"
                "|%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\t|\n",
                tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
                tem[i].contactNum, tem[i].uplineID,
                tem[i].applydate.date.day, tem[i].applydate.date.month, tem[i].applydate.date.year,
                tem[i].expdate.date.day, tem[i].expdate.date.month, tem[i].expdate.date.year);
            printf("=================================================================================================================\n");
            dlt++; //to make a condition to check searchedID exsit or not
        }
        i++;
    }

    if (dlt > 0)
    {
        printf("Sure to Delete? (Y/N)");
        scanf(" %c", &cont);
        if (cont == 'y' || cont == 'Y') {

            fclose(fp);
            fp = fopen("member.txt", "w");
            for (a = 0; a < i; a++) {

                if (strcmp(tem[a].memberID, searchID) != 0) {
                    fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                        tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC, tem[a].contactNum, tem[a].uplineID,
                        tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                        tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                }
            }
            printf("Delete Successful\n");
            fclose(fp);
        }
        else { printf("Delete Unsuccessful\n"); }
        fclose(fp);
    }
    else { printf("Invalid member's ID.\n"); }
}
#pragma endregion

#pragma region Sales management
void salesmain() {
    int slct;
    Sales sales;
    Member member; //local variable
    FILE* file;
    FILE* fp;
 

    do {
        file = fopen("sales.bin", "rb");
        fp = fopen("member.txt", "r");
        system("cls");
        printf("Sales's Menu\n");
        printf("================================\n");
        printf("|1.Add Sales                   |\n"
               "|2.Search Sales                |\n"
               "|3.Modify Sales                |\n"
               "|4.Display Sales               |\n"
               "|5.Report Sales                |\n"
               "|6.Delete Sales                |\n");
        printf("|7.EXIT                        |\n");
        printf("================================\n");
        printf("selection > ");
        scanf("%d", &slct);

        switch (slct) {
        case 1:addSales(file);
            break;
        case 2:searchSales(file, fp);
            break;
        case 3:modifySales(file, fp);
            break;
        case 4:displayAllSales(file, fp);
            break;
        case 5:reportSales(file, fp);
            break;
        case 6:deleteSales(file);
            break;
        case 7:
            slct = 7;
        }
    } while (slct != 7);
}

void addSales(FILE* file) {     // r mode 
    char cont;
    int found = 0;
    fclose(file); //test
    file = fopen("sales.bin", "ab");
    Sales sales;
    Stock stock[100];

    do {
        system("cls");
        printf("Enter sales order ID: ");
        scanf(" %[^\n]", &sales.salesOrderID);

        printf("Enter item code: ");
        scanf(" %[^\n]", &sales.itemCode);
        FILE* fptr = fopen("stock.bin", "rb");
        int stockCount = 0, a = 0, y = 0;
        while (fread(&stock[stockCount], sizeof(Stock), 1, fptr) != 0) {
            stockCount++;
        }
        fclose(fptr);

        for (y = 0; y < stockCount; y++) {
            if (strcmp(stock[y].itemCode, sales.itemCode) == 0) {

                printf("Enter quantity ordered: ");
                scanf("%d", &sales.quantityOrdered);

                sales.price = stock[y].price * sales.quantityOrdered;
                printf("Price: %.2f * %d = %.2f \n", stock[y].price, sales.quantityOrdered, sales.price);


                printf("Enter Member ID:");
                scanf(" %[^\n]", &sales.memberID);

                fwrite(&sales, sizeof(Sales), 1, file);
                printf("Sales record added successfully!\n");

                stock[y].quantityInStock -= sales.quantityOrdered;
                found = 1;
            }

        }
        
        if (found == 1)
        {
            fptr = fopen("stock.bin", "wb");
            /*for (a = 0; a < stockCount; a++) {
                fwrite(&stock[a], sizeof(Stock), 1, fptr);
            }*/
            fwrite(stock, sizeof(Stock), stockCount, fptr);
            fclose(fptr);
        }
        else if(found == 0) {
          printf("Item code not found\n");
        }
        printf("Continue to add sales? (Y/N)");
        scanf(" %c", &cont);  //y

    } while (cont == 'y' || cont == 'Y');
    system("pause");
    fclose(file);
}

void searchSales(FILE* file, FILE* fp) {
    char cont;
    char salesOrderID[6];
    int found = 0, i = 0;
    Sales sales;
    Member member, mem[100];


    do {
        system("cls");
        printf("Enter sales order ID to search for: ");
        scanf(" %[^\n]", &salesOrderID);
        while (fread(&sales, sizeof(Sales), 1, file) != 0)
        {

            if (strcmp(sales.salesOrderID, salesOrderID) == 0)
            {


                printf("\nSales record found:\n");
                printf("=================================\n");
                printf("|Sales Order ID: %s \t\t|\n", sales.salesOrderID);
                printf("|Item Code: %s \t\t|\n", sales.itemCode);
                printf("|Quantity Ordered: %d \t\t|\n", sales.quantityOrdered);
                printf("|Price: %.2f \t\t\t|\n", sales.price);
                printf("|Member ID: %s \t\t|\n", sales.memberID);
                printf("=================================\n");
                system("pause"); // look output (pause)
                i++;
                found++;

                break;
            }

        }
        if (found <= 0)
        {
            printf("\nSales record not found\n");
            system("pause");

        }
        printf("Continue to search? (Y/N)");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y');

    fclose(file);
    fclose(fp);
}

void displayAllSales(FILE* file, FILE* fp)
{

    system("cls");
    Sales sales;
    Member member;
    printf("\nSales records:\n");
    printf("===================================================================================\n");
    printf("|%-15s %-15s %-20s %-10s %-10s |\n", "Sales Order ID", "Item Code", "Member ID", "Quantity Ordered", "Price");
    printf("===================================================================================\n");
    while (fread(&sales, sizeof(Sales), 1, file) != 0) {

        printf("|%-15s %-15s %-20s %-10d %-10.2f\t  |\n",
            sales.salesOrderID, sales.itemCode, sales.memberID, sales.quantityOrdered, sales.price);
    }
    printf("===================================================================================\n");
    system("pause");
    fclose(file);
    fclose(fp);     //one function cant read two time ,until you close the previous file pointer
}

void modifySales(FILE* file, FILE* fp) {   //X for saleID ,memberID
    int slct, i = 0, a = 0, b, record = 0, remain = 0;
    char modify[6], cont;
    int newQty;
    double newPrice;
    Sales sales, tmpSale[100];
    Member member;


    while (fread(&tmpSale[i], sizeof(Sales), 1, file) != 0)
    {
        i++;
    }
    do {
        system("cls");
        printf("Enter SalesID to modify:");
        scanf(" %[^\n]", &modify);
        for (a = 0; a < i; a++) {

            if (strcmp(tmpSale[a].salesOrderID, modify) == 0) {
                system("cls");
              printf("Sales's Modify Menu\n");
              printf("=================================\n");
             printf("|1.modifySales's Quantity\t|\n"
                    "|2.modifySales's memberID\t|\n"
                    "|3.EXIT to main menu\t\t|\n");
             printf("=================================\n");
                printf("selection > ");
                scanf("%d", &slct);

                switch (slct) {
                case 1:
                    printf("Enter new Quantity:");
                    scanf("%d", &sales.quantityOrdered);
                    tmpSale[a].quantityOrdered = sales.quantityOrdered;
                    system("pause");
                    break;
                case 2:
                    printf("Enter new memberID:");
                    scanf(" %[^\n]", &sales.memberID);
                    strcpy(tmpSale[a].memberID,sales.memberID);

                    //tmpSale[a].price = sales.price;

                    break;
                case 3:
                    slct = 3;
                    break;
                }
                record++;

            }

        }
        //}
        fclose(file);
        file = fopen("sales.bin", "wb");

        for (a = 0; a < i; a++)
        {
            fwrite(&tmpSale[a], sizeof(Sales), 1, file);
        }



        if (record <= 0) {
            printf("\nSales record not found\n");
            system("pause");
        }
        printf("Continue to modify? (Y/N)");
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');
    fclose(file);
    fclose(fp);
}


void reportSales(FILE* file, FILE* fp) {   //main open r mode already , text file also
    Sales sales, tmpSale[100];
    Member member, tem[100];
    int i = 0, a, b, reportRec = 0;
    double comm, commRate;
    char memID[6];

    while (!feof(fp)) {
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
            tem[i].contactNum, tem[i].uplineID,
            &tem[i].applydate.date.day, &tem[i].applydate.date.month,
            &tem[i].applydate.date.year,
            &tem[i].expdate.date.day, &tem[i].expdate.date.month, &tem[i].expdate.date.year);
        i++;
    }
    i = 0; //reset the i for read the binary file
    while (fread(&tmpSale[i], sizeof(Sales), 1, file) != 0) {
        i++;
    }


    system("cls");
    printf("Enter member ID to show report (AXXXX):");    //search member ID to show sales report
    scanf(" %[^\n]", &memID);


    for (a = 0; a < i; a++) {

        if (strcmp(tem[a].memberID, memID) == 0) {
            //b = a;
            //if (strcmp(tem[b].memberID, memID) == 0) {
            //    reportRec++;
            //    printf("\n%-15s %-15s %-20s %-10s %-17s %s\n", "Sales Order ID", "Item Code", "Quantity Ordered", "Price", "Commision Rate", "Commision\n");
            //    printf("============================================================================================================================\n");
            //    printf("%-15s %-15s %-20d %-10.2f ",
            //            tmpSale[a].salesOrderID, tmpSale[a].itemCode, tmpSale[a].quantityOrdered, tmpSale[a].price);
            //    commRate = commissionSales(tmpSale[a].price);  //price= for one qty

            //    comm = ((tmpSale[a].price * tmpSale[a].quantityOrdered) * (commRate / 100));
            //    printf("%.0f%% %19.2f\n", commRate, comm);
            //}
            reportRec++;
            printf("\n%-15s %-15s %-20s %-10s %-17s %s\n", "Sales Order ID", "Item Code", "Quantity Ordered", "Total Price", "Commision Rate", "Commision\n");
            printf("============================================================================================================================\n");
            printf("%-15s %-15s %-20d %-10.2f ",
                tmpSale[a].salesOrderID, tmpSale[a].itemCode, tmpSale[a].quantityOrdered, tmpSale[a].price);
            commRate = commissionSales(tmpSale[a].price);  //price= for one qty

            comm = ((tmpSale[a].price) * (commRate / 100));
            printf("%.0f%% %19.2f\n", commRate, comm);
        }
        //what should report here
    }
    if (reportRec < 0) { //if record =0 (default) , mean no matched ID stored in sales.bin
        printf("Invalid Sales ID.\n");
    }
    system("pause");
    fclose(file);
    fclose(fp);
}

double commissionSales() {
    double rate = 0.05;

   return rate * 100;
}

void deleteSales(FILE* file) {    //main open r mode already

    Sales sales, tmpSale[100];
    char delete[6];
    int i = 0, a, record = 0;

    while (fread(&tmpSale[i], sizeof(Sales), 1, file) != 0) {
        i++;
    }

    system("cls");

    printf("Enter SalesID to delete (SXXXX):");
    scanf(" %[^\n]", &delete);

    for (a = 0; a < i; a++) {
        if (strcmp(tmpSale[a].salesOrderID, delete) == 0) {
            record++;
        }
        if (record > 0) { //if got user input's ID
            fclose(file);  //close the rb mode
            file = fopen("sales.bin", "wb"); //open wb mode
            for (a = 0; a < i; a++) {
                if (strcmp(tmpSale[a].salesOrderID, delete) != 0) {
                    fwrite(&tmpSale[a], sizeof(Sales), 1, file);
                }
            }
            printf("Delete Successful.\n");
            system("pause");
        }

        fclose(file);
    }
    if (record <= 0) { //if record =0 (default) , mean no record had been deleted
        printf("Invalid Sales ID.\n");
        system("pause");
    }
}
#pragma endregion

#pragma region Stock management
int stockmain() {
    int mainMenuChoice, stockMenuChoice, i = 0, a;
    Stock tempStock[999];

    system("cls");

        
        do {
            i = 0;
            FILE * stockFile = fopen("stock.bin", "rb");
            if (stockFile == NULL) {
                printf("File doesn't exist\n");
                exit(-1);
            }
            fseek(stockFile, 0, SEEK_SET);
            while (fread(&tempStock[i], sizeof(tempStock[i]), 1, stockFile) != 0) {
                i++;
            }
            fclose(stockFile);
            printf("Stock Information Module\n");
            printf("================================\n");
            printf("|1. Add new stock record       |\n");
            printf("|2. Search for stock record    |\n");
            printf("|3. Modify stock record        |\n");
            printf("|4. Display all stock records  |\n");
            printf("|5. Delete stock record        |\n");
            printf("|6. Display stock report       |\n");
            printf("|7. Back to main menu          |\n");
            printf("================================\n");
            printf("Enter your choice: ");
            scanf("%d", &stockMenuChoice);
            system("cls");

            switch (stockMenuChoice)
            {
            case 1:
                addStock(tempStock, &i);
                break;
            case 2:
                searchStock(tempStock, &i);
                break;
            case 3:
                modifyStock(tempStock, &i);
                break;
            case 4:
                displayAllStock(tempStock, &i);
                break;
            case 5:
                deleteStock(tempStock, &i);
                break;
            case 6:
                reportTypeSelection(tempStock, &i);
                break;
            case 7:
                printf("Exiting Stock Module...\n");
                system("pause");
                return;
            default:
                printf("Invalid choice\n");
                break;
            }
            fopen("stock.bin", "wb");
            for (a = 0; a < i; a++) {
                fwrite(&tempStock[a], sizeof(tempStock[a]), 1, stockFile);
            }
            fclose(stockFile);
        } while (stockMenuChoice != 7);
        


    }

void addStock(Stock tempStock[], int* i) {
    char choice;
    char addItemCode[7];
    int a, found = 0;


    do {
        found = 0;
        rewind(stdin);
        printf("Enter item code to add Stock (STKxxx, Example: STK001): ");
        scanf("%6s", &addItemCode);
        if (*i == 0) {
            strcpy(tempStock[*i].itemCode, addItemCode);

            printf("Enter item description: ");
            scanf("\n%[^\n]", tempStock[*i].itemDesc);

            printf("Enter item price: ");
            scanf("%f", &tempStock[*i].price);

            printf("Enter quantity in stock: ");
            scanf("%d", &tempStock[*i].quantityInStock);

            printf("Enter minimum level: ");
            scanf("%d", &tempStock[*i].minLevel);

            printf("Enter reorder quantity: ");
            scanf("%d", &tempStock[*i].reorderQty);

            printf("Stock record added successfully!\n");
            ++* i;

        }
        else {
            for (a = 0; a < *i; a++) {
                if (strcmp(addItemCode, tempStock[a].itemCode) == 0) {
                    printf("Item already exist\n");
                    found = 1;
                    break;
                }
            }

            if (found == 0) {
                strcpy(tempStock[*i].itemCode, addItemCode);

                printf("Enter item description: ");
                scanf("\n%[^\n]", tempStock[*i].itemDesc);
                rewind(stdin);

                printf("Enter item price: ");
                scanf("%f", &tempStock[*i].price);

                printf("Enter quantity in stock: ");
                scanf("%d", &tempStock[*i].quantityInStock);

                printf("Enter minimum level: ");
                scanf("%d", &tempStock[*i].minLevel);

                printf("Enter reorder quantity: ");
                scanf("%d", &tempStock[*i].reorderQty);

                printf("Stock record added successfully!\n");
                ++*i;

            }
        }
        do {
            printf("Do you want to add an another stock? (Y/N): ");
            rewind(stdin);
            scanf("%c", &choice);
            choice = toupper(choice);
            if (choice == 'Y' || choice == 'N') {
                system("cls");
                break;
            }
            printf("Invalid input\n");
        } while (1);
    } while (choice == 'Y');
}

void searchStock(Stock tempStock[], int* i) {

    char choice = 'N';
    char addItemCode[7];
    int a, found = 0;
    //Stock stockDetail;

    if (*i == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        do {
            found = 0;
            printf("Enter item code to search for (STKxxx, Example: STK001): ");
            scanf("%6s", addItemCode);

            for (a = 0; a < *i; a++)
            {
                if (strcmp(addItemCode, tempStock[a].itemCode) == 0)
                {

                    system("cls");
                    printf("Stock record found:\n");
                    printf("=================================================\n");
                    printf("|Item Code        : %s\t\t\t|\n", tempStock[a].itemCode);
                    printf("|Item Description : %-15s\t\t|\n", tempStock[a].itemDesc);
                    printf("|Item Price       : %.2f\t\t\t|\n", tempStock[a].price);
                    printf("|Quantity in Stock: %d\t\t\t\t|\n", tempStock[a].quantityInStock);
                    printf("|Minimum Level    : %d\t\t\t\t|\n", tempStock[a].minLevel);
                    printf("|Reorder Quantity : %d\t\t\t\t|\n", tempStock[a].reorderQty);
                    printf("=================================================\n");
                    found = 1;
                    do {
                        printf("Do you want to search an another stock? (Y/N): ");
                        rewind(stdin);
                        scanf("%c", &choice);
                        choice = toupper(choice);
                        if (choice == 'Y' || choice == 'N') {
                            system("cls");
                            break;
                        }
                        printf("Invalid input\n");
                    } while (1);
                }
            }
            if (found == 0) {
                printf("Stock record not found\n\n");
                do {
                    printf("Do you want to search an another stock? (Y/N): ");
                    rewind(stdin);
                    scanf("%c", &choice);
                    choice = toupper(choice);
                    if (choice == 'Y' || choice == 'N') {
                        system("cls");
                        break;
                    }
                    printf("Invalid input\n");
                } while (1);
            }
        } while (choice == 'Y');
    }
}

void modifyStock(Stock tempStock[], int* size) {

    char choice = 'N';
    char modifyItemCode[7];
    int a, found = 0;

    if (*size == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        do {
            printf("Enter item code to modify (STKxxx, Example: STK001): ");
            scanf("%6s", modifyItemCode);
            rewind(stdin);

            for (a = 0; a < *size; a++) {
                if (strcmp(modifyItemCode, tempStock[a].itemCode) == 0) {
                    system("cls");
                    printf("Stock record found:\n");
                    printf("=================================================\n");
                    printf("|Item Code        : %s\t\t\t|\n", tempStock[a].itemCode);
                    printf("|Item Description : %-15s\t\t|\n", tempStock[a].itemDesc);
                    printf("|Item Price       : %.2f\t\t\t|\n", tempStock[a].price);
                    printf("|Quantity in Stock: %d\t\t\t\t|\n", tempStock[a].quantityInStock);
                    printf("|Minimum Level    : %d\t\t\t\t|\n", tempStock[a].minLevel);
                    printf("|Reorder Quantity : %d\t\t\t\t|\n", tempStock[a].reorderQty);
                    printf("=================================================\n");
                    found = 1;

                    printf("\nEnter new item description: ");
                    scanf("\n%[^\n]", tempStock[a].itemDesc);

                    rewind(stdin);

                    printf("Enter new item price: ");
                    scanf("%f", &tempStock[a].price);

                    printf("Enter new quantity in stock: ");
                    scanf("%d", &tempStock[a].quantityInStock);

                    printf("Enter new minimum level: ");
                    scanf("%d", &tempStock[a].minLevel);

                    printf("Enter new reorder quantity: ");
                    scanf("%d", &tempStock[a].reorderQty);

                    printf("Stock record modify successfully!\n");
                    do {
                        printf("Do you want to modify an another stock? (Y/N): ");
                        rewind(stdin);
                        scanf("%c", &choice);
                        choice = toupper(choice);
                        if (choice == 'Y' || choice == 'N') {
                            system("cls");
                            break;
                        }
                        printf("Invalid input\n");
                    } while (1);
                }
            }

            if (found == 0) {
                printf("Stock record not found\n\n");
                do {
                    printf("Do you want to search an another stock? (Y/N): ");
                    rewind(stdin);
                    scanf("%c", &choice);
                    choice = toupper(choice);
                    if (choice == 'Y' || choice == 'N') {
                        system("cls");
                        break;
                    }
                    printf("Invalid input\n");
                } while (1);
            }
        } while (choice == 'Y');
    }
}

void displayAllStock(Stock tempStock[], int* i) {
    int a;

    if (*i == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        printf("\nStock records:\n");
        printf("=================================================================================================================\n");
        printf("|%-12s %-20s %-14s %-22s %-18s %s\t|\n",
            "Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
        printf("=================================================================================================================\n");

        for (a = 0; a < *i; a++) {
            printf("|%-12s %-20s %-14.2f %-22d %-18d %d\t\t\t|\n",
                tempStock[a].itemCode, tempStock[a].itemDesc, tempStock[a].price, tempStock[a].quantityInStock,
                tempStock[a].minLevel, tempStock[a].reorderQty);
        }
        printf("=================================================================================================================\n");
        system("pause");
        system("cls");
    }

}

void deleteStock(Stock tempStock[], int* size) {

    char choice = 'N';
    char itemCodeDelete[7];
    int a, b;
    int found = 0;

    if (*size == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        do {
            printf("Enter item code to delete (STKxxx, Example: STK001): ");
            scanf("%6s", itemCodeDelete);
            rewind(stdin);

            for (a = 0; a < *size; a++) {
                if (strcmp(itemCodeDelete, tempStock[a].itemCode) == 0) {
                    found = 1;
                    printf("Stock record found:\n");
                    printf("=================================================\n");
                    printf("|Item Code        : %s\t\t\t|\n", tempStock[a].itemCode);
                    printf("|Item Description : %-15s\t\t|\n", tempStock[a].itemDesc);
                    printf("|Item Price       : %.2f\t\t\t|\n", tempStock[a].price);
                    printf("|Quantity in Stock: %d\t\t\t\t|\n", tempStock[a].quantityInStock);
                    printf("|Minimum Level    : %d\t\t\t\t|\n", tempStock[a].minLevel);
                    printf("|Reorder Quantity : %d\t\t\t\t|\n", tempStock[a].reorderQty);
                    printf("=================================================\n");
                    do {
                        printf("Are you sure you want to delete this item? (Y/N): ");
                        rewind(stdin);
                        scanf("%c", &choice);
                        choice = toupper(choice);
                        if (choice == 'Y' || choice == 'N') {
                            break;
                        }
                        printf("Invalid input\n");
                    } while (1);

                    if (choice == 'Y') {
                        // shift all items after the deleted item one position to the left
                        for (b = a; b < *size - 1; b++) {
                            tempStock[b] = tempStock[b + 1];
                        }
                        (*size)--; // decrease size of the array
                        printf("Item deleted successfully.\n");
                    }
                    else {
                        printf("Item not deleted.\n");
                    }
                    break; // exit the loop once a match is found
                }

            }

            if (found == 0) {
                printf("Stock record not found\n");
            }

            do {
                printf("\nDo you want to delete another item? (Y/N): ");
                rewind(stdin);
                scanf("%c", &choice);
                choice = toupper(choice);
                if (choice == 'Y' || choice == 'N') {
                    system("cls");
                    found = 0;
                    break;
                }
                printf("Invalid input\n");
            } while (1);


        } while (choice == 'Y');
    }
}

void displayReport(Stock tempStock[], int* i, int reportType) {
    system("cls");
    int a;
    int stockStatus = 0;
    int filterCount = 0;
    Stock filterStock[999];

    for (a = 0; a < *i; a++) {
        if (tempStock[a].quantityInStock >= tempStock[a].minLevel) {
            if (reportType != 2 && reportType != 3)
                continue;
            filterStock[filterCount] = tempStock[a];
            filterCount++;
        }
        else {
            if (reportType != 1 && reportType != 3)
                continue;
            filterStock[filterCount] = tempStock[a];
            filterCount++;
        }
    }

    switch (reportType) {
        case 1:
            printf("Report of low stock\n");
            break;
        case 2:
            printf("Report of item in stock\n");
            break;
        case 3:
            printf("Report of all stock\n");
            break;
    }

    //If no record in file display no record avalible
    if (filterCount == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        printf("Stock records:\n");
        printf("%-10s %-22s %-14s %-20s %-16s %s\n",
            "Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Status");
        printf("================================================================================================================\n");

        for (a = 0; a < filterCount; a++) {
            printf("%-10s %-22s %-14.2f %-20d %-16d ",
                filterStock[a].itemCode, filterStock[a].itemDesc, filterStock[a].price, filterStock[a].quantityInStock,
                filterStock[a].minLevel);
            if (filterStock[a].quantityInStock >= filterStock[a].minLevel) {
                printf("In stock\n");
            }
            else {
                printf("Low stock, please restock\n");                
            }
        }
        system("pause");
        system("cls");
    }
}

void reportTypeSelection(Stock tempStock[], int *i) {
    int reportChoice;
    do {
        printf("======= Report Type =======\n");
        printf("1. Report of item low stock\n");
        printf("2. Report of item in stock\n");
        printf("3. Report of all item\n");
        printf("4. Return to stock menu\n");
        printf("Please enter the report type that you want to display: ");
        scanf("%d", &reportChoice);

        switch (reportChoice) {
        case 1:case 2:case 3:
            displayReport(tempStock, i, reportChoice);
            return;
        case 4:
            return;
        default:
            printf("Invalid chioce\n");
        }
    } while (1);
    
}
#pragma endregion