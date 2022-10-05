/**
 Course: ENSE 452
 Program Name: Assignment 2
 Programmer: Greg Sveinbjornson
 Date: October 4, 2022

 This program is a complex number calculator,
 which allows the user to enter two complex numbers
 and perform addition, subtraction, multiplication,
 and division on them either from the command line
 or from a data.txt file.

*/

#include <iostream>
#include <fstream>

using namespace std;

ifstream inData;
ofstream outData;

/**
 ComplexNumbers
 Represents complex number data type with a real and imaginary portion
 */
class ComplexNumbers
{
public:
    float real;//real part of the complex number
    float imaginary;//imaginary part of the complex number

    ComplexNumbers();//constructor
    ComplexNumbers(float rl, float imgy);//overloaded constructor
};

void add(ComplexNumbers a, ComplexNumbers b);
void subtract(ComplexNumbers a, ComplexNumbers b);
void multiply(ComplexNumbers a, ComplexNumbers b);
void divide(ComplexNumbers a, ComplexNumbers b);
void printResult(ComplexNumbers result);

int main() {

    inData.open("data.txt");//if there is a data.txt file we take this path
    if (inData)
    {
        outData.open("output.txt");
    }

    char operation = 'x';
    float real1, imaginary1, real2, imaginary2;

    printf("Type a letter to specify the arithmetic operator (A, S, M, D)\n");
    printf("followed by two complex numbers expressed as pairs of doubles.\n");
    printf("Type Q to quit.\n");


    while (operation != 'q' && operation != 'Q')
    {
        if (inData)//if there is a data.txt file we take this path
        {
            inData >> operation;
            if (operation == 'q' || operation == 'Q')
            {
                break;
            }
            inData >> real1;
            inData >> imaginary1;
            inData >> real2;
            inData >> imaginary2;
        }
        else//CLI path
        {
            printf("Enter exp: ");
            scanf_s("%c",&operation); 
            if (operation == 'q' || operation == 'Q')
            {
                break;
            }
            scanf_s("%f %f %f %f", &real1, &imaginary1, &real2, &imaginary2);
        
        }

        ComplexNumbers operand1(real1, imaginary1);
        ComplexNumbers operand2(real2, imaginary2);

        if (operation == 'a' || operation == 'A')
        {
            add(operand1, operand2);
        }
        else if (operation == 's' || operation == 'S')
        {
            subtract(operand1, operand2);
        }
        else if (operation == 'm' || operation == 'M')
        {
            multiply(operand1, operand2);
        }
        else if (operation == 'd' || operation == 'D')
        {
            divide(operand1, operand2);
        }

        
    } 

    inData.close();
    outData.close();
    return 0;
}

ComplexNumbers::ComplexNumbers()
{
    real = 0;
    imaginary = 0;
}

ComplexNumbers::ComplexNumbers(float r, float i)
{
    real = r;
    imaginary = i;
}

/**
 add
Adds a given complex number with another given complex number
*/
void add(ComplexNumbers x, ComplexNumbers y)
{
    ComplexNumbers cmplx;
    cmplx.real = x.real + y.real;
    cmplx.imaginary = x.imaginary + y.imaginary;

    printResult(cmplx);
}

/**
 subtract
 Subtracts a given complex number from another given complex number
 */
void subtract(ComplexNumbers x, ComplexNumbers y)
{
    ComplexNumbers cmplx;
    cmplx.real = x.real - y.real;
    cmplx.imaginary = x.imaginary - y.imaginary;

    printResult(cmplx);
}

/**
 multiply
 Multiplies a given complex number by another given complex number
 */
void multiply(ComplexNumbers x, ComplexNumbers y)
{
    ComplexNumbers cmplx;
    cmplx.real = x.real * y.real - x.imaginary * y.imaginary;
    cmplx.imaginary = x.imaginary * y.real + y.imaginary * x.real;

    printResult(cmplx);
}

/**
 divide
 Divides a given complex number by another given complex number
 */
void divide(ComplexNumbers x, ComplexNumbers y)
{
    ComplexNumbers cmplx;
    cmplx.real = (x.real * y.real + x.imaginary * y.imaginary)
        / (y.real * y.real + y.imaginary * y.imaginary);
    cmplx.imaginary = (x.imaginary * y.real - x.real * y.imaginary)
        / (y.real * y.real + y.imaginary * y.imaginary);

    printResult(cmplx);
}

/**
 printResult
 Prints a given complex number
 */
void printResult(ComplexNumbers cmplx)
{
    bool positive = true;
    if (cmplx.imaginary < 0)
    {
        positive = false;
        cmplx.imaginary *= -1;
    }

    if (inData)
    {
        if (positive == true)
        {
            outData << cmplx.real << " + j " << cmplx.imaginary << endl;
        }
        else
        {
            outData << cmplx.real << " - j " << cmplx.imaginary << endl;
        }
    }
    else
    {
        if (positive == true)
        {
            printf("%f + j %f\n", cmplx.real, cmplx.imaginary);
        }
        else
        {
            printf("%f - j %f\n", cmplx.real, cmplx.imaginary);
        }
    }
}
