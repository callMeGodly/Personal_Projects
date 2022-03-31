#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> data;
public:
    void push(const T& item);
    // Removes the largest element in the heap
    void pop();
    // Returns the largest element in the heap (but does not remove it)
    T const& top() const;
    std::size_t size() const;
    void trickleDown(const unsigned int position);
    
};

template <typename T>
void MaxHeap<T>::push(const T& item) {
    data.push_back(item);
    std::size_t index = data.size() - 1;
    while (index != 0) {
        std::size_t parent_index = (index - 1) / 2;
        T& current = data[index];
        T& parent = data[parent_index];
        if (current <= parent) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

template <typename T>
void MaxHeap<T>::pop() {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    
    unsigned int s = data.size()-1;
    
    std::swap(data[0], data[s]);
    data.erase(data.begin() + s);
    trickleDown(0);
    trickleDown(0);
    
}

template <typename T>
T const& MaxHeap<T>::top() const {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    return data[0];
}

template <typename T>
std::size_t MaxHeap<T>::size() const {
    return data.size();
}

template <typename T>
void MaxHeap<T>::trickleDown(const unsigned int position){
    
    unsigned int pos = position;
    unsigned int smaller = 2 * pos + 1;
    
    if (data.empty() || (smaller > data.size()-1)){
        return;
    }
    
    if((smaller + 1) < data.size()){
        if(data[smaller + 1] > data[smaller]){
            smaller += 1;
        }
    }
    
    if(data[pos] < data[smaller]){
        std::swap(data[pos], data[smaller]);
        trickleDown(smaller);
    }
}
