/*********************************************************************

This file is part of Spirograph (GNU GPL) - https://www.youtube.com/user/Muzkaw).

Spirograph is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Spirograph is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Spirograph. If not, see <http://www.gnu.org/licenses/>.

Spirograph codded by Muzkaw : https://www.youtube.com/user/Muzkaw
You need to link SFML 2.0 or above to run the program

********************************************************************/

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Utility.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_NBARMS 4
#define TIME_SCALE 50
#define ADD_VERTEX_TIME 0.005
#define MAX_COLOR_TIME 2*2

using namespace std ;
using namespace sf ;

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 32 ;
	RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Spirograph",Style::Fullscreen,settings);
	window.setMouseCursorVisible(false);
	//window.setFramerateLimit(50) ;
	bool endProgram = false ;
	Color tracerColor = Color::Color(100,130,155) ;
	Color painterColor = Color::Color(200,200,200) ;
	View view ;
	
	while(!endProgram)
	{
		srand(time(NULL));
		int nbArms = rand()%MAX_NBARMS+2;
		vector<int> lg(nbArms) ;
		vector<int> w(nbArms) ;
		for(int i(0) ; i < nbArms ; i++)
		{
			while(lg[i]==0)
				lg[i]=rand()%300-150 ;
		}
		for(int i(0) ; i < nbArms ; i++)
		{
			while(w[i]==0)
				w[i]=rand()%40-20 ;
		}
				
		vector<RectangleShape> l(nbArms) ;
		for(int i(0) ; i < nbArms ; i++)
		{
			l[i].setSize(Vector2f(2,lg[i])) ;
			l[i].setOrigin(0.5,lg[i]) ;
			l[i].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
			l[i].setFillColor(Color::Color(125,120,175)) ;
		}
		
		int pgcd = pgcd2(w) ;
		float drawingTime = (360.f / ((float)pgcd*TIME_SCALE))+0.1 ;
		
		VertexArray tracer ;
		tracer.setPrimitiveType(LinesStrip) ;
		VertexArray painter ;
		painter.setPrimitiveType(TrianglesFan) ;
		painter.append(Vertex(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2),painterColor)) ;
		
		Clock frameTime ;
		Clock time ;
		Clock addedVertex ;

		float deltaTime = 0;
				
		Event event ;

		while(window.isOpen() && time.getElapsedTime().asSeconds() < 2*drawingTime && !Keyboard::isKeyPressed(Keyboard::R))
		{
			while (window.pollEvent(event))
			{				
			}
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				endProgram = true ;
				break ;
			}

			for(int i(0) ; i < nbArms ; i++)
			{
				w[i] *= TIME_SCALE ;
				if(i>=1)
				{
					l[i].setPosition(l[i-1].getPosition()+Vector2f(lg[i-1]*sin(l[i-1].getRotation() * PI/180) , lg[i-1]*-cos(l[i-1].getRotation() * PI/180))) ;
				}
				l[i].rotate(w[i]*deltaTime);
				w[i] /= TIME_SCALE ;
			}

			Vertex vert(l[nbArms-1].getPosition()+Vector2f(lg[nbArms-1]*sin(l[nbArms-1].getRotation() * PI/180) , lg[nbArms-1]*-cos(l[nbArms-1].getRotation() * PI/180)),tracerColor) ;

			if(addedVertex.getElapsedTime().asSeconds() > ADD_VERTEX_TIME && time.getElapsedTime().asSeconds()<drawingTime+2*ADD_VERTEX_TIME)
			{
				tracer.append(vert) ;
				vert.color = painterColor ;
				painter.append(vert) ;
				addedVertex.restart() ;
			}
		
			window.clear(Color::Black) ;
			window.draw(painter) ;
			window.draw(tracer) ;
			if(time.getElapsedTime().asSeconds()>drawingTime)
			{
				for(int i(0) ; i < nbArms ; i++)
				{
					window.draw(l[i]) ;
				}
			}
			window.display() ;

			deltaTime = frameTime.restart().asSeconds() ;
		}
	}
}