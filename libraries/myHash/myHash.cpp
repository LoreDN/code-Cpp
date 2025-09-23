// including external libraries
#include <iostream>
#include <fstream>

// including myLibraries
#include "myExceptions.hpp"

// library definition
#include "myHash.hpp"


// explicit template instantiations
template class myHash<int>; template class myHash_Open<int>; template class myHash_Close<int>;
template class myHash<float>; template class myHash_Open<float>; template class myHash_Close<float>;


/* ---------------------------------------------------------------------------------- ROOT. myHash ---------------------------------------------------------------------------------- */


// Method 1 --- Scan the Hash-Table from terminal
template <typename TYPE>
void myHash<TYPE>::scan(const size_t num) {

    // scan the Hash-Table
    std::cout << std::endl;
    for (size_t i = 1; i <= num; i++) {

        TYPE value;
        std::cout << "Element " << i << ": ";
        std::cin >> value;
        this->add(value);

    }
    std::cout << std::endl;

    // exit
    return;

}


// Method 2 --- Scan the Hash-Table from file
template <typename TYPE>
void myHash<TYPE>::scan_file(const std::string path) {

    // open the file
    std::ifstream file(path);
    try {

        test_infile(path, &file);

    } catch (myFile_Exception &error) {

        error.print();

    }

    // scan the Hash-Table
    while (!file.eof()) {

        TYPE value;
        file >> value;
        this->add(value);

    }

    // close the file
    file.close();

    // exit
    return;

}


/* ---------------------------------------------------------------------------- 1. MyHash :: myHash_Open ---------------------------------------------------------------------------- */


// constructor
template <typename TYPE>
myHash_Open<TYPE>::myHash_Open(const size_t dim) {

    // set the dimension
    this->dimension = dim;

    // set the Hash-Table
    this->table = new myHash_Open::myBucket*[dim];
    for (size_t i = 0; i < dim; i++) { this->table[i] = nullptr; }

    // exit
    return;

}


// destructor
template <typename TYPE>
myHash_Open<TYPE>::~myHash_Open() {

    // delete the Hash-Table
    for (size_t i = 0; i < this->dimension; i++) { this->remove_Bucket(i); }
    delete this->table;

    // exit
    return;

}


/* ====================================== 1.1 Scan the Hash Table ===================================== */


// Method 1 --- Add a new Bucket
template <typename TYPE>
typename myHash_Open<TYPE>::myBucket *myHash_Open<TYPE>::add_Bucket(const TYPE key) {

    // allocate the new Bucket
    myHash_Open::myBucket *bucket = new myHash_Open::myBucket;

    // set the new Bucket
    bucket->value = key;
    bucket->next = nullptr;

    // exit
    return bucket;

}


// Method 2 --- Add an element to a Bucket
template <typename TYPE>
void myHash_Open<TYPE>::add(const TYPE key) {

    // find the Bucket
    size_t bucket = this->hash(key);

    // add the element to the Bucket
    if (this->table[bucket] == nullptr) {

        // new bucket
        this->table[bucket] = this->add_Bucket(key);

    } else {

        // go to the end of the Bucket
        myHash_Open::myBucket *temp = this->table[bucket];
        for (; temp->next != nullptr; temp = temp->next);

        // allocate the new element
        temp->next = this->add_Bucket(key);

    }

    // increment the elements counter
    this->elements++;

    // exit
    return;

}


/* ===================================== 1.2 Print the Hash Table ===================================== */


// Method 3 --- Print the Hash-Table to terminal
template <typename TYPE>
void myHash_Open<TYPE>::print(const size_t start, const size_t end, const bool flag_user_interface) {

    // check the indexes
    try {

        test_index(end, this->dimension - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            // print the Bucket
            std::cout << "- Bucket: " << i + 1 << std::endl;

            if (this->table[i] == nullptr) {

                // empty Bucket
                std::cout << "Empty Bucket" << std::endl << std::endl;

            } else {

                // print the elements of the Bucket
                size_t j = 1;
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) { std::cout << "Element " << j++ << ": " << temp->value << "\t"; }
                std::cout << std::endl << std::endl;

            }

        }

    } else {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            if (this->table[i] == nullptr) {

                // empty Bucket
                std::cout << "//" << std::endl;

            } else {

                // print the elements of the Bucket
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) { std::cout << temp->value << "\t"; }
                std::cout << std::endl;

            }

        }

    }
    
    // exit
    return;

}


// Method 4 --- Print the Hash-Table to file
template <typename TYPE>
void myHash_Open<TYPE>::print_file(const std::string path, const size_t start, size_t end, const bool flag_user_interface) {

    // check the indexes
    try {

        test_index(end, this->dimension - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // open the file
    std::ofstream file(path);
    try {

        test_outfile(path, &file);

    } catch (myFile_Exception &error) {

        error.print();

    }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            // print the Bucket
            file << "- Bucket: " << i + 1 << std::endl;

            if (this->table[i] == nullptr) {

                // empty Bucket
                file << "Empty Bucket" << std::endl << std::endl;

            } else {

                // print the elements of the Bucket
                size_t j = 1;
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) { file << "Element " << j++ << ": " << temp->value << "\t"; }
                file << std::endl << std::endl;

            }

        }

    } else {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            if (this->table[i] == nullptr) {

                // empty Bucket
                file << "//" << std::endl;

            } else {

                // print the elements of the Bucket
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

                    file << temp->value << "\t";

                }
                file << std::endl;

            }

        }

    }

    // close the file
    file.close();
    
    // exit
    return;

}


/* ============================================ 1.3 Utility =========================================== */


// Method 5 --- Find an element in the Bucket
template <typename TYPE>
typename myHash_Open<TYPE>::myBucket *myHash_Open<TYPE>::find(const TYPE key) {

    // get the Bucket
    size_t bucket = this->hash(key);

    // linear search of the element
    myHash_Open::myBucket *element = nullptr;
    for (element = this->table[bucket]; element != nullptr && element->value != key; element = element->next);

    // exit
    return element;

}


// Method 6 --- Remove an element from a Bucket
template <typename TYPE>
void myHash_Open<TYPE>::remove(const TYPE key) {

    // check if the element exists
    if (this->find(key) == nullptr) { return; }

    // find the Bucket
    size_t bucket = this->hash(key);

    if (this->table[bucket]->value == key) {

        // remove the Head
        myHash_Open::myBucket *del = this->table[bucket];
        this->table[bucket] = del->next;
        delete del;

    } else {

        // go to the previous element
        myHash_Open::myBucket *prev = this->table[bucket];
        for (; prev->next != nullptr && prev->next->value != key; prev = prev->next);

        // remove the element
        myHash_Open::myBucket *del = prev->next;
        prev->next = del->next;
        delete del;

    }

    // decrement the elements counter
    this->elements--;

    // exit
    return;

}


// Method 7 --- Remove a Bucket
template <typename TYPE>
void myHash_Open<TYPE>::remove_Bucket(const size_t bucket) {

    // check the index
    try {

        test_index(bucket, this->dimension - 1);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // remove all the elements of the Bucket
    myHash_Open::myBucket *current = this->table[bucket];
    while (current != nullptr) {

        myHash_Open::myBucket *del = current;
        current = current->next;
        this->remove(del->value);

    }

    // exit
    return;

}


// Method 8 --- Copy to a destination Hash-Table
template <typename TYPE>
void myHash_Open<TYPE>::copy(myHash_Open *destination) {

    // copy every Bucket
    size_t min_dimension = (this->dimension <= (*destination).dimension) ? this->dimension : (*destination).dimension;
    for (size_t i = 0; i < min_dimension; i++) {

        // copy the keys to the destination
        for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) { (*destination).add(temp->value); }

    }

    // exit
    return;

}


/* ---------------------------------------------------------------------------- 2. MyHash :: myHash_Close --------------------------------------------------------------------------- */


// constructor
template <typename TYPE>
myHash_Close<TYPE>::myHash_Close(const size_t dim, const bool flag) {

    // set the attributes
    this->dimension = dim;
    this->flag_probing = flag;

    // set the Hash-Table
    this->table = new TYPE[dim];
    for (size_t i = 0; i < dim; i++) { this->table[i] = myHash_Close::EMPTY; }

    // exit
    return;

}


// destructor
template <typename TYPE>
myHash_Close<TYPE>::~myHash_Close() {

    // delete the Hash-Table
    for (size_t i = 0; i < this->dimension; i++) { this->remove_Bucket(i); }
    delete this->table;

    // exit
    return;

}


/* ====================================== 2.1 Scan the Hash Table ===================================== */


// Method 1 --- Hash Function
template <typename TYPE>
int myHash_Close<TYPE>::hash(const TYPE key) {

    // check if the Bucket is avaible
    int key_abs = abs(key);
    size_t bucket = key_abs % this->dimension;
    if (table[bucket] == myHash_Close::EMPTY || table[bucket] == myHash_Close::TOMBSTONE) { return bucket; }

    // Bucket unavaible
    if (this->flag_probing) {

        // quadratic probing
        return this->quadratic_probing(key_abs);

    } else {

        // linear probing
        return this->linear_probing(key_abs);

    }

}


// Method 2 --- Linear Probing for a Bucket
template <typename TYPE>
int myHash_Close<TYPE>::linear_probing(const int key_abs) {

    // check a free Bucket
    for (size_t step = 1; step <= this->dimension; step++) {

        size_t bucket = (key_abs + step) % this->dimension;
        if (this->table[bucket] == myHash_Close::EMPTY || this->table[bucket] == myHash_Close::TOMBSTONE) { return bucket; }

    }

    // Bucket not found
    return -1;

}


// Method 3 --- Quadratic Probing for a Bucket
template <typename TYPE>
int myHash_Close<TYPE>::quadratic_probing(const int key_abs) {

    // check a free Bucket
    for (size_t step = 1; step <= this->dimension; step++) {

        size_t bucket = (key_abs + (size_t)((0.5 * step * step) + (0.5 * step))) % this->dimension;
        if (this->table[bucket] == myHash_Close::EMPTY || this->table[bucket] == myHash_Close::TOMBSTONE) { return bucket; }

    }

    // Bucket not found
    return -1;

}


// Method 4 --- Add an element to a Bucket
template <typename TYPE>
void myHash_Close<TYPE>::add(const TYPE key) {

    // find the Bucket
    int bucket = this->hash(key);
    if (bucket >= 0) {

        //add the element to the Bucket
        this->table[bucket] = key;
        this->elements++;

    }

    // exit
    return;

}


/* ===================================== 2.2 Print the Hash Table ===================================== */


// Method 5 --- Print the Hash-Table to terminal
template <typename TYPE>
void myHash_Close<TYPE>::print(const size_t start, const size_t end, const bool flag_user_interface) {

    // check the indexes
    try {

        test_index(end, this->dimension - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            // print the Bucket
            std::cout << "- Bucket " << i + 1 << ": ";

            if (this->table[i] == myHash_Close::EMPTY || this->table[i] == myHash_Close::TOMBSTONE) {

                // empty Bucket
                std::cout << "Empty Bucket" << std::endl << std::endl;

            } else {

                // print the Bucket
                std::cout << this->table[i] << std::endl << std::endl;

            }

        }

    } else {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            if (this->table[i] == myHash_Close::EMPTY || this->table[i] == myHash_Close::TOMBSTONE) {

                // empty Bucket
                std::cout << "//" << std::endl;

            } else {

                // print the Bucket
                std::cout << this->table[i] << std::endl;

            }

        }

    }
    
    // exit
    return;

}


// Method 6 --- Print the Hash-Table to file
template <typename TYPE>
void myHash_Close<TYPE>::print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) {

    // check the indexes
    try {

        test_index(end, this->dimension - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // open the file
    std::ofstream file(path);
    try {

        test_outfile(path, &file);

    } catch (myFile_Exception &error) {

        error.print();

    }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

            // print the Bucket
            file << "- Bucket: " << i + 1 << std::endl;

            if (this->table[i] == myHash_Close::EMPTY || this->table[i] == myHash_Close::TOMBSTONE) {

                // empty Bucket
                file << "Empty Bucket" << std::endl << std::endl;

            } else {

                // print the Bucket
                file << this->table[i] << std::endl << std::endl;

            }

        }

    } else {

        // print the Hash-Table
        for (size_t i = start; i <= end; i++) {

           if (this->table[i] == myHash_Close::EMPTY || this->table[i] == myHash_Close::TOMBSTONE) {

                // empty Bucket
                file << "//" << std::endl;

            } else {

                // print the elements of the Bucket
                file << this->table[i] << std::endl;

            }

        }

    }

    // close the file
    file.close();
    
    // exit
    return;

}


/* ============================================ 2.3 Utility =========================================== */


// Method 7 --- Find an element in the Bucket
template <typename TYPE>
int myHash_Close<TYPE>::find(const TYPE key) {

    // check the real key Bucket
    size_t index = (size_t)key % this->dimension;
    if (this->table[index] == (int)key) {

        // exit
        return index;

    } else if (this->table[index] == EMPTY) {

        // exit
        return -1;

    }

    // linear search of the element
    for (size_t i = 1; i < this->dimension; i++) {

        index = ((size_t)key + i) % this->dimension;
        if (this->table[index] == key) { return index; }

    }

    // element not found
    return -1;

}


// Method 8 --- Remove a Bucket
template <typename TYPE>
void myHash_Close<TYPE>::remove(const TYPE key) {

    // check if the element exists
    int del = this->find(key);
    if (del < 0) {

        // exit
        return;

    }

    // set the element as TOMBSTONE
    this->table[del] = myHash_Close::TOMBSTONE;

    // decrement the elements counter
    this->elements--;

    // exit
    return;

}


// Method 9 --- Remove a Bucket
template <typename TYPE>
void myHash_Close<TYPE>::remove_Bucket(const size_t bucket) {

    // check the index
    try {

        test_index(bucket, this->dimension - 1);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // check the Bucket
    if (this->table[bucket] == myHash_Close::EMPTY || this->table[bucket] == myHash_Close::TOMBSTONE) { return; }

    // set the Bucket as TOMBSTONE
    this->table[bucket] = myHash_Close::TOMBSTONE;
    this->elements--;

    // exit
    return;

}


// Method 10 --- Copy to a destination Hash-Table
template <typename TYPE>
void myHash_Close<TYPE>::copy(myHash_Close *destination) {

    // copy every Bucket
    for (size_t i = 0; i < this->dimension; i++) {

        // resize and copy the keys to the destination
        int value = this->table[i];
        if (value != myHash_Close::EMPTY && value != myHash_Close::TOMBSTONE) { (*destination).add(value); }

    }    

    // exit
    return;

}