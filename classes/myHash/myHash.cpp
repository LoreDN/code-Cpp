// including external libraries
#include <iostream>


/* ---------------------------------------------------------------------------------- ROOT. myHash ---------------------------------------------------------------------------------- */

class myHash {

    protected:

        // attributes
        size_t dimension;
        size_t elements = 0;

    public:

        // destructor
        virtual ~myHash() = default;

        // methods prototypes
        virtual void add(size_t key) = 0;
        virtual void scan(size_t num) = 0;
        virtual void scan_file(std::string path) = 0;
        
        virtual void print(size_t start, size_t end, bool flag_user_interface) = 0;
        virtual void print_file(std::string path, size_t start, size_t end, bool flag_user_interface) = 0;

        virtual bool find(size_t key) = 0;
        virtual void remove(size_t key) = 0;
        virtual float load_factor() = 0;

};