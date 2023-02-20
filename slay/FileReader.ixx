export module FileReader;

import <fstream>;
import <vector>;
import <iostream>;
import "data_struct.h";

export std::vector<data> Read(const char* filename)
{
	std::ifstream input(filename);
	std::vector<data> send;
	data result;

	while (input >> result.method >> result.matrix_order)
	{
		result.A = matrix(result.matrix_order, std::vector<double>(result.matrix_order));
		result.X = std::vector<double>(result.matrix_order);
		for (int i = 0; i < result.matrix_order; i++)
		{
			for (int j = 0; j < result.matrix_order; j++)
			{
				input >> result.A[i][j];
			}
			input >> result.X[i];
		}
		send.push_back(result);
		result.A.clear();
		result.X.clear();
	}
	
	return send;
}