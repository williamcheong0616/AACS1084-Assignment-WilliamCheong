#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#pragma warning (disable:4996)

// Stock Information Module
typedef struct
{
    char itemCode[7];
    char itemDesc[50];
    float price;
    int quantityInStock;
    int minLevel;
    int reorderQty;
} Stock;

void addStock(Stock tempStock[], int *i);
void searchStock(Stock tempStock[], int *i);
void modifyStock(Stock tempStock[], int *i);
void displayAllStock(Stock tempStock[], int *i);
void deleteStock(Stock tempStock[], int *size);
void displayReport(Stock tempStock[], int *i);

int stockmain() {
    int mainMenuChoice, stockMenuChoice, i = 0, a;
    Stock tempStock[999];
    FILE* stockFile;


    do
    {                
        printf("====== Menu ======\n");
        printf("1. Staff Information Module\n");
        printf("2. Member Information Module\n");
        printf("3. Sales Information Module\n");
        printf("4. Stock Information Module\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &mainMenuChoice);
        system("cls");

        switch (mainMenuChoice)
        {

        case 4:
            stockFile = fopen("stock.bin", "rb");
            if (stockFile == NULL) {
                printf("File doesn't exist\n");
            }
            while (fread(&tempStock[i], sizeof(tempStock[i]), 1, stockFile) != 0) {               
                i++;
            }
            fclose(stockFile);
            do {                              
                printf("====== Stock Information Module ======\n");
                printf("1. Add new stock record\n");
                printf("2. Search for stock record\n");
                printf("3. Modify stock record\n");
                printf("4. Display all stock records\n");
                printf("5. Delete stock record\n");
                printf("6. Display stock report\n");
                printf("7. Back to main menu\n");

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
                    displayReport(tempStock, &i);
                    break;
                case 7:
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
                }
            } while (stockMenuChoice != 7);
            FILE* stockFile = fopen("stock.bin", "wb");
            for (a = 0; a < i; a++) {
                fwrite(&tempStock[a], sizeof(tempStock[a]), 1, stockFile);
            }
            fclose(stockFile);
            break;

        case 5:
            // Exit the program
            printf("Exiting the program... Goodbye!\n");
            break;

        default:
            printf("Invalid choice\n");
            break;
        }

    } while (mainMenuChoice != 5);

    return 0;
}

void addStock(Stock tempStock[], int *i) {
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
            ++*i;

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

void searchStock(Stock tempStock[], int *i) {

    char choice = 'N';
    char addItemCode[7];
    int a ,found = 0;
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
                    printf("Item Code: %s\n", tempStock[a].itemCode);
                    printf("Item Description: %s\n", tempStock[a].itemDesc);
                    printf("Item Price: %.2f\n", tempStock[a].price);
                    printf("Quantity in Stock: %d\n", tempStock[a].quantityInStock);
                    printf("Minimum Level: %d\n", tempStock[a].minLevel);
                    printf("Reorder Quantity: %d\n", tempStock[a].reorderQty);
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
            if(found == 0) {
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

void modifyStock(Stock tempStock[], int *size) {

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
                    printf("Item Code: %s\n", tempStock[a].itemCode);
                    printf("Item Description: %s\n", tempStock[a].itemDesc);
                    printf("Item Price: %.2f\n", tempStock[a].price);
                    printf("Quantity in Stock: %d\n", tempStock[a].quantityInStock);
                    printf("Minimum Level: %d\n", tempStock[a].minLevel);
                    printf("Reorder Quantity: %d\n", tempStock[a].reorderQty);
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

            if(found == 0) {
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

void displayAllStock(Stock tempStock[], int *i) {
    int a;

    if (*i == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        printf("\nStock records:\n");
        printf("%-10s %-15s %-20s %-18s %-15s %-18s\n",
            "Item Code", "Item Description", "Item Price", "Qty in Stock", "Minimum Level", "Reorder Quantity");

        for (a = 0; a < *i; a++) {
            printf("%-15s %-20s %-18.2f %-15d %-18d %-18d\n",
                tempStock[a].itemCode, tempStock[a].itemDesc, tempStock[a].price, tempStock[a].quantityInStock,
                tempStock[a].minLevel, tempStock[a].reorderQty);
        }
        system("pause");
        system("cls");
    }
    
}

void deleteStock(Stock tempStock[], int *size) {

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
                    printf("Item Code: %s\n", tempStock[a].itemCode);
                    printf("Item Description: %s\n", tempStock[a].itemDesc);
                    printf("Item Price: %.2f\n", tempStock[a].price);
                    printf("Quantity in Stock: %d\n", tempStock[a].quantityInStock);
                    printf("Minimum Level: %d\n", tempStock[a].minLevel);
                    printf("Reorder Quantity: %d\n", tempStock[a].reorderQty);

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
                printf("\nAre you sure you want to delete another item? (Y/N): ");
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

void displayReport(Stock tempStock[], int *i) {
    int a;
    int stockStatus = 0;

    //If no record in file display no record avalible
    if (*i == 0) {
        printf("No record avaliable\n");
        system("pause");
        system("cls");
    }
    else {
        printf("Stock records:\n");
        printf("%-10s %-22s %-14s %-15s %-16s %s\n",
            "Item Code", "Item Description", "Item Price", "Qty in Stock", "Minimum Level", "Status");
        printf("==================================================================================================\n");

        for (a = 0; a < *i; a++) {
            if (tempStock[a].quantityInStock >= tempStock[a].minLevel) {
                printf("%-15s %-20s %-14.2f %-13d %-12d %s\n",
                    tempStock[a].itemCode, tempStock[a].itemDesc, tempStock[a].price, tempStock[a].quantityInStock,
                    tempStock[a].minLevel, "In stock");
            }
            else {
                printf("%-15s %-20s %-14.2f %-15d %-12d %s\n",
                    tempStock[a].itemCode, tempStock[a].itemDesc, tempStock[a].price, tempStock[a].quantityInStock,
                    tempStock[a].minLevel, "Low stock, please restock");
            }
        }
        system("pause");
        system("cls");
    }
    
}