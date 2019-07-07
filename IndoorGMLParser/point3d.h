#ifndef _POINT3D_H_
#define _POINT3D_H_
#pragma once
#include <iostream>

using namespace std;

namespace indoorgml {
	class Point3D {
	public:
		union {
			double xyz[3];
			double rgb[3];
			struct { double x, y, z; };
			struct { double r, g, b; };
		};
		Point3D(double xp, double yp, double zp);
		Point3D();
		Point3D(double vec[]);

		inline double length() const;
		inline double sqrLength() const;


		Point3D  normal() const;
		Point3D& normalEq();
		Point3D& normalEq(const double length);
		Point3D operator+(const Point3D& rhs) const;
		Point3D operator+(const double _v) const;
		Point3D operator-(const Point3D& rhs) const;
		Point3D operator-(const double _v) const;
		Point3D operator-() const;
		Point3D operator*(const Point3D& rhs) const;
		Point3D operator*(const double rhs) const;

		Point3D operator/(const Point3D& rhs) const;
		Point3D operator/(const double rhs) const;
		Point3D Point3D::cross(const Point3D& vec) const;
		inline bool operator==(const Point3D& rhs) const;
		inline bool operator!=(const Point3D& rhs) const;

		inline operator double*() { return xyz; }
		inline operator const double*() const { return xyz; }
		void unitary();
		double Point3D::scalar(const Point3D& vec) const;

	};
	

	
}
#endif
