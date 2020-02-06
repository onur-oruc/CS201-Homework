#include "SimpleBookCollection.h"
#include <iostream>
#include <string>
using namespace std;

BookCollection::BookCollection() {
	name = "";
	genreCount = 0;
	head = NULL;
}

BookCollection::~BookCollection() {
	while (head != NULL) {
		GenreNode* del;
		del = head;
		head = head->next;
		delete del;
	}
}

BookCollection::BookCollection(const BookCollection& bcToCopy) {

	genreCount = bcToCopy.genreCount;
	name = bcToCopy.name;

	if (bcToCopy.head == NULL)
		head = NULL;
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
		last->next = NULL; // runtime error if this is missing.
	}
}

void BookCollection::operator=(const BookCollection& right) {
	if (this != &right) {

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
			genreCount = right.genreCount;
		}
	}
}

void BookCollection::displayGenres() const {
	if (genreCount == 0) {
		cout << "--EMPTY--." << endl;
	}
	else {
		for (GenreNode* cur = head; cur != NULL; cur = cur->next) {
			cout << (cur->g).getGenreName() << endl;
		}
	}
}


bool BookCollection::addGenre(const string genreName) {
	GenreNode* existingGenre = findGenre(genreName);

	if ( existingGenre == NULL) {
		Genre* newGenre = new Genre(genreName);

		if (head == NULL) {
			head = new GenreNode;
			head->g = *newGenre;
			head->next = NULL;
			delete newGenre;

			genreCount++;
		}
		else {
			//to find end of the list
			GenreNode* end = head;
			GenreNode* cur = head->next;
			while (cur != NULL) {
				end = cur;
				cur = cur->next;
			}

			end->next = new GenreNode;
			end = end->next;
			end->g = *newGenre;
			end->next = NULL;
			delete newGenre;

			genreCount++;
		}
		
		return true;
	}
	else {
		cout << "The genre: " << genreName << " is already added!" << endl;
	}

	return false;
}

bool BookCollection::removeGenre(const string genreName) {
	GenreNode* genreToBeDeleted = findGenre(genreName);
	if (genreToBeDeleted != NULL) {
		if (head == genreToBeDeleted) {
			head = head->next;
			delete genreToBeDeleted;

			genreCount--;
		}
		else {
			GenreNode* cur = head->next;
			GenreNode* prev = head;
			while (cur != genreToBeDeleted) {
				prev = cur;
				cur = cur->next;
			}

			prev->next = prev->next->next;
			delete genreToBeDeleted;

			genreCount--;
		}

		return true;
	}

	cout << "The genre: " << genreName << " does not exist in the system!" << endl;

	return false;
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName) {
	GenreNode* exist = NULL;

	for (GenreNode* cur = head; cur != NULL; cur = cur->next) {
		string a = cur->g.getGenreName();
		string b = genreName;
		bool var = true;

		if (a.length() != b.length())
			var = false;

		int i = 0;
		if (var) {
			while (i < a.length()) {
				if (a[i] < b[i]) {
					if (a[i] + 32 != b[i]) {
						var = false;
					}
				}
				else if (a[i] > b[i]) {
					if (a[i] - 32 != b[i]) {
						var = false;
					}
				}
				i++;
			}
		}
		if (var) {
			exist = cur;
			break;
		}
	}

	return exist;
}


string BookCollection::getName() const {
	return name;
}

void BookCollection::setName(const string bcName) {
	name = bcName;
}


