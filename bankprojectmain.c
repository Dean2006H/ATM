#include <stdio.h>
#include <string.h>

int p,a,c,b;
int s1,s2,s3,s4,s5,s6,s7,s8;
int mistakes = 1 , choice , historycounter;
double deposit , withdraw;
double historyamount[10];
int active_account = 0;

struct account {
    char name[50];
    char last_name[50];
    double balance;
    int pin;
};

int main() {
    struct account a1;

    {
        printf("Choose a pin for your acount: ");
        scanf("%d", &a1.pin);
    };

    printf("Please enter your pin: ");
    scanf("%d", &p);

    while (mistakes <=3) {
        if (p == a1.pin) {

            while( 1){ /*تا وقتی که کاربر خارج نشده منو را چاپ کند */

                printf("***** ATM MENU *****\n");
                printf(" 1 . Create account\n");
                printf(" 2 . Deposit money\n");
                printf(" 3 . Withdraw money\n");
                printf(" 4 . Check balance\n");
                printf(" 5 . Account details\n");
                printf(" 6 . Change pin\n");
                printf(" 7 . Transaction history\n");
                printf(" 8 . Account credit score\n");
                printf(" 9 . Exit\n");
                printf("Select an option: ");
                scanf("%d", &choice);

                if (choice == 1) {

                    if (active_account == 1) {
                        printf("You already have  an account.\n");
                        continue;
                    }

                    printf("Do you want to create an account? (1.Yes / 0.No): ");
                    scanf("%d", &s1);

                    if (s1 == 0) {
                        continue;    /*ساخت اکانت */
                    } else if (s1 == 1) {
                        printf("Enter your first name: ");
                        scanf("%s", a1.name);
                        printf("Enter your last name: ");
                        scanf("%s", a1.last_name);
                        printf("Enter your initial deposit amount: ");
                        scanf("%lf", &a1.balance);
                        printf("Your account has been successfully created.\n\n");
                        active_account = 1; /*مقدار متغیر از 0 به 1 تغییر داده میشه که کامپیوتر متوجه شه اکانت ساهته شده */
                    } else {
                        printf("Invalid input.\n");
                    }
                }

                else if (choice >= 2 && choice <= 8 && active_account == 0) {
                	/*اگر اکانت نساخته باشید و به جز گزینه1 و 9چیز دیگری انتخاب کنید برنامه میگه باید اکانت بسازید */
                    printf("You do not have an account. Please create one first.\n");
                    continue;
                }

                else if (choice == 2) {   /*واریز پول به حساب */

                    printf("Enter the amount you want to deposit: ");
                    scanf("%lf", &deposit);

                    if (deposit <= 0) {
                        printf("Invalid amount.\n");
                        continue;
                    }

                    a1.balance += deposit; /*اضافه کردن مقدار واریزی به حساب*/
                    printf("Deposit completed successfully.\n\n");

                    if (historycounter == 10) {
                        for (int i = 0; i < 9; i++) {
                            historyamount[i] = historyamount[i + 1]; /*اگه تاریخچه از 10 بیشتر شود همه عملیات ها یک خانه به عقب میروند تا جا باز شود*/
                        }
                        historycounter = 9;
                    }

                    historyamount[historycounter] = deposit;
                    historycounter ++;
                }

                else if (choice == 3) {

                    printf("Enter the amount you want to withdraw: ");
                    scanf("%lf", &withdraw);

                    if (withdraw <= 0) {
                        printf("Invalid amount.\n");
                        continue;
                    } else if (withdraw > a1.balance) {
                        printf("insufficient balance. \n");
                        continue;
                    }

                    a1.balance -= withdraw;
                    printf("Withdraw completed successfully.\n\n");

                    if (historycounter == 10) {
                        for (int i = 0; i < 9; i++){
                            historyamount[i] = historyamount[i + 1]; /*اگه تاریخچه از 10 بیشتر شود همه عملیات ها یک خانه به عقب میروند تا جا باز شود*/
                       
					    }
                        historycounter = 9;
                    }

                    historyamount[historycounter] = -withdraw;/*مقدار برداشت را با منفی نشان میدهد*/
                    historycounter++;
                }

                else if (choice == 4) {
                    printf("Your current balance is: %.2lf\n\n", a1.balance);
                }

                else if (choice == 5) {/*نشان دادن اطلاعات کاربر*/
                    printf("Account details:\n");
                    printf("First name: %s\n", a1.name);
                    printf("Last name: %s\n", a1.last_name) ;
                    printf("pin: %d\n", a1.pin);
                }

                else if (choice == 6) {

                    int old_pin;

                    printf("Enter your current pin: ");
                    scanf("%d", &old_pin);

                    if (old_pin != a1.pin) {
                        printf("Incorrect pin , returning to menu...\n");
                        continue;/*ادامه پیدا کردن برنامه و بازگشت به منو*/
                    }

                    printf("Enter your new pin: ") ;
                    scanf("%d", &a1.pin);
                    printf("pin updated successfully.\n");
                }

                else if (choice == 7) {

                    if (historycounter == 0) {
                        printf("No transactions recorded yet.\n");
                    } else {
                        printf("Transaction history:\n");
                        for (int i = 0; i < historycounter; i++) {
                            printf("%d. %.2lf\n", i + 1, historyamount[i]);/*نشان دادن عدد عملیات و مقدار ان تا 2 عدد اعشار */
                        }
                    }
                }

                else if (choice == 8) {
                    int credit = a1.balance / 10000;/*به اضای هر 10000 کارکرد حساب 1 امتیاز میدهد*/
                    printf("Your account credit score is: %d\n\n", credit);
                }

                else if (choice == 9) {
                    printf("Are you sure you want to exit? (1.Yes / 0.No): ");
                    scanf("%d", &s8);
                    if (s8 == 1) {
                        printf("Goodbye!\n");
                        return 0;
                    }
                }

                else {
                    printf("Invalid option.\n");
                }
            }
        }

        else {
            printf("Incorrect pin ,  Try again.\n");
            printf("You have %d attempts left.\n", 3 - mistakes);
            scanf("%d", &p);
            mistakes++;
        }
    }

    if (mistakes == 3) {
        printf("Too many incorrect attempts . \n");
    return 0 ;    
	}

    return 0 ;
}
