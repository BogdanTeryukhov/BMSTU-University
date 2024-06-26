#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char **args)
{
    if (argc != 4){printf("Usage: frame <height> <width> <text>\n");return 0;}
    int h = atoi(args[1]),width = atoi(args[2]);

    char *let = args[3];
    int len = strlen(let);

    if (len > width - 2 || h < 3)
    {printf("Error\n");return 0;}

    int w = (h + 1) / 2,
    ws = (width - len) / 2 + 1,
    wordend = ws + len - 1;

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= width; j++)
        {if (i == 1 || i == h) {
                printf("*");
                if (j == width)printf("\n");
                continue;}

            if (j == 1 || j == width)
            {printf("*");if (j == width) printf("\n");
                continue;
            }

            if (i == w)
            {if (j >= ws && j <= wordend){printf("%c", let[j - ws]);}
                else printf(" ");
            }
            else printf(" ");}
    }
    return 0;

}

