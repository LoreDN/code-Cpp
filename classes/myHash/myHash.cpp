// including external libraries
#include <iostream>


/* ---------------------------------------------------------------------------------- ROOT. myHash ---------------------------------------------------------------------------------- */

template <typename TYPE>
class myHash {

    protected:

        // attributes
        size_t dimension;
        size_t elements = 0;

    public:

        // destructor
        virtual ~myHash() = default;

        // Method 1 --- Scan the Hash-Table from terminal
        void scan(const size_t num) {

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

        // Method 3 --- Calculate the load factor
        inline float load_factor() { return (float)this->elements / (float)this->dimension; }
        
        // methods prototypes
        virtual void add(const TYPE key) = 0;
        virtual void print(const size_t start, const size_t end, const bool flag_user_interface) = 0;
        virtual void print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) = 0;

        virtual void remove(const TYPE key) = 0;
        virtual void remove_Bucket(const size_t bucket) = 0;

};