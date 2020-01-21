#include <math.h>
#include <stdio.h>

double vectorlength(double x, double y, double z)
{
    return sqrt(x * x + y * y + z * z);
}

int main()
{
    printf("%f\n", vectorlength(1, 2, 2));
    printf("%f\n", vectorlength(2, 6, 3));
    return 0;
}
