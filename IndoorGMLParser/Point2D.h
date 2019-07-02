#ifndef _POINT2D_H_
#define _POINT2D_H_
#pragma once
#include <iostream>

using namespace std;

namespace indoorgml {
	class Point2D {
	public:
		union {
			double xy[2];
			double rgb[3];
			struct { double x, y; };
			struct { double r, g, b; };
		};
		Point2D(double xp, double yp);
		Point2D();
		Point2D(double vec[]);

		inline double length() const;
		inline double sqrLength() const;


		Point2D  normal() const;
		Point2D& normalEq();
		Point2D& normalEq(const double length);
		Point2D operator+(const Point2D& rhs) const;
		Point2D operator+(const double _v) const;
		Point2D operator-(const Point2D& rhs) const;
		Point2D operator-(const double _v) const;
		Point2D operator-() const;
		Point2D operator*(const Point2D& rhs) const;
		Point2D operator*(const double rhs) const;

		Point2D operator/(const Point2D& rhs) const;
		Point2D operator/(const double rhs) const;
		Point2D Point2D::cross(const Point2D& vec) const;
		double Point2D::scalar(const Point2D& vec) const;
		inline bool operator==(const Point2D& rhs) const;
		inline bool operator!=(const Point2D& rhs) const;

		inline operator double*() { return xy; }
		inline operator const double*() const { return xy; }

		void unitary();

	};



}
#endif
