#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int wcount(char *str){
    int wcount_counter=0,i=0,fl = false;
    while (*(str+i) != 0){
        if (*(str+i) != ' ' && fl == false){
            fl = true;
            wcount_counter++;
        }
        else if (*(str+i) == ' ' || *(str+i) == '\n' || *(str+i) == '\t'){fl = false;}
        i++;
    }
    return wcount_counter;
}

int main(){
    int num = 0;
    char buffer[80] = "";gets(buffer);
    num = wcount(buffer);
    printf("%d\n", num);
    for(int i=0; i<80; i++)
        buffer[i]=0;
}