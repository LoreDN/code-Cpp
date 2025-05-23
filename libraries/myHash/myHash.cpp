// including external libraries
#include <iostream>
#include <fstream>

// including myLibraries
#include "myExceptions.hpp"

// library definition
#include "myHash.hpp"


/* ---------------------------------------------------------------------------- 1. MyHash :: myHash_Open ---------------------------------------------------------------------------- */


// constructor
myHash_Open::myHash_Open(size_t dim) {

    // set the dimension
    this->dimension = dim;

    // set the Hash Table
    this->table = new myHash_Open::myBucket*[dim];
    for (size_t i = 0; i < dim; i++) {

        this->table[i] = nullptr;

    }

    // exit
    return;

}


// destructor
myHash_Open::~myHash_Open() {

    // delete all Buckets
    for (size_t i = 0; i < this->dimension; i++) {

        this->remove_Bucket(i);

    }

    // exit
    return;

}


/* ====================================== 1.1 Scan the Hash Table ===================================== */


// Method 1 --- Hash Function
inline size_t myHash_Open::hash(size_t key) {

    return key % this->dimension;

}


// Method 2 --- Add a new Bucket
myHash_Open::myBucket *myHash_Open::add_Bucket(size_t key) {

    // allocate the new Bucket
    myHash_Open::myBucket *bucket = new myHash_Open::myBucket;

    // set the new Bucket
    bucket->value = key;
    bucket->next = nullptr;

    // exit
    return bucket;

}


// Method 3 --- Add an element to a Bucket
void myHash_Open::add(size_t key) {

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


// Method 4 --- Scan the Hash Table from terminal
void myHash_Open::scan(size_t num) {

    // scan the Hash Table
    std::cout << std::endl;
    for (size_t i = 1; i <= num; i++) {

        size_t value;
        std::cout << "Element " << i << ": ";
        std::cin >> value;
        this->add(value);

    }
    std::cout << std::endl;

    // exit
    return;

}


// Method 5 --- Scan the Hash Table from file
void myHash_Open::scan_file(std::string path) {

    // open the file
    std::ifstream file(path);
    try {

        test_infile(path, &file);

    } catch (myFile_Exception &error) {

        error.print();

    }

    // scan the Hash Table
    while (!file.eof()) {

        size_t value;
        file >> value;
        this->add(value);

    }

    // close the file
    file.close();

    // exit
    return;

}


/* ===================================== 1.2 Print the Hash Table ===================================== */


// Method 6 --- Print the Hash Table to terminal
void myHash_Open::print(size_t start, size_t end, bool flag_user_interface) {

    // check the indexes
    try {

        test_index(end, this->dimension - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Hash Table
        for (size_t i = start; i <= end; i++) {

            // print the Bucket
            std::cout << "- Bucket: " << i + 1 << std::endl;

            if (this->table[i] == nullptr) {

                // empty Bucket
                std::cout << "Empty Bucket" << std::endl << std::endl;

            } else {

                // print the elements of the Bucket
                size_t j = 1;
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

                    std::cout << "Element " << j++ << ": " << temp->value << "\t";

                }
                std::cout << std::endl << std::endl;

            }

        }

    } else {

        // print the Hash Table
        for (size_t i = start; i <= end; i++) {

            if (this->table[i] == nullptr) {

                // empty Bucket
                std::cout << "//" << std::endl;

            } else {

                // print the elements of the Bucket
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

                    std::cout << temp->value << "\t";

                }
                std::cout << std::endl;

            }

        }

    }
    
    // exit
    return;

}


// Method 7 --- Print the Hash Table to file
void myHash_Open::print_file(std::string path, size_t start, size_t end, bool flag_user_interface) {

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

        // print the Hash Table
        for (size_t i = start; i <= end; i++) {

            // print the Bucket
            file << "- Bucket: " << i + 1 << std::endl;

            if (this->table[i] == nullptr) {

                // empty Bucket
                file << "Empty Bucket" << std::endl << std::endl;

            } else {

                // print the elements of the Bucket
                size_t j = 1;
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

                    file << "Element " << j++ << ": " << temp->value << "\t";

                }
                file << std::endl << std::endl;

            }

        }

    } else {

        // print the Hash Table
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


// Method 8 --- Find an element in the Bucket
myHash_Open::myBucket *myHash_Open::find(size_t key) {

    // get the Bucket
    size_t bucket = this->hash(key);

    // linear search of the element
    myHash_Open::myBucket *element = nullptr;
    for (element = this->table[bucket]; element != nullptr && element->value != key; element = element->next);

    // exit
    return element;

}


// Method 9 --- Remove an element from a Bucket
void myHash_Open::remove(size_t key) {

    // check if the element exists
    if (this->find(key) == nullptr) {

        // exit
        return;

    }

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


// Method 10 --- Remove a Bucket
void myHash_Open::remove_Bucket(size_t bucket) {

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


// Method 11 --- Get the load factor of the Hash Table
inline float myHash_Open::load_factor() {

    return (float)this->elements / (float)this->dimension;    

}


// Method 12 --- Copy to a destination Hash Table
void myHash_Open::copy(myHash_Open destination) {

    // copy every Bucket
    for (size_t i = 0; i < this->dimension; i++) {

        // resize and copy the keys to the destination
        for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

            destination.add(temp->value);

        }

    }

    // exit
    return;

}


/* ---------------------------------------------------------------------------- 2. MyHash :: myHash_Close --------------------------------------------------------------------------- */


// constructor
myHash_Close::myHash_Close(size_t dim, bool flag) {

    // set the attributes
    this->dimension = dim;
    this->flag_probing = flag;

    // set the Hash Table
    this->table = new int[dim];
    for (size_t i = 0; i < dim; i++) {

        this->table[i] = myHash_Close::EMPTY;

    }

    // exit
    return;

}


// destructor
myHash_Close::~myHash_Close() {

    // delete all the Buckets
    for (size_t i = 0; i < this->dimension; i++) {

        this->remove_Bucket(i);

    }

    // exit
    return;

}


/* ====================================== 2.1 Scan the Hash Table ===================================== */


// Method 1 --- Hash Function
int myHash_Close::hash(size_t key) {

    // check if the Bucket is avaible
    key %= this->dimension;
    if (table[key] == myHash_Close::EMPTY || table[key] == myHash_Close::TOMBSTONE) {

        // exit
        return key;

    }

    // Bucket unavaible
    if (this->flag_probing) {

        // quadratic probing
        return this->quadratic_probing(key);

    } else {

        // linear probing
        return this->linear_probing(key);

    }

}


// Method 2 --- Linear Probing for a Bucket
int myHash_Close::linear_probing(size_t key) {

    // check a free Bucket
    for (size_t step = 1; step <= this->dimension; step++) {

        size_t index = (key + step) % this->dimension;
        if (this->table[index] == myHash_Close::EMPTY || this->table[index] == myHash_Close::TOMBSTONE) {

            // Bucket found
            return index;

        }

    }

    // Bucket not found
    return -1;

}


// Method 3 --- Quadratic Probing for a Bucket
int myHash_Close::quadratic_probing(size_t key) {

    // check a free Bucket
    for (size_t step = 1; step <= this->dimension; step++) {

        size_t index = (key + (size_t)((0.5 * step * step) + (0.5 * step))) % this->dimension;
        if (this->table[index] == myHash_Close::EMPTY || this->table[index] == myHash_Close::TOMBSTONE) {

            // Bucket found
            return index;

        }

    }

    // Bucket not found
    return -1;

}


// Method 4 --- Add an element to a Bucket
void myHash_Close::add(size_t key) {

    // find the Bucket
    int bucket = this->hash(key);
    if (bucket >= 0) {

        //add the element to the Bucket
        this->table[bucket] = key;

        // increment the elements counter
        this->elements++;

    }

    // exit
    return;

}


// Method 5 --- Scan the Hash Table from terminal
void myHash_Close::scan(size_t num) {

    // scan the Hash Table
    std::cout << std::endl;
    for (size_t i = 1; i <= num; i++) {

        size_t value;
        std::cout << "Element " << i << ": ";
        std::cin >> value;
        this->add(value);

    }
    std::cout << std::endl;

    // exit
    return;

}


// Method 6 --- Scan the Hash Table from file
void myHash_Close::scan_file(std::string path) {

    // open the file
    std::ifstream file(path);
    try {

        test_infile(path, &file);

    } catch (myFile_Exception &error) {

        error.print();

    }

    // scan the Hash Table
    while (!file.eof()) {

        size_t value;
        file >> value;
        this->add(value);

    }

    // close the file
    file.close();

    // exit
    return;

}


/* ===================================== 2.2 Print the Hash Table ===================================== */


// Method 7 --- Print the Hash Table to terminal
void myHash_Close::print(size_t start, size_t end, bool flag_user_interface) {

    // check the indexes
    try {

        test_index(end, this->dimension - 1);
        test_index(start, end);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // if flag is set to 1, print the user interface
    if (flag_user_interface) {

        // print the Hash Table
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

        // print the Hash Table
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


// Method 8 --- Print the Hash Table to file
void myHash_Close::print_file(std::string path, size_t start, size_t end, bool flag_user_interface) {

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

        // print the Hash Table
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

        // print the Hash Table
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


// Method 9 --- Find an element in the Bucket
int myHash_Close::find(size_t key) {

    // check the real key Bucket
    size_t index = key % this->dimension;
    if (this->table[index] == (int)key) {

        // exit
        return index;

    } else if (this->table[index] == EMPTY) {

        // exit
        return -1;

    }

    // linear search of the element
    for (size_t i = 1; i < this->dimension; i++) {

        index = (key + i) % this->dimension;
        if (this->table[index] == (int)key) {

            // element found
            return index;

        }

    }

    // element not found
    return -1;

}


// Method 10 --- Remove a Bucket
void myHash_Close::remove(size_t key) {

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


// Method 11 --- Remove a Bucket
void myHash_Close::remove_Bucket(size_t bucket) {

    // check the index
    try {

        test_index(bucket, this->dimension - 1);

    } catch(myIndex_Exception &error) {

        error.print();

    }

    // check the Bucket
    if (this->table[bucket] == myHash_Close::EMPTY || this->table[bucket] == myHash_Close::TOMBSTONE) {

        // exit
        return;

    }

    // set the Bucket as TOMBSTONE
    this->table[bucket] = myHash_Close::TOMBSTONE;

    // decrement the elements counter
    this->elements--;

    // exit
    return;

}


// Method 12 --- Get the load factor of the Hash Table
inline float myHash_Close::load_factor() {

    return (float)this->elements / (float)this->dimension;    

}


// Method 13 --- Copy to a destination Hash Table
void myHash_Close::copy(myHash_Close *destination) {

    // copy every Bucket
    for (size_t i = 0; i < this->dimension; i++) {

        // resize and copy the keys to the destination
        int value = this->table[i];
        if (value != myHash_Close::EMPTY && value != myHash_Close::TOMBSTONE) {

            (*destination).add(value);
        
        }

    }    

    // exit
    return;

}