
#include  <stdio.h>

int strdiff(char *a, char *b)
{unsigned long g = 0, i = 0;char ga = 1, gb = 1;

    while (ga && gb)
    {ga = *(a + i);gb = *(b + i);
        for (int j = 0; j < 8; j++)
        {if (((ga >> j) & 1) != (((gb >> j) & 1)))return g;g++;}
        i++;
    }

    return ga || gb ? g : -1;
}

int main()
{
    char s1[1000], s2[1000];
    gets(s1);
    gets(s2);
    printf("%d\n", strdiff(s1, s2));

    return 0;
}
