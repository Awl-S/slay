#pragma once
import <fstream>;
import <vector>;

using matrix = std::vector<std::vector<double>>;

struct data
{
	std::size_t method;
	std::size_t matrix_order;
	std::vector<std::vector<double>> A;
	std::vector<double> X;
};

struct out
{
	std::vector<double> X;
	std::vector<std::vector<double>> U;
	std::vector<std::vector<double>> Z;
};
