#include "matrix.cpp"
#include "Logger.cpp"
#include <cstring>
using namespace std;

//The main function
int main(int argc, char **argv)
{
    //Taking Input
    string efile = "error.log";  //Logs will be stored in here
    Logger log(&efile[0]);  
    
    string inp;
    int m, n, temp;
    m = -99999;  //Giving them initial values to compare later for viweing input changes
    n = -99999;
    vector<Matrix> mat_list; //Stores all the matrices
    vector<double> list;  //Stores all the scalar

    while (getline(cin, inp))  //Taking input
    {
        if (inp[0] == '#' || inp == "")  //Empty line or comment
            continue;

        stringstream ss(inp);  
        if (ss >> temp)
            m = temp;
        if (m == -99999)  //If input was not a number, value of m will not change
        {
            log.add("Input format wrong. Expected a number");
            cout<< "#Output not possible. Check log for details.";
            return 0;
        }
        if (ss.peek() == ',')  //A comma is not expected with a scalar or size of array
        {
            log.add("Input format wrong. Comma not expected.");
            cout<< "#Output not possible. Check log for details.";
            return 0;
        }
        if (ss >> temp)  //If there is a second number present, then it must be size of a matrix
            n = temp;
        if (n == -99999)
        {
            list.push_back(m);
            Matrix mat(1, 1, {-99999});  //Taking a unit array with value -99999 into the matrix list
            mat_list.push_back(mat);
            continue;
        }
        if (ss.peek() == ',')
        {
            log.add("Input format wrong. Comma not expected.");
            cout<< "#Output not possible. Check log for details.";
            return 0;
        }
        if (ss >> temp)  //If there is a third number present, then it must raise error
        {
            log.add("Input format wrong. Third number not expected.");
            cout<< "#Output not possible. Check log for details.";
            return 0;
        }

        vector<double> matrices;
        for (int i = 0; i < m; i++)
        {
            string inpr;
            getline(cin, inpr);
            if (inpr == "" || inpr[0] == '#')  //Comments or empty lines not expected after size has been given
            {
                log.add("Input format wrong. Row missing.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }
            stringstream ssr(inpr);
            
            int j = -99999;
            int temp_j;
            for (int k = 0; k < n; k++)
            {
                if (ssr >> temp_j)  //If number is present then it gets stored in matrix
                {
                    j = temp_j;
                    matrices.push_back(j);
                    if (ssr.peek() == ',')
                        ssr.ignore();
                    else  //Comma must be present to separate numbers in array
                    {
                        log.add("Input format wrong. Comma missing.");
                        cout<< "#Output not possible. Check log for details.";
                        return 0;
                    }
                }
                if (j == -99999)  //If no number is present
                {
                    log.add("Input format wrong. Number missing from row.");
                    cout<< "#Output not possible. Check log for details.";
                    return 0;
                }
                j = -99999;
            }
        }
        if (m != 0 && n !=0)  //If size of array is not 0x0
        {
            Matrix mat(m, n, matrices);
            mat_list.push_back(mat);
        }
        m = -99999;
        n = -99999;
    }

    //Doing operation
    int opt;  //For command line arguments
    while ((opt = getopt(argc, argv, "asmdtx")) != -1)
    {
        switch (opt)
        {
        case 'a':  //Addition
        {
            if (mat_list.size() < 2)  //Addition needs two operands
            {
                log.add("Not enough operands. Addition not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            Matrix a = mat_list[0];
            mat_list.erase(mat_list.begin());
            Matrix b = mat_list[0];
            mat_list.erase(mat_list.begin());

            if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999 && b.row == 1 && b.col == 1 && b.m[0][0] == -99999)  //For two scalars
            {
                log.add("Two scalars given. Addition not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            else if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999)  //For one scalar and one matrix
            {
                b = b + (list[0]);
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }
            else if (b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                b = a + (list[0]);
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }

            else  //For both matrices
            {

                if (a.row != b.row || a.col != b.col)  //Sizes should match
                {
                    log.add("Sizes do not match. Addition not possible.");
                    cout << "#Output not possible. Check log for details.";
                    return 0;
                }
                b = a + b;
                mat_list.insert(mat_list.begin(), b);
            }

            break;
        }

        case 's': //Subtraction
        {
            if (mat_list.size() < 2)
            {
                log.add("Not enough operands. Subtraction not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            Matrix a = mat_list[0];
            mat_list.erase(mat_list.begin());
            Matrix b = mat_list[0];
            mat_list.erase(mat_list.begin());
            if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999 && b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                log.add("Two scalars given. Subtraction not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            else if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999)
            {
                b = b - list[0];
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }

            else if (b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                b = a - list[0];
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }
            else
            {
                if (a.row != b.row || a.col != b.col)
                {
                    log.add("Sizes do not match. Subtraction not possible.");
                    cout << "#Output not possible. Check log for details.";
                    return 0;
                }
                b = a - b;
                mat_list.insert(mat_list.begin(), b);
            }

            
            break;
        }

        case 'm':  //Multiplication
        {
            if (mat_list.size() < 2)
            {
                log.add("Not enough operands. Multiplication not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            Matrix a = mat_list[0];
            mat_list.erase(mat_list.begin());
            Matrix b = mat_list[0];
            mat_list.erase(mat_list.begin());
            if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999 && b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                log.add("Two Scalars given. Multiplication not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            else if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999)
            {
                b = b * (list[0]);
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }
            else if (b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                b = a * (list[0]);
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }
            else
            {
                if (a.col == b.row)
                {
                    b = a * b;
                    mat_list.insert(mat_list.begin(), b);
                    
                }
                
                else
                {
                    log.add("Sizes do not match. Multiplication not possible.");
                    cout << "#Output not possible. Check log for details.";
                    return 0;
                }
            }
            
            break;
        }

        case 'd':  //Division
        {
            if (mat_list.size() < 2)
            {
                log.add("Not enough operands. Division not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            Matrix a = mat_list[0];
            mat_list.erase(mat_list.begin());
            Matrix b = mat_list[0];
            mat_list.erase(mat_list.begin());
            if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999 && b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                log.add("Two Scalars given. Division not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            else if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999)
            {
                if(list[0] == 0)  //Division by zero not allowed
                {
                    log.add("Division by zero. Error.");
                    cout<< "#Output not possible. Check log for details.";
                    return 0;
                }
                b = b/(list[0]);
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }
            else if (b.row == 1 && b.col == 1 && b.m[0][0] == -99999)
            {
                if(list[0] == 0)
                {
                    log.add("Division by zero. Error.");
                    cout<< "#Output not possible. Check log for details.";
                    return 0;
                }
                b = a/(list[0]);
                list.erase(list.begin());
                mat_list.insert(mat_list.begin(), b);
            }
            else  //One matrix cannot divide another matrix
            {
                log.add("Matrix division not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }
            break;
        }

        case 't':  //Transpose
        {
            if (mat_list.size() < 1)  //It requires one element
            {
                log.add("Not enough operands. Transpose not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }
            Matrix a = mat_list[0];
            mat_list.erase(mat_list.begin());

            if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999)
            {
                log.add("Scalar variable present. Transpose not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }
            a = a.transpose();
            mat_list.insert(mat_list.begin(), a);
            break;
        }
        case 'x':  //Determinant
        {
            if (mat_list.size() < 1)
            {
                log.add("Not enough operands. Determinant not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }

            Matrix a = mat_list[0];
            if (a.row == 1 && a.col == 1 && a.m[0][0] == -99999)
            {
                log.add("Scalar variable present. Determinant not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }
            if (a.row != a.col)
            {
                log.add("Not a square matrix. Determinant not possible.");
                cout<< "#Output not possible. Check log for details.";
                return 0;
            }
            mat_list.erase(mat_list.begin());
            double det = a.determinant();
            list.insert(list.begin(), det);
            Matrix mat(1, 1, {-99999});
            mat_list.insert(mat_list.begin(), mat);

            break;
        }
        }
    }
    
    if (mat_list.size() == 0)  //If no result has been produced
    {
        log.add("No output available. Most probably due to no input/operations.");
        cout<< "#Output not possible. Check log for details.";
        return 0;
    }
    if (mat_list[0].row == 1 && mat_list[0].col == 1 && mat_list[0].m[0][0] == -99999)  //If the result is scalar
    {
        cout << "#The final result is a scalar value\n\n";
        cout << list[0] << "\n";
    }
    else
    {
        cout << "#The final result is a matrix \n\n";
        cout << mat_list[0].row << " " << mat_list[0].col << "\n";
        mat_list[0].print_mat();  //Printing matrix
    }
    log.add("Result displayed. Check output file for more details.");
    return 0;
}