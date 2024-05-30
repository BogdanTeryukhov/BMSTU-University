#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void maxprod(float *nat_log, int num){
    int searcher = 0;
    int index = 0; // отвечает за индекс
    int start = 0; // отвечает за начало
    float maxsum = nat_log[0],sum = 0;
    /*for (int i = 0; i < num; ++i) { //Данный цикл НЕ подошел для реализации
        sum = sum+nat_log[i];
        if (sum > maxsum){ //поиск максимальной суммы чисел
            maxsum = sum;
            searcher = start; // серчер нашел начало новой последовательности
            index = i; //запоминание индекса
        }
        if (sum < 0){ // проверка на случай если сумма оказалась меньше нуля
            sum = 0; // сумма становится нулем
            start = i; // старт начинается с данного индекса
        }
    }*/
    int i = 0;
    while (i < num){
        sum = sum+nat_log[i];
        if (sum > maxsum){ //поиск максимальной суммы чисел
            maxsum = sum;
            searcher = start; // серчер нашел начало новой последовательности
            index = i; //запоминание индекса
        }
        i++;
        if (sum < 0){ // проверка на случай если сумма оказалась меньше нуля
            sum = 0; // сумма становится нулем
            start = i; // старт начинается с данного индекса
        }
    }
    printf("%d %d\n", searcher, index);
}

int main(){
    int num;
    scanf("%d", &num);
    float *x = (float*)malloc(sizeof(float)*num); //освобождение памяти под числитель
    float *y = (float*)malloc(sizeof(float)*num); //освобождение памяти под знаменатель
    float *nat_log = (float*)malloc(sizeof(float)*num);

    for (int i = 0; i<num; i++)
        scanf("%f/%f", &x[i], &y[i]); //заполнение числителя и знаменателя
    for(int i = 0; i<num; i++)
        nat_log[i]=log(x[i]/y[i]);
    maxprod(nat_log, num);
    free(x);free(y);free(nat_log); // поочередное освобождение памяти
    return 0;
}

