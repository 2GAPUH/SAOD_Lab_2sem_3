#include "RTree.h"

int main() {
    RTree rtree(4); 


    int choice = 3;
    sf::FloatRect tmp;
    while (choice != 0)
    {
        std::cout << "1 - Insert \n2 - Search\n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Enter: ";
            std::cin >> tmp.left >> tmp.top >> tmp.width >> tmp.height;
            rtree.insert(tmp);
            break;

        case 2:
            std::cout << "Enter: ";
            std::cin >> tmp.left >> tmp.top >> tmp.width >> tmp.height;
            if (rtree.search(tmp))
                std::cout << "Rectangle found!\n";
            else
                std::cout << "Rectangle not found!\n";

            break;
        }
    }

    return 0;
}


/*
1
10 10 20 20
1
30 30 20 20
1
0 0 50 50
1
70 70 20 20
1
25 25 30 30







*/

