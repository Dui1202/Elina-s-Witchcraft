#include "Math.h"
#include <random>
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

int random(int p_startValue, int p_endValue) {
	// Define range
	int min = p_startValue;
	int max = p_endValue;

	// Initialize a random number generator 
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	// Generate random number in the range [min, max]
	int randomValue = distrib(gen);

	return randomValue;
}

