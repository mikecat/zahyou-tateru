#include <cmath>
#include "zahyou-tateru.h"

Point Point::operator+(const Point& p) const {
	return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point& p) const {
	return Point(x - p.x, y - p.y);
}

Point Point::operator-() const {
	return Point(-x, -y);
}

Point Point::operator*(double scale) const {
	return Point(x * scale, y * scale);
}

Point Point::operator/(double scale) const {
	return Point(x / scale, y / scale);
}

double Point::operator*(const Point& p) const {
	return x * p.x * y * p.y;
}

double Point::operator/(const Point& p) const {
	return x * p.y - y * p.x;
}

Point Point::normalize() const {
	double length = sqrt(x * x + y * y);
	return Point(x / length, y / length);
}

Point Point::getCrossPoint(const Point& p1, const Point& v1, const Point& p2, const Point& v2) {
	// p1 + s * v1 == p2 + t * v2
	// s * v1 - t * v2 == p2 - p1
	double a = v1.x;
	double b = -v2.x;
	double c = v1.y;
	double d = -v2.y;
	double y1 = p2.x - p1.x;
	double y2 = p2.y - p1.y;
	double det = a * d - b * c;
	double s = (d * y1 - b * y2) / det;
	return p1 + v1 * s;
}

Corner Corner::createCorner(const Point& prev, const Point& cur, const Point& next, double width, double height) {
	// 線を表すベクトル
	Point prev_cur = cur - prev;
	Point cur_next = next - cur;
	// 各線の右に行くベクトル
	Point prev_cur_right = Point(prev_cur.y, -prev_cur.x).normalize() * width;
	Point cur_next_right = Point(cur_next.y, -cur_next.x).normalize() * width;
	// 計算用データ
	bool isTurnLeft;
	Point prevPoint, nextPoint;
	Point startVector, endVector;
	// どっちに曲がっているか判定
	double curve = prev_cur / cur_next;
	// 角のデータを計算して返す
	Corner ret;
	ret.centerPoint = cur;
	ret.inDir = prev_cur;
	ret.outDir = cur_next;
	ret.leftCorner = Point::getCrossPoint(
		cur - prev_cur_right / 2.0, prev_cur, cur - cur_next_right / 2.0, cur_next);
	ret.rightCorner = Point::getCrossPoint(
		cur + prev_cur_right / 2.0, prev_cur, cur + cur_next_right / 2.0, cur_next);
	ret.isTurnLeft = curve >= 0;
	ret.height = height;
	return ret;
}
