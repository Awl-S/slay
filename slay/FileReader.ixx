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
		for (int i = 0; i < result.matrix_order; i++)
		{
			std::vector<double> buffer;
			double temp;
			for (int j = 0; j < result.matrix_order; j++)
			{
				input >> temp;
				buffer.push_back(temp);
			}
			result.A.push_back(buffer);

			input >> temp;
			result.X.push_back(temp);
		}
		send.push_back(result);
	}
	
	return send;
}


