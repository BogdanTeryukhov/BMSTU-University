#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int minn,maxx;
    int answer,guess,guesses=0;
    printf("Enter minimum number: ");
    scanf_s("%d",&minn);
    printf("Enter maximum number: ");
    scanf_s("%d",&maxx);

    srand(time(0));

    answer=(rand()%(maxx-minn+1))+minn;

    do{
        printf("Enter your number: ");
        scanf_s("%d",&guess);
        if(guess>answer){
            printf("Too big :(\n");
        } else if (guess<answer){
            printf("Too small :(\n");
        } else
            printf("Correct!!! Take a pie from the shelf :)\n");
        guesses++;
    }while(guess!=answer);
    printf("*****************\n");
    printf("Original number: ""%d\n",answer);
    printf("Count of guesses: ""%d\n",guesses);
    printf("*****************");
}
