#include <string>
#include <list>
#include <iostream>
using namespace std;

// for compilation purposes we use std::list to 
// model the singly-linked list with tail ptr, but you
// should understand and assume that `singly<T>` is a 
// singly linked list with tail ptr and is governed
// by those limitations / features.
template<typename T>
using singly = std::list<T>;

class StackStr {
private:
    // **singly-linked list with tail pointer**
    singly<std::string> dat_;
public:
    StackStr() {}
    // Adds item at the end using dat_'s tail pointer
    void push(const std::string val) 
        { return dat_.push_back(val); }
    // Removes the back item
    void pop()  { dat_.pop_back(); }
    // retrieves value pointed at by dat_'s tail pointer
    const std::string& top() const { return dat_.back(); }
    bool empty() const { return dat_.empty(); }
};

class SetStr {
public:
    SetStr() {}
    bool empty() const;  // assume is written for you
    void insert(std::string val);  // given on next page
    bool exists(std::string val);  // given on next page (has a bug)
    void erase(std::string val);   // assume is written for you
private:
    StackStr store_;
};

void SetStr::insert(std::string val)
{
    if( exists(val) == false ) 
    {
        store_.push(val);
    }
}


// =========================================================
//  You need only complete this function
// =========================================================
bool SetStr::exists(std::string val)
{
    // Your implementation here

    if (store_.empty()) return false;

    StackStr temp_ = new StackStr();

    while (store_.top() != val){

        temp_.push(store_.top());
        store_.pop();
        if (store_.empty()) return false;
    }

    while (!(temp_.empty())){
        store_.push(temp_.top());
        temp_.pop();
    }
    return true;
    // You may only use and declare Stack, strings, ints, and bools


}


// =========================================================
//  You will not be able to test this code because we
//  do not provide the implementation of erase() and empty()
// =========================================================