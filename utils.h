#pragma once
#include "vector"
#include "string"
#include <algorithm>


/*
	Description:
		- splits the command:	the first separator is a space followed by commas
		- returs a vector of strings
*/
std::vector<std::string> splitCommand(std::string line);


/*
	Description:
		- splits a line by the given delimiter
		- returs a vector of strings
*/
std::vector<std::string> splitDelimiter(std::string line, std::string delimiter);


