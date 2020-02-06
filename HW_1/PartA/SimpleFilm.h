#ifndef __SIMPLE_FILM_H
#define __SIMPLE_FILM_H
#include <string> 
using namespace std;
#include <iostream>
class Film {
public:
	Film(const string fTitle = "", const string fDirector = "",
		const unsigned int fYear = 0,
		const unsigned int fDuration = 0);
	Film(const Film& fToCopy);
	~Film();
	void operator=(const Film& right);
	string getTitle() const;
	string getDirector() const;
	unsigned int getYear() const;
	unsigned int getDuration() const;
	void setTitle( string a);
	void setDirector( string b);
	void setYear( unsigned int c);
	void setDuration( unsigned int d);
	friend ostream& operator<<(ostream& out, const Film& f);
private:
	string title;
	string director;
	unsigned int year;
	unsigned int duration;
};
#endif