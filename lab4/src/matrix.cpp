#include "../include/matrix.h"
using namespace std;

Matrix::Matrix(int r, int c, vector<double> mat)
{
    row = r;
    col = c;
    int count = 0;
    m.resize(row);
    for (int i = 0; i < row; i++)
    {
        m[i].resize(col);
        for (int j = 0; j < col; j++)
            m[i][j] = mat[count++];
    }
}
Matrix::Matrix(int r, int c)
{
    row = r;
    col = c;
    m.resize(row);
    for (int i = 0; i < row; i++)
    {
        m[i].resize(col);
        for (int j = 0; j < col; j++)
            m[i][j] = 0.0;
    }
}

//Vector Operations
Matrix Matrix::operator+(Matrix &m1)
{
    Matrix sum(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            sum.m[i][j] = this->m[i][j] + m1.m[i][j];
    return sum;
}

Matrix Matrix::operator-(Matrix &m1)
{
    Matrix sub(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            sub.m[i][j] = this->m[i][j] - m1.m[i][j];
    return sub;
}

Matrix Matrix::operator*(Matrix &m1)
{
    Matrix mul(row, m1.m[0].size());

    int i, j, k;
    double temp = 0.0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < m1.col; j++)
        {
            temp = 0.0;
            for (k = 0; k < col; k++)
            {
                temp += this->m[i][k] * m1.m[k][j];
            }
            mul.m[i][j] = temp;
        }
    }
    return mul;
}

Matrix Matrix::transpose()  //Function
{
    Matrix trans(col, row);
    for (int i = 0; i < col; i++)
        for (int j = 0; j < row; j++)
            trans.m[i][j] = this->m[j][i];
    return trans;
}


Matrix Matrix::subd(Matrix &mat,int p,int q, int n)
{
    int i = 0, j = 0;
 
    for (int r= 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (r != p && c != q)
            {
                this->m[i][j++] = mat.m[r][c];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return *this;
}
double Matrix::determinant()
{
    double d = 0; 
 
    if (row == 1)
        return m[0][0];
 
    Matrix temp(row-1,col-1);
 
    int sign = 1; 
 
    for (int i = 0; i < row; i++)
    {
        temp = temp.subd(*this, 0, i, row);
        d += sign * m[0][i]*(temp.determinant());
 
        sign = -sign;
    }
 
    return d;

}

void Matrix::print_mat()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << m[i][j] << ",";
        }
        cout << "\n";
    }
    return;
}
