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

class SolverPart2
{
public:
	vector<string> Results;

	void Process(std::vector<string> input)
	{
		for (vector<string>::iterator it = input.begin(); it != input.end(); ++it)
		{
			for (vector<string>::iterator comparedIt = vector<string>::iterator(it); comparedIt != input.end(); ++comparedIt)
			{
				string item1 = *it;
				string item2 = *comparedIt;

				ASSERT_EQ(item1.size(), item2.size());

				int diffCount = 0;

				for (int i = 0; i < item1.size(); i++)
				{
					char c1 = item1[i];
					char c2 = item2[i];

					if (c1 == c2)
						diffCount++;
				}

				bool isMatch = diffCount == 1;

				if (isMatch)
				{
					string intersect;
					set_intersection(item1.begin(), item1.end(), item2.begin(), item2.end(), std::inserter<string>(intersect, intersect.begin()));
					this->Results.push_back(intersect);
				}
			}
		}
	}

	void Process_NoConsiderPosition()
	{
		// each string should know char diff as [1, -1, 2, 3, 4]
		// or [0, 0, 0, 1, 0] where 1 is the diff char and 0 is the same char
		// to self: [0, 0, 0, 0, 0]
		// to match: [0, 0, 1, 0, 0]
		// to non-match: [0, 1, 1, 0, 0]

		// now, this can be reduced to single number count.
		// find x that has y such that count of x for y == 1.

		// when searching, line 1 needs to look for line 2 to n.
		// line k needs to look for line k+1 to n.

		set<string> setinput = set<string>(setinput.begin(), setinput.end());
		vector<pair<string, pair<string, string>>> matches; // [unique, [str1, str2]]

		for (set<string>::iterator it = setinput.begin(); it != setinput.end(); ++it)
		{
			string itemString = *it;
			set<char> item = set<char>(itemString.begin(), itemString.end());

			for (set<string>::iterator comparedIt = set<string>::iterator(it); comparedIt != setinput.end(); ++comparedIt)
			{
				string comparedItemString = *comparedIt;
				set<char> comparedItem = set<char>(comparedItemString.begin(), comparedItemString.end());

				set<char> intersect;
				set_intersection(item.begin(), item.end(), comparedItem.begin(), comparedItem.end(), std::inserter(intersect, intersect.begin()));

				bool isMatch = (intersect.size() == (item.size() - 1));

				pair<string, string> matchedStrings = pair<string, string>(itemString, comparedItemString);
				matches.push_back(pair<string, pair<string, string>>("unique", matchedStrings));

				// AH ... this will not consider the positions of characters....
			}
		}
	}
};

TEST(Quiz02, Part2_SetIntersection_On_String)
{
	set<string> s1 = { "a", "b", "c" };
	set<string> s2 = { "a", "d", "c" };

	set<string> intersection;

	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersection, intersection.begin()));

	string item0 = *std::next(intersection.begin(), 0);
	string item1 = *std::next(intersection.begin(), 1);

	ASSERT_EQ(2, intersection.size());
	ASSERT_EQ("a", item0);
	ASSERT_EQ("c", item1);
}

TEST(Quiz02, Part2_StringToCharSet)
{
	string str = "abcdeabc";
	set<char> unique = set<char>(str.begin(), str.end());

	ASSERT_EQ(5, unique.size());
}

TEST(Quiz02, Part2_SampleInput)
{
	std::vector<string> data;
	data.push_back("abcde");
	data.push_back("fghij");
	data.push_back("klmno");
	data.push_back("pqrst");
	data.push_back("fguij");
	data.push_back("axcye");
	data.push_back("wvxyz");

	SolverPart2 solver;
	solver.Process(data);
	vector<string> letterList = solver.Results;
	ASSERT_EQ(1, letterList.size());

	string letters = *std::next(letterList.begin(), 0);
	ASSERT_EQ(4, letters.size());

	ASSERT_EQ("fgij", letters);
}