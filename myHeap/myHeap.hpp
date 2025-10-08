#ifndef MYHEAP_HPP
#define MYHEAP_HPP

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*
*  This library contains the definition and implementation of the abstract Class "myHeap", as well as the derived Classes "myHeap_Min" and "myHeap_Max".
*  As the names suggest, "myHeap" represents the base for a generic Heap object, meanwhile "myHeap_Min" and "myHeap_Max" are the real Heaps implementetions.
*  This two classes work as the implementations of the Hash-Table object, which follows the 'open hashing' or 'closed hashing' rules respectively.
*
*
*  |-----** IMPORTANT!!! **-----|
*  The keys of the Heap have been implemented using templates: this means that can be virtually used all custom types and classes.
*  In practice, in order to use a type must be added the corrisponding "explicit template instantiations" in the file "myHeap.cpp"; this is essential when working with templates.
*  It is easy to do, since you can do it at the start of the file, and are already given some instantiations, so you can copy them and modify only the type or class name. 
*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */





// including external libraries
#include <iostream>


/* ---------------------------------------------------------------------------------- ROOT. myHeap ---------------------------------------------------------------------------------- */

template <typename TYPE>
class myHeap {

    protected:

        // attributes
        size_t size;
        size_t usage;
        TYPE *heap;

        // methods prototypes
        void resize();
        void switch_keys(const size_t first, const size_t second);
        virtual void heapify_up(int index) = 0;
        virtual void heapify_down(size_t index) = 0;

    public:

        // constructor
        myHeap(const size_t dim);

        // destructor
        virtual ~myHeap() = default;

        // methods prototypes
        inline size_t get_size() { return this->size; };
        inline size_t get_usage() { return this->usage; };
        inline TYPE get_first() { return this->heap[0]; };
        inline bool is_empty() { return !(this->usage); };

        void scan(const size_t num);
        void scan_file(const std::string path);

        void print(const size_t start, const size_t end, const bool flag_user_interface);
        void print_file(const std::string path, const size_t start, const size_t end, const bool flag_user_interface);

        void push(const TYPE key);
        TYPE pop();

};

/* ---------------------------------------------------------------------------------- 1. myHeap_Min --------------------------------------------------------------------------------- */

template <typename TYPE>
class myHeap_Min : public myHeap<TYPE> {

    private:

        // methods prototypes
        void heapify_up(int index) override;
        void heapify_down(size_t index) override;


    public:

        // constructor
        myHeap_Min(const size_t dim);

        // destructor
        ~myHeap_Min() override;

};

/* ---------------------------------------------------------------------------------- 2. myHeap_Max --------------------------------------------------------------------------------- */

template <typename TYPE>
class myHeap_Max : public myHeap<TYPE> {

    private:

        // methods prototypes
        void heapify_up(int index) override;
        void heapify_down(size_t index) override;

    public:

        // constructor
        myHeap_Max(const size_t dim);

        // destructor
        ~myHeap_Max() override;

};


#endif // MYHEAP_HPP