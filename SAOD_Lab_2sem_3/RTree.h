#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

struct Node {
    sf::FloatRect bounds;
    std::vector<sf::FloatRect> rectangles;
    std::vector<Node*> children;

    Node(sf::FloatRect bounds) : bounds(bounds) {}

    bool isLeafNode() const {
        return children.empty();
    }
};

class RTree {
private:
    Node* root;
    int maxRectanglesPerNode;

public:
    RTree(int maxRectanglesPerNode) : root(nullptr), maxRectanglesPerNode(maxRectanglesPerNode) {}

    ~RTree();

    void insert(const sf::FloatRect& rect);

    bool search(const sf::FloatRect& rect);

private:
    void insert(const sf::FloatRect& rect, Node* node);

    void splitNode(Node* node);

    bool search(const sf::FloatRect& rect, Node* node);

    void clear(Node* node);
};