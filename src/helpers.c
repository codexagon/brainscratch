#include <string.h>

#include "../include/helpers.h"

bool str_ends_with(const char *s, const char *end) {
	if (!s || !end) {
		return false;
	}

	int l = strlen(s);
	int lend = strlen(end);

	if (lend > l) {
		return false;
	}

	return strncmp(s + l - lend, end, lend) == 0;
}
