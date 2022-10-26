#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('d',1));
    // bt.insert(std::make_pair('b',2));
    // bt.insert(std::make_pair('f',3));
    // bt.insert(std::make_pair('a',4));
    // bt.insert(std::make_pair('c',5));
    // bt.insert(std::make_pair('l',6));
    // bt.insert(std::make_pair('p',7));
    // bt.insert(std::make_pair('j',8));
    // bt.insert(std::make_pair('k',9));

    bt.insert(std::make_pair('a',9));
    bt.insert(std::make_pair('c',10));
    bt.insert(std::make_pair('b',11));

    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing c" << endl;
    bt.remove('c');

    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    // bt.print();

    // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
