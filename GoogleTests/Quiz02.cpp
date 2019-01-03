#include "pch.h"
#include <fstream>
#include <algorithm>

using namespace std;

class Solver
{
public:
	void SetInput(std::vector<string> input)
	{
		this->input = input;
	}

	void AddLookupCount(int lookupCount)
	{
		this->lookupMap[lookupCount] = 0;
	}

	int GetLookupCount(int lookupCount)
	{
		bool hasKey = this->lookupMap.count(lookupCount) == 1;

		if (hasKey)
			// doing this when the key does not exist will CREATE the KeyValuePair in the table
			return this->lookupMap[lookupCount];
		else
			return 0;
	}

	void Calculate()
	{
		// for all lines
		// get a set of unique characters in the line
		// for each unique character
		// get the number of occurences in the line
		// if this occurnce count is in the key of the map
		// increment the key by 1

		for (std::vector<string>::iterator iter = this->input.begin(); iter != this->input.end(); ++iter)
		{
			string line = *iter;
			std::set<char> uniqueChars(line.begin(), line.end());
			
			// For each char count, only increment once.
			// Example: aabbcccde, will increment key 2 for 1 instead of 2, and key 3 for 1.
			std::map<int, bool> hasIncrementedForCount;

			for (std::set<char>::iterator charIter = uniqueChars.begin(); charIter != uniqueChars.end(); ++charIter)
			{
				char uniqueChar = *charIter;
				size_t count = std::count(line.begin(), line.end(), uniqueChar);

				bool hasKey = this->lookupMap.count(count) == 1;
				if (hasKey && !hasIncrementedForCount[count])
				{
					hasIncrementedForCount[count] = true;
					this->lookupMap[count]++;
				}
			}
		}

		// key-value pair... not needed.
		for (std::map<int, int>::iterator iter = lookupMap.begin(); iter != lookupMap.end(); ++iter)
		{
			int k = iter->first;
			//ignore value
			//Value v = iter->second;
		}
	}

private:
	std::vector<string> input;
	std::map<int, int> lookupMap;
};

TEST(Quiz02, TestMapFunctions)
{
	std::map<int, int> testMap;

	int count = testMap.count(2); // 0 means not existing
	int index = testMap[2]; // made it. index is 0.
	int count2 = testMap.count(2); // now 1, means exists

	std::cerr << "[          ] Printing Values for TestMapFunctions ..." << std::endl;
	std::cerr << "[          ] ============================" << std::endl;
	std::cerr << "[          ] count = " << count << std::endl;
	std::cerr << "[          ] index = " << index << std::endl;
	std::cerr << "[          ] count2 = " << count2 << std::endl;

	// values are found by prints. why no DIctionary.ContainsKey() in C++ tho??
	ASSERT_EQ(0, count);
	ASSERT_EQ(0, index);
	ASSERT_EQ(1, count2);
}

TEST(Quiz02, Part1_TestInput)
{
	std::vector<string> ids;

	std:ifstream inputFile("../Quiz02.txt");
	string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream inputStringStream(line);
		string id;
		if (!(inputStringStream >> id)) { break; } // error

		// Process line for id
		ids.push_back(id);
	}

	Solver solver;
	solver.SetInput(ids);
	solver.AddLookupCount(2);
	solver.AddLookupCount(3);
	solver.Calculate();
	int count2 = solver.GetLookupCount(2);
	int count3 = solver.GetLookupCount(3);
	int total = count2 * count3;

	std::cerr << "[          ] Printing Quiz02 Solution ..." << std::endl;
	std::cerr << "[          ] ============================" << std::endl;
	std::cerr << "[          ] count2 = " << count2 << std::endl;
	std::cerr << "[          ] count3 = " << count3 << std::endl;
	std::cerr << "[          ] total = " << total << std::endl;
}
