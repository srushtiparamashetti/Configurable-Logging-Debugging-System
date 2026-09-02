#include <stdio.h>
#include <string.h>

#define MAX 1000

void remove_comments(char *line)
{
    char *p;

    // Remove single line comment
    p = strstr(line, "//");

    if (p != NULL)
        *p = '\0';
}

void macro_substitution(char *line)
{
    char temp[MAX];

    strcpy(temp, line);

    // Macro abc -> 3456
    char *p = strstr(temp, "abc");
    if (p != NULL)
    {
        strcpy(p, "3456");
    }

    strcpy(line, temp);

    // Macro pf -> printf
    p = strstr(line, "pf");
    if (p != NULL)
    {
        p[0] = 'p';
        p[1] = 'r';
        p[2] = 'i';
        p[3] = 'n';
        p[4] = 't';
        p[5] = 'f';
    }

    // Macro coding -> 65
    p = strstr(line, "coding");
    if (p != NULL)
    {
        strcpy(p, "65");
    }
}

int main()
{
    FILE *fp, *out;
    char line[MAX];

    fp = fopen("abc.c", "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    out = fopen("abc.i", "w");

    if (out == NULL)
    {
        printf("Unable to create output file\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, MAX, fp) != NULL)
    {
        remove_comments(line);

        if (strstr(line, "#define") == NULL)
        {
            macro_substitution(line);
            fputs(line, out);
        }
    }

    fclose(fp);
    fclose(out);

    printf("Preprocessing completed\n");

    return 0;
}