//This file is part of Spirograph(GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <iostream>

using namespace sf ;
using namespace std ;

Color colorInterpolation(Color initialColor, Color aimColor, float time, float timeSpent, float deltaTime)
{
	Color color = initialColor ;
	color.r = initialColor.r + ((aimColor.r-initialColor.r)*timeSpent)/time ;
	color.g = initialColor.g + ((aimColor.g-initialColor.g)*timeSpent)/time ;
	color.b = initialColor.b + ((aimColor.b-initialColor.b)*timeSpent)/time ;
	if(timeSpent>=time)
	{
		color = aimColor ;
	}
	return color ;
}

void interpolation(float &x, float y, float time, float deltaTime)
{
	x += (2.f*(y-x)*deltaTime)/time ;
}

float determinant(Vector2f const& u, Vector2f const& v) 
{
	float result = u.x*v.y - u.y*v.x ;
	return result ;
}

float dotProduct(Vector2f const& u, Vector2f const& v)
{
	return u.x*v.x + u.y*v.y ;
}

float Angle(Vector2f const& v1, Vector2f const& v2)
{
	float angle = atan2(determinant(v1,v2), dotProduct(v1,v2))*180/PI ;
	if(angle<0)
		angle = 360 + angle ;
	return angle ;
}

int pgcd(int a, int b)
{
	a=abs(a) ;
	b=abs(b) ;
	if(a==0) return b ;
	else if(b==0) return a ;
	else while(a!=b)
	{
		if(a>b)
			a-=b ;
		else
			b-=a ;
	}
	return a ;
}

int pgcd2(vector<int> nb)
{
	if(nb.size()<2)
		return 0 ;
	else
	{
		int result = pgcd(nb[0],nb[1]) ;
		for(int i(0) ; i < nb.size() ; i++)
		{
			result = pgcd(nb[i],result) ;
		}
		return result ;
	}
}

int interpolation(int& x, int y, float time, float deltaTime)
{
	return x += (2.f*(y-x)*deltaTime)/time ;
}

float clamp(float value, float min, float max) 
{
	float result ;
	if(value > max)
		result = max ;
	else if(value < min)
		result = min ;
	else
		result = value ;
	return result ;
}