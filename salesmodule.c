#include<stdio.h>       
#include<stdlib.h>
#include<string.h>       //strcmp ,strcpy
#pragma warning(disable:4996)

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

//// Sales Information Module
typedef struct
{
    char salesOrderID[6];
    char itemCode[6];
    int quantityOrdered;
    double price;
    char memberID[6];

} Sales;

void addSales(FILE* file);   
void searchSales(FILE* file, FILE* fp);
void modifySales(FILE* file,FILE*fp);         //file = binary file for sales
void displayAllSales(FILE* file, FILE* fp); //fp= text file of member
void reportSales(FILE* file,FILE*fp);
void deleteSales(FILE* file);
double commissionSales(double rate);

void main() {
    int slct;
    Sales sales;
    Member member; //local variable
    FILE* file;
    FILE* fp;
   
    do {
        file = fopen("sales.bin", "rb");
        fp = fopen("membertest.txt", "r");
    system("cls");
                printf("Sales's Menu\n====\n");
                printf("1.addSales\n"
                    "2.searchSales\n"
                    "3.ModifySales\n"
                    "4.displaySales\n"
                    "5.reportSales\n"
                    "6.DeleteSales\n"
                    "7.EXIT\n");
    
        printf("selection > ");
        scanf("%d", &slct);

        switch (slct) {
        case 1:addSales(file);
            break;
        case 2:searchSales(file,fp);
            break;
        case 3:modifySales(file, fp);
            break;
        case 4:displayAllSales(file, fp);
            break;
        case 5:reportSales(file,fp);
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
    fclose(file);
    file = fopen("sales.bin","ab");
    Sales sales;
    do {
        system("cls");
        printf("Enter sales order ID: ");
        scanf(" %[^\n]", &sales.salesOrderID);
       
        printf("Enter item code: ");
        scanf(" %[^\n]", &sales.itemCode);
        FILE* fptr = fopen("stock.bin","rb");
        int i = 0;
        //while (!feof(fptr)) {
        //    fread(&stock[i], sizeof(Stock), 1, fptr) != 0;
        //    i++;
        //}
        //if(strcmp(sales.itemCode,))
       
        printf("Enter quantity ordered: ");
        scanf("%d", &sales.quantityOrdered);
       
        printf("Enter price: ");
        scanf("%lf", &sales.price);

        printf("Enter Member ID:");
        scanf(" %[^\n]", &sales.memberID);

        fwrite(&sales, sizeof(Sales), 1, file);
        printf("Sales record added successfully!\n");

        printf("Continue to add sales? (Y/N)");
        scanf(" %c", &cont);  //y
    } while (cont == 'y' || cont == 'Y');
      system("pause");
      fclose(file);
}

void searchSales(FILE* file,FILE*fp) {
        char cont;
        char salesOrderID[6];
        int found = 0,i=0;
        Sales sales; 
        Member member,mem[100];
        
            
        do {
            system("cls");
            printf("Enter sales order ID to search for: ");
            scanf(" %[^\n]", &salesOrderID);
            while (fread(&sales, sizeof(Sales), 1, file) != 0)
            {

                if (strcmp(sales.salesOrderID, salesOrderID) == 0)
                {


                    printf("\nSales record found:\n");
                    printf("Sales Order ID: %s\n", sales.salesOrderID);
                    printf("Item Code: %s\n", sales.itemCode);
                    printf("Quantity Ordered: %d\n", sales.quantityOrdered);
                    printf("Price: %.2f\n", sales.price);
                    printf("Member ID: %s\n", sales.memberID);
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

       } while(cont=='y'||cont=='Y');

        fclose(file);
        fclose(fp);
}

void displayAllSales(FILE* file, FILE* fp)
{
   
    
    Sales sales;
    Member member;
    printf("\nSales records:\n");
    printf("%-15s %-15s %-20s %-10s %-10s\n", "Sales Order ID", "Item Code", "Member ID", "Quantity Ordered", "Price\n");
    printf("====================================================================================\n");
    while (fread(&sales, sizeof(Sales), 1, file) != 0) {

        printf("%-15s %-15s %-20s %-10d %-10.2f\n",
            sales.salesOrderID, sales.itemCode,sales.memberID,sales.quantityOrdered, sales.price);
    }
    system("pause");
    fclose(file);   
    fclose(fp);     //one function cant read two time ,until you close the privious file pointer
}

void modifySales(FILE* file, FILE* fp) {   //X for saleID ,memberID
    int slct,i=0,a=0,b,record=0,remain=0;
    char modify[6],cont;
    int newQty;
    double newPrice;
    Sales sales,tmpSale[100];
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
                printf("Sales's Modify Menu\n====\n");
                printf("1.modifySales's Quantity\n"
                    "2.modifySales's Price\n"
                    "3.EXIT to main menu\n");
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
                    printf("Enter new Price:");
                    scanf("%lf", &sales.price);
                    tmpSale[a].price = sales.price;

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
    } while (cont=='y'||cont=='Y');
    fclose(file);
    fclose(fp);
}


void reportSales(FILE* file, FILE* fp) {   //main open r mode already , text file also
    Sales sales, tmpSale[100];
    Member member, tem[100];
    int i = 0, a, reportRec = 0;
    double comm,commRate;
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
            reportRec++;
            printf("\n%-15s %-15s %-20s %-10s %-10s %-10s\n", "Sales Order ID", "Item Code", "Quantity Ordered", "Price", "Commision Rate", "Commision\n");
            printf("============================================================================================================================\n");
            printf("%-15s %-15s %-20d %-10.2f ",
                tmpSale[a].salesOrderID, tmpSale[a].itemCode, tmpSale[a].quantityOrdered, tmpSale[a].price);
             commRate=commissionSales(tmpSale[a].price);  //price= for one qty

             comm =((tmpSale[a].price *tmpSale[a].quantityOrdered)*commRate);
             printf("%.0f%% %-10.2f\n",commRate,comm);
            system("pause");
        }

        //what should report here
   }
    if (reportRec < 0) { //if record =0 (default) , mean no matched ID stored in sales.bin
        printf("Invalid Sales ID.\n");
        system("pause");
    }
    fclose(file);
    fclose(fp);
}



double commissionSales(double sales) {
    double rate;
    //condition of comission ,base on salesman's sales (price)  
    
     if (sales > 0 && sales<=9999) {
        rate = 0.25;
    }
    else if (sales >=10000 && sales <=49999) {
        rate = 0.50;
    }
    else{
        rate = 0.10;
    }
    return rate*100;
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
     if(record<=0){ //if record =0 (default) , mean no record had been deleted
     printf("Invalid Sales ID.\n");
        }
}


