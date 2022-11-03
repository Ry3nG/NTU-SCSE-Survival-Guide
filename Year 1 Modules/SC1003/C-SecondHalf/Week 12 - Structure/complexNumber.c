/*
 * @Author: Ryan, Gong Zerui
 * @Date: 2021-11-01 22:30:16
 * @Last Modified by: Ryan, Gong Zerui
 * @Last Modified time: 2021-11-01 22:49:31
 */

/*
A structure called complex is defined to represent a complex number. Each complex number
consists of the real and imaginary parts as follows:
typedef struct {
   double real;
   double imag;
} Complex;
Write C functions that perform addition, subtraction, multiplication and division operations on
two complex numbers. The function prototypes are given as follows:
Complex add(Complex c1, Complex c2);
Complex mul(Complex c1, Complex c2);
Complex sub(Complex *c1, Complex *c2);
Complex div(Complex *c1, Complex *c2);
*/
#include <stdio.h>
#include <math.h>

typedef struct
{
    double real;
    double imag;
} Complex;

Complex add(Complex c1, Complex c2);
Complex mul(Complex c1, Complex c2);
Complex sub(Complex *c1, Complex *c2);
Complex div(Complex *c1, Complex *c2);

int main()
{
    int choice;
    Complex input1, input2, result;
    printf("Complex number operations: \n");
    printf("1 - addition \n");
    printf("2 - subtraction \n");
    printf("3 - multiplication \n");
    printf("4 - division \n");
    printf("5 - quit \n");
    do
    {
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        if (choice >= 5)
            return 0;
        printf("Enter Complex Number 1: \n");
        scanf("%lf %lf", &input1.real, &input1.imag);
        printf("Enter Complex Number 2: \n");
        scanf("%lf %lf", &input2.real, &input2.imag);
        switch (choice)
        {
        case 1:
            result = add(input1, input2);
            break;
        case 2:
            result = sub(&input1, &input2);
            break;
        case 3:
            result = mul(input1, input2);
            break;
        case 4:
            result = div(&input1, &input2);
            break;
        }
        printf("complex(): real %.2f imag %.2f\n",
               result.real, result.imag);
    } while (choice < 5);
    return 0;
}

Complex add(Complex c1, Complex c2)
{
    Complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}
Complex sub(Complex *c1, Complex *c2)
{
    Complex result;
    result.real = c1->real - c2->real;
    result.imag = c1->imag - c2->imag;
    return result;
}
Complex mul(Complex c1, Complex c2)
{
    Complex result;
    result.real = c1.real * c2.real - c1.imag * c2.imag;
    result.imag = c1.real * c2.imag + c1.imag * c2.real;
    return result;
}
Complex div(Complex *c1, Complex *c2)
{
    Complex result;
    result.real = (c1->real * c2->real + c1->imag * c2->imag) / (c2->real * c2->real + c2->imag * c2->imag);
    result.imag = (c1->imag * c2->real - c1->real * c2->imag) / (c2->real * c2->real + c2->imag * c2->imag);
    return result;
}