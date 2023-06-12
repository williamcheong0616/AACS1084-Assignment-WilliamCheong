#include<stdio.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable:4996)

//function declaration
void addMember(FILE*fp);
void searchMember(FILE*fp);
void modifyMember(FILE*fp);
void displayMember(FILE*fp);
void reportMember(FILE* fp);
void deleteMember(FILE*fp);
   

//struct for day/month/year
typedef struct {
    int day,month,year;
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

void membermain() {
    Date date;
    MemDate applydate, expdate;
    
    int slct,exit=1;
    char cont;
    Member member;
    FILE* fp;
   
    do {
        //to make every looping can reopen the file
        fp = fopen("membertest.txt", "a");
        if (fp == NULL) {
            printf("Error\n");
		
        }
        //member's module menu
            system("cls");
            printf("Member's Menu\n=============\n");
            printf("1.addMember\n"
                "2.searchMember\n"
                "3.ModifyMember\n"
                "4.displayMember\n"
                "5.reportMember\n"
                "6.DeleteMember\n"
                "7.EXIT\n"
                "select:");
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
        } while (exit==0); //when user type invalid code , loop the selection

        if (exit != 10) { //avoid EXIT selection to ask the user go to menu or not
            printf("turn to member's menu? (Y/N)"); //if 'Y' loop again , 'N' end the member's module
            scanf(" %c", &cont);
        }
        else { cont = 'n'; } //direct quit the system
    } while (cont=='Y'||cont=='y');
}

void addMember(FILE*fp) {   
    Member member,mem[100];
    int i = 0,a,exist=0;
    char cont;
    fclose(fp);
    fp = fopen("membertest.txt", "r"); if (fp == NULL) { printf("Error\n"); exit(-1); }

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
                fclose(fp); fp = fopen("membertest.txt","a"); //open for append mode
                //exp date is apply date after 2 year, day and month same as apply date
                member.expdate.date.day = member.applydate.date.day;
                member.expdate.date.month = member.applydate.date.month;
                member.expdate.date.year = member.applydate.date.year + 2;

                fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                    member.memberID, member.name,member.gender, member.IC, member.contactNum, member.uplineID,
                    member.applydate.date.day, member.applydate.date.month, member.applydate.date.year,
                    member.expdate.date.day, member.expdate.date.month, member.expdate.date.year);

                printf("Successful to add member.\n");
            }
            else printf("Unsuccessful to add member.\n"); //cancel addition of member
            printf("Continue to add other member? (Y/N)");
            scanf(" %c", &cont);

        fclose(fp);   //re open the read mode for check the member ID exist or not
        fp = fopen("membertest.txt", "r"); if (fp == NULL) { printf("Error\n"); exit(-1); }
    } while (cont == 'y' || cont == 'Y');
}

void searchMember(FILE*fp){
    Member member;
    char searchID[15];
    char cont;
    int record=0,i=0;
    fclose(fp);
   

    do {
        fp = fopen("membertest.txt", "r");      //because main program opened append mode 
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
                    "===========================================================================================================\n"
                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                    "===========================================================================================================\n"
                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                    member.memberID, member.name, member.gender, member.IC,
                    member.contactNum, member.uplineID,
                    member.applydate.date.day, member.applydate.date.month, member.applydate.date.year,
                    member.expdate.date.day, member.expdate.date.month, member.expdate.date.year);
                record++;

            }

        }
        if (record == 0) { printf("Record not found\n"); }
        printf("===========================================================================================================\n");
        printf("Continue to search? (Y/N)");
        scanf(" %c", &cont);
        fclose(fp);
        record = 0;  //reset the value
    } while (cont=='y'||cont=='Y');
  
}

void modifyMember(FILE*fp) {
    fclose(fp);
    fp = fopen("membertest.txt","r");

    char searchID[6],modifyContactNum[20],modifyName[50],modifyGender[2],modifyIC[15];
    char cont;
    int i=0,a,slct,exit=1,record=0;
    Member member,tem[100];

    while(!feof(fp)){
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
            tem[i].contactNum, tem[i].uplineID,
            &tem[i].applydate.date.day,&tem[i].applydate.date.month,
            &tem[i].applydate.date.year,
            &tem[i].expdate.date.day,&tem[i].expdate.date.month,&tem[i].expdate.date.year);
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
                printf("Modify's Menu\n==============\n");
                printf(
                    "1.Member's name\n"
                    "2.Member's gender (if needed)\n"
                    "3.Member's IC\n"
                    "4.Member's contact number\n"
                    "5.turn to menu\n"
                    "select:\n");
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
                                    //"===========================================================================================================\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("===========================================================================================================\n");
                                printf("\nAFTER MODIFY member information:\n\n"
                                    //"===========================================================================================================\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, modifyName, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("===========================================================================================================\n");

                                printf("Sure to Modify? (Y/N)");
                                scanf(" %c", &cont);
                                if (cont == 'y' || cont == 'Y') {
                                    strcpy(tem[a].name, modifyName);
                                    printf("Modify Successful\n");
                                }
                                else { printf("Modify Unsuccessful\n"); }
                            }
                            else { continue; } //quit the for loop when modify has been fulfilled

                        }

                        // modify the information of searched ID
                        fclose(fp);
                        fp = fopen("membertest.txt", "w");
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
                                    //"===========================================================================================================\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("===========================================================================================================\n");
                                printf("\nAFTER MODIFY member information:\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "==============================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, tem[a].name, modifyGender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("===========================================================================================================\n");
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
                        fp = fopen("membertest.txt", "w");
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
                                    "===========================================================================================================\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("\nAFTER MODIFY member information:\n\n"
                                    "===========================================================================================================\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, modifyIC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);

                                printf("===========================================================================================================\n");
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
                        fp = fopen("membertest.txt", "w");
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
                                    //"===========================================================================================================\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    tem[a].contactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("\n===========================================================================================================\n");
                                printf("AFTER MODIFY member information:\n"
                                    "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                                    "===========================================================================================================\n"
                                    "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                                    tem[a].memberID, tem[a].name, tem[a].gender, tem[a].IC,
                                    modifyContactNum, tem[a].uplineID,
                                    tem[a].applydate.date.day, tem[a].applydate.date.month, tem[a].applydate.date.year,
                                    tem[a].expdate.date.day, tem[a].expdate.date.month, tem[a].expdate.date.year);
                                printf("===========================================================================================================\n");
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
                        fp = fopen("membertest.txt", "w");
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
            }while (exit!=10);
            
        }
         else if(exit!=10 && exit!=1){ //to fillter the exit selection and modify selection
            printf("invalid member's ID.\n");     
            break;
        }

    }
    if (record <= 0) {
        printf("Invalid member's ID\n");
    }
}

void displayMember(FILE*fp) {
    Member member;
    fclose(fp);
    fp = fopen("membertest.txt", "r");
    printf("member information:\n\n"
        "===========================================================================================================\n"
        "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
        "===========================================================================================================\n");
        while (!feof(fp)) {
        fscanf(fp,"%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            member.memberID, member.name, member.gender, member.IC,
            member.contactNum, member.uplineID,
            &member.applydate.date.day, &member.applydate.date.month,
            &member.applydate.date.year,
            &member.expdate.date.day, &member.expdate.date.month, &member.expdate.date.year);
        printf(
            "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
            member.memberID, member.name, member.gender, member.IC,
            member.contactNum, member.uplineID,
            member.applydate.date.day, member.applydate.date.month, member.applydate.date.year,
            member.expdate.date.day, member.expdate.date.month, member.expdate.date.year);
        }
        printf("===========================================================================================================\n");
    fclose(fp);
}

void reportMember(FILE* fp) {
    Member member,tem[100];
    int reportyear,i=0,invalid=0;

    printf("Enter the member's year to show report:");
    scanf("%d", &reportyear);

    fclose(fp);
    fp = fopen("membertest.txt", "r");

    while (!feof(fp)) {
        fscanf(fp, "%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%[^\,],%d,%d,%d,%d,%d,%d\n",
            tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
            tem[i].contactNum, tem[i].uplineID,
            &tem[i].applydate.date.day, &tem[i].applydate.date.month,
            &tem[i].applydate.date.year,
            &tem[i].expdate.date.day, &tem[i].expdate.date.month, &tem[i].expdate.date.year);

        if (reportyear == tem[i].expdate.date.year) {
            printf("This report shown the member who membership almost expire base on following year:\n\n"
                "===========================================================================================================\n"
                "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                "===========================================================================================================\n"
                "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
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
    fclose(fp);
}

void deleteMember(FILE* fp) {
    int i = 0, a, dlt = 0;
    char searchID[6], deleteContactNum[20];
    char cont;
    Member member, tem[100];


    fclose(fp);
    fp = fopen("membertest.txt", "r");

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
                "ID\tname\t\tgender\tIC\t\tcontact number\tuplineID\tApply Date\tExpire Date\n"
                "==============================================================================================================\n"
                "%-5s\t%-10s\t%-2s\t%-12s\t%-11s\t%-10s\t%d/%d/%d\t%d/%d/%d\n",
                tem[i].memberID, tem[i].name, tem[i].gender, tem[i].IC,
                tem[i].contactNum, tem[i].uplineID,
                tem[i].applydate.date.day, tem[i].applydate.date.month, tem[i].applydate.date.year,
                tem[i].expdate.date.day, tem[i].expdate.date.month, tem[i].expdate.date.year);
            printf("===========================================================================================================\n");
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
            fp = fopen("membertest.txt", "w");
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
    else { printf("invalid member's ID.\n"); }
}