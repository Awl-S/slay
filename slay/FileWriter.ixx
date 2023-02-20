export module FileWriter;
import <vector>;
import <fstream>;
import <iomanip>;

export void out(std::ofstream& fileout, const std::vector<double>& matrix, const std::string& name)
{
	fileout << name << " :\n";
	for (const auto i : matrix)
	{
		fileout << std::setw(4) << std::setprecision(2) << i << "\t";
	}
	fileout << "\n\n";
}

export void out(std::ofstream& fileout, const std::vector<std::vector<double>>& matrix, const std::string& name)
{
	fileout << name << " :\n";
	for (const auto& i : matrix)
	{
		for (const auto& j : i)
		{
			fileout << std::setw(4) << std::setprecision(2) << j << "\t";
		}
		fileout << "\n";
	}
	fileout << "\n";
}
