#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = k * a.data[i][j];
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

Matrix get_submatrix(Matrix a, int row, int col)
{
    Matrix sub = create_matrix(a.rows - 1, a.cols - 1);
    int sub_i = 0, sub_j = 0;
    for (int i = 0; i < a.rows; i++) {
        if (i == row) continue;
        sub_j = 0;
        for (int j = 0; j < a.cols; j++) {
            if (j == col) continue;
            sub.data[sub_i][sub_j] = a.data[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    if (a.rows == 1) {
        return a.data[0][0];
    }
    if (a.rows == 2) {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    double det = 0;
    for (int j = 0; j < a.cols; j++) {
        Matrix sub = get_submatrix(a, 0, j);
        det += pow(-1, j) * a.data[0][j] * det_matrix(sub);
    }
    return det;
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    double det = det_matrix(a);
    if (det == 0) {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    Matrix inv = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            Matrix sub = get_submatrix(a, i, j);
            inv.data[j][i] = pow(-1, i + j) * det_matrix(sub) / det;
        }
    }
    return inv;
}

void swap_rows(Matrix *a, int i, int j)
{
    double temp;
    for (int k = 0; k < a->cols; k++) {
        temp = a->data[i][k];
        a->data[i][k] = a->data[j][k];
        a->data[j][k] = temp;
    }
}

int rank_matrix(Matrix a)
{
    int rank = 0;
    for (int i = 0; i < a.rows && rank < a.cols; i++) {
        if (a.data[i][rank] == 0) {
            int c = 1;
            while (i + c < a.rows && a.data[i + c][rank] == 0) c++;
            if (i + c < a.rows) {
                swap_rows(&a, i, i + c);
            }
        }
        if (a.data[i][rank] != 0) {
            for (int j = i + 1; j < a.rows; j++) {
                double factor = a.data[j][rank] / a.data[i][rank];
                for (int k = rank; k < a.cols; k++) {
                    a.data[j][k] -= factor * a.data[i][k];
                }
            }
            rank++;
        }
    }
    return rank;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    double trace = 0;
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}