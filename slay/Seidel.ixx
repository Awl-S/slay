export module Seidel;

import Matrix;
import FileWriter;
import <fstream>;
import "data_struct.h";

export void seidel(const data i, std::ofstream &fileout)
{
	struct out result;
	std::tie(result.X, result.U, result.Z) = SLAY_solution(i);

	out(fileout, result.X, "Решение СЛАУ");
	out(fileout, result.U, "Матрица U");
	out(fileout, result.Z, "Матрица Z");

	const auto eb = vector_minus(matrix_prod_vector(i.A, result.X), i.X);
	out(fileout, eb, "Вектор невязки");

	double normal_eb = 0;
	for(int j = 0; j < i.matrix_order; j++)
	{
		normal_eb += eb[j] * eb[j];
	}
	normal_eb = sqrt(normal_eb);
	fileout << "Норма невязки: " << normal_eb << "\n\n";
}
