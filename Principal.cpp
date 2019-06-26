
#include <iostream>
#include <sstream>
#include <algorithm>
#include "ReadDataBase.h"
#include "DecisionTree.h"

typedef std::vector<std::pair<std::string, std::vector<std::pair<std::string,int>>>> ConfusionMatrix;

float K_Fold(Group dataSet, float percentage);
ConfusionMatrix GenerateConfusionMatrix (std::vector<std::pair<std::string,std::string>> results);
void PrintConfusionMatrix(ConfusionMatrix& confusionMatrix);

int main (void)
{
	std::string filePath = "nursery.data";
	Group dataSet;
	CreateDataSet createDataSet;
	
	createDataSet.ReadFile (filePath);
	createDataSet.get(dataSet);
	std::random_shuffle(dataSet.begin(), dataSet.end());
	Group auxDebug;
	
	for (int i = 0; i < dataSet.size(); i++)
		auxDebug.push_back(dataSet[i]);
	

//for (int t = 1; t < 10; t++)
//{
	float percentage = 30;//*(float)t;

	std::cout << "\n\nPERCENTAGE " << percentage << "\n";
	 
	float average = K_Fold(auxDebug, percentage);
	
	std::cout << "AVERAGE : " << average << "%\n";
//} 
	return 0;
}

float K_Fold(Group dataSet, float percentage)
{
	int trainingSize = (dataSet.size() * percentage)/100;
	
	int debug = 1;
	int begin = 0, end = begin + trainingSize;
	float average = 0;
	std::vector<std::pair<std::string,std::string>> resAndExpect;
	
	
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
	    for (int j = 0; j < dataSet[0].size() - 1; j++)
			parameters.push_back(j);

		/*parameters.push_back(0);
		//parameters.push_back(1);
		parameters.push_back(2);
		parameters.push_back(3);
		parameters.push_back(4);
		parameters.push_back(5);*/

		int goodAnswer = 0, wrongAnswer = 0;
		DecisionTree decisionTree;
		Node* tree = decisionTree.GenerateTree (trainSample, parameters, -1);
		//decisionTree.PrintTree(tree);
		for (int i = 0; i < testSample.size(); i++)//Testing each example from the test sample
		{
			std::pair<std::string,std::string> results;
			results.first = testSample[i][testSample[i].size() - 1];
			results.second = decisionTree.ClassifyExample(testSample[i],tree);
			//std::cout << resultClass << " = " << res << "\n";
			if (results.first == results.second)
				goodAnswer++;
			else
				wrongAnswer++;
			
			resAndExpect.push_back(results);
			
		}//For//
		decisionTree.Delete(tree);
		
		float quality = ((float)goodAnswer/(float)testSample.size())*100;
		average += quality;
		std::cout << "      SAMPLE NUMBER " << debug << "\n";
		
		/*
		std::cout << "           Good Answers: " << goodAnswer << "\n";
		std::cout << "          Wrong Answers: " << wrongAnswer << "\n";
		std::cout << "                Quality: " << quality << "%\n";*/
		debug ++;
		
	}//While//
	
	ConfusionMatrix confusionMatrix = GenerateConfusionMatrix(resAndExpect);
	PrintConfusionMatrix(confusionMatrix);
	
	return average/(float)(debug - 1);
}

ConfusionMatrix GenerateConfusionMatrix (std::vector<std::pair<std::string,std::string>> results)
{ 
	ConfusionMatrix confusionMatrix;
	
	for(int i = 0; i < results.size(); i++)//Take all the results
	{
		int firstIsIn = 0; 
		for (int j = 0; j < confusionMatrix.size(); j++)//Look if the first result is in the matrix
		{
			if (confusionMatrix[j].first == results[i].first)//If it is, 
			{
				firstIsIn = 1;
				int secondIsIn = 0;
				for (int k = 0; k < confusionMatrix[j].second.size(); k++)// looks if the second is in the matrix
				{
					if (confusionMatrix[j].second[k].first == results[i].second)// if it is, increment the int
					{
						confusionMatrix[j].second[k].second += 1;
						secondIsIn = 1;
					}
				}
				if (secondIsIn == 0)
				{
					std::pair<std::string, int> aux;
					aux.first = results[i].second;
					aux.second = 1;
					confusionMatrix[j].second.push_back(aux);
				}
			}		
		}
		if (firstIsIn == 0)
		{
			std::pair<std::string, int> auxsecond;
			auxsecond.first = results[i].second;
			auxsecond.second = 1;
			std::pair<std::string, std::vector<std::pair<std::string, int>>> auxfirst;
			auxfirst.first = results[i].first;
			auxfirst.second.push_back(auxsecond);		
			
			confusionMatrix.push_back(auxfirst);
		}
	}
	
	return confusionMatrix;
}

void PrintConfusionMatrix(ConfusionMatrix& confusionMatrix)
{
	for (int i = 0; i < confusionMatrix.size(); i++)
	{
		std::cout << "\n          EXPECTED : " << confusionMatrix[i].first << "\n";
		for(int j = 0; j < confusionMatrix[i].second.size(); j++)
		{
			std::cout << "                - " << confusionMatrix[i].second[j].first << "  :  " << confusionMatrix[i].second[j].second << "\n";
		}
	}
}
