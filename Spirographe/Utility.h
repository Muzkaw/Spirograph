//This file is part of Spirograph(GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define PI 3.14159265359

using namespace sf ;
using namespace std ;

Color colorInterpolation(Color initialColor, Color aimColor, float time, float timeSpent, float deltaTime) ;
void interpolation(float &x, float y, float time, float deltaTime);
float determinant(Vector2f const& u, Vector2f const& v) ;
float dotProduct(Vector2f const& u, Vector2f const& v) ;
float Angle(Vector2f const& v1, Vector2f const& v2) ;
int pgcd(int a, int b) ;
int pgcd2(vector<int> nb) ;
int interpolation(int& x, int y, float time, float deltaTime) ;
float clamp(float value, float min, float max) ;
