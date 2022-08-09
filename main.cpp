#include <iostream>
#include "Canvas.h"
#include "TurtleController.h"

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void fractalTree(TurtleController& turtle,const float& angle, const float& distance,const int& gen,const float& startRotation = 60.f) 
{
	turtle.setFastUpdate(true);
	turtle.setSpeed(2000.f);
	turtle.penUp();
	turtle.setRotation(startRotation);
	turtle.setLinesColor(100, 100, 255);
	turtle.setPosition(-500, -400);
	turtle.penDown();
	turtle.hideTurtle();

	std::string start = std::string("X");
	std::map<std::string, std::string> rules;
	rules.emplace("X", "F+[[X]-X]D-F[-FX]+X");
	rules.emplace("F", "FF");

	for (int i = 0; i < gen; ++i) 
	{
		replaceAll(start, "X", rules["X"]);
		replaceAll(start, "F", rules["F"]);
	}

	for (char& c : start) 
	{
		switch (c)
		{
		case 'F':
			turtle.fastForward(distance);
			break;
		case '+':
			turtle.left(angle);
			break;
		case '[':
			turtle.pushState();
			break;
		case '-':
			turtle.right(angle);
			break;
		case ']':
			turtle.popState();
			break;
		case 'D':
			turtle.dot(1.f,255U);
		default:
			break;
		}
	}

}

void ex1(Canvas& c,const float& r = 100.f,const int& pointCount = 180) 
{
	TurtleController turtle(c.turlte);

	turtle.setLinesColor(100, 100, 255);
	turtle.setSpeed(300000.f);
	turtle.beginFill();
	turtle.circle(r, 180, true, pointCount);
	turtle.circle(r, 180, false, pointCount);
	turtle.circle(2*r, 180.f, false, pointCount);
	turtle.endFill();
	turtle.circle(2*r, 180.f, false, pointCount);
	turtle.right(90.f);
	turtle.penUp();
	turtle.forward(100.f);
	turtle.dot();
	turtle.forward(200.f);
	turtle.dot(15,100,100,255);
	turtle.hideTurtle();
}
float f(const float& x)
{
	return pow(x, 2);
};

float sin__(const float& x)
{
	return std::sin(x * 0.05) * 100;
}

void ex2(Canvas& c)
{
	TurtleController turtle(c.turlte);
	turtle.setSpeed(3000.f);
	turtle.setLinesColor(120, 120, 255);
	turtle.penUp();
	turtle.fastMove(-200, -200);
	//turtle.setPosition(-200, 0);
	turtle.penDown();
	for (int i = 0; i < 4; ++i)
	{
		turtle.forward(100.f);
		turtle.plotFunction(sin__, -3.1415926535 * 40, 3.1415926535 * 40, 1);
		turtle.setRotation(90 * i);
		turtle.forward(100.f);
		turtle.left(90.f);
	}
	turtle.left(45);
	turtle.forward(200);
	turtle.setLinesColor(255, 0, 0);
	turtle.plotFunction(sin__, -3.1415926535 * 40, 3.1415926535 * 80, 1);
	turtle.setRotation(45);
	turtle.setLinesColor(0, 255, 0);
	turtle.circle(100, 180, false);
	turtle.forward(50);
	turtle.setLinesColor(255, 0, 255);
	turtle.plotFunction(f, -10, 10, 0.1);
	turtle.plotFunction(f, -10, 10, 0.1);
	turtle.plotFunction(f, -10, 10, 0.1);
	turtle.plotFunction(f, -10, 10, 0.1);
}
void ex3(Canvas& c) 
{
	TurtleController turtle(c.turlte);
	c.setBackgroundColor(0, 0, 0);
	int a = 0;
	int b = 0;
	turtle.setSpeed(3000);
	turtle.penUp();
	turtle.setPosition(0, 200);
	turtle.penDown();
	turtle.setLinesColor(255, 0, 0);
	while (true)
	{
		turtle.forward(a);
		turtle.right(b);
		a += 3;
		b += 1;
		if (b == 210)
		{
			break;
		}
	}
	turtle.hideTurtle();
}
void ex4(Canvas& c) 
{
	TurtleController turtle(c.turlte);
	c.setBackgroundColor(0, 0, 0);
	turtle.setSpeed(2000);
	int r = 255;
	int g = 0;
	int b = 0;
	for (int i = 0; i < 255 * 2; ++i)
	{
		if (i < 255 / 3)
		{
			g += 3;
		}
		else if (i < 255 * 2 / 3)
		{
			r -= 3;
		}
		else if (i < 255)
		{
			b += 3;
		}
		else if (i < 255 * 4 / 3)
		{
			g -= 3;
		}
		else if (i < 255 * 5 / 3)
		{
			r += 3;
		}
		else
		{
			b -= 3;
		}
		turtle.forward(50 + i);
		turtle.right(91);
		turtle.setLinesColor(r, g, b);
	}
}

int main() 
{
	
	Canvas c(1600, 1000);
	ex4(c);
	//turtle.hideTurtle();

	c.run();
	return 0;
}