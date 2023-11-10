#pragma once

#include <list>
#include <cctype>

template<typename T>
class MyQueue {
private:
    // The container of type T which stores the values in the queue
    std::list<T> container;
public:
    /**
     * Adds input to the back of the queue
     *
     * @param input the item that should be added to the queue
     */
    void enqueue(T input) {
	container.push_back(input);
    }

    /**
     * Remove the item at the beginning of the queue. Return the value popped
     *
     * @return T the item at the front of the queue
     */
    T dequeue() {
	T value = container.front();
	container.pop_front();
	return value;
    }

    /**
     * Return the item at the front of the queue without removing it
     *
     * @return T the item at the front of the queue
     */
    T front() {
	return container.front();
    }

    /**
     * Return true if there are no items in the queue
     *
     * @return bool whether or not the queue is empty
     */
    bool empty() {
	return container.empty();
    }

    /**
     * Return the size of the queue
     *
     * @return size_t the number of items in the queue
     */
    std::size_t size() {
	return container.size();
    }
};
