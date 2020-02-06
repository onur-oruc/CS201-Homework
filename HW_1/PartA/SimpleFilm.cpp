#include "SimpleFilm.h"
#include <string> 
#include <iostream>
using namespace std;


Film::Film(const string fTitle, const string fDirector,
	const unsigned int fYear,
	const unsigned int fDuration) {

	title = fTitle;
	director = fDirector;
	year = fYear;
	duration = fDuration;
}

void Film::setTitle( string newTitle) {
	title = newTitle;
}
void Film::setDirector(string newDirector) {
	director = newDirector;
}
void Film::setYear( unsigned int newYear) {
	year = newYear;
}
void Film::setDuration( unsigned int newDuration) {
	duration = newDuration;
}

Film::Film(const Film& fTopy) {
	duration = fTopy.getDuration();
	title = fTopy.getTitle();
	year = fTopy.getYear();
	director = fTopy.getDirector();
}

Film::~Film() {}

void Film::operator=(const Film& right) {
	if (&right != this) {
		duration = right.duration;
		title = right.title;
		year = right.year;
		director = right.director;
	}
}


string Film::getTitle() const {
	return title;
}

string Film::getDirector() const {
	return director;
}

unsigned int Film::getYear() const {
	return year;
}

unsigned int Film::getDuration() const {
	return duration;
}

ostream& operator<<(ostream& out, const Film& f){
	out << "Title of the film:  " << f.getTitle() << "  Duration:  " << f.getDuration() << "  Year:  " << f.getYear() << "  Director:  " << f.getDirector() << endl;
	return out;
}

