//PSEUDO CODE
/*********FUNCAO PRINCIPAL***********/
// decisionTree CreateTree (exemples, attributes, default)
//{
  //if (exemples == nullptr)
  //  return default;
  //else if (attributes == nullptr)
  //  return MODE(exemples);
  //else
  //{
  //  best = SelectAttribute(attributes, examples);
  //  tree = 
  //}
//}
#include <vector>
#include <iostream>
#include <sstream>
#include "ReadDataBase.h"

int main (void)
{
	std::string filePath = "car-2.data";
	std::vector<std::vector<std::string>> dataSet;
	CreateDataSet createDataSet;

	createDataSet.ReadFile (filePath);
	createDataSet.get(dataSet);

	return 0;
}

int Entropy ()
{
	int size;
	
	//Split the examples by final results
	//Cacul the probability of each result
	//Multiply the probability by the log of this probability
	//Sum everything 
}

