// including external libraries
#include <iostream>
#include <fstream>


/* ---------------------------------------------------------------------------- 1. MyHash :: myHash_Open ---------------------------------------------------------------------------- */

template <typename TYPE>
class myHash_Open : public myHash<TYPE> {

    // Bucket definition
    typedef struct myHash_Node {

        TYPE value;
        myHash_Node *next;

    }myBucket;

    private:

        // attributes
        myBucket **table;

        // Method 1 --- Hash Function
        inline size_t hash(const TYPE key) { return abs(key) % this->dimension; }

        // Method 2 --- Add a new Bucket
        myBucket *add_Bucket(const TYPE key) {

            // allocate the new Bucket
            myHash_Open::myBucket *bucket = new myHash_Open::myBucket;

            // set the new Bucket
            bucket->value = key;
            bucket->next = nullptr;

            // exit
            return bucket;

        }


    public:

        // constructor
        myHash_Open(const size_t dim) {

            // set the dimension
            this->dimension = dim;

            // set the Hash-Table
            this->table = new myHash_Open::myBucket*[dim];
            for (size_t i = 0; i < dim; i++) { this->table[i] = nullptr; }

            // exit
            return;

        }

        // destructor
        ~myHash_Open() override {

            // delete the Hash-Table
            for (size_t i = 0; i < this->dimension; i++) { this->remove_Bucket(i); }
            delete this->table;

            // exit
            return;

        }

        // Method 3 --- Add an element to a Bucket
        void add(const TYPE key) override {

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
        
        // Method 4 --- Print the Hash-Table to terminal
        void print(const size_t start, const size_t end, const bool flag_user_interface) override {

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

        // Method 5 --- Print the Hash-Table to file
        void print_file(const std::string path, const size_t start, size_t end, const bool flag_user_interface) override {

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

        // Method 6 --- Find an element in the bucket
        size_t find(const TYPE key) override {

            // get the Bucket
            size_t bucket = this->hash(key);

            // linear search of the element
            myHash_Open::myBucket *element = nullptr;
            for (element = this->table[bucket]; element != nullptr && element->value != key; element = element->next);

            // exit
            return element;

        }

        // Method 7 --- Remove an element from a Bucket
        void remove(const TYPE key) override {

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

        // Method 8 --- Remove a Bucket
        void remove_Bucket(const size_t bucket) {

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

        // Method 9 --- Copy to a destination Hash Table
        void copy(myHash_Open *destination) {

            // copy every Bucket
            size_t min_dimension = (this->dimension <= (*destination).dimension) ? this->dimension : (*destination).dimension;
            for (size_t i = 0; i < min_dimension; i++) {

                // copy the keys to the destination
                for (myHash_Open::myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) { (*destination).add(temp->value); }

            }

            // exit
            return;

        }
        
};