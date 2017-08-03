#include <stdio.h> 
typedef struct {
	char name[40];
	char last[40];
	int accnum;
	char acctype;
	float balance;
}record;
main() {
	int i;
	record customer;
	record *ptr;
	ptr = &customer;
		printf("Enter name of the customer or Enter *END* to end : \n");
		scanf("%s" ,customer.name);
		printf("Enter the last name : \n");
                scanf("%s" ,customer.last);
		printf("Enter the account number : \n");
                scanf("%d" ,&customer.accnum);
		printf("Enter the account type : \n");
                scanf(" %c" ,&customer.acctype);
		printf("Enter the balance : \n");
                scanf("%f" ,&customer.balance);
		add100(ptr);
		printf("\n\nUPDATED ACCOUNT - \n\n");
		writeout(ptr);
	}
add100(record *ptr) {
	ptr->balance += 100.0;
	return;
}
writeout(record *ptr) {
	printf("Name : %s\n", ptr->name);
        printf("Last Name : %s\n", ptr->last);
        printf("Account number : %d\n ", ptr->accnum);
        printf("Account Type : %c\n", ptr->acctype);
        printf("Balance : %5.2f\n", ptr->balance);
	return;
}

