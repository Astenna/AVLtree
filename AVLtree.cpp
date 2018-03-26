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
        printTree(root,0);
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
/* metoda poczatkowa wywolywana aby dodac element */
template <class type>
void AVLtree<type>::add(type addVal)
{
    if(root == nullptr)
    {
        root = new Node<type>;
        root->value = addVal;
    }
    else
    {
        Node<type> *ptr = findAndInsert(addVal,root);
        balance(ptr);
    }
}
/* metoda znajduje odpowiednie miejsce w drzewie i dodaje element */
template<class type>
Node<type>* AVLtree<type>::findAndInsert(type key,Node<type>* ptr)
{
    if(ptr->value >= key)
    {
        if(ptr->left != nullptr)
        {
            findAndInsert(key, ptr->left);
        }
        else
        {
            Node<type> *leaf = new Node<type>;
            leaf->up = ptr;
            ptr->left = leaf;
            leaf->value = key;
            return leaf;
        }
    }
    else
    {
        if (ptr->right != nullptr)
        {
            findAndInsert(key, ptr->right);
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
/* rekurencyjna metoda zwracajaca max wysokosc poddrzewa*/
template<class type>
int AVLtree<type>::maxHeight(Node<type> *ptr, int counter)
{
    int h1 = counter,h2 = counter;
    if(ptr != nullptr)
    {
        if(ptr->right != nullptr)
        {
            h1++;
            h1 = maxHeight(ptr->right, h1);
        }
        if(ptr->left != nullptr)
        {
            h2++;
            h2 = maxHeight(ptr->left, h2);
        }
        if(h1>=h2)
            return h1;
        else
            return h2;
    }
    else
         return 0;
}
/* metoda obliczajaca wspolczynnik rownowagi */
template<class type>
int AVLtree<type>::getBalanceFactor(Node<type> *ptr)
{
    int hr=0, hl=0;
    if(ptr->right != nullptr)
    {
        hr = maxHeight(ptr->right,1);
    }
    if (ptr->left != nullptr)
    {
        hl =  maxHeight(ptr->left,1);
    }
    return hl-hr;
}
/* metoda sprawdzajaca wspolczynnik rownowagi,
 * w razie potrzeby wywlowuje odpowiednie rotacje */
template <class type>
void AVLtree<type>::balance(Node<type>* ptr)
{
    int bf = getBalanceFactor(ptr);
    if(bf > 1) // pierwsza litera L
    {
        if(getBalanceFactor(ptr->left) > 0)
            LLrotate(ptr->left);
        else
            LRrotate(ptr->left);
    }
    if(bf < -1) // pierwsza litera R
    {
        if(getBalanceFactor(ptr->right) > 0)
            RLrotate(ptr->right);
        else
            RRrotate(ptr->right);
    }
    if(ptr->up != nullptr)
        balance(ptr->up);
    else
        root = ptr;
}
/* metoda wyszukujaca wezel z szukanym kluczem */
template<class type>
Node<type> *AVLtree<type>::findValue(Node<type>* ptr,type key)
{
    if(key < ptr->value)
    {
        if(ptr->left != nullptr)
        {
            ptr = ptr->left;
            findValue(ptr, key);
        } else
            return nullptr;
    }
    else if(key > ptr->value)
    {
        if(ptr->right != nullptr)
        {
            ptr = ptr->right;
            findValue(ptr, key);
        } else
            return nullptr;
    } else
        return ptr;
}
/* metoda do usuwania wezlow o danej wartosci */
template<class type>
void AVLtree<type>::remove(type key)
{
    Node<type>* balanceFrom;
    if(root != nullptr)
    {
        Node<type>* ptr = findValue(root,key);
        if(ptr != nullptr)
        {   /* wariant 1, brak dzieci */
            if(ptr->left == nullptr && ptr->right == nullptr)
            {
                if(ptr->up != nullptr) /* usuwanie 1 elementu, roota? */
                {
                    balanceFrom = ptr->up;
                    if(ptr->up->left == ptr)
                        ptr->up->left = nullptr;
                    if(ptr->up->right == ptr)
                        ptr->up->right = nullptr;
                    balance(balanceFrom);
                } else
                    root = nullptr;
                delete(ptr);
            } /* ma jednego, prawego potomka */
            else if(ptr->left == nullptr && ptr->right != nullptr)
            {
                balanceFrom = ptr->up;
                if(ptr->up->right == ptr)
                    ptr->up->right = ptr->right;
                else
                    ptr->up->left = ptr->right;
                ptr->right->up = ptr->up;
                balance(balanceFrom);
                delete(ptr);
            } /* ma jednego, lewego potomka */
            else if(ptr->right == nullptr && ptr->left != nullptr)
            {
                balanceFrom = ptr->up;
                if(ptr->up->right == ptr)
                    ptr->up->right = ptr->left;
                else
                    ptr->up->left = ptr->left;
                ptr->left->up = ptr->up;
                balance(balanceFrom);
                delete(ptr);
            } /* ma dwoch potomkow */
            else
            {
                Node<type>* tmp = ptr;
                while(tmp->right != nullptr)
                {
                    tmp = tmp->right;
                }
                balanceFrom = tmp->up;
                type max = tmp->value;
                if(tmp == ptr->right)
                    ptr->right = nullptr;
                if(tmp->left != nullptr)
                {
                    tmp->up->right = tmp->left;
                    tmp->left->up = tmp->up;
                    balanceFrom = tmp->left;
                    delete(tmp);
                }
                ptr->value = max;
                balance(balanceFrom);
            }
        }else // CZY TO OK ZE TO NA CERR??!?!!
            cerr << "Brak elementu do usunięcia!" << endl;
    } else
        cerr << "Drzewo jest puste!" << endl;
}
/* rekurencyjna metoda drukujaca drzewo na stdout */
template<class type>
void AVLtree<type>::printTree(Node<type> *ptr, int level)
{
    if(ptr != nullptr)
    {
        printTree(ptr->right, level + 1);
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
        printTree(ptr->left, level + 1);
    } else
        cerr << "Drzewo jest puste!" << endl;
}
/* rekurencyjne przejscie PRE Order*/
template<class type>
void AVLtree<type>::preOrderRec(Node<type>* ptr, ostream &stream)
{
    if(ptr != nullptr)
    {
        stream << ptr->value << "   ";
        preOrderRec(ptr->right, stream);
        preOrderRec(ptr->left, stream);
    } else
        cerr << "Drzewo jest puste!" << endl;
}
/* rekurencyjne przejscie POST Order*/
template<class type>
void AVLtree<type>::postOrderRec(Node<type> *ptr, ostream &stream)
{
    if(ptr != nullptr)
    {
        preOrderRec(ptr->right, stream);
        preOrderRec(ptr->left, stream);
        stream << ptr->value << "   ";
    } else
        cerr << "Drzewo jest puste!" << endl;
}
/* rekurencyjne przejscie IN Order*/
template<class type>
void AVLtree<type>::inOrderRec(Node<type> *ptr, ostream &stream)
{
    if(ptr != nullptr)
    {
        inOrderRec(ptr->right, stream);
        stream << ptr->value << "   ";
        inOrderRec(ptr->left, stream);
    } else
        cerr << "Drzewo jest puste!" << endl;
}
