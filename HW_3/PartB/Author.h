#ifndef __AUTHOR_H
#define __AUTHOR_H
#include <string>
using namespace std;

class Author {
public:
	Author();
	Author(const int id, const string name);
	int getID() const;
	void setID(const int id);
	string getName() const;
	void setName(const string id);
private:
	string name;
	int id;
};
#endif
