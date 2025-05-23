// library definition
#ifndef MYHASH_HPP
#define MYHASH_HPP

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*
*  This library contains the definition and implementation of the abstract Class "myHash", as well as the derived Classes "myHash_Open" and "myHash_Close".
*  As the names suggest, "myHash" represents the base for a generic Hash table object, meanwhile "myHash_Open" and "myHash_Close" are the real Hash Tables.
*  This two classes work as the implementations of the hash Table object, which follows the 'open hashing' or 'closed_hashing' rules respectively.
*
*
*  |-----** IMPORTANT!!! **-----|
*  The keys of the Hash Table have been implemented via 'size_t type': their meaning is to be used as array indexes (in this case as Hash Table indexes), then the given Class will 
*  handle correctly all possible values (such as out of range indexes) via the corrispective Hash Function.
*  In "myHash_Close" the Hash Table is an array of 'int type', this is done in order to handle negative flags; hovewer the values are insert in the Hash Table as 'size_t type'.
*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */





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

        virtual void remove(size_t key) = 0;
        virtual void remove_Bucket(size_t bucket) = 0;
        virtual float load_factor() = 0;

};

/* ---------------------------------------------------------------------------- 1. MyHash :: myHash_Open ---------------------------------------------------------------------------- */

class myHash_Open : public myHash {

    public:

        // Bucket definition
        typedef struct myHash_Node {

            size_t value;
            myHash_Node *next;

        }myBucket;

    private:

        // attributes
        myBucket **table;

        // methods prototypes
        size_t hash(size_t key);
        myBucket *add_Bucket(size_t key);

    public:

        // constructor
        myHash_Open(size_t dim);

        // destructor
        ~myHash_Open() override;

        // methods prototypes
        void add(size_t key) override;
        void scan(size_t num) override;
        void scan_file(std::string path) override;
        
        void print(size_t start, size_t end, bool flag_user_interface) override;
        void print_file(std::string path, size_t start, size_t end, bool flag_user_interface) override;

        myBucket *find(size_t key);
        void remove(size_t key) override;
        void remove_Bucket(size_t bucket) override;
        float load_factor() override;
        void copy(myHash_Open destination);
        
};

/* ---------------------------------------------------------------------------- 2. MyHash :: myHash_Close --------------------------------------------------------------------------- */

class myHash_Close : public myHash {

    // set constants
    int const EMPTY = -1;
    int const TOMBSTONE = -2;

    private:

        // attributes
        int *table;
        bool flag_probing;

        // methods prototypes
        int hash(size_t key);
        int linear_probing(size_t key);
        int quadratic_probing(size_t key);

    public:

        // constructor
        myHash_Close(size_t dim, bool flag);

        // destructor
        ~myHash_Close() override;

        // methods prototypes
        void add(size_t key) override;
        void scan(size_t num) override;
        void scan_file(std::string path) override;
        
        void print(size_t start, size_t end, bool flag_user_interface) override;
        void print_file(std::string path, size_t start, size_t end, bool flag_user_interface) override;

        int find(size_t key);
        void remove(size_t key) override;
        void remove_Bucket(size_t bucket) override;
        float load_factor() override;
        void copy(myHash_Close *destination);
        
};


#endif // MYHASH_HPP