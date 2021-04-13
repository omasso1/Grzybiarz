#include "functions.h"
#include <math.h>
#include <iostream>
sf::Vector2f normalizeVector(sf::Vector2f& vector){
	float length = sqrt((double)vector.x * vector.x + (double)vector.y * vector.y);
	if (length > 0) {
		return sf::Vector2f(vector.x / length, vector.y / length);
	}
	else return sf::Vector2f(0,0);
}
