// library definition
#ifndef MYHASH_HPP
#define MYHASH_HPP

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*
*  This library contains the definition and implementation of the abstract Class "myHash", as well as the derived Classes "myHash_Open" and "myHash_Close".
*  As the names suggest, "myHash" represents the base for a generic Hash-Table object, meanwhile "myHash_Open" and "myHash_Close" are the real Hash-Tables.
*  This two classes work as the implementations of the Hash-Table object, which follows the 'open hashing' or 'closed hashing' rules respectively.
*
*
*  |-----** IMPORTANT!!! **-----|
*  The keys of the Hash-Table have been implemented using templates: this means that can be virtually used all custom types and classes.
*  In practice, in order to use a type must be added the corrisponding "explicit template instantiations" in the file "myHash.cpp"; this is essential when working with templates.
*  It is easy to do, since you can do it at the start of the file, and all already given some instantiations, so you can copy them and modify only the type or class name. 
*
*  In "myHash_Close" the Hash-Table is an array of 'TYPE', hovewer has been set two flags: EMPTY = __INT_MAX__ && TOMBSTONE = __INT_MAX__ - 1.
*  This flags are assigned as TYPE const variables, so theri value depends on the implementations;
*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */





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

        // methods prototypes
        virtual void add(const TYPE key) = 0;
        void scan(const size_t num);
        void scan_file(const std::string path);
        
        virtual void print(const size_t start, const size_t end, const bool flag_user_interface) = 0;
        virtual void print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) = 0;

        virtual void remove(const TYPE key) = 0;
        virtual void remove_Bucket(const size_t bucket) = 0;
        inline float load_factor() { return (float)this->elements / (float)this->dimension; }

};

/* ---------------------------------------------------------------------------- 1. MyHash :: myHash_Open ---------------------------------------------------------------------------- */

template <typename TYPE>
class myHash_Open : public myHash<TYPE> {

    public:

        // Bucket definition
        typedef struct myHash_Node {

            TYPE value;
            myHash_Node *next;

        }myBucket;

    private:

        // attributes
        myBucket **table;

        // methods prototypes
        inline size_t hash(const TYPE key) { return abs(key) % this->dimension; }
        myBucket *add_Bucket(const TYPE key);

    public:

        // constructor
        myHash_Open(const size_t dim);

        // destructor
        ~myHash_Open() override;

        // methods prototypes
        void add(const TYPE key) override;
        
        void print(const size_t start, const size_t end, const bool flag_user_interface) override;
        void print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) override;

        myBucket *find(const TYPE key);
        void remove(const TYPE key) override;
        void remove_Bucket(const size_t bucket) override;
        void copy(myHash_Open *destination);
        
};

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

        // methods prototypes
        int hash(const TYPE key);
        int linear_probing(const int key_abs);
        int quadratic_probing(const int key_abs);

    public:

        // constructor
        myHash_Close(const size_t dim, const bool flag);

        // destructor
        ~myHash_Close() override;

        // methods prototypes
        void add(const TYPE key) override;
        
        void print(const size_t start, const size_t end, const bool flag_user_interface) override;
        void print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface) override;

        int find(const TYPE key);
        void remove(const TYPE key) override;
        void remove_Bucket(const size_t bucket) override;
        void copy(myHash_Close *destination);
        
};


#endif // MYHASH_HPP