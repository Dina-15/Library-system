#include <iostream>
#include <unistd.h>
#include <string.h>
#include "Container.h"
using namespace std;
struct Book
{
    string title, author, genre, ISBN, status;
};

int main()
{
    Container<Book> Library;
    int ch;
    while(true)
    {
        cout<<"[1] INSERT A BOOK AT THE FRONT OF THE LIST\n[2] INSERT A BOOK AT THE BACK OF THE LIST\n"
            <<"[3] INSERT A BOOK AT A SPECIFIC POSITION\n[4] REMOVE A BOOK FROM A SPECIFIC POSITION\n"
            <<"[5] FIND A BOOK IN THE LIST\n[6] RETRIEVE A BOOK IN A POSITION\n"
            <<"[7] SHOW ALL BOOKS SORTED BASED ON TITLE\n[8] BORROW A BOOK\n"
            <<"[9] STATISTICS OF BOOKS\n[0] CLEAR THE LIST AND EXIT\n"
            <<"Select a choice : ";
        cin>>ch;
        switch(ch)
        {
        case 1:
        {
            system("cls");
            Book book;
            cout<<"Enter book title : ";
            cin.ignore(1, '\n');
            getline(cin, book.title);
            cout<<"Enter book author : ";
            getline(cin, book.author);
            cout<<"Enter book genre : ";
            getline(cin, book.genre);
            cout<<"Enter book ISBN : ";
            getline(cin, book.ISBN);
            book.status="available";
            Library.insertFront(book);
            system("pause");
        }
        break;
        case 2:
        {
            system("cls");
            Book book;
            cout<<"Enter book title : ";
            cin.ignore(1, '\n');
            getline(cin, book.title);
            cout<<"Enter book author : ";
            getline(cin, book.author);
            cout<<"Enter book genre : ";
            getline(cin, book.genre);
            cout<<"Enter book ISBN : ";
            getline(cin, book.ISBN);
            book.status="available";
            Library.insertBack(book);
            system("pause");
        }
        break;
        case 3:
        {
            system("cls");
            Book book;
            int pos;
            try{
            cout<<"Enter a position to insert at : ";
            cin>>pos;
            if(pos>Library.containersize())
                throw "IndexError: ";
            cout<<"Enter book title : ";
            cin.ignore(1, '\n');
            getline(cin, book.title);
            cout<<"Enter book author : ";
            getline(cin, book.author);
            cout<<"Enter book genre : ";
            getline(cin, book.genre);
            cout<<"Enter book ISBN : ";
            getline(cin, book.ISBN);
            book.status="available";
            Library.insertAt(book,pos);
            }
            catch(...)
            {
                cout<<"IndexError: List index out of range !"<<endl;
            }
            system("pause");
        }
        break;
        case 4:
        {
            system("cls");
            int pos;
            try{
            cout<<"Enter a position to remove from : ";
            cin>>pos;
            if(pos>Library.containersize())
                throw "IndexError: ";
            Library.removeAt(pos);
            cout<<"\nBOOK REMOVED FROM THE LIST SUCCESFULLY !"<<endl;
            }
            catch(...)
            {
              cout<<"IndexError: Invalid index !"<<endl;
            }
            system("pause");
        }
        break;
        case 5:
        {
            system("cls");
            string key;
            cout<<"Enter any key(title, author, genre,or ISBN) to find the book : ";
            cin.ignore(1, '\n');
            getline(cin,key);
            Book b;
            try{
            b=Library.find(key);
                cout<<"BOOK TITLE : "<<b.title
                    <<"\nBOOK AUTHOR : "<<b.author
                    <<"\nBOOK GENRE : "<<b.genre
                    <<"\nBOOK ISBN : "<<b.ISBN
                    <<"\nBOOK STATUS : "<<b.status<<endl;
            }
            catch(Container<Book>::notFound)
            {
                cout<<"SORRY! THIS BOOK IS UNAVAILABLE  !"<<endl;
            }
            system("pause");
        }
        break;
        case 6:
        {
            system("cls");
            int pos;
            try{
            cout<<"Enter a position to retrieve from : ";
            cin>>pos;
            if(pos>Library.containersize())
                throw "IndexError: ";
            Book b;
            b=Library.retrieve(pos);
            cout<<"BOOK TITLE : "<<b.title
                <<"\nBOOK AUTHOR : "<<b.author
                <<"\nBOOK GENRE : "<<b.genre
                <<"\nBOOK ISBN : "<<b.ISBN
                <<"\nBOOK STATUS : "<<b.status<<endl;
            }
            catch(...)
            {
              cout<<"IndexError: List index out of range !"<<endl;
            }
            system("pause");
        }
        break;
        case 7:
        {
            system("cls");
            Library.sort(Library.begin(),Library.end());
            for(int i=0; i<Library.containersize(); ++i)
            {
                Book b;
                b=Library.retrieve(i);
                cout<<"BOOK TITLE : "<<b.title
                    <<"\nBOOK AUTHOR : "<<b.author
                    <<"\nBOOK GENRE : "<<b.genre
                    <<"\nBOOK ISBN : "<<b.ISBN
                    <<"\nBOOK STATUS : "<<b.status
                    <<"\n===========================\n";
            }
            system("pause");
        }
        break;
        case 8:
        {
            system("cls");
            string key;
            cout<<"Enter any key(title, author, genre,or ISBN) to find the book : ";
            cin.ignore(1, '\n');
            getline(cin,key);
            Book b;
            try{
            b=Library.borrow(key);
                cout<<"\nBOOK TITLE : "<<b.title
                    <<"\nBOOK AUTHOR : "<<b.author
                    <<"\nBOOK GENRE : "<<b.genre
                    <<"\nBOOK ISBN : "<<b.ISBN
                    <<"\n\n\tBORROWED THE BOOK, SUCCEFULLY !"<<endl;
            }
            catch(Container<Book>::notFound)
            {
                cout<<"SORRY! THIS BOOK IS UNAVAILABLE  !"<<endl;
            }
            system("pause");
        }
        break;
        case 9:
            system("cls");
            cout<<"\nTOTAL NUMBER OF BOOKS : "<<Library.containersize()<<endl;
            cout<<"NUMBER OF AVAILABLE BOOKS : "<<Library.availableBooks()<<endl;
            cout<<"NUMBER OF BORROWED BOOKS : "<<Library.borrowedBooks()<<endl;
            system("pause");
            break;
        case 0:
            Library.remove();
            return 0;
            break;
        default:
            cout<<"invalid choice!"<<endl;
        }
        system("cls");
    }
    return 0;
}
