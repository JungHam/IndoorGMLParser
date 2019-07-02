#pragma once
#include <sstream>
#include <iostream>
#include <string.h>
#include "Point2D.h"

namespace indoorgml {
	Point2D::Point2D(double x, double y)
	{
		this->x = x;
		this->y = y;

	}
	Point2D::Point2D(double vec[])
	{
		memcpy(xy, vec, 2 * sizeof(double));
	}

	double Point2D::length() const
	{
		return (double)sqrt(x*x + y*y);
	}

	double Point2D::sqrLength() const
	{
		return x*x + y*y;
	}


	Point2D Point2D::normal() const
	{
		const double len = length();
		const double tmp = (len != (double)0) ? ((double)1 / len) : (double)0;
		return Point2D(x * tmp, y * tmp);
	}

	Point2D& Point2D::normalEq()
	{
		const double len = length();
		const double tmp = (len != (double)0) ? ((double)1 / len) : (double)0;
		x *= tmp;
		y *= tmp;
		z *= tmp;
		return *this;
	}

	Point2D& Point2D::normalEq(const double length)
	{
		const double len = Point2D::length();
		const double tmp = (len != (double)0) ? length / len : (double)0;
		x *= tmp;
		y *= tmp;
		return *this;
	}

	Point2D Point2D::operator+(const Point2D& rhs) const
	{
		return Point2D(x + rhs.x, y + rhs.y);
	}

	Point2D Point2D::operator+(const double _v) const
	{
		return Point2D(x + _v, y + _v);
	}

	Point2D Point2D::operator-(const Point2D& rhs) const
	{
		return Point2D(x - rhs.x, y - rhs.y);
	}

	Point2D Point2D::operator-(const double _v) const
	{
		return Point2D(x - _v, y - _v);
	}

	Point2D Point2D::operator-() const
	{
		return Point2D(-x, -y);
	}

	Point2D Point2D::operator*(const double rhs) const
	{
		return Point2D(x * rhs, y * rhs);
	}

	Point2D Point2D::operator*(const Point2D& rhs) const
	{
		return Point2D(x * rhs.x, y * rhs.y);
	}

	Point2D Point2D::operator/(const double rhs) const
	{
		return Point2D(x / rhs, y / rhs);
	}

	Point2D Point2D::operator/(const Point2D& rhs) const
	{
		return Point2D(x / rhs.x, y / rhs.y);
	}

	inline bool Point2D::operator==(const Point2D& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	inline bool Point2D::operator!=(const Point2D& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}


	std::ostream& operator<<(std::ostream & os, const Point2D & v)
	{
		return os << std::fixed << v.x << " " << std::fixed << v.y << " ";
	}

	std::istream& operator >> (std::istream & is, Point2D & v) {
		return is >> v.x >> v.y ;
	}

	void Point2D::unitary() {
		double module = x*x + y*y;
		module = sqrt(module);
		x = x / module;
		y = y / module;
	}

	double Point2D::scalar(const Point2D& vec) const {
		return x * vec.x + y * vec.y;
	}
}


