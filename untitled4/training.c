#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
//Является ли число простым?
/*int is_prime(int a) {int count = 0;for (int i = 2; i < abs(a / 2) + 1; i++) {if (a % i == 0) {count++;}}if (count == 0) {return 1;} else return 0;}
int main(){int a;scanf_s("%d",&a);printf("%d",is_prime(a));}*/



//Вывод делителей первых ста чисел
/*int main(){printf("1: \n");for (int i=2; i<=100; i++){printf("%d: ", i);for (int j=2; j<=i; j++){if (i%j==0){printf("%d ",j);}if (j==i){printf("\n");}}}}*/

//Принимает два элемента и выводит их в обратном порядке
/*void swap(int* px,int* py){*px=*px+*py;*py=*px-*py;*px=*px-*py;}int main(){int a=2,b=1;swap(&a,&b);printf("%d " "%d",a,b);}*/

//Какая то фигня
/*void normalize(int *px){while(*px%2==0 && *px>0){*px/=2;}}int main(){int a=5;normalize(&a);printf("%d",a);}*/


int main ()
{
    int n, p;
    int *mass;
    bool flag; //"зачеркивали" ли число для данного p
    printf("Input n: ");
    scanf_s("%d", &n);
    if (n >= 2)
    {
        n = n - 1; //теперь n - это количесвтво чисел в массиве
        mass = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            mass[i] = i + 2;
        for (int i = 0; i < n; i++)
        {
            p = mass[i];
            flag = false;
            for (int j = i + 1; j < n; j++)
            {
                if (!(mass[j] % p))
                {
                    for (int k = j; k < n - 1; k++)
                        mass[k] = mass[k+1];
                    flag = true;
                    n--; //уменьшаем, потому что чисел на одно стало меньше
                    j--; //уменьшаем, для того чтобы снова проверить на кратность j-е число. Оно же теперь стало другим
                }
            }
            if (flag == false) break;
        }
        for (int i = 0; i < n; i++)
            printf("%d ", mass[i]);
        free(mass);
    }
    else
        printf("Error. n must be >= 2\n");

    _getch();
    return 0;
}
