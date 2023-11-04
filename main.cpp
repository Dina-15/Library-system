#include <iostream>
#include <unistd.h>
#include <string.h>
#include "Container.h"
#include "IList.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
using namespace std;

struct Book
{
    string title, author, genre, ISBN, status;
};
bool checkEQ(Book b, string key)
{
    return key == b.title || key == b.author || key == b.genre || key == b.ISBN;
}
bool checkST(Book b1, Book b2)
{
    return b1.title < b2.title || b1.author < b2.author || b1.genre < b2.genre || b1.ISBN < b2.ISBN;
}
bool checkAvailability(Book book)
{
    if(book.status=="available")
        return true;
    else
        return false;
}
int main()
{
    // Container<Book,IList<Book>,SinglyLinkedList<Book>> Library;
    Container<Book,IList<Book>,DoublyLinkedList<Book>> Library;
    
    int ch;
    while (ch !=0)
    {
        cout << "[1] INSERT A BOOK AT THE FRONT OF THE LIST\n[2] INSERT A BOOK AT THE BACK OF THE LIST\n"
            << "[3] INSERT A BOOK AT A SPECIFIC POSITION\n[4] POP A BOOK FROM THE FRONT OF THE LIST\n"
            << "[5] POP A BOOK FROM THE BACK OF THE LIST\n[6] POP A BOOK FROM A SPECIFIC POSITION\n"
            << "[7] FIND A BOOK IN THE LIST\n[8] RETRIEVE A BOOK IN A POSITION\n"
            << "[9] SORT THE LIST\n[10] SHOW ALL BOOKS \n[11] BORROW A BOOK\n"
            << "[12] REVERSE THE LIST\n[13] STATISTICS OF BOOKS\n[0] EXIT\n"
            << "Select a choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            system("cls");
            Book book;
            cout << "Enter book title : ";
            cin.ignore(1, '\n');
            getline(cin, book.title);
            cout << "Enter book author : ";
            getline(cin, book.author);
            cout << "Enter book genre : ";
            getline(cin, book.genre);
            cout << "Enter book ISBN : ";
            getline(cin, book.ISBN);
            book.status = "available";
            Library.pushFront(book);
            system("pause");
        }
        break;
        case 2:
        {
            system("cls");
            Book book;
            cout << "Enter book title : ";
            cin.ignore(1, '\n');
            getline(cin, book.title);
            cout << "Enter book author : ";
            getline(cin, book.author);
            cout << "Enter book genre : ";
            getline(cin, book.genre);
            cout << "Enter book ISBN : ";
            getline(cin, book.ISBN);
            book.status = "available";
            Library.pushBack(book);
            system("pause");
        }
        break;
        case 3:
        {
            system("cls");
            Book book;
            int pos;
            try
            {
                cout << "Enter a position to insert at : ";
                cin >> pos;
                if (pos<0 || pos > Library.containersize())
                    throw "IndexError: ";
                cout << "Enter book title : ";
                cin.ignore(1, '\n');
                getline(cin, book.title);
                cout << "Enter book author : ";
                getline(cin, book.author);
                cout << "Enter book genre : ";
                getline(cin, book.genre);
                cout << "Enter book ISBN : ";
                getline(cin, book.ISBN);
                book.status = "available";
                Library.insertAt( pos, book);
            }
            catch (...)
            {
                cout << "IndexError: List index out of range !" << endl;
            }
            system("pause");
        }
        break;
        case 4:
        {
            system("cls");
            try
            {
                if (Library.containerEmpty())
                    throw "SORRY ! ";
                Book b;
                b = Library.popFront();
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status 
                    << "\n\t POPED !"<<endl;
            }
            catch (...)
            {
                cout << "LIST IS EMPTY !" << endl;
            }
            system("pause");
        }
        break;
        case 5:
        {
            system("cls");
            try
            {
                if (Library.containerEmpty())
                    throw "SORRY ! ";
                Book b;
                b = Library.popBack();
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status 
                    << "\n\t POPED !"<<endl;
            }
            catch (...)
            {
                cout << "LIST IS EMPTY !" << endl;
            }
            system("pause");
        }
        break;
        case 6:
        {
            system("cls");
            int pos;
            try
            {
                if (Library.containerEmpty())
                    throw "SORRY ! ";
                else{
                cout << "Enter a position to pop from : ";
                cin >> pos;
                if (pos<0 || pos > Library.containersize())
                    throw "IndexError: ";
                Book b;
                b = Library.removeAt(pos);
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status << endl;
                }
            }
            catch (...)
            {
                cout << "Invalid pop !" << endl;
            }
            system("pause");
        }
        break;
        case 7:
        {
            system("cls");
            string key;
            cout << "Enter any key(title, author, genre,or ISBN) to find the book : ";
            cin.ignore(1, '\n');
            getline(cin, key);
            Book b;
            try
            {
                b = Library.search(key, &checkEQ);
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status << endl;
            }
            // catch (Container<Book,IList<Book>,SinglyLinkedList<Book>>::notFound)
            catch (Container<Book,IList<Book>,DoublyLinkedList<Book>>::notFound)
            {
                cout << "SORRY! THIS BOOK IS NOT FOUND  !" << endl;
            }
            system("pause");
        }
        break;
        case 8:
        {
            system("cls");
            int pos;
            try
            {
                cout << "Enter a position to retrieve from : ";
                cin >> pos;
                if (pos<0 || pos > Library.containersize())
                    throw "IndexError: ";
                Book b;
                b = Library.retrieveAt(pos);
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status << endl;
            }
            catch (...)
            {
                cout << "IndexError: List index out of range !" << endl;
            }
            system("pause");
        }
        break;
        case 9:
        {
            system("cls");
            Library.sort(&checkST);
            for (int i = 0; i < Library.containersize(); ++i)
            {
                Book b;
                b = Library.retrieveAt(i);
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status
                    << "\n===========================\n";
            }
            system("pause");
        }
        break;
        case 10:
        {
            system("cls");
            for (int i = 0; i < Library.containersize(); ++i)
            {
                Book b;
                b = Library.retrieveAt(i);
                cout << "BOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN
                    << "\nBOOK STATUS : " << b.status
                    << "\n===========================\n";
            }
            system("pause");
        }
        break;
        case 11:
        {
            system("cls");
            string key;
            cout << "Enter any key(title, author, genre,or ISBN) to find the book : ";
            cin.ignore(1, '\n');
            getline(cin, key);
            Book b;
            try
            {
                b = Library.borrow(key, &checkEQ, &checkAvailability);
                cout << "\nBOOK TITLE : " << b.title
                    << "\nBOOK AUTHOR : " << b.author
                    << "\nBOOK GENRE : " << b.genre
                    << "\nBOOK ISBN : " << b.ISBN<<endl;
                b.status = "unavailable";                 // switch the status
                Library.Update(key, &checkEQ, b);
                cout<< "\n\tBORROWED THE BOOK, SUCCEFULLY !" << endl;
                    
            }
            // catch (Container<Book,IList<Book>,SinglyLinkedList<Book>>::notFound)
            catch (Container<Book,IList<Book>,DoublyLinkedList<Book>>::notFound)
            {
                cout << "SORRY! THIS BOOK IS NOT FOUND  !" << endl;
            }
            // catch(Container<Book,IList<Book>,SinglyLinkedList<Book>>::notAvailable)
            catch(Container<Book,IList<Book>,DoublyLinkedList<Book>>::notAvailable)
            {
                cout<<"SORRY! THIS BOOK IS UNAVAILABLE NOW !"<<endl;
            }
            system("pause");
        }
        break;
        case 12:
            system("cls");
            try
            {
                if (Library.containerEmpty())
                    throw "SORRY ! ";
                else
                {
                    Library.reverse();
                    for (int i = 0; i < Library.containersize(); ++i)
                    {
                        Book b;
                        b = Library.retrieveAt(i);
                        cout << "BOOK TITLE : " << b.title
                        << "\nBOOK AUTHOR : " << b.author
                        << "\nBOOK GENRE : " << b.genre
                        << "\nBOOK ISBN : " << b.ISBN 
                        << "\nBOOK STATUS : " << b.status
                        << "\n===========================\n";
            }
                }
            }
            catch (...)
            {
                cout << "LIST IS EMPTY !" << endl;
            }
            
            system("pause");
        break;
        case 13:
        {
            system("cls");
            cout << "\nTOTAL NUMBER OF BOOKS : " << Library.containersize() << endl;
            cout << "NUMBER OF AVAILABLE BOOKS : " << Library.availableItems() << endl;
            cout << "NUMBER OF BORROWED BOOKS : " << Library.borrowedItems() << endl;
            system("pause");
        }
        break;
        
        case 0:
            break;
        default:
            cout << "invalid choice!" << endl;
        }
        system("cls");
    }
    return 0;
}
