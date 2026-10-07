#include <stdio.h>

int main(void)
{
    int power, row, position;

    printf("Введите степень\n");
    scanf("%d", &power);

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
                current[position] = previous[position-1]+previous[position];
            }

            printf("%lld ", current[position]);
        }

        printf("\n");

        for (position = 0; position <= row; position++)
        {
            previous[position] = current[position];
        }
    }

    return 0;
}