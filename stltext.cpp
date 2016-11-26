#include <cstdio>
#include <cmath>
#include <vector>
#include "zahyou-tateru.h"

// 右ねじの向きにfacetの所のベクトルが出る
static void printTriangle(FILE* out, const PointWithHeight& a, const PointWithHeight& b, const PointWithHeight& c) {
	double ax = b.point.x - a.point.x;
	double ay = b.point.y - a.point.y;
	double az = b.height - a.height;
	double bx = c.point.x - a.point.x;
	double by = c.point.y - a.point.y;
	double bz = c.height - a.height;
	double x = ay * bz - by * az;
	double y = az * bx - bz * ax;
	double z = ax * by - bx * ay;
	double len = sqrt(x * x + y * y + z * z);
	fprintf(out, "  facet normal %.6e %.6e %.6e\n", x / len, y / len, z / len);
	fprintf(out, "    outer loop\n");
	fprintf(out, "      vertex   %.6e %.6e %.6e\n", a.point.x, a.point.y, a.height);
	fprintf(out, "      vertex   %.6e %.6e %.6e\n", b.point.x, b.point.y, b.height);
	fprintf(out, "      vertex   %.6e %.6e %.6e\n", c.point.x, c.point.y, c.height);
	fprintf(out, "    endloop\n");
	fprintf(out, "  endfacet\n");
}

static void printstl(FILE* out, const Corner& corner1, const Corner& corner2) {
	// 底面を出力
	printTriangle(out, PointWithHeight(corner2.leftCorner, 0),
		PointWithHeight(corner1.leftCorner, 0), PointWithHeight(corner2.rightCorner, 0));
	printTriangle(out, PointWithHeight(corner2.rightCorner, 0),
		PointWithHeight(corner1.leftCorner, 0), PointWithHeight(corner1.rightCorner, 0));
	// 左の壁を出力
	printTriangle(out, PointWithHeight(corner2.leftCorner, corner2.height),
		PointWithHeight(corner2.leftCorner, 0), PointWithHeight(corner1.leftCorner, 0));
	printTriangle(out, PointWithHeight(corner2.leftCorner, corner2.height),
		PointWithHeight(corner1.leftCorner, 0), PointWithHeight(corner1.leftCorner, corner1.height));
	// 右の壁を出力
	printTriangle(out, PointWithHeight(corner2.rightCorner, corner2.height),
		PointWithHeight(corner1.rightCorner, 0), PointWithHeight(corner2.rightCorner, 0));
	printTriangle(out, PointWithHeight(corner2.rightCorner, corner2.height),
		PointWithHeight(corner1.rightCorner, corner1.height), PointWithHeight(corner1.rightCorner, 0));
	// 上面を出力
	printTriangle(out, PointWithHeight(corner2.leftCorner, corner2.height),
		PointWithHeight(corner1.leftCorner, corner1.height), PointWithHeight(corner2.rightCorner, corner2.height));
	printTriangle(out, PointWithHeight(corner2.rightCorner, corner2.height),
		PointWithHeight(corner1.leftCorner, corner1.height), PointWithHeight(corner1.rightCorner, corner1.height));
}

int stltext(FILE* out, const std::vector<Corner>& corners, const char* param) {
	param = param; // avoid warning for unused argugment
	fputs("solid ascii\n", out);
	for (std::vector<Corner>::const_iterator it = corners.begin(); it != corners.end() - 1; it++) {
		printstl(out, *it, *(it + 1));
	}
	printstl(out, corners[corners.size() - 1], corners[0]);
	fputs("endsolid\n", out);
	return 0;
}
