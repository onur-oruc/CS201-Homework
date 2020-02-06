#ifndef __SIMPLE_GENRE_H
#define __SIMPLE_GENRE_H
#include <string>
using namespace std;

// You are not allowed to define additional functions and data members to
// this class for Part A.
class Genre {
public:
	Genre(const string gname = "");
	~Genre();
	Genre(const Genre& genreToCopy);
	void operator=(const Genre& right);
	string getGenreName() const;
	void setGenreName(const string gName);
private:
	string genreName; // the only data member 
};

#endif