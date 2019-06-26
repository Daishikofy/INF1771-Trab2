/*****

Creator: Lola Magnard
Description of the following code : 

	The following functions allow the creation and the use of a generic DecisionTree 

*****/
#pragma once
#include <vector>

typedef std::vector<std::vector<std::vector<std::string>>> Children;
typedef std::vector<std::vector<std::string>> Group;
typedef struct node Node;

class DecisionTree
{
public:
	/******
		Function: Generate Tree

		Description: Given a certain dataSet, returns the decisionTree proper to this dataSet

		Parameters:
			- examples : The dataSet used to create the tree
			- parameters : A vector with the index of each parameters relative to their position in an
		example starting at 0.
			- classIndex : must be -1

		Return:
			Node* is a pointer to the root of the decisionTree.
	******/
	Node* GenerateTree (Group examples, std::vector<int> parameters, int classIndex);

	/******
		Function: Classify Example

		Description: Given an example extrated from the same dataSet from which were extracted the 
	samples used in the training of the tree, classifies the example.

		Parameters:
			- examples : The dataSet used to create the tree
			- parameters : A vector with the index of each parameters relative to their position in an
		example starting at 0.
			- classIndex : must be -1

		Return:
			Node* is a pointer to the root of the decisionTree.
	******/
	std::string ClassifyExample (std::vector<std::string> example, Node* decisionTree);
	
	/********
	Function : Delete Tree

	Description : Free the nodes of the structur

	Parameters : 
		- root : Pointer to the root of the tree you want to destroy
	********/
	void Delete(Node* tree);
	
	/******
		Function: Print Tree

		Description: Prints the parameters of the decision tree begining by the fisrt element
	and descending to the left.

		Parameters:
			- root : Pointer to the decisionTree
	******/
	void PrintTree(Node* root);

private:
	float Entropy (Group leaf);
	Children Split (Group node, int parameter);
	Children SelectBestParameter(Group node, std::vector<int>& parameters, int* usedParameter);
	std::string DominantClass(Group leaf);
	void PrintSplit(Children split, int parameter);
};
