#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;
int main() {
    // // Create a MagicalContainer and add some elements
    // MagicalContainer container;
    // container.addElement(17);
    // container.addElement(2);
    // container.addElement(25);
    // container.addElement(9);
    // container.addElement(3);

    // // Print container size
    // std::cout << "Size of container: " << container.size() << std::endl;

    // // Use AscendingIterator to display elements in ascending order
    // std::cout << "Elements in ascending order:\n";
    // MagicalContainer::AscendingIterator ascIter(container);
    // for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
    //     std::cout << *it << ' ';   // 2 3 9 17 25
    // }
    // std::cout << std::endl;

    // // Use DescendingIterator to display elements in descending order
    // std::cout << "Elements in cross order:\n";
    // MagicalContainer::SideCrossIterator crossIter(container);
    // for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
    //     std::cout << *it << ' ';  // 2 25 3 17 9
    // }
    // std::cout << std::endl;

    // // Use PrimeIterator to display prime numbers only
    // std::cout << "Prime numbers:\n";
    // MagicalContainer::PrimeIterator primeIter(container);
    // for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
    //     std::cout << *it << ' ';  // 2 3 17 
    // }
    // std::cout << std::endl;

    // // Remove an element from the container and display the size
    // container.removeElement(9);
    // std::cout << "Size of container after removing an element: " << container.size() << std::endl;

MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(40);

        MagicalContainer::SideCrossIterator it(container);
        int a = *it;
        ++it;
        int b = *it;
        ++it;
        int c = *it;
        ++it;
        int d = *it;
        ++it;
        int e = *it;
        ++it;
        // CHECK(*it == 10);
        // ++it;
        // CHECK(*it == 15);
        // ++it;
        // CHECK(*it == 20);
        // ++it;
        // CHECK(*it == 25);
        // ++it;
        // CHECK(*it == 30);
        // ++it;
        // CHECK(it == it.end());

    return 0;
}
