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
#include <iostream>
#include <sstream>
#include <cmath>
#include "ReadDataBase.h"
#include "DecisionTree.h"

typedef struct instance
{
	std::string name;
	int number;
}Instance;

typedef struct node Node;
struct node {
	int parameter;
	std::string classe;
	std::string value;
	
	std::vector<Node*> children;
};

int main (void)
{
	std::string filePath = "car-2.data";
	Group dataSet, auxDebug;
	CreateDataSet createDataSet;
	std::vector<int> parameters;
	for (int i = 0; i < 6; i++)
		parameters.push_back(i);

	createDataSet.ReadFile (filePath);
	createDataSet.get(dataSet);
	for (int i = dataSet.size() - 10; i < dataSet.size() ; i++)	
		auxDebug.push_back(dataSet[i]);

	DecisionTree decisionTree;
	std::cout << "CREATE TREE\n\n";
	Node* root = decisionTree.GenerateTree (auxDebug, parameters, -1);
	std::cout << "\n\nEXPLORE TREE\n\n";
	decisionTree.PrintTree(root);
	std::cout << "\n\nTEST TREE\n\n";
	std::vector<std::string> example = dataSet[dataSet.size() - 13];
	std::string res = decisionTree.ClassifyExample(example,root);
	std::cout << "Result: " << res << "\n";
	return 0;
}

float DecisionTree::Entropy (Group leaf)
{
	int flag;
	int leafSize = leaf.size();
	int instanceSize = leaf[0].size();
	std::vector<Instance> nInstances;
	Instance instance;
	
	instance.name = leaf[0][instanceSize - 1];
	instance.number = 1;
	nInstances.push_back(instance);

	for (int i = 1; i < leafSize ; i++)
	{
		flag = 0;
		for (int j = 0; j < nInstances.size(); j++)
		{
			if (leaf[i][instanceSize - 1] == nInstances[j].name)
			{
				nInstances[j].number += 1;
				flag = 1;
			}
		}
		if (!flag)
		{
			instance.name = leaf[i][instanceSize - 1];
			instance.number = 1;
			nInstances.push_back(instance);
		}
	}

	float probability, sum = 0;
	for (int i = 0; i < nInstances.size(); i++)
	{
		probability = (float)nInstances[i].number/(float)leafSize;
		sum += probability*std::log(probability);
	}
	
	return std::abs(sum);
}

Children DecisionTree::Split (Group node, int parameter)
{
	int flag;
	int nodeSize = node.size();
	Children children;

	for (int i = 0; i < nodeSize ; i++)
	{
		flag = 0;
		for (int j = 0; j < children.size(); j++)
		{
			if (node[i][parameter] == children[j][0][parameter])
			{
				children[j].push_back(node[i]);
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			std::vector<std::vector<std::string>> group;
			group.push_back(node[i]);
			children.push_back(group);
		}
	}

	return children;
}

Children DecisionTree::SelectBestParameter(Group node, std::vector<int>& parameters, int* usedParameter)
{
	int bestParamIndex = 0;
	Children bestChildren = Split(node, parameters[bestParamIndex]);

	float bestEntropy = 0;
	for (int i = 0 ; i < bestChildren.size(); i++)
		bestEntropy += Entropy(bestChildren[i]);

	for (int i = 1 ; i < parameters.size(); i++)
	{
		Children children = Split (node, parameters[i]);

		float entropy = 0;
		for (int j = 0 ; j < children.size(); j++)
			entropy += Entropy(children[j]);

		if (entropy < bestEntropy)
		{
			bestParamIndex = i;
			bestChildren = children;
			bestEntropy = entropy;
		}
	}
	*usedParameter = parameters [bestParamIndex];
	parameters.erase(parameters.begin() + bestParamIndex);
	return bestChildren;
}

Node* DecisionTree::GenerateTree (Group examples, std::vector<int> parameters, int classIndex)
{
	if (examples.size() == 0)
		return nullptr;
	else if (parameters.size() == 0)
		return nullptr; //FIND SOMETHING BETTER
		
	Node* node = new Node;

//Set the node's class	
	if (classIndex >= 0)
	{
		
		node->classe = examples[0][classIndex];
	}
	else
		node->classe = "NoClass";
	
//Set the node's value (has a value only if it's group is pure)	
	if (Entropy(examples) == 0)
	{
		node->value = examples[0][examples[0].size() - 1];
		return node;	
	}	
	else
		node->value = "NoValue";
		
//Set the node's parameter
	Children children = SelectBestParameter(examples, parameters, &node->parameter);
	std::cout << "\n- - - - -NOVA ENTRADA- - - - -\n";
	PrintSplit(children, 6);
	
	std::cout << "Parametro: " << node->parameter << "\n";
	for (int i = 0; i < children.size(); i++)
	{
		//std::cout << "\nEntra em parametro " << node->parameter << " class " << children[i][0][node->parameter] << "\n";
		node->children.push_back(GenerateTree (children[i], parameters, node->parameter));
	}
	
	return node;
}

void DecisionTree::PrintSplit(Children split, int parameter)
{
	for (int i = 0; i < split.size(); i++)
	{
		std::cout << "\nGROUP " << i << "\n";
		for (int j = 0; j < split[i].size(); j++)
		{
			std::cout << j << " - " << split[i][j][parameter] << "\n";
		}
	}
}

void DecisionTree::PrintTree(Node* root)
{
	if (root->value != "NoValue")
	{
		std::cout << root->value << "\n";
		return;
	}
	std::cout << "Class: " << root->classe << " - Parameter: " << root->parameter << "\n";
	for (int i = 0; i < root->children.size(); i++)
	{
		PrintTree(root->children[i]);
	}
}

std::string DecisionTree::ClassifyExample (std::vector<std::string> example, Node* decisionTree)
{
	std::string value = decisionTree->value;
	while (value == "NoValue")
	{
		int flag = 0;
		int parameter = decisionTree->parameter;
		for (int i = 0; i < decisionTree -> children.size(); i++)
		{
			//DEBUGstd::cout << "Ex: " << example[parameter] << " classe: " << decisionTree->children[i]->classe << "\n";
			if (example[parameter] == decisionTree->children[i]->classe)
			{
				decisionTree = decisionTree->children[i];
				flag = 1;
			}
		}
		if (!flag)
		{
			std::cout << "Error: The data cannot be represented by this tree\n";
			return "Error";
		}
		value = decisionTree->value;
	}

	return value;
}