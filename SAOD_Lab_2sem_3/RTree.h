#pragma once
#include "SFML/Graphics.hpp"

class RTree
{
private:
	struct Node
	{

	};
	Node* root = nullptr;

	void Search(Node node, sf::IntRect rect, Node* res);

public:
	RTree();
	~RTree(); 
	void Search(sf::IntRect rect, Node* res);
};

