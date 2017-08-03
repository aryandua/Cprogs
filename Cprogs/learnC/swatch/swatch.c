#include <stdio.h>
int main() {
	 int hr, min, sec;
	 int opt;
	 unsigned int fend;
	 printf("TIMER\n");
	 printf("Enter 1 for beep sound when timer ends, 2 for military, 3 for minion ring ring, 4 for morning wake up, or 5 for strum : ");
	 scanf("%d", &opt);
	 printf("HOURS : ");
         scanf("%d" ,&hr);
 	 if(hr<0) {
		printf("ERORR CANNOT START TIMER FOR NEGATIVE VALUE!");
		return(-1);
	}
	 printf("MINS : ");
	 scanf("%d" ,&min);
	 if(min<0) {
                printf("ERORR CANNOT START TIMER FOR NEGATIVE VALUE!");
                return(-1);
        }
	 printf("SECS : ");
         scanf("%d" ,&sec);
	 if(sec<0) {
                printf("ERORR CANNOT START TIMER FOR NEGATIVE VALUE!");
                return(-1);
        }
	 fend = sec + (60*min) + (3600*hr);
	 sleep(fend);
	 switch(opt) {
	 case 1:
		system("play -q beep.mp3");
		break;
	 case 2:
		system("play -q military.mp3");
		break;
	case 3:
		system("play -q minion.mp3");
		break;
	case 4:
		system("play -q morning.mp3");
		break;
	case 5:
		system("play -q strum.mp3");
		break;
	default:
		printf("ERROR NOT A OPTION\n");
	}
}


