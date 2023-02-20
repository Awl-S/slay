export module Matrix;
import <vector>;
import "data_struct.h";
import <iostream>;

//Функция для создания расширенной матрицы (extended matrix) exA:
matrix exA_creation(data input)
{
	const size_t size = input.matrix_order;
	matrix exA(size+1, std::vector<double>(size + 1, 0));

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			exA[i][j] = input.A[i][j];
		}
		exA[i][size] = -input.X[i];
		exA[size][i] = 0;
	}
	exA[size][size] = 1;

	return exA;
}

//Функция для создания матриц Z и U:
void create_U_Z(matrix exA, matrix& U, matrix& Z, std::size_t size)
{
	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			double sumH = 0;
			for (int h = 0; h <= i - 1; h++)
			{
				double sumK = 0;
				for (int k = 0; k <= size; ++k)
				{
					sumK += exA[i][k] * Z[h][k];
				}
				sumH += sumK * Z[h][j];
			}
			U[i][j] = exA[i][j] - sumH;
		}
		for (int j = 0; j <= size; j++)
		{
			double sumT = 0;
			for (int t = 0; t <= size; t++)
			{
				sumT += U[i][t] * U[i][t];
			}
			Z[i][j] = U[i][j] / sqrt(sumT);
		}
	}
}

//решает систему линейных уравнений методом итераций Зейделя
export std::tuple<std::vector<double>, matrix, matrix> SLAY_solution(data input)
{
	const size_t size = input.matrix_order;

	const auto exA = exA_creation(input);

	std::vector Z(input.matrix_order + 1, std::vector<double>(input.matrix_order + 1));
	std::vector U(input.matrix_order + 1, std::vector<double>(input.matrix_order + 1));

	create_U_Z(exA, U, Z, size);

	std::vector<double> X(size);
	for (int i = 0; i < size; i++)
	{
		X[i] = Z[size][i] / Z[size][size];
	}
	return std::make_tuple(X, U, Z);
}

//Функция умножения матрицы на вектор
export std::vector<double> matrix_prod_vector(matrix matrix, std::vector<double> vector)
{
	std::vector<double> c;
	for (int i = 0; i < vector.size(); i++)
	{
		c.push_back(0);
		for (int j = 0; j < vector.size(); j++)
			c[i] += matrix[i][j] * vector[j];
	}
	return c;
}

//Функция разницы векторов
export std::vector<double> vector_minus(std::vector<double> vector1, std::vector<double> vector2)
{
	std::vector<double> vector3(vector1.size());
	for (int i = 0; i < vector1.size(); i++)
		vector3[i] = vector1[i] - vector2[i];
	return vector3;
}

//Функция умножения матрицы на матрицу
export matrix matrix_prod_matrix(matrix A, matrix B)
{
	matrix c(B.size(), std::vector<double>(B.size(), 0));
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			c[i][j] = 0;
			for (int p = 0; p < B.size(); p++)
			{
				c[i][j] += A[i][p] * B[p][j];
			}
		}
	}
	return c;
}

//Функция разницы матриц
export matrix matrix_minus_matrix(matrix A, matrix B)
{
	matrix c(A.size(), std::vector<double>(A.size()));
	for (int i = 0; i < B.size(); i++)
		for (int j = 0; j < B.size(); j++)
			c[i][j] = A[i][j] - B[i][j];
	return c;
}