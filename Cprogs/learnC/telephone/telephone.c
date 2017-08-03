#include <stdio.h> 
main() {
int mode;
printf("Enter 1 to add a new record, Enter 2 to delete a record, Enter 3 to modify a current record, or Enter 4 to see a current record : ");
scanf("%d" ,&mode);
switch (mode) {
	case 1:
		add();
		break;
	case 2: 
		del();
		break;
	case 3:
		mod();
		break;
	case 4:
		see();
		break;
	}
}
add() {
FILE *records;
char name[20];
long int tel;

printf("Enter your name : ");
scanf("%[^\n]" ,name);
printf("Enter your telephone Number : ");
scanf("%ld" ,&tel);
records = fopen(name,  "a+");
fprintf(records,"Name : %s\nTelephone : %ld" ,name ,tel);
fclose(records);
}

del() {
FILE *records;
char name[20];
printf("Enter the name to remove file for : ");
scanf("%s" ,name);
records = fopen(name, "w");
fprintf(records, "FILE RECORD DELETED \n");
fclose(records);
}
mod() {
FILE *records, *records2;
char name[20];
long int  newtel;
char newname[20];
printf("Enter the name of person to modify their file : ");
scanf("%s" ,name);
records = fopen(name, "w");
printf("Enter the new name :  ");
scanf("%s" ,newname);
printf("Enter the new telephone number : ");
scanf("%ld" ,&newtel);
fprintf(records, "FILE RECORDS MODIFIED AND TRANSFERED TO FILE %s\n" ,newname);
records2 = fopen(newname, "w");
fprintf(records2, "Name : %s \n Telephone Number : %ld " ,newname ,newtel);
printf("File modified \n");
fclose(records);
fclose(records2);
}

see() {
	FILE *records;	
	char name[20];
	char c;
	printf("Enter the name of person to view their file : ");
	scanf("%s", name);
	records = fopen(name, "r");
	 while ((c = getc(records)) != EOF)
        putchar(c);

	fclose(records);
}
