// Containers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>

struct Enemy
{
    std::string name;
    int hp;

    Enemy(std::string n, int h)
        : name{ std::move(n) }, hp{ h }
    {
        std::cout << "Enemy created" << std::endl;
    }
};

int main()
{
    std::vector<Enemy> enemies;
    int h = 100;
    Enemy e{ "Orc", h };
    enemies.insert(enemies.begin(), e); // Usually means the vector will copy if you an lvalue like e.

    Enemy e2{ "Night Elf", h };
    enemies.insert(enemies.begin(), std::move(e2));

    enemies.emplace(enemies.begin(), "Human", 100); // Give the constructor arguments directly
    // "use these arguments to create the object right here inside the vector"

    Enemy e3{ "Troll", 100 };
    enemies.push_back(e3); // Usually copies e into the vector

    enemies.emplace_back("Dwarf", 100); // Construct enemy object directly. Avoid a copy.
    // emplace does not magically guarantee zero moves/copies in all situations.
    //

    // Copy or not copy?
    // Copying = making a new independent object with the same content
    std::string a{ "hello" };
    std::string b = a;

    std::vector<int> vec;
    int var = 10;
    int& ref = var;

    vec.emplace(vec.begin() + 1, ref); // Does not store a reference in the vector
	var = 99; // vec[1] will still be 10, not 99, because the vector stores a copy of the value, not a reference to it.

    // [5, 2, 6, 1, 3]
    // Doubly linked list: 5 <-> 2 <-> 6 <-> 1 <-> 3, n = 5. look_up(3) -> O(n)
    std::vector<int> numbers{ 1,2,3,4,5 };
    for (int i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[2] << std::endl;
    }


    std::map<int, std::string> studentIdMap;

    studentIdMap[940402] = "Calle";
    studentIdMap[970122] = "Calle";
	studentIdMap[970122] = "Bert"; // same key, different value. The map will update the value for the existing key.

    /*
    it = begin(); // point at first "box"
    std::cout << *it << std::endl; // look inside the box
    ++i; // move finger to the next box
    end(); // point at just after last box
    */

    std::map<int, std::string> m;
    m[50] = "A"; // each node: key-value pair, pointer to left child, pointer to right child, often a pointer to parent
    m[20] = "B";
    m[70] = "C";
    m[10] = "D";
    m[30] = "E";

	// Maps are often implemented as binary search trees, which are a type of linked data structure.
	// Binary search tree: each node has a key-value pair, pointer to left child, pointer to right child, often a pointer to parent
    struct Node
    {
        std::pair<const int, std::string> data;
        Node* left;
        Node* left;
        Node* parent;
    };



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
