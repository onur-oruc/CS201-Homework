#include "CaseInsensitivity.h"
#include <string>
#include <iostream> 
#include <cstdlib>
using namespace std;

bool CaseSensitivity::iequals(const string& a, const string& b) {

	if (a.length() != b.length())
		return false;

	int i = 0;
	while (i < a.length()) {
		if (a[i] < b[i]) {
			if (a[i] + 32 != b[i])
				return false;
		}
		else if (a[i] > b[i]) {
			if (a[i] - 32 != b[i])
				return false;
		}

		i++;
	}

	return true;
}