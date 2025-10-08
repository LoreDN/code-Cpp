// including standard libraries
#include <iostream>
#include <fstream>

// including myLibraries
#include "myExceptions.hpp"

// library definition
#include "myHeap.hpp"


// explicit template instantiations
template class myHeap<int>; template class myHeap_Min<int>; template class myHeap_Max<int>;
template class myHeap<float>; template class myHeap_Min<float>; template class myHeap_Max<float>;


/* ---------------------------------------------------------------------------------- ROOT. myHeap ---------------------------------------------------------------------------------- */


// constructor
template <typename TYPE>
myHeap<TYPE>::myHeap(const size_t dim) : size(dim), usage(0) {

    // allocate the Heap
    this->heap = new TYPE[this->size];

    // exit
    return;

}


// Method 1 --- Resize the Heap
template <typename TYPE>
void myHeap<TYPE>::resize() {

    // allocate new Heap
    size_t new_size = this->size * 2;
    TYPE *new_heap = new TYPE[new_size];
    for (size_t i = 0; i < this->size; i++) { new_heap[i] = this->heap[i]; }

    // change the Heap
    delete this->heap;
    this->size = new_size;
    this->heap = new_heap;

    // exit
    return;

}


// Method 2 --- Switch two keys of the Heap
template <typename TYPE>
void myHeap<TYPE>::switch_keys(const size_t first, const size_t second) {

    // switch keys
    TYPE temp = this->heap[first];
    this->heap[first] = this->heap[second];
    this->heap[second] = temp;
    
    // exit
    return;

}


/* ======================================= ROOT.1 Scan the Heap ======================================= */


// Method 3 --- Scan the Heap from terminal
template <typename TYPE>
void myHeap<TYPE>::scan(const size_t num) {

    // scan the Heap
    for (size_t i = 0; i < num; i++) {

        // check the heapsize
        try {

            test_data_size(this->usage, this->size);

        } catch(myDataSize_Exception &error) {

            error.print();
            this->resize();

        }

        // scan the element
        TYPE element;
        std::cout << "Element " << i + 1 << ": ";
        std::cin >> element;
        this->push(element);

    }

    // exit
    return;

}


// Method 4 --- Scan the Heap from file
template <typename TYPE>
void myHeap<TYPE>::scan_file(const std::string path) {

    // open the file
    std::ifstream file(path);
    try {

        test_infile(path, &file);

    } catch (myFile_Exception &error) { error.print(); }
    
    // scan the Heap
    while (!file.eof()) {

        // check the heapsize
        try {

            test_data_size(this->usage, this->size);

        } catch(myDataSize_Exception &error) {

            error.print();
            this->resize();

        }

        // scan the element
        TYPE element;
        file >> element;
        this->push(element);

    }

    // exit
    return;

}


/* ======================================= ROOT.2 Print the Heap ====================================== */


// Method 5 --- Print the Heap to terminal
template <typename TYPE>
void myHeap<TYPE>::print(const size_t start, const size_t end, const bool flag_user_interface) {

    // check the indexes
    if (!this->usage) { return; }
    try {

        test_index(end, this->usage - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) { error.print(); }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Heap
        for (size_t i = start; i <= end; i++) { std::cout << "Bucket " << i + 1 << ": " << this->heap[i] << std::endl; }

    } else {

        // print the Heap
        for (size_t i = start; i <= end; i++) { std::cout << this->heap[i] << std::endl; }

    }
    
    // exit
    return;

}


// Method 6 --- Print the Heap to file
template <typename TYPE>
void myHeap<TYPE>::print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) {

    // check the indexes
    if (!this->usage) { return; }
    try {

        test_index(end, this->usage - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) { error.print(); }

    // open the file
    std::ofstream file(path);
    try {

        test_outfile(path, &file);

    } catch (myFile_Exception &error) { error.print(); }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Heap
        for (size_t i = start; i <= end; i++) { file << "Bucket " << i + 1 << ": " << this->heap[i] << std::endl; }

    } else {

        // print the Heap
        for (size_t i = start; i <= end; i++) { file << this->heap[i] << std::endl; }

    }

    // close the file
    file.close();
    
    // exit
    return;

}


/* =================================== ROOT.3 Operations on the Heap ================================== */


// Method 7 --- Push an Element to the Heap
template <typename TYPE>
void myHeap<TYPE>::push(const TYPE key) {

    // push and heapify up
    this->heap[this->usage] = key;
    this->heapify_up(this->usage++);

    // exit
    return;

}


// Method 8 --- Pop an Element from the Heap
template <typename TYPE>
TYPE myHeap<TYPE>::pop() {

    // pop and heapify down
    TYPE first = this->heap[0];
    this->heap[0] = this->heap[--this->usage];
    this->heapify_down(0);

    // exit
    return first;
    
}


/* ---------------------------------------------------------------------------------- 1. myHeap_Min --------------------------------------------------------------------------------- */


// constructor
template <typename TYPE>
myHeap_Min<TYPE>::myHeap_Min(const size_t dim) : myHeap<TYPE>(dim) {}


//destructor
template <typename TYPE>
myHeap_Min<TYPE>::~myHeap_Min() {

    // free the Heap
    delete this->heap;
    this->heap = nullptr;

    // exit
    return;

}


/* ==================================== 1.1 Operations on the Heap ==================================== */


// Method 1 --- Heapify up the Min-Heap
template <typename TYPE>
void myHeap_Min<TYPE>::heapify_up(int index) {

    while (index > 0) {

        // check if parent is smaller
        size_t parent_index = (index - 1) >> 1;
        if (this->heap[parent_index] <= this->heap[index]) { break; }

        // heapify parent
        this->switch_keys(index, parent_index);
        index = parent_index;

    }

    // exit
    return;

}


// Method 2 --- Hepify down the Min-Heap
template <typename TYPE>
void myHeap_Min<TYPE>::heapify_down(size_t index) {

    while (index < this->usage) {

        // find the smallest child
        size_t smallest = index;
        size_t child = (index << 1) + 1;
        for (size_t i = 0; i < 2; i++) {

            size_t children_indexes = child + i;
            if (children_indexes < this->usage 
                && this->heap[children_indexes] < this->heap[smallest]) { smallest = children_indexes; }
            
        } if (smallest == index) { break; }

        // heapify smallest child
        this->switch_keys(index, smallest);
        index = smallest;

    }

    // exit
    return;

}


/* ---------------------------------------------------------------------------------- 2. myHeap_Max --------------------------------------------------------------------------------- */


// constructor
template <typename TYPE>
myHeap_Max<TYPE>::myHeap_Max(const size_t dim) : myHeap<TYPE>(dim) {}


//destructor
template <typename TYPE>
myHeap_Max<TYPE>::~myHeap_Max() {

    // free the Heap
    delete this->heap;
    this->heap = nullptr;

    // exit
    return;

}


/* ==================================== 1.1 Operations on the Heap ==================================== */


// Method 1 --- Heapify up the Min-Heap
template <typename TYPE>
void myHeap_Max<TYPE>::heapify_up(int index) {

    while (index > 0) {

        // check if parent is smaller
        size_t parent_index = (index - 1) >> 1;
        if (this->heap[parent_index] >= this->heap[index]) { break; }

        // heapify parent
        this->switch_keys(index, parent_index);
        index = parent_index;

    }

    // exit
    return;

}


// Method 2 --- Hepify down the Min-Heap
template <typename TYPE>
void myHeap_Max<TYPE>::heapify_down(size_t index) {

    while (index < this->usage) {

        // find the smallest child
        size_t smallest = index;
        size_t child = (index << 1) + 1;
        for (size_t i = 0; i < 2; i++) {

            size_t children_indexes = child + i;
            if (children_indexes < this->usage 
                && this->heap[children_indexes] > this->heap[smallest]) { smallest = children_indexes; }
            
        } if (smallest == index) { break; }

        // heapify smallest child
        this->switch_keys(index, smallest);
        index = smallest;

    }

    // exit
    return;

}