// DSU MICRO-PROJECT OF GROUP NO. 21, CM3I
// Topic - Develop A C Program To Perform Banking Operations Using Appropriate Data Structures

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structure account -> to store all the personal details of the user...
struct account
{
    char fname[20];
    char lname[20];
    char gender[2];
    char dob[12];
    char pnumber[15];
    char anumber[15];
    char address[50];
    char city[15];
    char account_type[10];
};
typedef struct account account;

char username[10][22];
char password[10][22];
char account_no[10][6];
int balanceamt[10];
int total_accs = 0;

// Function declarations...
void heading_display();       // used to display the heading of the bank...
void account_creation();      // used to create a bank account and allot account no. to the user...
void login();                 // used to log in to the created account...
void login_funcs(int acc);    // used to perform login functions like balance, transfer and log out...
void moneytransfer(int acc);  // used to transfer money from one account to the other...
void write_file(account a);   // write the account details and account no. to respective files...
void totalaccscheck();        // used to check total created accounts in the bank...
void fetch_userdetails();     // fetching username and password to respective arrays from file...
void fetch_balance();         // used to fetch balance details of each user from respective file...
void delay(int milliseconds); // used to delay the output of the program...

void main()
{
    int choice;
    for (;;)
    {
        heading_display();
        totalaccscheck();
        delay(1000);
        printf("-------- HOME --------\n");
        printf("**********************\n");
        printf("1 -> CREATE ACCOUNT\n");
        printf("2 -> LOGIN\n");
        printf("3 -> EXIT\n");
        printf("**********************\n");
        printf("ENTER YOUR CHOICE -> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            account_creation();
            break;
        case 2:
            login();
            break;
        case 3:
            printf("\n\nTHANK YOU FOR VISITING...");
            printf("\nHAVE A GOOD DAY...\n");
            getch();
            exit(0);
        default:
            printf("\n\nINVALID CHOICE...");
            printf("\nENTER AGAIN...\n");
            getch();
        }
    }
}

void heading_display()
{
    system("cls");
    printf("******* WELCOME TO SPSR BANK *******\n");
    printf("THE MOST-TRUSTED BANK IN THE COUNTRY\n");
    printf("------------------------------------\n\n");
}

void account_creation()
{
    account a;
    delay(1000);
    heading_display();
    printf("\n\n   ACCOUNT CREATION   \n");
    printf("----------------------\n");
    printf("\nEnter First Name -> ");
    scanf("%s", a.fname);
    printf("\nEnter Last Name -> ");
    scanf("%s", a.lname);
gender:
    printf("\nEnter Gender (M or F) -> ");
    scanf("%s", a.gender);
    if (a.gender[0] != 'M' && a.gender[0] != 'm' && a.gender[0] != 'F' && a.gender[0] != 'f')
    {
        printf("Invalid gender...\n");
        goto gender;
    }
    printf("\nEnter Date of Birth -> ");
    scanf("%s", a.dob);
phno:
    printf("\nEnter Phone Number -> ");
    scanf("%s", a.pnumber);
    if (a.pnumber[10] != '\0')
    {
        printf("Invalid phone number...\n");
        goto phno;
    }
aadhar:
    printf("\nEnter Aadhar Number -> ");
    scanf("%s", a.anumber);
    if (a.anumber[12] != '\0')
    {
        printf("Invalid aadhar number...\n");
        goto aadhar;
    }
    printf("\nEnter Address -> ");
    scanf("%c", &a.address[0]);
    gets(a.address);
    printf("\nEnter City -> ");
    scanf("%s", a.city);
    printf("\nEnter Account Type -> ");
    scanf("%s", a.account_type);
    printf("\nEnter Username (5-20 characters) -> ");
    scanf("%s", username[total_accs]);
    printf("\nEnter Password (5-20 characters) -> ");
    for (int i = 0; i < 20; i++)
    {
        char ch = getch();
        if (ch != 13)
        {
            password[total_accs][i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }
    memset(account_no[total_accs], '\0', sizeof(account_no[total_accs]));
    sprintf(account_no[total_accs], "2209%d", total_accs);
    printf("\n\nPROCESSING DATA... PLEASE WAIT");
    for (int i = 0; i < 5; i++)
    {
        delay(500);
        printf(".");
    }
    delay(500);
    heading_display();
    printf("ACCOUNT CREATED SUCCESSFULLY...\n");
    printf("\nYour account number is %s", account_no[total_accs]);
    printf("\n\nAt first, Rs. 1000 are deposited into your account...");
    printf("\n\nPress Enter to login...");
    balanceamt[total_accs] = 1000;
    write_file(a);
    total_accs++;
    getch();
}

void login()
{
    char uname[22], pass[22];
    memset(pass, '\0', sizeof(pass));
    memset(uname, '\0', sizeof(uname));
    for (;;)
    {
        heading_display();
        delay(200);
        printf("Enter username -> ");
        scanf("%s", uname);
        printf("\nEnter password -> ");
        for (int i = 0; i < 20; i++)
        {
            char ch = getch();
            if (ch != 13)
            {
                pass[i] = ch;
                ch = '*';
                printf("%c", ch);
            }
            else
                break;
        }
        fetch_userdetails();
        fetch_balance();
        int flag = -1;
        for (int i = 0; i < total_accs; i++)
        {
            if (strcmp(uname, username[i]) == 0 && strcmp(pass, password[i]) == 0)
            {
                flag = i;
                break;
            }
        }
        if (flag != -1)
        {
            printf("\n\nLogging in");
            for (int i = 0; i < 3; i++)
            {
                delay(500);
                printf(".");
            }
            login_funcs(flag);
            break;
        }
        else
        {
            delay(200);
            printf("\n\nInvalid username or password...\nEnter again...");
            getch();
        }
    }
}

void login_funcs(int acc)
{
    char filedata[1000];
    memset(filedata, '\0', sizeof(filedata));
    FILE *fp = NULL;
    fp = fopen("data.txt", "r");
    fgets(filedata, 1000, fp);
    fclose(fp);
    int key;
    char req_acc = acc + '0';
    for (int i = 0; i < strlen(filedata); i++)
    {
        if (req_acc == filedata[i] && filedata[i + 1] == '_')
        {
            key = i + 2;
            break;
        }
    }
    char name[50];
    memset(name, '\0', sizeof(name));
    int index = key;
    for (int i = 0; i < 2; i++)
    {
        while (filedata[index] != '_')
            index++;
        index++;
    }
    strncpy(name, &filedata[key], index - key);
    for (int i = 0; i < strlen(name); i++)
        if (name[i] == '_')
            name[i] = ' ';
    delay(1000);
outer:
    for (;;)
    {
        heading_display();
        printf("***** ACCOUNT DETAILS *****");
        printf("\n\nName -> %s", name);
        printf("\nUsername -> %s", username[acc]);
        printf("\nAccount Number -> %s", account_no[acc]);
        int choice2;
        printf("\n\n----- LOGIN HOME -----\n");
        printf("**********************\n\n");
        printf("1 -> BALANCE ENQUIRY\n");
        printf("2 -> MONEY TRANSFER\n");
        printf("3 -> LOGOUT\n");
        printf("**********************\n");
        printf("ENTER YOUR CHOICE -> ");
        scanf("%d", &choice2);
        switch (choice2)
        {
        case 1:
            heading_display();
            printf("\nBalance amount -> Rs. %d\n", balanceamt[acc]);
            break;
        case 2:
            moneytransfer(acc);
            break;
        case 3:
            printf("\nLogging out");
            for (int i = 0; i < 3; i++)
            {
                delay(500);
                printf(".");
            }
            delay(500);
            goto exit;
            break;
        default:
            printf("\n\nInvalid choice...\nEnter again...");
        }
        getch();
    }
exit:
    printf("Proceeding to home screen...");
}

void moneytransfer(int acc)
{
    char from_accno[6], to_accno[6];
    int transferamt;
    memset(from_accno, '\0', sizeof(from_accno));
    memset(to_accno, '\0', sizeof(to_accno));
transfer:
    heading_display();
    printf("----- MONEY TRANSFER -----\n");
    printf("**************************\n");
    printf("\n\nEnter 1 -> To proceed");
    printf("\n\nEnter 2 -> To cancel");
    printf("\n\nENTER YOU CHOICE -> ");
    int choice3;
    scanf("%d", &choice3);
    if (choice3 == 1)
    {
    amount:
        delay(500);
        heading_display();
        printf("----- MONEY TRANSFER -----\n");
        printf("**************************\n");
        printf("\nFROM (Enter your account no.) -> ");
        scanf("%s", from_accno);
        printf("\nTO (Enter receiver's account no.) -> ");
        scanf("%s", to_accno);
        int flag = -1, flag2 = -1;
        if (strcmp(from_accno, account_no[acc]) == 0)
            flag = acc;
        for (int i = 0; i < total_accs; i++)
            if (strcmp(to_accno, account_no[i]) == 0)
            {
                flag2 = i;
                break;
            }
        if (flag != -1 && flag2 != -1)
        {
            printf("\nEnter amount to be transferred -> Rs. ");
            scanf("%d", &transferamt);
            if (transferamt > balanceamt[flag])
            {
                printf("\n\nCannot transfer..\nInsufficient balance...\nEnter again...");
                getch();
                goto amount;
            }
            else
            {
                char pass[22];
            confirmation:
                memset(pass, '\0', sizeof(pass));
                printf("\nEnter your password to confirm -> ");
                for (int i = 0; i < 20; i++)
                {
                    char ch = getch();
                    if (ch != 13)
                    {
                        pass[i] = ch;
                        ch = '*';
                        printf("%c", ch);
                    }
                    else
                        break;
                }
                if (strcmp(password[acc], pass) == 0)
                {
                    balanceamt[acc] = balanceamt[acc] - transferamt;
                    balanceamt[flag2] = balanceamt[flag2] + transferamt;
                    printf("\n\nVALIDATING PASSWORD");
                    for (int i = 0; i < 3; i++)
                    {
                        delay(500);
                        printf(".");
                    }
                    delay(200);
                    printf("\n\nTRANSFERRING MONEY");
                    for (int i = 0; i < 5; i++)
                    {
                        delay(500);
                        printf(".");
                    }
                    delay(500);
                    heading_display();
                    printf("Amount of Rs. %d transferred successfully from account no. %s to account no. %s\n", transferamt, account_no[acc], account_no[flag2]);
                    FILE *fp = NULL;
                    fp = fopen("balance.txt", "w");
                    for (int i = 0; i < total_accs; i++)
                    {
                        memset(pass, '\0', sizeof(pass));
                        sprintf(pass, "%d", balanceamt[i]);
                        fputs(pass, fp);
                        fputs("_", fp);
                    }
                    fclose(fp);
                    fetch_balance();
                }
                else
                {
                    printf("\nInvalid password..\nEnter again...\n");
                    getch();
                    goto confirmation;
                }
            }
        }
        else
        {
            printf("\n\nInvalid account number...\nEnter again..");
            getch();
            goto amount;
        }
    }
    else
    {
        printf("\nRedirecting to Home screen");
        for (int i = 0; i < 3; i++)
        {
            delay(500);
            printf(".");
        }
    }
}

void write_file(account a)
{
    FILE *fp = NULL;
    fp = fopen("data.txt", "a");
    char s[12];
    sprintf(s, "%d", total_accs);
    fputs(s, fp);
    fputs("_", fp);
    fputs(a.fname, fp);
    fputs("_", fp);
    fputs(a.lname, fp);
    fputs("_", fp);
    fputs(a.gender, fp);
    fputs("_", fp);
    fputs(a.dob, fp);
    fputs("_", fp);
    fputs(a.pnumber, fp);
    fputs("_", fp);
    fputs(a.anumber, fp);
    fputs("_", fp);
    fputs(a.address, fp);
    fputs("_", fp);
    fputs(a.city, fp);
    fputs("_", fp);
    fputs(a.account_type, fp);
    fputs("_", fp);
    fclose(fp);

    fp = fopen("userpassacc.txt", "a");
    fputs(username[total_accs], fp);
    fputs("_", fp);
    fputs(password[total_accs], fp);
    fputs("_", fp);
    fputs(account_no[total_accs], fp);
    fputs("_", fp);
    fclose(fp);

    fp = fopen("totalacc.txt", "a");
    sprintf(s, "%d", total_accs);
    fputs(s, fp);
    fclose(fp);

    fp = fopen("balance.txt", "a");
    sprintf(s, "%d", balanceamt[total_accs]);
    fputs(s, fp);
    fputs("_", fp);
    fclose(fp);
}

void totalaccscheck()
{
    FILE *fp = NULL;
    fp = fopen("totalacc.txt", "r");
    char totaldata[10];
    memset(totaldata, '\0', sizeof(totaldata));
    fgets(totaldata, 10, fp);
    total_accs = strlen(totaldata);
    fclose(fp);
}

void fetch_userdetails()
{
    FILE *fp = NULL;
    fp = fopen("userpassacc.txt", "r");
    char userfiledata[500];
    memset(userfiledata, '\0', sizeof(userfiledata));
    memset(username, '\0', sizeof(username));
    memset(password, '\0', sizeof(username));
    fgets(userfiledata, 500, fp);
    int k = 0, j = 0;
    for (int i = 0; i < strlen(userfiledata); i++)
    {
        if (userfiledata[i] != '_')
        {
            username[k][j] = userfiledata[i];
            j++;
        }
        else
        {
            i++;
            j = 0;
            while (userfiledata[i] != '_')
            {
                password[k][j] = userfiledata[i];
                i++;
                j++;
            }
            i++;
            j = 0;
            while (userfiledata[i] != '_')
            {
                account_no[k][j] = userfiledata[i];
                i++;
                j++;
            }
            k++;
            j = 0;
        }
    }
}

void fetch_balance()
{
    char balancedata[100];
    memset(balancedata, '\0', sizeof(balancedata));
    FILE *fp = NULL;
    fp = fopen("balance.txt", "r");
    fgets(balancedata, 100, fp);
    fclose(fp);
    char temp[7];
    memset(temp, '\0', sizeof(temp));
    for (int i = 0, j = 0, k = 0; i < strlen(balancedata); i++)
    {
        if (balancedata[i] != '_')
        {
            temp[j] = balancedata[i];
            j++;
        }
        else
        {
            balanceamt[k] = atoi(temp);
            k++;
            j = 0;
            memset(temp, '\0', sizeof(temp));
        }
    }
}

void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds)
        ;
}