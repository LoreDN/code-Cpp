// including external libraries
#include <iostream>
#include <fstream>


/* ---------------------------------------------------------------------------- 1. MyHash :: myHash_Open ---------------------------------------------------------------------------- */


class myHash_Open : public myHash {

    // Bucket definition
    typedef struct myHash_Node {

        size_t value;
        myHash_Node *next;

    }myBucket;

    private:

        // attributes
        myBucket **table;

        // Method 1 --- Hash Function
        inline size_t hash(size_t key) {

            return key % this->dimension;

        }

        // Method 2 --- Add a new Bucket
        myBucket *add_Bucket(size_t key) {

            // allocate the new Bucket
            myBucket *bucket = new myBucket;

            // set the new Bucket
            bucket->value = key;
            bucket->next = nullptr;

            // exit
            return bucket;

        }


    public:

        // constructor
        myHash_Open(size_t dim) {

            // set the dimension
            this->dimension = dim;

            // set the Hash Table
            this->table = new myBucket*[dim];
            for (size_t i = 0; i < dim; i++) {

                this->table[i] = nullptr;

            }

            // exit
            return;

        }

        // destructor
        ~myHash_Open() override {

            // delete all Buckets
            for (size_t i = 0; i < this->dimension; i++) {

                this->remove_Bucket(i);

            }

            // exit
            return;

        }

        // Method 3 --- Add an element to a Bucket
        void add(size_t key) override {

            // find the Bucket
            size_t bucket = this->hash(key);

            // add the element to the Bucket
            if (this->table[bucket] == nullptr) {

                // new bucket
                this->table[bucket] = this->add_Bucket(key);

            } else {

                // go to the end of the Bucket
                myBucket *temp = this->table[bucket];
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
        void scan(size_t num) override {

            // scan the Hash Table
            std::cout << std::endl;
            for (size_t i = 1; i <= num; i++) {

                int value;
                std::cout << "Element " << i << ": ";
                std::cin >> value;
                this->add(value);

            }
            std::cout << std::endl;

            // exit
            return;

        }

        // Method 5 --- Scan the Hash Table from file
        void scan_file(std::string path) override {

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
        
        // Method 6 --- Print the Hash Table to terminal
        void print(size_t start, size_t end, bool flag_user_interface) override {

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
                        for (myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

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
                        for (myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

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
        void print_file(std::string path, size_t start, size_t end, bool flag_user_interface) override {

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
                        for (myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

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
                        for (myBucket *temp = this->table[i]; temp != nullptr; temp = temp->next) {

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

        // Method 8 --- Find an element in the bucket
        bool find(size_t key) override {

            // get the bucket
            size_t bucket = this->hash(key);

            // linear search of the element
            bool find = false;
            for (myBucket *element = this->table[bucket]; element != nullptr && find == false; element = element->next) {

                find = element->value == key;

            }

            // exit
            return find;

        }

        // Method 9 --- Remove an element from a Bucket
        void remove(size_t key) override {

            // check if the element exists
            if (!this->find(key)) {

                // exit
                return;

            }

            // find the Bucket
            size_t bucket = this->hash(key);

            if (this->table[bucket]->value == key) {

                // remove the Head
                myBucket *del = this->table[bucket];
                this->table[bucket] = del->next;
                delete del;

            } else {

                // go to the previous element
                myBucket *prev = table[bucket];
                for (; prev->next != nullptr && prev->next->value != key; prev = prev->next);

                // remove the element
                myBucket *del = prev->next;
                prev->next = del->next;
                delete del;

            }

            // decrement the elements counter
            this->elements--;

            // exit
            return;

        }

        // Method 10 --- Remove a Bucket
        void remove_Bucket(size_t bucket) {

            // check the index
            try {

                test_index(bucket, this->dimension - 1);

            } catch(myIndex_Exception &error) {

                error.print();

            }

            // remove all the elements of the bucket
            myBucket *current = table[bucket];
            while (current != nullptr) {

                myBucket *del = current;
                current = current->next;
                this->remove(del->value);

            }

            // exit
            return;

        }

        // Method 11 --- Get the load factor of the Hash Table
        inline float load_factor() override {

            return (float)this->elements / (float)this->dimension;    

        }

        // Method 12 --- Copy to a destination Hash Table
        void copy(myHash_Open destination) {

            // copy every Bucket
            for (size_t i = 0; i < this->dimension; i++) {

                // resize and copy the keys for the destination
                for (myBucket *temp = table[i]; temp != nullptr; temp = temp->next) {

                    destination.add(temp->value);

                }

            }

            // exit
            return;

        }
        
};