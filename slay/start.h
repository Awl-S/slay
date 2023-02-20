#pragma once
import FileReader;
import Seidel;
import inverse;
import Matrix;
import FileWriter;

import <iostream>;
import <fstream>;
import "data_struct.h";

inline void start()
{
	auto output = Read("input.txt");
	std::ofstream fileout("output.txt");

	for (::data i : output)
	{
		switch (i.method)
		{
		case 1:
		{
			out(fileout, Extended_Matrix(i), "Расширенная Матрица");
			seidel(i, fileout);
			fileout << "\n\n\n\n";
			break;
		}
		case 3:
		{
			out(fileout, Extended_Matrix(i), "Расширенная Матрица");
			inverse_method(i, fileout);
			fileout << "\n\n\n\n";
			break;
		}
		default: std::cout << "Error\n";
		}
	}
	fileout.close();
}