#include <stdio.h>

int count_digits(long long number)
{
    int digits = 0;

    if (number == 0)
    {
        return 1;
    }

    while (number > 0)
    {
        number = number / 10;
        digits++;
    }

    return digits;
}

int main(void)
{
    int power,row,position;

    long long previous[67];
    long long current[67];

    printf("Введите степень: ");
    scanf("%d", &power);

    for (row = 0; row <= power; row++)
    {
        for (position = 0; position <= row; position++)
        {
            if (position == 0 || position == row)
            {
                current[position] = 1;
            }
            else
            {
                current[position] =
                    previous[position - 1] + previous[position];
            }
        }

        for (position = 0; position <= row; position++)
        {
            previous[position] = current[position];
        }
    }

    int max_digits = 0;

    for (position = 0; position <= power; position++)
    {
        int digits = count_digits(current[position]);

        if (digits > max_digits)
        {
            max_digits = digits;
        }
    }


    for (position = 0; position <= power; position++)
    {
        previous[position] = 0;
    }

    for (row = 0; row <= power; row++)
    {
        int row_width = (row + 1) * max_digits + row;
        int last_width = (power + 1) * max_digits + power;
        int spaces = (last_width - row_width) / 2;

        for (position = 0; position < spaces; position++)
        {
            printf(" ");
        }

        for (position = 0; position <= row; position++)
        {
            if (position == 0 || position == row)
            {
                current[position] = 1;
            }
            else
            {
                current[position] =
                    previous[position - 1] + previous[position];
            }

            printf("%*lld", max_digits, current[position]);

            if (position < row)
            {
                printf(" ");
            }
        }

        printf("\n");

        for (position = 0; position <= row; position++)
        {
            previous[position] = current[position];
        }
    }

    return 0;
}