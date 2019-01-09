#pragma once

#ifndef QUIZ02_H
#define QUIZ02_H

#include "pch.h"
#include <fstream>
#include <algorithm>

using namespace std;

class Q02SolverPart2
{
public:
	vector<string> Results;

	Q02SolverPart2();
	Q02SolverPart2(int i);

	void Process(std::vector<string> input);
	void Process_NoConsiderPosition();
};
#endif