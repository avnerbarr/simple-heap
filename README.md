# simple-heap

I needed a data structure with some specific requirements for a project I was working. Part of that included a heap and the regular `std` stuff wasn't a good fit. Here is the stripped down version without the auxillary functionality I ended up using.


# usage


```cpp
Heap<Thing> heap;
// add to the heap:
heap.push(thing1);
// get the max member
const Thing& heap.peak();
// pop the heap
Thing max = heap.pop();
// Thing new_max = heap.pop();
```

# assumptions 

Objects are comparable  `operator>` and `operator<`

```
friend bool operator<(const Thing& item1, const Thing& item2) {
        return item1.s <= item2.s && item1.count < item2.count;
    }
    friend bool operator>(const Thing& item1, const Thing& item2) {
        return item1.s >= item2.s && item1.count > item2.count;
    }
```
