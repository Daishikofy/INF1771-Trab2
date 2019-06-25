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
#pragma once
#include <vector>

class CreateDataSet
{
public:
	void ReadFile (std::string filePath);
	void get(std::vector<std::vector<std::string>>& dataSet);

private:
	std::vector<std::vector<std::string>> _dataSet;
};