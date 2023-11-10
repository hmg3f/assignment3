#include <iostream>
#include "expmanager.hpp"
#include "myqueue.hpp"

int main(int argc, char *argv[])
{
    std::cout << "{--- Infix to Postfix Test ---}\n";
    std::string infix_string1 = "(4 + 52) / (99 * [6 - 24]) + 31";
    std::optional<std::string> postfix_string1 = infix_to_postfix(infix_string1);
    std::cout << "infix: " << infix_string1 << std::endl;
    std::cout << "postfix: " << postfix_string1.value_or("unable to complete conversion") << std::endl << std::endl;

    std::string infix_string2 = "[45 / 2] + (3 * 4) / {3 + (53 - 2)}";
    std::optional<std::string> postfix_string2 = infix_to_postfix(infix_string2);
    std::cout << "infix: " << infix_string2 << std::endl;
    std::cout << "postfix: " << postfix_string2.value_or("unable to complete conversion") << std::endl << std::endl;

    std::string infix_string3 = "(45 + 23 / [3 - 3] + {(44 * 2) - 7}";
    std::cout << "infix: " << infix_string3 << std::endl;
    std::optional<std::string> postfix_string3 = infix_to_postfix(infix_string3);
    std::cout << "postfix: " << postfix_string3.value_or("unable to complete conversion") << std::endl << std::endl;

    std::string infix_string4 = "(19 / [13} + 2)";
    std::cout << "infix: " << infix_string4 << std::endl;
    std::optional<std::string> postfix_string4 = infix_to_postfix(infix_string4);
    std::cout << "postfix: " << postfix_string4.value_or("unable to complete conversion") << std::endl << std::endl;

    std::cout << "\n{--- Queue Test ---}\n";
    MyQueue<int> integer_queue;
    integer_queue.enqueue(5);
    integer_queue.enqueue(10);
    integer_queue.enqueue(15);
    integer_queue.enqueue(20);

    std::cout << "current queue: 5 -> 10 -> 15 -> 20\n";
    
    std::cout << "size: " << integer_queue.size() << std::endl;
    std::cout << "front: " << integer_queue.front() << std::endl;
    std::cout << "dequeue: " << integer_queue.dequeue() << std::endl;
    std::cout << "size: " << integer_queue.size() << std::endl;
    std::cout << "front: " << integer_queue.front() << std::endl;

    std::cout << "empty: ";
    if(integer_queue.empty())
	std::cout << "queue is empty\n";
    else
	std::cout << "queue is not empty\n";

    std::size_t integer_queue_size = integer_queue.size();
    for (int i = 0; i < integer_queue_size; i++)
	std::cout << "dequeue: " << integer_queue.dequeue() << std::endl;

    std::cout << "size: " << integer_queue.size() << std::endl;
    std::cout << "front: " << integer_queue.front() << std::endl;

    std::cout << "empty: ";
    if(integer_queue.empty())
	std::cout << "queue is empty\n";
    else
	std::cout << "queue is not empty\n";

    integer_queue.enqueue(2);
    std::cout << "enqueue: 2\n";
    std::cout << "front: " << integer_queue.front() << std::endl;
    
    std::cout << "empty: ";
    if(integer_queue.empty())
	std::cout << "queue is empty\n";
    else
	std::cout << "queue is not empty\n";
    
    return 0;
}
