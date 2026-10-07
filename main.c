#include <stdio.h>
#include <ctype.h>

int read_number(char expression[], int *position)
{
    int number = 0;

    while (isdigit(expression[*position]))
    {
        number = number * 10 + (expression[*position] - '0');
        (*position)++;
    }

    return number;
}

int check_expression(char expression[], int *power)
{
    int position = 0;

    if (expression[position] != '(')
    {
        printf("Ошибка: выражение должно начинаться с '('\n");
        return 0;
    }

    position++;

    if (isdigit(expression[position]))
    {
        read_number(expression, &position);
    }
    else if (isalpha(expression[position]))
    {
        position++;
    }
    else
    {
        printf("Ошибка: первый член должен быть числом или одной буквой\n");
        return 0;
    }

    if (expression[position] != '+')
    {
        printf("Ошибка: после первого члена должен быть '+'\n");
        return 0;
    }

    position++;

    if (isdigit(expression[position]))
    {
        read_number(expression, &position);
    }
    else if (isalpha(expression[position]))
    {
        position++;
    }
    else
    {
        printf("Ошибка: второй член должен быть числом или одной буквой\n");
        return 0;
    }

    if (expression[position] != ')')
    {
        printf("Ошибка: после второго члена должна быть ')'\n");
        return 0;
    }

    position++;

    if (expression[position] != '^')
    {
        printf("Ошибка: после ')' должен быть '^'\n");
        return 0;
    }

    position++;

    if (!isdigit(expression[position]))
    {
        printf("Ошибка: после '^' должна быть степень\n");
        return 0;
    }

    *power = read_number(expression, &position);

    if (expression[position] != '\0')
    {
        printf("Ошибка: после степени не должно быть других символов\n");
        return 0;
    }

    return 1;
}

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
    int power, row, position;
    char expression[100];

    printf("Введите выражение: ");
    scanf("%99s", expression);

    if (!check_expression(expression, &power))
    {
        return 0;
    }

    printf("Выражение прошло проверку\n");
    printf("Степень: %d\n", power);

    long long previous[67];
    long long current[67];

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