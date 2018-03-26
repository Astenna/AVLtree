#include "AVLtree.cpp"
using namespace std;

void menu()
{
    cout << "Drzewo AVL" << endl;
    cout << "1 - wyswietl drzewo (schemat)" << endl;
    cout << "2 - dodaj element" << endl;
    cout << "3 - usun element" << endl;
    cout << "4 - wyswietl wysokosc drzewa" << endl;
    cout << "5 - wyswietl wartosc korzenia" << endl;
    cout << "6 - przejscie inOrder" << endl;
    cout << "7 - przejscie postOrder" << endl;
    cout << "8 - przejscie preOrder" << endl;
    cout << "9 - wyswietl menu" << endl;
    cout << "10 - wyjscie z programu" << endl;
}

int main()
{
    AVLtree<int> tr;
    menu();
    int toAddOrDel;
    int choice = 9;
    while(choice != 10)
    {
        cout << "Podaj opcje: (9 - wyswietl menu) ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                tr.display();
                break;
            case 2:
                cout << "Podaj element do dodania: ";
                cin >> toAddOrDel;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cerr << "Dodanie sie nie powiodlo! Nalezy podac liczbe!" << endl;
                } else
                    tr.add(toAddOrDel);
                cout << endl;
                break;
            case 3:
                cout << "Podaj element do usuniecia: ";
                cin  >> toAddOrDel;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cerr << "Usuniecie sie nie powiodlo! Nalezy podac liczbe!" << endl;
                } else
                    tr.remove(toAddOrDel);
                cout << endl;
                break;
            case 4:
                cout << tr.height() << endl;
                break;
            case 5:
                cout << tr.getRootValue() << endl;
                break;
            case 6:
                tr.inOrder(cout);
                break;
            case 7:
                tr.postOrder(cout);
                break;
            case 8:
                tr.preOrder(cout);
                break;
            case 9:
                menu();
                break;
            case 10:
                choice = 10;
                break;
            default:
                cout << "Nie ma takiej opcji!" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
                break;
        }
        cout << endl;
    }
    return 0;
}



