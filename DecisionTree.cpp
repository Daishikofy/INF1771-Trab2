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
#include <cmath>
#include "ReadDataBase.h"

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

typedef std::vector<std::vector<std::vector<std::string>>> Children;
typedef std::vector<std::vector<std::string>> Group;

float Entropy (Group leaf);
Children Split (Group node, int parameter);
void PrintSplit(Children split, int parameter);
Children SelectBestParameter(Group node, std::vector<int>& parameters, int* usedParameter);
Node* GenerateTree (Group exemples, std::vector<int> parameters, int classIndex);

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
	int a = 1;
	for (int i = dataSet.size() - 10; i < dataSet.size() ; i++)
	{
		auxDebug.push_back(dataSet[i]);
		std::cout << "El: " << a << " " << dataSet[i][3] << "\n";
		a++;
	}
	/*int parameter;
	Children children = SelectBestParameter(auxDebug, parameters, &parameter);
	PrintSplit(children, 6);
	std::cout << "Used parameter: " << parameter << "\n";
	*/
	Node* node = GenerateTree (auxDebug, parameters, -1);

	return 0;
}

float Entropy (Group leaf)
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

Children Split (Group node, int parameter)
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

Children SelectBestParameter(Group node, std::vector<int>& parameters, int* usedParameter)
{
	//Para todos os parametros na lista fazer split
	//Cacular a entropia de todos os filhos
	//Adicionar a entropia
	//Comparar com o melhor
	//Se o atual for melhor do que o melhor
		//O Children best passa a ser o atual
		//O indice do melhor parametro passa  ser o atual
	//Remove o melhor parametro da lista de parametros
	//retorna o children
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

Node* GenerateTree (Group exemples, std::vector<int> parameters, int classIndex)
{
	if (exemples.size() == 0)
		return nullptr;
	else if (parameters.size() == 0)
		return nullptr; //FIND SOMETHING BETTER
		
	Node* node = new Node;
	
//Set the node's class	
	if (classIndex >= 0)
		node->classe = exemples[0][classIndex];
	else
		node->classe = "NoClass";
		
//Set the node's value (has a value only if it's group is pure)	
	if (Entropy(exemples) == 0)
	{
		node->value = exemples[0][exemples[0].size() - 1];
		return node;	
	}		
	else
		node->value = "NoValue";
//Set the node's parameter
	Children children = SelectBestParameter(exemples, parameters, &node->parameter);
	std::cout << "\n- - - - -NOVA ENTRADA- - - - -\n";
	PrintSplit(children, 6);
	std::cout << "Parametro: " << node->parameter << "\n";
	for (int i = 0; i < children.size(); i++)
	{
		std::cout << "Entra em parametro " << node->parameter << " class " << children[i][0][node->parameter] << "\n";
		node->children[i] = GenerateTree (children[i], parameters, node->parameter);
	}
	
	return node;
}

void PrintSplit(Children split, int parameter)
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
