#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
struct s {
	char color[40];
	struct s *next;
};
typedef struct s node;
main() {
	int choice=0;
	int listcreated=0;
	node *head;
	while(choice != 4) {
		printf("Enter 1 to create a list, 2 to insert, 3 to delete, and 4 to end :  \n");
		scanf("%d", &choice);
//(for debug)		printf("choice = %d\n", choice);
		switch(choice) {
			case 1:
				head = (node *) malloc(sizeof(node));
				create(head);
				listcreated = 1;
				display(head);
				break;
			case 2:
                                if(listcreated==0) {
					printf("Create a list first\n");
					break;
				}
				insert(head);
				display(head);
				break;
			case 3:
				if(listcreated==0){
					printf("Create a list first\n");
					break;
				}
					delete(head);
					display(head);
					break;
			case 4:
				printf("Have a good day!\n");
				break;
			default :
				printf("ERROR");
				break;
		}
	}
}

create(node *record) {
	printf("Enter the color or end to end  : ");
	scanf(" %[^\n]" ,record->color);
	if(strcmp(record->color, "end") == 0) {
                record->next=NULL;
         }
	else {
		record->next = (node *) malloc(sizeof(node));
		create(record->next);
	}
	return;
}

insert(node *first) {
	node *newrecord, *temp;
	char after[40];
	newrecord = (node *) malloc(sizeof(node));
	printf("Enter the name of the color to add : ");
	scanf("%s" ,newrecord->color);
	printf("Enter the color to insert new color after : ");
	scanf("%s" ,after);
	temp=first;
	while(strcmp(after,temp->color) != 0) {
		temp=temp->next;
		if(temp==NULL) {
			printf("INVALID %s not found\n",after);
			return;
		}
	}
	newrecord->next=temp->next;
	temp->next=newrecord;
	return;
}

delete(node *first) {
	node *temp2;
        node *temp;
        char colortodelete[40];
        printf("Enter the name of the color to delete : ");
        scanf("%s" ,colortodelete);
        temp=first;
	if (strcmp(colortodelete, first->color)==0) {
		// printf("Cannot delete head\n");
		first=first->next;
		free (temp);
		return;
	}
        while(strcmp(colortodelete,temp->next->color) != 0) {
                temp=temp->next;
                if(temp->next==NULL) {
                        printf("INVALID %s not found\n",colortodelete);
                        return;
                }
        }

	temp2=temp->next;
        temp->next=temp->next->next;
	free(temp2);
        return;
}




display(node *record) {
       	if(record->next == 0) {
		return;
	}
        else if(record->next != 0) {
		printf("%s\n" ,record->color);
        	display(record->next);
        }
        return;
}

