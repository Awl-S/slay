export module Seidel;

import Matrix;
import FileWriter;
import <fstream>;
import "data_struct.h";

export void seidel(const data i, std::ofstream &fileout)
{
	struct out result;
	std::tie(result.X, result.U, result.Z) = SLAY_solution(i);

	out(fileout, result.X, "������� ����");
	out(fileout, result.U, "������� U");
	out(fileout, result.Z, "������� Z");

	const auto eb = vector_minus(matrix_prod_vector(i.A, result.X), i.X);
	out(fileout, eb, "������ �������");

	double normal_eb = 0;
	for(int j = 0; j < i.matrix_order; j++)
	{
		normal_eb += eb[j] * eb[j];
	}
	normal_eb = sqrt(normal_eb);
	fileout << "����� �������: " << normal_eb << "\n\n";
}