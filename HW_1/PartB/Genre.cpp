#include "Genre.h"
#include "Book.h"
#include "Author.h"
#include <iostream>
#include <string>
#include "CaseInsensitivity.h"
using namespace std;

Genre::Genre(const string gname) {
	head = NULL;
	genreName = gname;
}

Genre::~Genre() {
	while (head != NULL) {
		BookNode* del = head;
		head = head->nextBook;
		delete del;
	}

}

Genre::Genre(const Genre& genreToCopy) {
	genreName = genreToCopy.genreName;

	if (genreToCopy.head == NULL) {
		head = NULL;
	}
	else {
		BookNode* cur = genreToCopy.head;
		BookNode* last;

		head = new BookNode;
		head->book = cur->book;
		head->nextBook = NULL;

		last = head;
		cur = cur->nextBook;
		while (cur != NULL) {
			last->nextBook = new BookNode;
			last->nextBook->book = cur->book;
			last = last->nextBook;
			cur = cur->nextBook;
		}
		last->nextBook = NULL; // runtime error ( segmentation fault) if this is missing.
	}
}

void Genre::operator=(const Genre& right) {
	if (this != &right) {
		genreName = right.genreName;

		if (right.head == NULL) {
			head = NULL;
		}
		else {
			BookNode* del;
			while (head != NULL) {
				del = head;
				head = head->nextBook;
				delete del;
			}
			del = NULL;

			head = new BookNode;
			BookNode* cur = right.head;
			BookNode* last;

			head->book = cur->book;
			last = head;
			cur = cur->nextBook;

			while (cur != NULL) {
				last->nextBook = new BookNode;
				last->nextBook->book = cur->book;

				last = last->nextBook;
				cur = cur->nextBook;
			}
			last->nextBook = NULL;
		}
	}
}

void Genre::removeAuthor(string bookName, int authorID) {
	BookNode* bookOfAuthor = findBookNode(bookName);

	bookOfAuthor->book.removeAuthor(authorID);
}

void Genre::addAuthor(string bookName, int authorId, string authorName) {
	BookNode* bookOfAuthor = findBookNode(bookName);
	BookNode* cur = head;
	while (cur != NULL) {
		if (cur->book.findAuthorById(authorId) && !CaseSensitivity::iequals(cur->book.getAuthorName(authorId), authorName)) {
			string name = cur->book.getAuthorName(authorId);
			cout << "The ID: " << authorId << " is already taken by the author: " << name << endl;
			return;
		}
		cur = cur->nextBook;
	}
	bookOfAuthor->book.addAuthor(authorId, authorName);
}

bool Genre::findID(const int id, string bookName) {
	if (findBookNode(bookName)->book.findAuthorById(id))
		return true;
	return false;
}


bool Genre::findAuthorByID(const int authorID) {
	BookNode* cur = head;
	while (cur != NULL) {
		if (cur->book.findAuthorById(authorID))  
			return true;
		cur = cur->nextBook;
	}
	return false;
}

bool Genre::findBook(string bookName) const {
	BookNode* exist = findBookNode(bookName);

	return exist != NULL;
}

Genre::BookNode* Genre::findBookNode(string bookName) const {
	BookNode* existingBook = NULL;

	if (head != NULL) {
		BookNode* cur = head;
		while (cur != NULL) {
			if (CaseSensitivity::iequals(cur->book.getName(), bookName)) {
				existingBook = cur;
				return existingBook;
			}
			cur = cur->nextBook;
		}
	}
	return existingBook;
}

string Genre::getAuthorName(int authorID) {
	BookNode* cur = head;
	string name;
	while (cur != NULL) {
		if (cur->book.findAuthorById(authorID)) {
			return cur->book.getAuthorName(authorID);
		}
		cur = cur->nextBook;
	}

	return "";
}

void Genre::displayBooksWithSpesifiedGenre() {
	BookNode* cur = head;
	while (cur != NULL) {
		cout << cur->book.getName() << endl;
		cur->book.displayAuthors();

		cur = cur->nextBook;
	}
}

void Genre::displayAuthorsRelatedInfo(int authorID) {
	BookNode* cur = head;
	bool authorExist = false;
	while (cur != NULL) {
		if (cur->book.findAuthorById(authorID)) {
			cout << genreName << endl;
			authorExist = true;
			break;
		}
		cur = cur->nextBook;
	}
	cur = head;
	while (cur != NULL) {
		if (cur->book.findAuthorById(authorID)) {
			cout << "	" << cur->book.getName() << endl;
		}
		cur = cur->nextBook;
	}
}


void Genre::addBook(string bookName) {
	if (!findBook(bookName)) {
		if (head == NULL) {
			Book* newBook = new Book(bookName);
			head = new BookNode;
			head->book = *newBook;
			head->nextBook = NULL;

			delete newBook;
		}
		else {
			BookNode* last = NULL;
			BookNode* cur = head;

			while (cur != NULL) {
				last = cur;
				cur = cur->nextBook;
			}
			Book* newBook = new Book(bookName);

			last->nextBook = new BookNode;
			last = last->nextBook;
			last->book = *newBook;
			last->nextBook = NULL;

			delete newBook;
		}
	}
	else {
		cout << "The book: " << bookName << " has been already added!" << endl;
	}
}

void Genre::removeBook(string bookName) {
	if (head != NULL) {
		if (findBook(bookName)) {
			BookNode* del = NULL;
			BookNode* last = head;
			if (CaseSensitivity::iequals(head->book.getName(), bookName)) {
				del = head;
				head = head->nextBook;
				delete del;
			}
			else {
				BookNode* cur = head;
				while (!CaseSensitivity::iequals(cur->book.getName(), bookName)) {
					last = cur;
					cur = cur->nextBook;
				}
				del = cur;
				last->nextBook = cur->nextBook;

				delete del;
			}
		}
	}

}


string Genre::getGenreName() const {
	return genreName;
}

void Genre::setGenreName(const string gName) {
	genreName = gName;
}

