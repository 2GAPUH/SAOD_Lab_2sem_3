#include "RTree.h"

void RTree::Search(Node node, sf::IntRect rect, Node* res)
{

}

RTree::RTree()
{
	root = new Node;
	sf::Vector2f vect;
	vect.x = 0;
}

RTree::~RTree()
{

}

void RTree::Search(sf::IntRect rect, Node* res)
{
	Search(*root, rect, res);
}
