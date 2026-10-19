
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char **number;
    int n;
} T;

void write_t(T arr)
{
    for (int i = 0; i < arr.n; i++)
        printf("%s\n", arr.number[i]);
}

int compare(const void *a, const void *b)
{
    const char *s1 = *(const char * const *)a;
    const char *s2 = *(const char * const *)b;

    return strcmp(s1, s2);
}

/* Convert an integer to a binary string of exactly n bits */
char *to_binary(unsigned int value, int n)
{
    char *result = malloc((n + 1) * sizeof(char));
    if (result == NULL)
        return NULL;

    result[n] = '\0';

    for (int i = n - 1; i >= 0; i--)
    {
        result[i] = (value % 2) + '0';
        value /= 2;
    }

    return result;
}

char *not_found(T arr)
{
    qsort(arr.number, arr.n, sizeof(arr.number[0]), compare);

    for (unsigned int i = 0; i <= (unsigned int)arr.n; i++)
    {
        char *candidate = to_binary(i, arr.n);
        if (candidate == NULL)
            return NULL;

        char *key = candidate;

        if (bsearch(&key, arr.number, arr.n,
                    sizeof(arr.number[0]), compare) == NULL)
            return candidate;

        free(candidate);
    }

    return NULL;
}

int main()
{
    char *numbers[] = {"101", "000", "110"};
    T arr = {numbers, 3};

    printf("Input:\n");
    write_t(arr);

    char *result = not_found(arr);

    if (result != NULL)
    {
        printf("Missing binary string: %s\n", result);
        free(result);
    }
    else
    {
        printf("No result found or memory allocation failed.\n");
    }

    return 0;
}
