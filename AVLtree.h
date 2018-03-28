#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
using namespace std;
// Czy wysokosc bez roota to po prostu zero tak jak jest czy na cerr tez?
// aktualnie root = poziom 1, normalnie zwraca zero
// height() -> maxGeight() itd.
// exception przy usuwaniu z pustego drzewa czy tylko cerr tak jak jest?
// probowac skrocic metode remove?
template <class type>
struct Node
{
    type value;
    Node *right;
    Node *left;
    Node *up;
    Node()
    {
        up = nullptr;
        right = nullptr;
        left = nullptr;
    }
};

template<class type>
class AVLtree
{
    Node<type> *root;
    Node<type>* findAndInsert(type key,Node<type>* ptr);
    void RRrotate(Node<type>* ptr);
    void LLrotate(Node<type>* ptr);
    void RLrotate(Node<type>* ptr);
    void LRrotate(Node<type>* ptr);
    void balance(Node<type>* ptr);
    int getBalanceFactor(Node<type>* ptr);
    int maxHeight(Node<type>* ptr,int counter);
    Node<type>* findValue(Node<type>* ptr, type key);
    void printTree(Node<type>* ptr, int level);
    void preOrderRec(Node<type>* ptr, ostream &stream);
    void postOrderRec(Node<type>* ptr, ostream &stream);
    void inOrderRec(Node<type>* ptr, ostream &stream);
public:
    void preOrder(ostream &stream)
    {
        preOrderRec(root, stream);
    }
    void postOrder(ostream &stream)
    {
        postOrderRec(root, stream);
    }
    void remove(type key);
    void inOrder(ostream &stream)
    {
        inOrderRec(root, stream);
    }
    void add(type addVal);
    void display()
    {
        if(root != nullptr)
            printTree(root,0);
        else
            cerr << "Drzewo jest puste!" << endl;
    }
    int height()
    {
        return maxHeight(root,1);
    }
    const type getRootValue()
    {
        if(root != nullptr)
            return root->value;
        else
            cerr << "Drzewo jest puste!" << endl;
        return 0;
    }
    AVLtree()
    {
        root = nullptr;
    }
};

#endif //AVLTREE_AVLTREE_H
