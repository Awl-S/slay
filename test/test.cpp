#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

//Функция умножения векторов
double scalar_product(int vector_order, double* vector1, double* vector2)
{
     double sum = 0;
     for (int i = 0; i < vector_order; i++)
          sum += vector1[i] * vector2[i];
     return sum;
}

//Функция умножения вектора на число
double* vector_prod_number(int vector_order, double* vector1, double number)
{
     double* vector2 = new double[vector_order];
     for (int i = 0; i < vector_order; i++)
          vector2[i] = vector1[i] * number;
     return vector2;
}

//Функция разницы векторов
double* vector_minus(int vector_order, double* vector1, double* vector2)
{
     double* vector3 = new double[vector_order];
     for (int i = 0; i < vector_order; i++)
          vector3[i] = vector1[i] - vector2[i];
     return vector3;
}

//Функция сложения векторов
double* vector_plus(int vector_order, double* vector1, double* vector2)
{
     double* vector3 = new double[vector_order];
     for (int i = 0; i < vector_order; i++)
          vector3[i] = vector1[i] + vector2[i];
     return vector3;
}

//Функция умножения матрицы на вектор
double* matrix_prod_vector(int order, double** matrix, double* vector)
{
     int i, j;
     double* c = new double[order];
     for (i = 0; i < order; i++)
     {
          c[i] = 0;
          for (j = 0; j < order; j++)
               c[i] += matrix[i][j] * vector[j];
     }
     return c;
}

//Функция умножения матрицы на матрицу
double** matrix_prod_matrix(int order, double** A, double** B)
{
     int i, j, p;
     double** c = new double* [order];
     for (i = 0; i < order; i++)
          c[i] = new double[order];
     for (i = 0; i < order; i++)
          for (j = 0; j < order; j++)
          {
               c[i][j] = 0;
               for (p = 0; p < order; p++)
                    c[i][j] += A[i][p] * B[p][j];
          }
     return c;
}

//Функция разницы матриц
double** matrix_minus_matrix(int order, double** A, double** B)
{
     int i, j;
     double** c = new double* [order];
     for (i = 0; i < order; i++)
          c[i] = new double[order];
     for (i = 0; i < order; i++)
          for (j = 0; j < order; j++)
               c[i][j] = A[i][j] - B[i][j];
     return c;
}

//Функция решения СЛАУ
double* SLAE_solution(int matrix_order, double** A, double* B, double** U, double** Z)
{
     int i, j, h, k, t, r;

     //Инициализация и заполнение расширенной матрицы
     double** exA = new double* [matrix_order + 1];
     for (i = 0; i < matrix_order + 1; i++)
          exA[i] = new double[matrix_order + 1];
     for (i = 0; i < matrix_order; i++)
     {
          for (j = 0; j < matrix_order; j++)
               exA[i][j] = A[i][j];
          exA[i][j] = -B[i];
     }
     for (i = 0; i < matrix_order; i++)
          exA[matrix_order][i] = 0;
     exA[matrix_order][matrix_order] = 1;

     //Иницаиализация вектора X
     double* X = new double[matrix_order];
     double sumH, sumK, sumT;

     //Построение матриц U и Z
     for (i = 0; i < matrix_order + 1; i++)
     {
          for (j = 0; j < matrix_order + 1; j++)
          {
               sumH = 0;
               for (h = 0; h <= i - 1; h++)
               {
                    sumK = 0;
                    for (k = 0; k < matrix_order + 1; k++)
                         sumK += exA[i][k] * Z[h][k];
                    sumH += sumK * Z[h][j];
               }
               U[i][j] = exA[i][j] - sumH;
          }
          for (r = 0; r < matrix_order + 1; r++)
          {
               sumT = 0;
               for (t = 0; t < matrix_order + 1; t++)
                    sumT += U[i][t] * U[i][t];
               Z[i][r] = U[i][r] / sqrt(sumT);
          }
     }

     //Нахождение вектора X
     for (i = 0; i < matrix_order; i++)
          X[i] = Z[matrix_order][i] / Z[matrix_order][matrix_order];

     //Освобождение памяти
     for (int i = 0; i < matrix_order + 1; i++)
          delete[]exA[i];

     //Возвращение вектора X
     return X;
}

int main()
{
     setlocale(LC_ALL, "RUS");
     ifstream input("input.txt");
     ofstream output("output.txt");
     if (!input.is_open()) return -1;
     int task, matrix_order, i, j, k, p;
     input >> task >> matrix_order;

     //Инициализация матрицы А
     double** A = new double* [matrix_order];
     for (i = 0; i < matrix_order; i++)
          A[i] = new double[matrix_order];

     //Инициализация ветора В
     double* B = new double[matrix_order];

     //3аполнение матрицы А и ветора В
     for (i = 0; i < matrix_order; i++)
     {
          for (j = 0; j < matrix_order; j++)
               input >> A[i][j];
          input >> B[i];
     }

     //Инициализация матрицы U
     double** U = new double* [matrix_order + 1];
     for (i = 0; i < matrix_order + 1; i++)
          U[i] = new double[matrix_order + 1];

     //Инициализация матрицы Z
     double** Z = new double* [matrix_order + 1];
     for (i = 0; i < matrix_order + 1; i++)
          Z[i] = new double[matrix_order + 1];

     //Инициализация расширенной матрицы
     double** exA = new double* [matrix_order + 1];
     for (i = 0; i < matrix_order + 1; i++)
          exA[i] = new double[matrix_order + 1];

     //3аполнение расширенной матрицы
     for (i = 0; i < matrix_order; i++)
     {
          for (j = 0; j < matrix_order; j++)
               exA[i][j] = A[i][j];
          exA[i][j] = -B[i];
     }
     for (i = 0; i < matrix_order; i++)
          exA[matrix_order][i] = 0;
     exA[matrix_order][matrix_order] = 1;

     //Bывод расширенной матрицы
     output << "Расширенная матрица: " << endl;
     for (i = 0; i < matrix_order + 1; i++)
     {
          for (j = 0; j < matrix_order + 1; j++)
               output << setw(4) << setprecision(2) << exA[i][j] << " ";
          output << endl;
     }

     //Инициализация ветора X
     double* X = new double[matrix_order];

     //Инициализация вектора невязки и его нормы
     double norma_eb;
     double* eb = new double[matrix_order];

     //Инициализация матрицы невязки и ее нормы
     double norma_eA;
     double** eA = new double* [matrix_order];
     for (i = 0; i < matrix_order; i++)
          eA[i] = new double[matrix_order];

     //Инициаиализация единичной матрицы
     double** E = new double* [matrix_order];
     for (i = 0; i < matrix_order; i++)
          E[i] = new double[matrix_order];
     for (i = 0; i < matrix_order; i++)
     {
          for (j = 0; j < matrix_order; j++)
          {
               if (i == j)
                    E[i][j] = 1;
               else
                    E[i][j] = 0;
          }
     }

     //Инициализация обратной матрицы
     double** A_1 = new double* [matrix_order];
     for (i = 0; i < matrix_order; i++)
          A_1[i] = new double[matrix_order];

     switch (task)
     {
     case 1: //Решение СЛАУ
          X = SLAE_solution(matrix_order, A, B, U, Z);
          output << "\nРешение СЛАУ: " << endl;
          for (i = 0; i < matrix_order; i++)
               output << "x" << i + 1 << " =" << setw(6) << setprecision(2) << X[i] << endl;
          eb = vector_minus(matrix_order, matrix_prod_vector(matrix_order, A, X), B);
          output << "\nМатрица U: " << endl;
          for (i = 0; i < matrix_order + 1; i++)
          {
               for (j = 0; j < matrix_order + 1; j++)
                    output << U[i][j] << " ";
               output << endl;
          }
          output << "\nМатрица Z:" << endl;
          for (i = 0; i < matrix_order + 1; i++)
          {
               for (j = 0; j < matrix_order + 1; j++)
                    output << Z[i][j] << " ";
               output << endl;
          }
          output << "\nВектор невязки:" << endl;
          for (i = 0; i < matrix_order; i++)
               output << setw(6) << setprecision(2) << eb[i] << endl;
          norma_eb = 0;
          for (i = 0; i < matrix_order; i++)
               norma_eb += eb[i] * eb[i];
          norma_eb = sqrt(norma_eb);
          output << "\nНорма невязки:" << setw(6) << setprecision(2) << norma_eb << endl;
          break;

     case 3: //Поиск обратной матрицы
          for (i = 0; i < matrix_order; i++)
          {
               X = SLAE_solution(matrix_order, A, E[i], U, Z);
               output << "\nМатрица U" << i + 1 << ":" << endl;
               for (k = 0; k < matrix_order + 1; k++)
               {
                    for (p = 0; p < matrix_order + 1; p++)
                         output << setw(6) << setprecision(2) << U[k][p] << " ";
                    output << endl;
               }
               output << "\nМатрица Z" << i + 1 << ":" << endl;
               for (k = 0; k < matrix_order + 1; k++)
               {
                    for (p = 0; p < matrix_order + 1; p++)
                         output << setw(6) << setprecision(2) << Z[k][p] << " ";
                    output << endl;
               }
               for (j = 0; j < matrix_order; j++)
                    A_1[j][i] = X[j];
               delete[]X;
          }
          output << "\nОбратная матрица: " << endl;
          for (i = 0; i < matrix_order; i++)
          {
               for (j = 0; j < matrix_order; j++)
                    output << setw(6) << setprecision(2) << A_1[i][j] << " ";
               output << endl;
          }
          output << "\nМатрица невязки:" << endl;
          eA = matrix_minus_matrix(matrix_order, matrix_prod_matrix(matrix_order, A, A_1), E);
          for (i = 0; i < matrix_order; i++)
          {
               for (j = 0; j < matrix_order; j++)
                    output << setw(10) << setprecision(2) << eA[i][j];
               output << endl;
          }
          double sum;
          norma_eA = 0;
          for (i = 0; i < matrix_order; i++)
          {
               sum = 0;
               for (j = 0; j < matrix_order; j++)
                    sum += eA[i][j] * eA[i][j];
               norma_eA += sum;
          }
          norma_eA = sqrt(norma_eA);
          output << "\nНорма матрицы невязки:" << setw(6) << setprecision(2) << norma_eA << endl;
          break;

     default:
          output << "\nОшибка выбора задания. Попробуйте еще раз";
          return 0;
          break;
     }
     delete[]B;
     delete[]eb;
     for (i = 0; i < matrix_order; i++)
          delete[]eA[i];
     for (i = 0; i < matrix_order; i++)
          delete[]A[i];
}
