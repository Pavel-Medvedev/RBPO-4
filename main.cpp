#include <iostream>

import Deque;

int main()
{
    Deque::DequeBasedOnBidirectionalCyclicLinkedList<double> deque1;
    Deque::DequeBasedOnBidirectionalCyclicLinkedList<int> deque2(10);
    Deque::DequeBasedOnBidirectionalCyclicLinkedList<int> deque3(deque2);

    deque1.PushBack(1.2);
    deque1.PushBack(3.4);
    deque1.PushBack(5.6);
    deque1.PushBack(3.22);
    deque1.PushFront(1.23);

    std::cout << std::endl << "Elements of deque1: ";
    for (auto i = 0; i < deque1.GetSize(); i++)
    {
        std::cout << deque1[i] << '\t';
    }
    std::cout << std::endl;

    double temp;
    std::cout << std::endl << "Elements of deque1: ";
    for (auto i = 0; i < deque1.GetSize(); i++)
    {
        std::cout << deque1[i] << '\t';
    }
    std::cout << std::endl;

    deque1.PeekBack(temp);
    std::cout << std::endl << "PeekBacked element: " << temp << std::endl;
    deque1.PeekFront(temp);
    std::cout << std::endl << "PeekFronted element: " << temp << std::endl;
    deque1.PopBack(temp);
    std::cout << std::endl << "PopBacked element: " << temp << std::endl;
    deque1.PopFront(temp);
    std::cout << std::endl << "PopFronte element: " << temp << std::endl;
    std::cout << std::endl << "Elements of deque1: ";
    for (auto i = 0; i < deque1.GetSize(); i++)
    {
        std::cout << deque1[i] << '\t';
    }
    std::cout << std::endl;
    Deque::DequeBasedOnBidirectionalCyclicLinkedList<char> deque4 = { 'M', 'e', 'd', 'v', 'e', 'd', 'e', 'v'};
    std::cout << std::endl << "Elements of deque4: ";
    for (auto i = 0; i < deque4.GetSize(); i++)
    {
        std::cout << deque4[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
