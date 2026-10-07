#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#define MAX_POWER 66

int read_number(char expression[], int *position, long long *number)
{
    long long result = 0;

    while (isdigit(expression[*position]))
    {
        int digit = expression[*position] - '0';

        if (result > (LLONG_MAX - digit) / 10)
        {
            return 0;
        }

        result = result * 10 + digit;
        (*position)++;
    }

    *number = result;

    return 1;
}

int read_term(
    char expression[],
    int *position,
    long long *number,
    char *letter
)
{
    if (isdigit(expression[*position]))
    {
        if (!read_number(expression, position, number))
        {
            return 0;
        }

        return 1;
    }

    if (isalpha(expression[*position]))
    {
        *letter = expression[*position];
        (*position)++;

        return 2;
    }

    return 0;
}

int check_expression(char expression[], int *power)
{
    int position = 0;
    long long number;
    long long power_number_value;

    if (expression[position] != '(')
    {
        printf("Ошибка: выражение должно начинаться с '('\n");
        return 0;
    }

    position++;

    if (isdigit(expression[position]))
    {
        if (!read_number(expression, &position, &number))
        {
            printf("Ошибка: число слишком большое\n");
            return 0;
        }
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
        printf("Ошибка: между членами должен быть '+'\n");
        return 0;
    }

    position++;

    if (isdigit(expression[position]))
    {
        if (!read_number(expression, &position, &number))
        {
            printf("Ошибка: число слишком большое\n");
            return 0;
        }
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

    if (!read_number(expression, &position, &power_number_value))
    {
        printf("Ошибка: степень слишком большая\n");
        return 0;
    }

    if (power_number_value > MAX_POWER)
    {
        printf("Ошибка: степень не должна быть больше %d\n", MAX_POWER);
        return 0;
    }

    *power = (int)power_number_value;

    if (expression[position] != '\0')
    {
        printf("Ошибка: после степени не должно быть других символов\n");
        return 0;
    }

    return 1;
}

int safe_multiply(
    long long first,
    long long second,
    long long *result
)
{
    if (first == 0 || second == 0)
    {
        *result = 0;
        return 1;
    }

    if (first > LLONG_MAX / second)
    {
        return 0;
    }

    *result = first * second;

    return 1;
}

int power_number(
    long long number,
    int power,
    long long *result
)
{
    long long value = 1;
    int position;

    for (position = 0; position < power; position++)
    {
        if (!safe_multiply(value, number, &value))
        {
            return 0;
        }
    }

    *result = value;

    return 1;
}

int build_pascal_row(int power, long long row[])
{
    long long previous[67];
    long long current[67];

    int position;
    int line;

    for (line = 0; line <= power; line++)
    {
        for (position = 0; position <= line; position++)
        {
            if (position == 0 || position == line)
            {
                current[position] = 1;
            }
            else
            {
                if (previous[position - 1] >
                    LLONG_MAX - previous[position])
                {
                    printf("Ошибка: переполнение при построении треугольника Паскаля\n");
                    return 0;
                }

                current[position] =
                    previous[position - 1] + previous[position];
            }
        }

        for (position = 0; position <= line; position++)
        {
            previous[position] = current[position];
        }
    }

    for (position = 0; position <= power; position++)
    {
        row[position] = current[position];
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
        number /= 10;
        digits++;
    }

    return digits;
}

void print_pascal_triangle(int power)
{
    long long previous[67];
    long long current[67];

    int row;
    int position;
    int max_digits = 0;

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
}

int calculate_term(
    long long coefficient,
    int first_type,
    int second_type,
    long long first_number,
    long long second_number,
    int first_power,
    int second_power,
    long long *result
)
{
    long long value = coefficient;
    long long power_value;

    if (first_type == 1 && first_power > 0)
    {
        if (!power_number(first_number, first_power, &power_value))
        {
            return 0;
        }

        if (!safe_multiply(value, power_value, &value))
        {
            return 0;
        }
    }

    if (second_type == 1 && second_power > 0)
    {
        if (!power_number(second_number, second_power, &power_value))
        {
            return 0;
        }

        if (!safe_multiply(value, power_value, &value))
        {
            return 0;
        }
    }

    *result = value;

    return 1;
}

int check_expansion(
    int power,
    long long coefficients[],
    int first_type,
    int second_type,
    long long first_number,
    long long second_number
)
{
    int position;
    long long result;

    for (position = 0; position <= power; position++)
    {
        int first_power = power - position;
        int second_power = position;

        if (!calculate_term(
                coefficients[position],
                first_type,
                second_type,
                first_number,
                second_number,
                first_power,
                second_power,
                &result))
        {
            return 0;
        }
    }

    return 1;
}

void print_expansion(
    int power,
    long long coefficients[],
    int first_type,
    int second_type,
    long long first_number,
    long long second_number,
    char first_letter,
    char second_letter
)
{
    int position;

    printf("Разложение: ");

    for (position = 0; position <= power; position++)
    {
        long long coefficient = coefficients[position];
        int first_power = power - position;
        int second_power = position;

        long long variable_coefficient = coefficient;
        long long power_value;

        if (first_type == 1 && first_power > 0)
        {
            power_number(first_number, first_power, &power_value);

            safe_multiply(
                variable_coefficient,
                power_value,
                &variable_coefficient
            );
        }

        if (second_type == 1 && second_power > 0)
        {
            power_number(second_number, second_power, &power_value);

            safe_multiply(
                variable_coefficient,
                power_value,
                &variable_coefficient
            );
        }

        if (first_type == 1 && second_type == 1)
        {
            printf("%lld", variable_coefficient);
        }
        else
        {
            if (variable_coefficient != 1)
            {
                printf("%lld", variable_coefficient);
            }

            if (first_type == 2 && first_power > 0)
            {
                printf("%c", first_letter);

                if (first_power > 1)
                {
                    printf("^%d", first_power);
                }
            }

            if (second_type == 2 && second_power > 0)
            {
                printf("%c", second_letter);

                if (second_power > 1)
                {
                    printf("^%d", second_power);
                }
            }
        }

        if (position < power)
        {
            printf(" + ");
        }
    }

    printf("\n");
}

int main(void)
{
    int power;
    int term_position;
    int first_type;
    int second_type;
    int position;
    int input_position;

    char expression[100];

    long long first_number = 0;
    long long second_number = 0;

    char first_letter = '\0';
    char second_letter = '\0';

    long long coefficients[67];

    printf("Введите выражение: ");

    if (fgets(expression, sizeof(expression), stdin) == NULL)
    {
        printf("Ошибка: не удалось прочитать выражение\n");
        return 0;
    }

    input_position = 0;

    while (expression[input_position] != '\0')
    {
        if (expression[input_position] == '\n')
        {
            expression[input_position] = '\0';
            break;
        }

        input_position++;
    }

    if (!check_expression(expression, &power))
    {
        return 0;
    }

    term_position = 1;

    first_type = read_term(
        expression,
        &term_position,
        &first_number,
        &first_letter
    );

    if (first_type == 0)
    {
        printf("Ошибка: первый член слишком большой\n");
        return 0;
    }

    term_position++;

    second_type = read_term(
        expression,
        &term_position,
        &second_number,
        &second_letter
    );

    if (second_type == 0)
    {
        printf("Ошибка: второй член слишком большой\n");
        return 0;
    }

    if (!build_pascal_row(power, coefficients))
    {
        return 0;
    }

    if (!check_expansion(
            power,
            coefficients,
            first_type,
            second_type,
            first_number,
            second_number))
    {
        printf("Ошибка: переполнение при вычислении разложения\n");
        return 0;
    }

    printf("\nТреугольник Паскаля:\n");

    print_pascal_triangle(power);

    printf("\n");

    print_expansion(
        power,
        coefficients,
        first_type,
        second_type,
        first_number,
        second_number,
        first_letter,
        second_letter
    );

    return 0;
}