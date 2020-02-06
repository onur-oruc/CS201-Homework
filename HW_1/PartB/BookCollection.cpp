#include <string>
#include <iostream>
#include <algorithm>
#include "CaseInsensitivity.h"
#include "Genre.h" 
#include "BookCollection.h"
using namespace std;

BookCollection::BookCollection() {
	head = NULL;
	genreCount = 0;
}

BookCollection::~BookCollection() {
	GenreNode* del;
	while (head != NULL) {
		del = head;
		head = head->next;
		delete del;
	}
	del = NULL;
}

BookCollection::BookCollection(const BookCollection& bcToCopy) {
	genreCount = bcToCopy.genreCount;

	if (bcToCopy.head == NULL) {
		head = NULL;
	}
	else {
		GenreNode* cur = bcToCopy.head;
		GenreNode* last;

		head = new GenreNode;
		head->g = cur->g;
		head->next = NULL;

		last = head;
		cur = cur->next;
		while (cur != NULL) {
			last->next = new GenreNode;
			last->next->g = cur->g;
			last = last->next;
			cur = cur->next;
		}
		last->next = NULL; // runtime error ( segmentation fault) if this is missing.
	}
}

void BookCollection::operator=(const BookCollection& right) {
	if (this != &right) {
		genreCount = right.genreCount;

		if (right.head == NULL) {
			head = NULL;
		}
		else {
			GenreNode* del;
			while (head != NULL) {
				del = head;
				head = head->next;
				delete del;
			}
			del = NULL;

			head = new GenreNode;
			GenreNode* cur = right.head;
			GenreNode* last;

			head->g = cur->g;
			last = head;
			cur = cur->next;

			while (cur != NULL) {
				last->next = new GenreNode;
				last->next->g = cur->g;

				last = last->next;
				cur = cur->next;
			}
			last->next = NULL;
		}
	}
}

void BookCollection::addGenre(string genreName) {
	if (findGenre(genreName) != NULL) {
		cout << "The genre " << genreName << " has been already added!" << endl;
	}
	if (head == NULL) {
		head = new GenreNode;
		head->g.setGenreName(genreName);
		head->next = NULL;
		genreCount++;
	}
	else if (findGenre(genreName) == NULL && genreName != "") {
		GenreNode* cur = head;
		GenreNode* lastNode = NULL;
		while (cur != NULL) {
			lastNode = cur;
			cur = cur->next;
		}

		GenreNode* newGenre = new GenreNode;
		newGenre->g.setGenreName(genreName);
		newGenre->next = NULL;

		lastNode->next = newGenre;
		genreCount++;
	}
}

void BookCollection::removeGenre(string genreName) {
	GenreNode* del = findGenre(genreName);
	if (del == NULL) {
		cout << "The genre " << genreName << " does not exist in the system! " << endl;
	}
	else {
		GenreNode* prev = head;
		if (CaseSensitivity::iequals(head->g.getGenreName(), genreName)) {
			del = head;
			head = head->next;
			delete del;

			genreCount--;
		}
		else {
			while (prev->next != del) {
				prev = prev->next;
			}
			prev->next = prev->next->next;
			delete del;
			genreCount--;
		}
	}
}

void BookCollection::displayAllGenres() const {
	GenreNode* cur = head;
	if (head == NULL) {
		cout << "	--EMPTY--." << endl;
	}
	while (cur != NULL) {
		cout << "Genre name: " << cur->g.getGenreName() << endl;
		cur = cur->next;
	}
}

void BookCollection::addBook(string genreName, string bookName) { 
	GenreNode* add = findGenre(genreName);

	if (add == NULL) {
		cout << "There is no such a genre" << endl;
	}
	else {
		add->g.addBook(bookName);
	}
}

/*	Note	that
	this	 operation	 should	 also	 clear	 the	 author	 list of the book.
*/
void BookCollection::removeBook(string genreName, string bookName) {
	GenreNode* add = findGenre(genreName);

	if (add == NULL) {
		cout << "The genre: " << genreName << " does not exist!" << endl;
	}
	else if (!(add->g.findBook(bookName))) {
		cout << "Book named: " << bookName << " does not exist in the genre: " << genreName << endl;
	}
	else {
		add->g.removeBook(bookName);
	}
}

void BookCollection::addAuthor(string genreName, string bookName, int authorID, string
	authorName) {
	GenreNode* genre = findGenre(genreName);
	GenreNode* cur = head;
	while (cur != NULL) {
		if (cur->g.findAuthorByID(authorID) && !CaseSensitivity::iequals(cur->g.getAuthorName(authorID), authorName)) {
			cout << "The author with the ID: " << authorID << " is already taken by: " << cur->g.getAuthorName(authorID) << endl;
			return;
		}
		cur = cur->next;
	}

	if (genre == NULL) {
		cout << "The genre: " << genreName << " does not exist!" << endl;
	}
	else if (!(genre->g.findBook(bookName))) {
		cout << "Book named: " << bookName << " does not exist in the genre: " << genreName << endl;
	}
	else if (genre->g.findID(authorID, bookName)) {
		cout << "The author with the ID: " << authorID << " is already listed!" << endl;
	}
	else {
		genre->g.addAuthor(bookName, authorID, authorName);
	}
}

void BookCollection::removeAuthor(string genreName, string bookName, int authorID) {
	GenreNode* genre = findGenre(genreName);
	if (genre == NULL) {
		cout << "The genre: " << genreName << " does not exist!" << endl;
	}
	else if (!(genre->g.findBook(bookName))) {
		cout << "Book named: " << bookName << " does not exist in the genre: " << genreName << endl;
	}
	else if (genre->g.findID(authorID, bookName)) {
		genre->g.removeAuthor(bookName, authorID);
	}
	else {
		cout << "There is no such an author with the ID: " << authorID << " for book: " << bookName << endl;
	}
}

void BookCollection::displayGenre(string genreName) {
	GenreNode* genreToBeDisplayed = findGenre(genreName);
	if (genreToBeDisplayed == NULL) {
		cout << endl;
		cout << "	--EMPTY--." << endl;
	}
	else {
		cout << genreName << endl;
		genreToBeDisplayed->g.displayBooksWithSpesifiedGenre();
	}
}

void BookCollection::displayAuthor(int authorID) {
	GenreNode* genres = head;
	string name = "NO AUTHOR NAME TO BE DISPLAYED!";
	bool inCollection = findAuthorInCollection(authorID);

	while (genres != NULL) {
		if (inCollection) {
			if (genres->g.findAuthorByID(authorID)) {
				name = genres->g.getAuthorName(authorID);
				cout << authorID << ", " << name << endl;
				break;
			}
		}
		genres = genres->next;
	}

	if (!inCollection) {
		cout << authorID << ", " << name << endl;
		cout << "	--EMPTY--." << endl;
		return;
	}

	genres = head;
	while (genres != NULL) {
		genres->g.displayAuthorsRelatedInfo(authorID);

		genres = genres->next;
	}
}

bool BookCollection::findAuthorInCollection(const int authorID) {
	GenreNode* genreInCollection = head;

	while (genreInCollection != NULL) {
		if (genreInCollection->g.findAuthorByID(authorID))
			return true;
		genreInCollection = genreInCollection->next;
	}

	return false;
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName) {
	GenreNode* genreToBeSearch = NULL;

	GenreNode* cur = head;
	while (cur != NULL) {
		string name = cur->g.getGenreName();
		if (CaseSensitivity::iequals(name, genreName)) {
			genreToBeSearch = cur;
		}
		cur = cur->next;
	}

	return genreToBeSearch;
}