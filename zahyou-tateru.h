#ifndef ZAHYOU_TATERU_H_GUARD_E0DA0E2F_DFFF_46D5_B9E2_055BC689BD8A
#define ZAHYOU_TATERU_H_GUARD_E0DA0E2F_DFFF_46D5_B9E2_055BC689BD8A

struct Point {
	double x, y;
	Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator-() const;
	Point operator*(double scale) const;
	Point operator/(double scale) const;

	// 内積
	double operator*(const Point& p) const;
	// z成分0を追加して3次元にしたベクトルの外積のz成分
	double operator/(const Point& p) const;
	// 向きをそのままに長さを1にしたやつ
	Point normalize() const;

	static Point getCrossPoint(const Point& p1, const Point& v1, const Point& p2, const Point& v2);
};

struct PointWithHeight {
	Point point;
	double height;
	PointWithHeight(double x_ = 0, double y_ = 0, double height_ = 0) :
		point(x_, y_), height(height_) {}
	PointWithHeight(const Point& p, double height_ = 0) : point(p), height(height_) {}
};

struct Corner {
	Point centerPoint, inDir, outDir;
	Point leftCorner, rightCorner;
	double height;
	bool isTurnLeft;

	static Corner createCorner(const Point& prev, const Point& cur, const Point& next, double width, double height);
};

#endif
