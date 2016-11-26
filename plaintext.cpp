#include <cstdio>
#include <vector>
#include "zahyou-tateru.h"

int plaintext(FILE* out, const std::vector<Corner>& corners, const char* param) {
	param = param; // avoid warning for unused argugment
	for (std::vector<Corner>::const_iterator it = corners.begin(); it != corners.end(); it++) {
		fprintf(out, "%.15f\t%.15f\t%.15f\t%.15f\t%.15f\t%.15f\n",
			it->leftCorner.x, it->leftCorner.y,
			it->centerPoint.x, it->centerPoint.y,
			it->rightCorner.x, it->rightCorner.y);
	}
	return 0;
}
