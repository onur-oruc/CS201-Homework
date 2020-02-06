#include <string>
#include "Book.h"
#include "Author.h"
#include <iostream>
#include <cctype>
#include "CaseInsensitivity.h"
using namespace std;

Book::Book() {
	head = NULL;
	name = "";
	authorCount = 0;
}

Book::Book(const string name) {
	head = NULL;
	this->name = name;
	authorCount = 0;
}

Book::~Book() {
	AuthorNode* del;
	while (head != NULL) {
		del = head;
		head = head->next;
		delete del;
	}
	del = NULL;
}

Book::Book(const Book& bookToCopy) {
	authorCount = bookToCopy.authorCount;
	name = bookToCopy.name;

	if (bookToCopy.head == NULL)
		head = NULL;
	else {
		AuthorNode* cur = bookToCopy.head;
		AuthorNode* last;

		head = new AuthorNode;
		head->a = cur->a;
		head->next = NULL;

		last = head;
		cur = cur->next;
		while (cur != NULL) {
			last->next = new AuthorNode;
			last->next->a = cur->a;
			last = last->next;
			cur = cur->next;
		}
		last->next = NULL; // runtime error ( segmentation fault) if this is missing.
	}
}

void Book::operator=(const Book& right) {
	if (this != &right) {
		name = right.name;

		if (right.head == NULL) {
			head = NULL;
		}
		else {
			AuthorNode* del;
			while (head != NULL) {
				del = head;
				head = head->next;
				delete del;
			}
			del = NULL;

			head = new AuthorNode;
			AuthorNode* cur = right.head;
			AuthorNode* last;

			head->a = cur->a;
			last = head;
			cur = cur->next;

			while (cur != NULL) {
				last->next = new AuthorNode;
				last->next->a = cur->a;

				last = last->next;
				cur = cur->next;
			}
			last->next = NULL;
			authorCount = right.authorCount;
		}
	}
}

string Book::getName() const {
	return name;
}

void Book::setName(const string bookName) {
	name = bookName;
}

string Book::getAuthorName(const int id) {
	AuthorNode* cur = head;

	while (cur != NULL) {
		if (cur->a.getID() == id) {
			return cur->a.getName();
		}
		cur = cur->next;
	}

	return "";
}

bool Book::addAuthor(const int id, const string name) {
	if (!findAuthor(id) || CaseSensitivity::iequals(findAuthor(id)->a.getName(), name) && findAuthor(id)) {
		AuthorNode* newNode = new AuthorNode;
		Author* newAuthor = new Author(id, name);

		newNode->a = *newAuthor;
		newNode->next = NULL;

		delete newAuthor;				

		if (head == NULL) {
			head = newNode;
		}
		else {
			AuthorNode* cur = head;
			AuthorNode* last = NULL;
			while (cur != NULL) {
				last = cur;
				cur = cur->next;
			}
			last->next = newNode;
		}
		authorCount++;
		return true;
	}
	else {
		cout << "The author with the ID:" << id << " has been already listed!" << endl;
		return false;
	}
}

bool Book::removeAuthor(const int id) {
	if (!findAuthor(id)) {
		cout << "There is no author with the ID: " << id << "!" << endl;
		return false;
	}
	if (head == NULL) {
		return false;
	}
	else {
		if (findAuthor(id) != NULL) {
			AuthorNode* del;
			AuthorNode* cur = head;
			AuthorNode* last = cur;

			while (cur != NULL) {
				if (head->a.getID() == id) {
					if (head->next == NULL) {
						delete head;
						head = NULL;
					}
					else {
						del = head;
						head = head->next;
						delete del;
					}
					return true;
				}
				if (cur->a.getID() == id) {
					del = cur;
					cur = cur->next;
					last->next = cur;
					delete del;
				}
				else {
					last = cur;
					cur = cur->next;
				}
			}
		}
		authorCount--;
		return true;
	}
}

void Book::displayAuthors() const {
	AuthorNode* cur = head;
	if (head != NULL) {
		while (cur != NULL) {
			cout << "	" << cur->a.getID() << ", " << cur->a.getName() << endl;
			cur = cur->next;
		}
	}
	else {
		cout << "	--EMPTY--." << endl;
	}
}

Book::AuthorNode* Book::findAuthor(int id) {
	AuthorNode* existingAuthor = NULL;

	for (AuthorNode* cur = head; cur != NULL; cur = cur->next) {
		if (cur->a.getID() == id)
			return cur;
	}

	return existingAuthor;
}

bool Book::findAuthorById(const int id) {
	if (findAuthor(id) == NULL)
		return false;
	return true;
}