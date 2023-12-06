//
//  heap.hpp
//
//  Created by Avner on 26/11/2023.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>
#include <optional>
#include <vector>
#include <iostream>


// stupidly simple heap
// usage:
// Heap<Thing> heap;
// add to the heap:
// heap.push(thing1);
// get the max member
// const Thing& heap.peak();
// pop the heap
// Thing max = heap.pop();
// Thing new_max = heap.pop();

template <typename T, size_t INITIAL_SIZE = 100>
class Heap {
public:
    std::vector<T> items;
    
    Heap() {
        items.reserve(INITIAL_SIZE);
    }
    const T& peek() {
        return items[0];
    }
    
    void push(T& item) {
        items.push_back(item);
        auto size = items.size();
        siftUp((int)size - 1);
    }
    template <class... Args>
    void push(Args&&... args) {
        items.emplace_back(std::forward<Args>(args)...);
        siftUp((int)items.size() - 1);
    }
    
    void push(T&& item) {
        items.emplace_back(std::move(item));
        siftUp((int)items.size() - 1);
    }

    std::optional<T> pop() {
        if (items.size() == 0) {
            return std::nullopt;
        }
        auto& item = items[0];
        auto movedItem = std::move(item);
        if (items.size() == 1) {
            return movedItem;
        }
        std::swap(items[0],items[items.size() - 1]);
        items.erase(items.end() -1);
        if (items.size() > 1) {
            swap(items[0], items[items.size() -1]);
            siftDown(0);
        }
        return movedItem;
    }
    
private:
    void siftUp(int i) {
        if (i == 0) {
            return;
        }
        int pIdx = parent(i);
        if (items[pIdx] < items[i]) {
            std::swap(items[pIdx], items[i]);
            return siftUp(pIdx);
        }
    }
    
    void siftDown(const int i) {
        if (i == items.size() - 1) {
            return;
        }
        int leftChildIdx = left(i);
        int rightChildIdx = right(i);
        int smallestIdx = i;
        // check valid index to proceed checking
        if (leftChildIdx < items.size()) {
            if (items[leftChildIdx] > items[i]) {
                smallestIdx = leftChildIdx;
            }
        }
        if (rightChildIdx < items.size()) {
            if (items[rightChildIdx] > items[smallestIdx]) {
                smallestIdx = rightChildIdx;
            }
        }
        if (smallestIdx != i) {
            std::swap(items[i], items[smallestIdx]);
            return siftDown(smallestIdx);
        }
    }
    int parent(int i) { return (i - 1) / 2;}
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
};



#endif /* heap_hpp */
