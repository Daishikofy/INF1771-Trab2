#include <iostream>
#include <sstream>
#include <algorithm>
#include "ReadDataBase.h"
#include "DecisionTree.h"

int main (void)
{
	std::string filePath = "car-2.data";
	Group dataSet;
	CreateDataSet createDataSet;
	
	createDataSet.ReadFile (filePath);
	createDataSet.get(dataSet);
	std::random_shuffle(dataSet.begin(), dataSet.end());
for (int t = 1; t < 8; t++)
{
	int percentage = 10*t;

	int trainingSize = (dataSet.size() * percentage)/100;
	std::cout << "\nPERCENTAGE " << percentage; 

	int debug = 1;
	int begin = 0, end = begin + trainingSize;
	float average = 0;
	while (end <= dataSet.size())//K-Fold
	{
		Group trainSample, testSample;
		for (int i = 0; i < begin; i++)
			testSample.push_back(dataSet[i]);
		for (int i = begin; i < end ; i++)	
			trainSample.push_back(dataSet[i]);
		for (int i = end; i < dataSet.size(); i++)
			testSample.push_back(dataSet[i]);
		//std::cout << "BEGIN : " << begin << "  END : " << end << "\n";
		begin = end;
		end = begin + trainingSize;

		if (testSample.size() == 0)
		{
			std::cout << "Test sample is empty\n";
			return 0;
		}
		
		std::vector<int> parameters;
	    /*for (int j = 0; j < 6; j++)
			parameters.push_back(j);*/
		parameters.push_back(0);
		//parameters.push_back(1);
		parameters.push_back(2);
		parameters.push_back(3);
		parameters.push_back(4);
		parameters.push_back(5);

		int goodAnswer = 0, wrongAnswer = 0;
		DecisionTree decisionTree;
		Node* tree = decisionTree.GenerateTree (trainSample, parameters, -1);
		//decisionTree.PrintTree(tree);

		for (int i = 0; i < testSample.size(); i++)//Testing each example from the test sample
		{
			std::string resultClass = testSample[i][testSample[i].size() - 1];
			std::string res = decisionTree.ClassifyExample(testSample[i],tree);
			//std::cout << resultClass << " = " << res << "\n";
			if (res == resultClass)
				goodAnswer++;
			else
				wrongAnswer++;
		}//For//
		float quality = ((float)goodAnswer/(float)testSample.size())*100;
		average += quality;
		/*std::cout << "\nSAMPLE NUMBER " << debug << "\n";
		std::cout << "           Good Answers: " << goodAnswer << "\n";
		std::cout << "          Wrong Answers: " << wrongAnswer << "\n";
		std::cout << "                Quality: " << quality << "%\n";*/
		debug ++;

	}//While//

	average = average/(debug - 1);
	std::cout << "\nAVERAGE : " << average << "%\n";
} 
	return 0;
}