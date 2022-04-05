#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>
using namespace std;

class Matrix
{
    
    public:
        int row, col; 
        vector<vector<double>> m;
        Matrix(int, int, vector<double>);  //Input where all elements are given in a list row-wise
        Matrix(int,int);  //Input for empty matrix with all 0s
        
        // Scalar Operations
        Matrix operator + (double);
        Matrix operator - (double);
        Matrix operator * (double);
        Matrix operator / (double);

        //Vector Operations
        Matrix operator+(Matrix &);
        Matrix operator-(Matrix &);
        Matrix operator*(Matrix &);
        Matrix subd(Matrix &,int,int,int);
        Matrix transpose();
        double determinant();
        void print_mat();
    
} ;

#endif