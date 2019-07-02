#pragma once
#include <sstream>
#include <iostream>
#include <string.h>
#include "point3d.h"

// 2D vector class.

/*
template< class T > inline TVec2<T>::TVec2(const T x, const T y)
{
this->x = x;
this->y = y;
}

template< class T >	inline TVec2<T>::TVec2(const T vec[])
{
x = vec[0];
y = vec[1];
}

template< class T >	inline TVec2<T> TVec2<T>::operator+(const TVec2<T>& v) const
{
return TVec2<T>(x + v.x, y + v.y);
}

template< class T >	inline TVec2<T> TVec2<T>::operator-(const TVec2<T>& v) const
{
return TVec2<T>(x - v.x, y - v.y);
}

template< class T >	inline TVec2<T> TVec2<T>::operator-() const
{
return TVec2<T>(-x, -y);
}

template< class T >	inline TVec2<T> TVec2<T>::operator*(const T& v) const
{
return TVec2<T>(x * v, y * v);
}

template< class T >	inline TVec2<T> TVec2<T>::operator*(const TVec2<T>& v) const
{
return TVec2<T>(x * v.x, y * v.y);
}

template< class T >	inline TVec2<T> TVec2<T>::operator/(const T& v) const
{
return TVec2<T>(x / v, y / v);
}

template< class T >	inline TVec2<T> TVec2<T>::operator/(const TVec2<T>& v) const
{
return TVec2<T>(x / v.x, y / v.y);
}

template< class T >	inline bool TVec2<T>::operator==(const TVec2<T>& v) const
{
return x == v.x && y == v.y;
}

template< class T >	inline bool TVec2<T>::operator!=(const TVec2<T>& v) const
{
return x != v.x || y != v.y;
}

template< class T >	inline TVec2<T> operator*(const T& val, const TVec2<T>& vec)
{
return TVec2<T>(vec.x * val, vec.y * val);
}

template<class T> inline std::ostream& operator<<(std::ostream & os, TVec2<T> const & v)
{
return os << std::fixed << v.x << " " << std::fixed << v.y;
}

template<class T> inline std::istream& operator >> (std::istream & is, TVec2<T> & v)
{
return is >> v.x >> v.y;
}
*/

// 3D vector class.
namespace indoorgml {
	Point3D::Point3D(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point3D::Point3D(double vec[])
	{
		memcpy(xyz, vec, 3 * sizeof(double));
	}

	double Point3D::length() const
	{
		return (double)sqrt(x*x + y*y + z*z);
	}

	double Point3D::sqrLength() const
	{
		return x*x + y*y + z*z;
	}

	Point3D Point3D::cross(const Point3D& vec) const
	{
		return Point3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	Point3D Point3D::normal() const
	{
		const double len = length();
		const double tmp = (len != (double)0) ? ((double)1 / len) : (double)0;
		return Point3D(x * tmp, y * tmp, z * tmp);
	}

	Point3D& Point3D::normalEq()
	{
		const double len = length();
		const double tmp = (len != (double)0) ? ((double)1 / len) : (double)0;
		x *= tmp;
		y *= tmp;
		z *= tmp;
		return *this;
	}

	Point3D& Point3D::normalEq(const double length)
	{
		const double len = Point3D::length();
		const double tmp = (len != (double)0) ? length / len : (double)0;
		x *= tmp;
		y *= tmp;
		z *= tmp;
		return *this;
	}

	Point3D Point3D::operator+(const Point3D& rhs) const
	{
		return Point3D(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Point3D Point3D::operator+(const double _v) const
	{
		return Point3D(x + _v, y + _v, z + _v);
	}

	Point3D Point3D::operator-(const Point3D& rhs) const
	{
		return Point3D(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Point3D Point3D::operator-(const double _v) const
	{
		return Point3D(x - _v, y - _v, z - _v);
	}

	Point3D Point3D::operator-() const
	{
		return Point3D(-x, -y, -z);
	}

	Point3D Point3D::operator*(const double rhs) const
	{
		return Point3D(x * rhs, y * rhs, z * rhs);
	}

	Point3D Point3D::operator*(const Point3D& rhs) const
	{
		return Point3D(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	Point3D Point3D::operator/(const double rhs) const
	{
		return Point3D(x / rhs, y / rhs, z / rhs);
	}

	Point3D Point3D::operator/(const Point3D& rhs) const
	{
		return Point3D(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	inline bool Point3D::operator==(const Point3D& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	inline bool Point3D::operator!=(const Point3D& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z;
	}

	
	std::ostream& operator<<(std::ostream & os, const Point3D & v)
	{
		return os << std::fixed << v.x << " " << std::fixed << v.y << " " << std::fixed << v.z;
	}

	std::istream& operator >> (std::istream & is, Point3D & v) {
		return is >> v.x >> v.y >> v.z;
	}

	void Point3D::unitary() {
		double module = x*x + y*y + z*z;
		module = sqrt(module);
		x = x / module;
		y = y / module;
		z = z / module;
	}

	double Point3D::scalar(const Point3D& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}
}


