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

	// ����
	double operator*(const Point& p) const;
	// z����0��ǉ�����3�����ɂ����x�N�g���̊O�ς�z����
	double operator/(const Point& p) const;
	// ���������̂܂܂ɒ�����1�ɂ������
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
