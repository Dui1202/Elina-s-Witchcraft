#include "Math.h"
#include<iostream>

Vector2f::Vector2f()
	:x(0),y(0)
{}

Vector2f::Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
{}

void Vector2f::print() {
	std::cout << x << ' ' << y << std::endl;
}

void Vector2f::normalize() {
	if (x != 0 || y!= 0) {
		float length = sqrt(x * x + y * y);
		x /= length;
		y /= length;
	}
}

Vector2f Vector2f::operator+(const Vector2f& other) const {
	return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f& other) const {
	return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator*(float other) const {
	return Vector2f(x * other, y * other);
}

Vector2f Vector2f::operator/(float other) const {
	return Vector2f(x / other, y / other);
}

