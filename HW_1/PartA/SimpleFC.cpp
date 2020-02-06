#include "SimpleFC.h"
#include <iostream>
using namespace std;

FC::FC(){
	size = 1;
	films = new Film[size];
	noOfFilms = 0;
}

FC::FC(const FC& right) {
	noOfFilms = right.noOfFilms;
	size = right.size;
	films = new Film[size];

	for (unsigned int i = 0; i < size; i ++) {
		films[i] = right.films[i];
	}
}

FC::~FC() {
	delete[] films;
}

void FC::operator=(const FC& right) {
	if ( &right != this) {
		if (size > 0) {
			delete[] films;
		}
		size = right.size;
		if (size > 0) {
			films = new Film[size];
		}
		else
			films = NULL;
		for (unsigned int i = 0; i < size; i++) {
			films[i] = right.films[i];
		}
	}
}

bool FC::addFilm( const string fTitle, const string fDirector,
	const unsigned int fYear,
	const unsigned int fDuration) {
	
	bool filmAdded = true; 
	Film* temp = films;

	for ( unsigned int i = 0; i < noOfFilms; i++) {
		if (films[i].getTitle() == fTitle && films[i].getDirector() == fDirector) {
			filmAdded = false;
		}
	}

	if (filmAdded) {
		if ( size == 0) {
			size++;
			films = new Film[size];
			films[0].setTitle(fTitle);
			films[0].setDirector(fDirector);
			films[0].setYear(fYear);
			films[0].setDuration(fDuration);
			noOfFilms++;
		}
		else if (size > 0) {
			if (size <= noOfFilms) {
				size *= 2;
			}
			films = new Film[size];
			for (unsigned int i = 0; i < noOfFilms; i++) {
				films[i] = temp[i];
			}			
			films[noOfFilms].setTitle(fTitle);
			films[noOfFilms].setDirector(fDirector);
			films[noOfFilms].setYear(fYear);
			films[noOfFilms].setDuration(fDuration);
			noOfFilms++;

			delete[] temp;
		}
	}
	return filmAdded;
}

bool FC::removeFilm(const string fTitle, const string fDirector) {
	bool filmExist = false;
	unsigned int index = noOfFilms;

	for (unsigned int i = 0; i < noOfFilms; i++) {
		if (films[i].getTitle() == fTitle && films[i].getDirector() == fDirector) {
			index = i;
			break;
		}
	}
	if (index == noOfFilms) {
		filmExist = false;
	}
	else {
		filmExist = true;
	}

	if (filmExist) {

		if (noOfFilms == 1) {
			noOfFilms--;
			delete[] films;
			films = NULL;
		}
		else {
			Film* temp;

			temp = new Film[size];
			for (unsigned int i = 0; i < size; i++) {
				temp[i] = films[i];
			}
			delete[] films;
			films = new Film[size];

			for (unsigned int i = 0; i < index; i++) {
				films[i] = temp[i];
			}
			for (unsigned int i = index; i < noOfFilms - 1; i++) {
				films[i] = temp[i + 1];
			}
			noOfFilms--;
			delete[] temp;
		}
	}
	return filmExist;
}



unsigned int FC::getFilms(Film*& allFilms) const { 
	allFilms = new Film[noOfFilms];

	for (unsigned int i = 0; i < noOfFilms; i++) {
		allFilms[i] = films[i];
	}

	return noOfFilms;
}
