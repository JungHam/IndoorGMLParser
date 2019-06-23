#pragma once
#include <sstream>
#include <iostream>
#include <string.h>

/*
// 2D vector class.

template< class T > class TVec2
{
public:
T x;
T y;

public:
TVec2(const TVec2<T>& o) {
this->x = o.x;
this->y = o.y;
}

TVec2(const T x = (T)0, const T y = (T)0);
TVec2(const T vec[]);

TVec2 operator+(const TVec2<T>& v) const;
TVec2 operator-(const TVec2<T>& v) const;
TVec2 operator-() const;
TVec2 operator*(const T& v) const;
TVec2 operator*(const TVec2<T>& v) const;
TVec2 operator/(const T& v) const;
TVec2 operator/(const TVec2<T>& v) const;

bool operator==(const TVec2<T>& v) const;
bool operator!=(const TVec2<T>& v) const;
};

typedef TVec2< float >			TVec2f;
typedef TVec2< double >			TVec2d;


*/


// 3D vector class.

template< class T > class TVec3
{
public:
	union
	{
		T xyz[3];
		T rgb[3];
		struct { T x, y, z; };
		struct { T r, g, b; };
	};

public:
	TVec3(const T x = (T)0, const T y = (T)0, const T z = (T)0);
	TVec3(const T vec[]);

	inline T length() const;
	inline T sqrLength() const;

	T dot(const TVec3<T>& vec) const;
	TVec3 cross(const TVec3<T>& vec) const;

	TVec3  normal() const;
	TVec3& normalEq();
	TVec3& normalEq(const T length);

	TVec3 operator+(const TVec3<T>& rhs) const;
	TVec3 operator+(const T& _v) const;
	TVec3 operator-(const TVec3<T>& rhs) const;
	TVec3 operator-(const T& _v) const;
	TVec3 operator-() const;
	TVec3 operator*(const T& rhs) const;
	TVec3 operator*(const TVec3<T>& rhs) const;
	TVec3 operator/(const T& rhs) const;
	TVec3 operator/(const TVec3<T>& rhs) const;

	inline bool operator==(const TVec3<T>& rhs) const;
	inline bool operator!=(const TVec3<T>& rhs) const;

	inline operator T*() { return xyz; }
	inline operator const T*() const { return xyz; }
};

typedef TVec3< float >			TVec3f;
typedef TVec3< double >			TVec3d;

