#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
    Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
    ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
    void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
    T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
    void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
    bool empty() const;

private:
  /// Add whatever helper functions and data members you need below

    //  helper function for pop, trickles down an item to correct heap property
    void trickleDown(const size_t position);
    
    std::vector<T> heap;
    int m;
    PComparator c;
};

// Add implementation of member functions here

//  constructor
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
    this->m = m;
    this->c = c;
}

// destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}

//  adds a new element to the end of the heap, then trickles up until its correct position
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
    heap.push_back(item);
    std::size_t index = heap.size() - 1;
    
    while (index != 0) {
        std::size_t parent_index = (index - 1) / m;
        T& current = heap[index];
        T& parent = heap[parent_index];
        if (c(parent,current)) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }

}

template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
    if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
        throw std::underflow_error("Heap is empty");

    }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
    return heap[0];
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
      throw std::underflow_error("heap is empty");
  }
    unsigned int s = heap.size()-1;
    
    std::swap(heap[0], heap[s]);
    heap.erase(heap.begin() + s);
    trickleDown(0);
}

//  swaps down until the element is in the correct spot
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(const size_t position){
    
    size_t parent = position;
    size_t child = m * parent + 1;
    size_t best = child;
    
    if (heap.empty() || (child > heap.size()-1)){
        return;
    }

    for(int i = 1; i < m; ++i){
        if((child + i) < heap.size()){
            if(c(heap[child+i], heap[best])){
                best = child + i;
            }
        }
    }
    
    if(c(heap[best], heap[parent])){
        std::swap(heap[parent], heap[best]);
        trickleDown(best);
    }
}


//  returns true if heap is size 0 else false
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
    return heap.empty();
}



#endif

