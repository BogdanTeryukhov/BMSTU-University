#include <stdio.h>
#include <string.h>

void Suffix(char *s, int *new_pos, int len_s){
    int t = len_s - 1;
    new_pos[len_s - 1] = t;
    int i = len_s - 2;
    while (i >= 0){
        while (t < len_s - 1 && s[t] != s[i]){
            t = new_pos[t + 1];
        }
        if (s[t] == s[i]) {
            t--;
        }
        new_pos[i] = t;
        i--;
    }
}

void Delta1(char *s, int size, int *pos1, int len_s){
    int a = 0;
    while (a < size) {
        pos1[a] = len_s;
        a++;
    }
    int j = 0;
    while (j < len_s) {
        pos1[s[j] - 33] = len_s - 1 - j;
        j++;
    }
}


void Delta2(char *s, int *pos2, int len_s){
    int new_pos[len_s];
    Suffix(s, new_pos, len_s);
    int i = 0;
    int t = new_pos[0];
    while (i < len_s){
        while (t < i){
            t = new_pos[t + 1];
        }
        pos2[i] = t - i + len_s;
        i++;
    }
    i = 0;
    while (i < len_s - 1) {
        t = i;
        while (t < len_s - 1) {
            t = new_pos[t + 1];
            if (s[i] != s[t]) {
                pos2[t] = len_s - i - 1;
            }
        }
        i++;
    }
}

int main(int argc, char **argv){
    char *s = argv[1], *t = argv[2];
    int len_s = strlen(s), len_t = strlen(t);
    int pos1[94];
    int pos2[len_s];
    Delta1(s, 94, pos1, len_s);
    Delta2(s, pos2, len_s);
    int k = len_s - 1;
    while (k < len_t) {
        int i = len_s - 1;
        while (t[k] == s[i]) {
            if (i == 0){
                printf("%d ", k);
                break;
            }
            i--;
            k--;
        }
        k += pos1[t[k]-33] > pos2[i] ? pos1[t[k] - 33] : pos2[i];
    }
    return 0;
}

