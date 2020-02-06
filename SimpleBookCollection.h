#ifndef __SIMPLE_BOOKCOLLECTION_H
#define __SIMPLE_BOOKCOLLECTION_H
#include <string>
using namespace std;
#include "SimpleGenre.h"

class BookCollection {
public:
	BookCollection();
	~BookCollection();
	BookCollection(const BookCollection& bcToCopy);
	void operator=(const BookCollection& right);
	void displayGenres() const;
	bool addGenre(const string genreName);
	bool removeGenre(const string genreName);
	string getName() const;
	void setName(const string bcName);
private:
	struct GenreNode {
		Genre g;
		GenreNode* next;
	};

	string name;
	int genreCount;
	GenreNode* head;
	GenreNode* findGenre(string genreName);
};
#endif