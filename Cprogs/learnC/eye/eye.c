#include <stdio.h>
#include <time.h>

main()
{
    int user, opt, points = 0, exc, red, red1, a = 0;
    time_t t;
    FILE *fptr;

    fptr = fopen ("C:\\Users\\AryanArnav\\Desktop\\Cprogs\\EyeEx//eye_ex.txt","a+");
    printf ("Enter 1 if you are Aryan. Enter 2 if you are Arnav");
    scanf("%d",&user);
    if (user == 1)
    {
        printf("enter 1 to see your points. Enter 2 to add an entry. Enter 3 to redeem points. ");
        scanf("%d",&opt);
        if (opt == 1) {
            printf("You have %d points" , points);
        }
        else if (opt == 2){
            printf ("did you do your eye exercise today? Enter 1 if you did. Enter 2 if you did not.");
            scanf("%d" , & exc);
            if (exc == 1) {
                points = points + 1;
                printf("nice job!");
                time(&t);


       fprintf(fptr, "%s : | \n",ctime(&t));
            }
            else if (exc == 2)
                {
                printf ("OH NO!!");
                       fprintf(fptr, "%s : X\n",ctime(&t));

                a = a + 1;
                }

                    if (a == 20)
                        {


                            printf("oops! you have used all your lives, now your balance is 0 points ");
                            points = 0;
                        }


            }

        if (opt == 3) {
                printf ("choose what you want to redeem.  Press 1 to go to chuck E cheeses or to play a 5 over match. \n  Press 2 to go to golfland or  to play 10 over match.\n  press 3 to go to laser tag or play 20-20. \n Press 4 to go to Daves and Busters or play a 30-30 match.\n press 5 to play 50-50 match or go to Great America.\n For any other redeem option press 0 \n");
                scanf("%d",&red);
                    if (red == 1)
                    {
                        points =  points - 10;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points + 10;
                         }
                    }
                            if (red == 2)
                    {
                        points =  points - 20;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points + 20;
                         }
                    }
                            if (red == 3)
                    {
                        points =  points - 30;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points +30;
                         }
                    }
                            if (red == 4)
                    {
                        points =  points - 40;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points + 40;
                         }
                    }
                            if (red == 5)
                    {
                        points =  points - 50;
                                if (points < 0)
                         {
                             printf ("You do not have enough points ");
                         points = points + 50;
                         }
                    }
                            if (red == 0)
                               {
                                 printf("Press 1 to get papa take holiday. \n  Press 2 to go to any amusement park. \n press 3 to travel anywhere in USA. \n press 4 to go anywhere in the world");
                                 scanf("%d", &red1);
                               if (red1 == 1)
                    {
                        points =  points - 75;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points + 75;
                         }
                    }
                            if (red1 == 2)
                    {
                        points =  points - 100;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points + 100;
                         }
                    }
                            if (red1 == 3)
                    {
                        points =  points - 150;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points +150;
                         }
                    }
                            if (red1 == 4)
                    {
                        points =  points - 200;
                                if (points < 0)
                         {
                             printf ("you do not have enough points ");
                         points = points + 200;
                         }
                    }
                            else
                                printf("not a valid command");
                         }

                               }
fclose(fptr);
        }


  }




