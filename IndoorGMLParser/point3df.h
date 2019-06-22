#pragma once
#include <iostream>

using namespace std;

namespace indoorgml {
	class Point3Df {
		union {
			float xyz[3];
			float rgb[3];
			struct { float x, y, z; };
			struct { float r, g, b; };
		};
		Point3Df(float xp, float yp, float zp);
		Point3Df();
		Point3Df(float vec[]);

		inline float length() const;
		inline float sqrLength() const;


		Point3Df  normal() const;
		Point3Df& normalEq();
		Point3Df& normalEq(const float length);
		Point3Df operator+(const Point3Df& rhs) const;
		Point3Df operator+(const float _v) const;
		Point3Df operator-(const Point3Df& rhs) const;
		Point3Df operator-(const float _v) const;
		Point3Df operator-() const;
		Point3Df operator*(const Point3Df& rhs) const;
		Point3Df operator*(const float rhs) const;
		Point3Df operator/(const Point3Df& rhs) const;
		Point3Df operator/(const float rhs) const;

		inline bool operator==(const Point3Df& rhs) const;
		inline bool operator!=(const Point3Df& rhs) const;

		inline operator float*() { return xyz; }
		inline operator const float*() const { return xyz; }


	};
	

	
}
