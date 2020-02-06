#ifndef __GENRE_H
#define __GENRE_H
#include <string>
#include "Book.h"
using namespace std;

class Genre {
public:
	Genre(const string gname = "");
	~Genre();
	Genre(const Genre& genreToCopy);
	void operator=(const Genre& right);
	string getGenreName() const;
	void setGenreName(const string gName);

	//additional member functions
	void addBook(string bookName);
	void removeBook(string bookName);
	void removeAuthor(string bookName, int authorID);
	bool findID(const int id, string bookName);
	bool findBook(string bookName) const;
	void displayBooksWithSpesifiedGenre();
	void displayAuthorsRelatedInfo(int authorID);
	void addAuthor(string bookName, int authorId, string authorName);
	bool findAuthorByID( const int authorID);
	string getAuthorName(int authorID);
private:
	string genreName;

	//additional data members
	struct BookNode {
		Book book;
		BookNode* nextBook;
	};
	BookNode* head;
	BookNode* findBookNode(string bookName) const;
};

#endif