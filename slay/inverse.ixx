export module inverse;

import Matrix;
import FileWriter;
import <iostream>;
import <vector>;
import "data_struct.h";
import <string>;


double normalize(matrix eA)
{
	double normal_ea = 0;
	const std::size_t size = eA[0].size();
	for (int j = 0; j < size; j++)
	{
		double sum = 0;
		for (int k = 0; k < size; k++)
		{
			sum += eA[j][k] * eA[j][k];
		}
		normal_ea += sum;
	}
	return sqrt(normal_ea);
}

export void inverse_method(data i, std::ofstream& fileout)
{
	fileout << "\nПоиск обратной матрицы:\n";
	std::vector e(i.matrix_order, std::vector<double>(i.matrix_order));
	for (int j = 0; j < i.matrix_order; j++)
	{
		for (int k = 0; k < i.matrix_order; k++)
		{
			e[j][k] = (k == j) ? 1 : 0;
		}
	}

	std::vector A(i.matrix_order, std::vector<double>(i.matrix_order));
	for (size_t j = 0; j < i.matrix_order; j++)
	{
		i.X = e[j];
		struct out result;
		std::tie(result.X, result.U, result.Z) = SLAY_solution(i);
		out(fileout, result.U, "Матрица U" + std::to_string(j));
		out(fileout, result.Z, "Матрица Z" + std::to_string(j));

		for (int k = 0; k < i.matrix_order; k++)
		{
			A[k][j] = result.X[k];
		}
	}
	out(fileout, A, "Обратная матрица");
	auto eA = matrix_minus_matrix(matrix_prod_matrix(i.A, A), e);
	out(fileout, eA, "Матрица невязки");

	fileout << "Норма невязки: " << normalize(eA) << "\n\n";
}

