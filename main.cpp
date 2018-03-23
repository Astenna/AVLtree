#include <iostream>
#include <fstream>
using namespace std;

template <class type>
struct Node
{
    type value;
    Node *right;
    Node *left;
    Node *up;
    int bf;
    Node()
    {
        up = nullptr;
        right = nullptr;
        left = nullptr;
        bf = 0;
    }
};

template<class type>
class AVLtree
{
    Node<type> *root;
    Node<type>* FindAndInsert(type key,Node<type>* ptr);
    void RRrotate(Node<type>* ptr);
    void LLrotate(Node<type>* ptr);
    void RLrotate(Node<type>* ptr);
    void LRrotate(Node<type>* ptr);
    void CheckBalance(Node<type>* ptr);
    int SetBF(Node<type>* ptr);
    int MaxHeight(Node<type>* ptr,int counter);
    Node<type>* FindKey(Node<type>* ptr, type key);
    void PrintTree(Node<type>* ptr, int level);
    void PreOrderRec(Node<type>* ptr, ofstream stream);
    void PostOrderRec(Node<type>* ptr, ofstream stream);
    void InOrderRec(Node<type>* ptr, ofstream stream);
public:
    void PreOrder(ofstream stream)
    {
        PreOrderRec(root, stream);
    }
    void PostOrder(ofstream stream)
    {
        PostOrderRec(root, stream);
    }
    void Remove(type key);
    void InOrderRec(ofstream stream)
    {
        InOrderRec(root, stream);
    }
    void Add(type addVal);
    void Display()
    {
        PrintTree(root,0);
    }
    int Height()
    {
        return MaxHeight(root,0);
    }
    const type getRootValue()
    {
        return root->value;
    }
    AVLtree()
    {
        root = nullptr;
    }
};

int main()
{
    AVLtree<int> tr;
    return 0;
}

template <class type>
void AVLtree<type>::Add(type addVal)
{
    if(root == nullptr)
    {
        root = new Node<type>;
        root->value = addVal;
    }
    else
    {
        Node<type> *ptr = FindAndInsert(addVal,root);
        CheckBalance(ptr);
    }
}
/* metoda znajduje odpowiednie miejsce w drzewie do dodoania klucza */
template<class type>
Node<type>* AVLtree<type>::FindAndInsert(type key,Node<type>* ptr)
{
    if(ptr->value >= key)
    {
        if(ptr->left != nullptr)
        {
            FindAndInsert(key, ptr->left);
        }
        else
        {
            Node<type> *leaf = new Node<type>;
            leaf->up = ptr;
            ptr->left = leaf;
            leaf->value = key;
            return leaf; // zwroc miejsce gdzie zostal utw
        }
    }
    else
    {
        if (ptr->right != nullptr)
        {
            FindAndInsert(key, ptr->right);
        } else
        {
            Node<type> *leaf = new Node<type>;
            leaf->up = ptr;
            ptr->right = leaf;
            leaf->value = key;
            return leaf;
        }
    }
}
template<class type>
void AVLtree<type>::RRrotate(Node<type>* ptr)
{
    Node<type> *tmp = ptr->up;
    /* zamiana rodzicow */
    ptr->up = ptr->up->up;
    tmp->up = ptr;
    /* zamiana dzieci */
    tmp->right = ptr->left;
    ptr->left = tmp;
    if(tmp->right != nullptr)
        tmp->right->up = tmp;
    /* sprawdz, czy korzen nie zostal zmieniony */
    if(ptr->up == nullptr)
        root = ptr;
    else
    {   /* zamiana wskazania wezla powyzej rotacji */
        if(ptr->up->right == tmp)
            ptr->up->right = ptr;
        else
            ptr->up->left = ptr;
    }
}
template<class type>
void AVLtree<type>::LLrotate(Node<type>* ptr)
{
    Node<type>* tmp = ptr->up;
    /* zamiana rodzicow */
    ptr->up = ptr->up->up;
    tmp->up = ptr;
    /* zmiana dzieci */
    tmp->left = ptr->right;
    ptr->right = tmp;
    if(tmp->left != nullptr)
        tmp->left->up = tmp;
    /* sprawdz, czy korzen nie zostal zmieniony */
    if(ptr->up == nullptr)
        root = ptr;
    else
    {   /* zamiana wskazania wezla powyzej rotacji */
        if(ptr->up->right == tmp)
            ptr->up->right = ptr;
        else
            ptr->up->left = ptr;
    }
}

template<class type>
void AVLtree<type>::RLrotate(Node<type>* ptr)
{
    LLrotate(ptr->left);
    RRrotate(ptr->up);
}

template<class type>
void AVLtree<type>::LRrotate(Node<type>* ptr)
{
    RRrotate(ptr->right);
    LLrotate(ptr->up);
}

template<class type>
int AVLtree<type>::MaxHeight(Node<type> *ptr, int counter)
{
    int h1 = counter,h2 = counter;
    if(ptr->right != nullptr)
    {
        h1++;
        h1 = MaxHeight(ptr->right, h1);
    }
    if(ptr->left != nullptr)
    {
        h2++;
        h2 = MaxHeight(ptr->left, h2);
    }
    if(h1>=h2)
        return h1;
    else
        return h2;
}

template<class type>
int AVLtree<type>::SetBF(Node<type> *ptr)
{
    int hr=0, hl=0;
    if(ptr->right != nullptr)
    {
        hr = MaxHeight(ptr->right,1);
    }
    if (ptr->left != nullptr)
    {
        hl =  MaxHeight(ptr->left,1);
    }
    ptr->bf = hl - hr;
    return hl-hr;
}

template <class type>
void AVLtree<type>::CheckBalance(Node<type>* ptr)
{
    int bf = SetBF(ptr);
    if(bf > 1) // pierwsza litera L
    {
        if(SetBF(ptr->left) > 0)
            LLrotate(ptr->left);
        else
            LRrotate(ptr->left);
    }
    if(bf < -1) // pierwsza litera R
    {
        if(SetBF(ptr->right) > 0)
            RLrotate(ptr->right);
        else
            RRrotate(ptr->right);
    }
    if(ptr->up != nullptr)
        CheckBalance(ptr->up);
    else // czy ta linijka tutaj jest potrzebna?
        root = ptr;
}

template<class type>
Node<type> *AVLtree<type>::FindKey(Node<type>* ptr,type key)
{
    if(key < ptr->value)
    {
        if(ptr->left != nullptr)
        {
            ptr = ptr->left;
            FindKey(ptr, key);
        }
        else
            return nullptr;
    }
    else if(key > ptr->value)
    {
        if(ptr->right != nullptr)
        {
            ptr = ptr->right;
            FindKey(ptr, key);
        }
        else
            return nullptr;
    }
    else
        return ptr;
}

template<class type>
void AVLtree<type>::Remove(type key)
{
    Node<type>* checkBalanceFrom;
    Node<type>* ptr = FindKey(root,key);
    if(ptr != nullptr)
    {   /* wariant 1, brak dzieci */
        if(ptr->left == nullptr && ptr->right == nullptr)
        {
            if(ptr->up != nullptr) /* usuwanie 1 elementu, roota? */
            {
                checkBalanceFrom = ptr->up;
                if(ptr->up->left == ptr)
                    ptr->up->left = nullptr;
                if(ptr->up->right == ptr)
                    ptr->up->right = nullptr;
                CheckBalance(checkBalanceFrom);
            }
            else
                root = nullptr;
            delete(ptr);
        } /* ma jednego, prawego potomka */
        else if(ptr->left == nullptr && ptr->right != nullptr)
        {
            checkBalanceFrom = ptr->up;
            if(ptr->up->right == ptr)
                ptr->up->right = ptr->right;
            else
                ptr->up->left = ptr->right;
            ptr->right->up = ptr->up;
            CheckBalance(checkBalanceFrom);
            delete(ptr);
        } /* ma jednego, lewego potomka */
        else if(ptr->right == nullptr && ptr->left != nullptr)
        {
            checkBalanceFrom = ptr->up;
            if(ptr->up->right == ptr)
                ptr->up->right = ptr->left;
            else
                ptr->up->left = ptr->left;
            ptr->left->up = ptr->up;
            CheckBalance(checkBalanceFrom);
            delete(ptr);
        } /* ma dwoch potomkow */
        else
        {
            Node<type>* tmp = ptr;
            while(tmp->right != nullptr)
            {
                tmp = tmp->right;
            }
            checkBalanceFrom = tmp->up;
            type max = tmp->value;
            if(tmp == ptr->right)
                ptr->right = nullptr;
            if(tmp->left != nullptr)
            {
                tmp->up->right = tmp->left;
                tmp->left->up = tmp->up;
                checkBalanceFrom = tmp->left;
                delete(tmp);
            }
            ptr->value = max;
            CheckBalance(checkBalanceFrom);
        }
    }
    else
        cout << " Brak elementu do usunięcia!" << endl;
}

template<class type>
void AVLtree<type>::PrintTree(Node<type> *ptr, int level)
{
    if(ptr != nullptr)
    {
        PrintTree(ptr->right, level + 1);
        cout << endl;
        for(int i=0; i<level; ++i)
        {
            cout << "       ";
        }
        if(ptr != root)
            cout << ptr->value;
        else
            cout << "R: " << ptr->value;
        cout << endl;
        PrintTree(ptr->left, level + 1);
    }
}

template<class type>
void AVLtree<type>::PreOrderRec(Node<type> *ptr, ofstream stream)
{
    if(ptr != nullptr)
    {
        stream << ptr->value << "   ";
        PreOrderRec(ptr->right, stream);
        PreOrderRec(ptr->left, stream);
    }
}

template<class type>
void AVLtree<type>::PostOrderRec(Node<type> *ptr, ofstream stream)
{
    if(ptr != nullptr)
    {
        PreOrderRec(ptr->right, stream);
        PreOrderRec(ptr->left, stream);
        stream << ptr->value << "   ";
    }
}

template<class type>
void AVLtree<type>::InOrderRec(Node<type> *ptr, ofstream stream)
{
    if(ptr != nullptr)
    {
        PreOrderRec(ptr->right, stream);
        stream << ptr->value << "   ";
        PreOrderRec(ptr->left, stream);
    }
}



