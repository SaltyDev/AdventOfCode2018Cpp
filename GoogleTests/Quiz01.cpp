#include "pch.h"
#include <fstream>
#include <algorithm>

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

struct DuplicateFrequencyRecord
{
public:
	bool IsDuplicate;
	int NewFrequency;

	DuplicateFrequencyRecord(bool isDuplicate, int newFrequency)
	{
		IsDuplicate = isDuplicate;
		NewFrequency = newFrequency;
	}

	DuplicateFrequencyRecord() : DuplicateFrequencyRecord(false, 0) { }
};

class SolverPart2
{
public:
	int RepeatListCount;
	int FirstTwiceFrequency;

	SolverPart2()
	{
		RepeatListCount = 0;
		FirstTwiceFrequency = 0;
		records.push_back(0);
	}

	void FindTwice(vector<int> input)
	{
		bool found = false;

		while (!found)
		{
			RepeatListCount++;

			for (std::vector<int>::iterator it = input.begin(); !found && it != input.end(); ++it)
			{
				int newAddedFrequency = *it;
				solver = solver.Add(newAddedFrequency);
				
				found = records.size() > 0 && (std::find(records.begin(), records.end(), solver.CurrentFrequency) != records.end());

				if (found)
				{
					FirstTwiceFrequency = solver.CurrentFrequency;
					break;
				}

				records.push_back(solver.CurrentFrequency);
			}
		}
	}

private:
	std::vector<int> records;
	Solver solver = Solver(0);
};

TEST(Quiz01, Part1)
{
	Solver solver1 = Solver(0).Add(1).Add(1).Add(1);
	EXPECT_TRUE(solver1.HasFrequency(3));

	Solver solver2 = Solver(0).Add(1).Add(1).Add(-2);
	EXPECT_TRUE(solver2.HasFrequency(0));

	Solver solver3 = Solver(0).Add(-1).Add(-2).Add(-3);
	EXPECT_TRUE(solver3.HasFrequency(-6));

	Solver solver4 = Solver(0).Add(1).Add(1).Add(1);
	EXPECT_TRUE(solver4.HasFrequency(3));

	Solver solverFinal = Solver(0);

	// https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
	std::ifstream infile("../Quiz01.txt");
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

TEST(Quiz01, Part2)
{
	vector<int> input1;
	input1.push_back(1);
	input1.push_back(-1);
	SolverPart2 solver1 = SolverPart2();
	solver1.FindTwice(input1);
	EXPECT_EQ(0, solver1.FirstTwiceFrequency);

	vector<int> input2;
	input2.push_back(3);
	input2.push_back(3);
	input2.push_back(4);
	input2.push_back(-2);
	input2.push_back(-4);
	SolverPart2 solver2 = SolverPart2();
	solver2.FindTwice(input2);
	EXPECT_EQ(10, solver2.FirstTwiceFrequency);

	vector<int> input3;
	input3.push_back(-6);
	input3.push_back(3);
	input3.push_back(8);
	input3.push_back(5);
	input3.push_back(-6);
	SolverPart2 solver3 = SolverPart2();
	solver3.FindTwice(input3);
	EXPECT_EQ(5, solver3.FirstTwiceFrequency);

	vector<int> input4;
	input4.push_back(7);
	input4.push_back(7);
	input4.push_back(-2);
	input4.push_back(-7);
	input4.push_back(-4);
	SolverPart2 solver4 = SolverPart2();
	solver4.FindTwice(input4);
	EXPECT_EQ(14, solver4.FirstTwiceFrequency);

	vector<int> inputFinal;

	// https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
	std::ifstream infile("../Quiz01.txt");
	string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int frequency;
		if (!(iss >> frequency)) { break; } // error

		// process pair (a,b)
		inputFinal.push_back(frequency);
	}

	SolverPart2 solverFinal;
	//solverFinal.FindTwice(inputFinal);

	std::cerr << "[          ] solverFinal.RepeatListCount = " << solverFinal.RepeatListCount << std::endl;
	std::cerr << "[          ] solverFinal.FirstTwiceFrequency = " << solverFinal.FirstTwiceFrequency << std::endl;
}

TEST(Quiz01, Part2Additional)
{
	vector<int> input;
	input.push_back(7); // 7
	input.push_back(7); // 14
	input.push_back(-13); // 1
	input.push_back(4); //5
	input.push_back(9); //14
	input.push_back(3); //17
	SolverPart2 solver = SolverPart2();
	solver.FindTwice(input);
	EXPECT_EQ(14, solver.FirstTwiceFrequency);
}

TEST(Quiz01, Part2Additional_RepeatList)
{
	vector<int> input;
	input.push_back(7); // 7
	input.push_back(-6); // 1
	// 8, 2, 9, 3, ..., 13, 7
	SolverPart2 solver = SolverPart2();
	solver.FindTwice(input);
	EXPECT_EQ(7, solver.FirstTwiceFrequency);
}