#include <stdio.h>

int play();

int main()
{
    int result = 0, keep_playing = 1;
    char name[20];
    FILE *fptr;
    int team; 
    printf("Welcome to the game of craps! Enter your name : ");
    scanf("%s" ,name);
    printf("Your game will now begin \n");

    fptr = fopen("./craps_results/results.dat" ,"a+");
    if (fptr == NULL) {
      printf ("Error opening file\n");
      return (-1);
    }
    while(keep_playing == 1) {

      result = play();

      if(result == 1) 
	fprintf(fptr, "%s : WON\n" ,name);
      else 
	fprintf(fptr, "%s : LOST\n" ,name);

      printf ("Enter 1 to play again. Else any other number\n");
      scanf ("%d", &keep_playing);
    }
    fclose(fptr);

    return 0;
}

int play() {
    int val, secval, result=0;
    char thar;
    printf("Press T to throw : \n");
    scanf(" %c", &thar);
    if(thar == 't' || thar == 'T') {
        val = thro();        
    }
   else {
       printf("ERROR \n");
   }
    switch(val) {
        case 3 :
        case 4 :
        case 6 :
        case 8 :
        case 9 :
        case 10 :
            printf("You threw a %d, Press T  to throw \n" ,val);
	    char t;
	    scanf(" %c",&t);
            if(t == 't' || t=='T') {
		secval = thro();
            	if(secval == val) {
                	printf("You WIN by matching your first score \n");
            		result=1;
		}
            	else { 
                  printf("Threw %d. Did not match. You lose :\( \n", secval);
            	}
	    }
	    else {
		printf ("You lose, didn't throw the dice the second time \n");
	    }
	    break;
        case 2 :
        case 5 :
        case 12 :
            printf("You lost on the first throw by scoring a %d \n" ,val);
    	    break;
        case 7 : 
        case 11 :
            printf("YOU WIN!!! by scoring a %d \n" ,val);
	    result = 1;
	    break;    
	}
    return(result);
}

int thro() {
    int ret;
    int val, val2;
   srand(time(NULL)); 
    val = rand() % 11;
    return (val+2);
}

