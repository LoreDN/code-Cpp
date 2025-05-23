// including external libraries
#include <iostream>
#include <fstream>


/* ---------------------------------------------------------------------------- 2. MyHash :: myHash_Close --------------------------------------------------------------------------- */

class myHash_Close : public myHash {

    // set constants
    int const EMPTY = -1;
    int const TOMBSTONE = -2;

    private:

        // attributes
        int *table;
        bool flag_probing;

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
        int linear_probing(size_t key) {

            // check a free Bucket
            for (size_t step = 1; step <= this->dimension; step++) {

                size_t index = (key + step) % this->dimension;
                if (this->table[index] == EMPTY || this->table[index] == TOMBSTONE) {

                    // Bucket found
                    return index;

                }

            }

            // Bucket not found
            return -1;

        }

        // Method 3 --- Quadratic Probing for a Bucket
        int quadratic_probing(size_t key) {

            // check a free Bucket
            for (size_t step = 1; step <= this->dimension; step++) {

                size_t index = (key + (size_t)((0.5 * step * step) + (0.5 * step))) % this->dimension;
                if (this->table[index] == EMPTY || this->table[index] == TOMBSTONE) {

                    // Bucket found
                    return index;

                }

            }

            // Bucket not found
            return -1;

        }

    public:

        // constructor
        myHash_Close(size_t dim, bool flag) {

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
        ~myHash_Close() override {

            // delete all the Buckets
            for (size_t i = 0; i < this->dimension; i++) {

                this->remove_Bucket(i);

            }

            // exit
            return;

        }

        // Method 4 --- Add an element to a Bucket
        void add(size_t key) override {

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
        void scan(size_t num) override {

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
            
        // Method 7 --- Print the Hash Table to terminal
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
                    std::cout << "- Bucket " << i + 1 << ": ";

                    if (this->table[i] == EMPTY || this->table[i] == TOMBSTONE) {

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

                    if (this->table[i] == EMPTY || this->table[i] == TOMBSTONE) {

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

                    if (this->table[i] == EMPTY || this->table[i] == TOMBSTONE) {

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

                if (this->table[i] == EMPTY || this->table[i] == TOMBSTONE) {

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

        // Method 9 --- Find an element in the Bucket
        int find(size_t key) {

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
        void remove(size_t key) override {

            // check if the element exists
            int del = this->find(key);
            if (del < 0) {

                // exit
                return;

            }

            // set the element as TOMBSTONE
            this->table[del] = TOMBSTONE;

            // decrement the elements counter
            this->elements--;

            // exit
            return;

        }

        // Method 11 --- Remove a Bucket
        void remove_Bucket(size_t bucket) override {

            // check the index
            try {

                test_index(bucket, this->dimension - 1);

            } catch(myIndex_Exception &error) {

                error.print();

            }

            // check the Bucket
            if (this->table[bucket] == EMPTY || this->table[bucket] == TOMBSTONE) {

                // exit
                return;

            }

            // set the Bucket as TOMBSTONE
            this->table[bucket] = TOMBSTONE;

            // decrement the elements counter
            this->elements--;

            // exit
            return;

        }

        // Method 12 --- Get the load factor of the Hash Table
        inline float load_factor() override {

            return (float)this->elements / (float)this->dimension;    

        }

        // Method 13 --- Copy to a destination Hash Table
        void copy(myHash_Close *destination) {

            // copy every Bucket
            for (size_t i = 0; i < this->dimension; i++) {

                // resize and copy the keys to the destination
                int value = this->table[i];
                if (value != EMPTY && value != TOMBSTONE) {

                    (*destination).add(value);
                
                }

            }    

            // exit
            return;

        }
        
};