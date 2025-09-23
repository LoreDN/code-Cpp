// including external libraries
#include <iostream>
#include <fstream>


/* ---------------------------------------------------------------------------- 2. MyHash :: myHash_Close --------------------------------------------------------------------------- */

template <typename TYPE>
class myHash_Close : public myHash<TYPE> {

    // set constants
    TYPE const EMPTY = __INT_MAX__;
    TYPE const TOMBSTONE = __INT_MAX__ - 1;

    private:

        // attributes
        TYPE *table;
        bool flag_probing;

        // Method 1 --- Hash Function
        int hash(const TYPE key) {

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
        int linear_probing(const int key_abs) {

            // check a free Bucket
            for (size_t step = 1; step <= this->dimension; step++) {

                size_t bucket = (key_abs + step) % this->dimension;
                if (this->table[bucket] == myHash_Close::EMPTY || this->table[bucket] == myHash_Close::TOMBSTONE) { return bucket; }

            }

            // Bucket not found
            return -1;

        }

        // Method 3 --- Quadratic Probing for a Bucket
        int quadratic_probing(const int key_abs) {

            // check a free Bucket
            for (size_t step = 1; step <= this->dimension; step++) {

                size_t bucket = (key_abs + (size_t)((0.5 * step * step) + (0.5 * step))) % this->dimension;
                if (this->table[bucket] == myHash_Close::EMPTY || this->table[bucket] == myHash_Close::TOMBSTONE) { return bucket; }

            }

            // Bucket not found
            return -1;

        }

    public:

        // constructor
        myHash_Close(const size_t dim, const bool flag) {

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
        ~myHash_Close() override {

            // delete the Hash-Table
            for (size_t i = 0; i < this->dimension; i++) { this->remove_Bucket(i); }
            delete this->table;

            // exit
            return;

        }

        // Method 4 --- Add an element to a Bucket
        void add(const TYPE key) override {

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
            
        // Method 5 --- Print the Hash-Table to terminal
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
        void print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) override {

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

        // Method 7 --- Find an element in the Bucket
        int find(const TYPE key) {

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
        void remove(const TYPE key) override {

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
        void remove_Bucket(const size_t bucket) override {

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
        void copy(myHash_Close *destination) {

            // copy every Bucket
            for (size_t i = 0; i < this->dimension; i++) {

                // resize and copy the keys to the destination
                int value = this->table[i];
                if (value != myHash_Close::EMPTY && value != myHash_Close::TOMBSTONE) { (*destination).add(value); }

            }    

            // exit
            return;

        }
        
};