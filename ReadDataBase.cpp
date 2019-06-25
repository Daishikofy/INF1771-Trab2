/*****

Creator: Lola Magnard
Description of the following code : 

	The purpose of this code is reading the data from the UCI repository : Car evaluation
	- An example is stored in a vector of string 
	- Each vector contains 6 spaces corresponding to the 6 parameters
	- The whole database is stored in a vector<vector<std::string>>

Class values:
	unacc, acc, good, vgood

Attributes
	buying:   vhigh, high, med, low.
	maint:    vhigh, high, med, low.
	doors:    2, 3, 4, 5more.
	persons:  2, 4, more.
	lug_boot: small, med, big.
	safety:   low, med, high.

*****/

#include <iostream>
#include <fstream>
#include <sstream>
#include "ReadDataBase.h"

void CreateDataSet::ReadFile (std::string filePath)
{
	std::string line;
	std::ifstream file (filePath);
	int debug = 0;

	if (! file.is_open ())
	{
		std::cout << "Couldn't open de file\n";
		return;
	}

	while ( getline (file, line))
	{
		std::vector<std::string> example;
		std::istringstream lineStream(line);
		std::string token;

		//Fill the example with all its attributes
		while(std::getline(lineStream, token, ',')) 
		{
			example.push_back(token);
		}

		//Add the example to the current dataSet
		_dataSet.push_back(example);
		debug ++;
	}

	std::cout << _dataSet[3][5] << "\n";
}

void CreateDataSet::get(std::vector<std::vector<std::string>>& dataSet)
{
	dataSet = _dataSet;
}