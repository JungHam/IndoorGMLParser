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


template< class T > inline TVec3<T>::TVec3(const T x, const T y, const T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template< class T >	inline TVec3<T>::TVec3(const T vec[])
{
	memcpy(xyz, vec, 3 * sizeof(T));
}

template< class T > inline T TVec3<T>::length() const
{
	return (T)sqrt(x*x + y*y + z*z);
}

template< class T > inline T TVec3<T>::sqrLength() const
{
	return x*x + y*y + z*z;
}

template< class T > inline T TVec3<T>::dot(const TVec3<T>& vec) const
{
	return x*vec.x + y*vec.y + z*vec.z;
}

template< class T > inline TVec3<T> TVec3<T>::cross(const TVec3<T>& vec) const
{
	return TVec3<T>(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

template< class T > inline TVec3<T> TVec3<T>::normal() const
{
	const T len = length();
	const T tmp = (len != (T)0) ? ((T)1 / len) : (T)0;
	return TVec3<T>(x * tmp, y * tmp, z * tmp);
}

template< class T > inline TVec3<T>& TVec3<T>::normalEq()
{
	const T len = length();
	const T tmp = (len != (T)0) ? ((T)1 / len) : (T)0;
	x *= tmp;
	y *= tmp;
	z *= tmp;
	return *this;
}

template< class T > inline TVec3<T>& TVec3<T>::normalEq(const T length)
{
	const T len = TVec3<T>::length();
	const T tmp = (len != (T)0) ? length / len : (T)0;
	x *= tmp;
	y *= tmp;
	z *= tmp;
	return *this;
}

template< class T > inline TVec3<T> TVec3<T>::operator+(const TVec3<T>& rhs) const
{
	return TVec3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

template< class T >	inline TVec3<T> TVec3<T>::operator+(const T& _v) const
{
	return TVec3<T>(x + _v, y + _v, z + _v);
}

template< class T > inline TVec3<T> TVec3<T>::operator-(const TVec3<T>& rhs) const
{
	return TVec3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
}

template< class T > inline TVec3<T> TVec3<T>::operator-(const T& _v) const
{
	return TVec3<T>(x - _v, y - _v, z - _v);
}

template< class T >	inline TVec3<T> TVec3<T>::operator-() const
{
	return TVec3<T>(-x, -y, -z);
}

template< class T > inline TVec3<T> TVec3<T>::operator*(const T& rhs) const
{
	return TVec3<T>(x * rhs, y * rhs, z * rhs);
}

template< class T >	inline TVec3<T> TVec3<T>::operator*(const TVec3<T>& rhs) const
{
	return TVec3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
}

template< class T > inline TVec3<T> TVec3<T>::operator/(const T& rhs) const
{
	return TVec3<T>(x / rhs, y / rhs, z / rhs);
}

template< class T > inline TVec3<T> TVec3<T>::operator/(const TVec3<T>& rhs) const
{
	return TVec3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
}

template< class T > inline bool TVec3<T>::operator==(const TVec3<T>& rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

template< class T > inline bool TVec3<T>::operator!=(const TVec3<T>& rhs) const
{
	return x != rhs.x || y != rhs.y || z != rhs.z;
}

template< class T >	inline TVec3<T> operator*(const T& val, const TVec3<T>& vec)
{
	return TVec3<T>(vec.x * val, vec.y * val, vec.z * val);
}

template<class T> inline std::ostream& operator<<(std::ostream & os, const TVec3<T> & v)
{
	return os << std::fixed << v.x << " " << std::fixed << v.y << " " << std::fixed << v.z;
}

template<class T> inline std::istream& operator >> (std::istream & is, TVec3<T> & v) {
	return is >> v.x >> v.y >> v.z;
}

std::istream& operator>>(std::istream & is, TVec3d & v)
{
    return is >> v.x >> v.y >> v.z;
}

std::istream& operator>>(std::istream & is, TVec3f & v)
{
    return is >> v.x >> v.y >> v.z;
}

