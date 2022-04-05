#include "../include/matrix.h"
using namespace std;

// Scalar Operations
Matrix Matrix::operator+(double a) //Operator overloading
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            this->m[i][j] += a;
    return *this;
}

Matrix Matrix::operator-(double a)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            this->m[i][j] -= a;
    return *this;
}
Matrix Matrix::operator*(double a)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            this->m[i][j] *= a;
    return *this;
}

Matrix Matrix::operator/(double a)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            this->m[i][j] /= a;
    return *this;
}