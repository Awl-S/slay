#pragma once
import FileReader;
import Seidel;
import inverse;

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
			seidel(i, fileout);
			break;
		}
		case 3:
		{
			inverse_method(i, fileout);
			break;
		}

		default: std::cout << "Error\n";
		}
	}
	fileout.close();
}
