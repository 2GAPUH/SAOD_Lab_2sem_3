#include "RTree.h"


RTree::~RTree() 
{
    clear(root);
}

void RTree::insert(const sf::FloatRect& rect) 
{
    if (!root) {
        root = new Node(rect);
    }
    else {
        insert(rect, root);
    }
}

bool RTree::search(const sf::FloatRect& rect) 
{
    return search(rect, root);
}


void RTree::insert(const sf::FloatRect& rect, Node* node) 
{
    if (node->isLeafNode()) {
        if (node->rectangles.size() < maxRectanglesPerNode) {
            node->rectangles.push_back(rect);
        }
        else {
            splitNode(node);
            insert(rect, node);
        }
    }
    else {
        double minEnlargement = std::numeric_limits<double>::max();
        Node* chosenChild = nullptr;

        for (Node* child : node->children) {
            sf::FloatRect combinedRect = node->bounds;
            combinedRect = node->bounds;
            combinedRect.left = std::min(combinedRect.left, rect.left);
            combinedRect.top = std::min(combinedRect.top, rect.top);
            float right = std::max(combinedRect.left + combinedRect.width, rect.left + rect.width);
            float bottom = std::max(combinedRect.top + combinedRect.height, rect.top + rect.height);
            combinedRect.width = right - combinedRect.left;
            combinedRect.height = bottom - combinedRect.top;

            double enlargement = combinedRect.width * combinedRect.height - node->bounds.width * node->bounds.height;
            if (enlargement < minEnlargement) {
                minEnlargement = enlargement;
                chosenChild = child;
            }
        }

        insert(rect, chosenChild);
    }
}

void RTree::splitNode(Node* node) 
{
    float width = node->bounds.width;
    float height = node->bounds.height;

    sf::FloatRect bounds1, bounds2;

    if (width > height) {
        bounds1 = sf::FloatRect(node->bounds.left, node->bounds.top, width / 2.f, height);
        bounds2 = sf::FloatRect(node->bounds.left + width / 2.f, node->bounds.top, width / 2.f, height);
    }
    else {
        bounds1 = sf::FloatRect(node->bounds.left, node->bounds.top, width, height / 2.f);
        bounds2 = sf::FloatRect(node->bounds.left, node->bounds.top + height / 2.f, width, height / 2.f);
    }

    node->children.push_back(new Node(bounds1));
    node->children.push_back(new Node(bounds2));

    for (const sf::FloatRect& rect : node->rectangles) {
        sf::FloatRect combinedRect1 = bounds1;
        sf::FloatRect combinedRect2 = bounds2;
        {
            combinedRect1 = node->bounds;
            combinedRect1.left = std::min(combinedRect1.left, rect.left);
            combinedRect1.top = std::min(combinedRect1.top, rect.top);
            float right = std::max(combinedRect1.left + combinedRect1.width, rect.left + rect.width);
            float bottom = std::max(combinedRect1.top + combinedRect1.height, rect.top + rect.height);
            combinedRect1.width = right - combinedRect1.left;
            combinedRect1.height = bottom - combinedRect1.top;
        }

        {
            combinedRect2 = node->bounds;
            combinedRect2.left = std::min(combinedRect2.left, rect.left);
            combinedRect2.top = std::min(combinedRect2.top, rect.top);
            float right = std::max(combinedRect2.left + combinedRect2.width, rect.left + rect.width);
            float bottom = std::max(combinedRect2.top + combinedRect2.height, rect.top + rect.height);
            combinedRect2.width = right - combinedRect2.left;
            combinedRect2.height = bottom - combinedRect2.top;
        }

        double area1 = combinedRect1.width * combinedRect1.height;
        double area2 = combinedRect2.width * combinedRect2.height;

        if (area1 < area2) {
            node->children[0]->rectangles.push_back(rect);
        }
        else {
            node->children[1]->rectangles.push_back(rect);
        }
    }

    node->rectangles.clear();
}

bool RTree::search(const sf::FloatRect& rect, Node* node)  
{
    if (!node)
        return false;

    if (node->isLeafNode()) {
        for (const sf::FloatRect& r : node->rectangles) {
            if (r.intersects(rect))
                return true;
        }
        return false;
    }
    else {
        for (Node* child : node->children) {
            if (child->bounds.intersects(rect)) {
                if (search(rect, child))
                    return true;
            }
        }
        return false;
    }
}

void RTree::clear(Node* node) 
{
    if (node) {
        for (Node* child : node->children)
            clear(child);
        delete node;
    }
}
