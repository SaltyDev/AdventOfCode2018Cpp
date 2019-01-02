#include "pch.h"
#include <fstream>

using namespace std;

class Solver
{
public:
	int CurrentFrequency;
	int AddCount;

	Solver(int start, int addCount)
	{
		this->CurrentFrequency = start;
		this->AddCount = addCount;
	}

	Solver(int start) : Solver(start, 0)
	{

	}

	Solver Add(int diff)
	{
		return Solver(this->CurrentFrequency + diff, this->AddCount + 1);
	}

	bool HasFrequency(int frequency)
	{
		return this->CurrentFrequency == frequency;
	}
};

TEST(Quiz01, SampleInput)
{
	Solver solver1 = Solver(0).Add(1).Add(1).Add(1);
	EXPECT_TRUE(solver1.HasFrequency(3));

	Solver solver2 = Solver(0).Add(1).Add(1).Add(-2);
	EXPECT_TRUE(solver2.HasFrequency(0));

	Solver solver3 = Solver(0).Add(-1).Add(-2).Add(-3);
	EXPECT_TRUE(solver3.HasFrequency(-6));

	Solver solver4 = Solver(0).Add(1).Add(1).Add(1);
	EXPECT_TRUE(solver4.HasFrequency(3));

	// https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
	std::ifstream infile("../Quiz01.txt");

	Solver solverFinal = Solver(0);

	string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int frequency;
		if (!(iss >> frequency)) { break; } // error

		// process pair (a,b)
		solverFinal = solverFinal.Add(frequency);
	}

	std::cerr << "[          ] solverFinal.solverFinal.AddCount = " << solverFinal.AddCount << std::endl;
	std::cerr << "[          ] solverFinal.CurrentFrequency = " << solverFinal.CurrentFrequency << std::endl;
}