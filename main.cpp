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
			turtle.fastLeft(angle);
			break;
		case '[':
			turtle.pushState();
			break;
		case '-':
			turtle.fastRight(angle);
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
	TurtleController turtle(c.newTurtle("1"));

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
	TurtleController turtle(c.newTurtle("1"));
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
	TurtleController turtle(c.newTurtle("1"));
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
	TurtleController turtle(c.newTurtle("1"));
	c.setBackgroundColor(0, 0, 0);
	turtle.setSpeed(2000);
	turtle.setFastUpdate(true);
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
		turtle.fastForward(50 + i);
		turtle.fastRight(91);
		turtle.setLinesColor(r, g, b);

	}
}

void DragonCurve(Canvas& canvas,const std::string& turtleName,const float& len,const float& angle, const int& iter = 3) 
{
	TurtleController turtle;
	if (canvas.isExistTurtle(turtleName)) 
	{
		turtle = canvas.getTurtle(turtleName);
	}
	else 
	{
		turtle = canvas.newTurtle(turtleName);
	}
	turtle.setFastUpdate(true);
	std::string start = "FX";

	for (int i = 0; i < iter; ++i) 
	{
		std::string tmp;
		tmp.reserve(start.size() * 5);
		for (int i = 0; i < start.size(); ++i) 
		{
			switch (start[i])
			{
			case 'X':
				tmp.append("X+YF");
				break;
			case 'Y':
				tmp.append("FX-Y");
				break;
			default:
				tmp.push_back(start[i]);
				break;
			}
		}
		start = std::move(tmp);
	}
	for (const char& c : start) 
	{
		switch (c)
		{
		case 'F':
			turtle.fastForward(len);
			break;
		case '+':
			turtle.fastRight(angle);
			break;
		case '-':
			turtle.fastLeft(angle);
			break;
		default:
			break;
		}
	}

}

void ex5(Canvas& c) 
{
	TurtleController t1 = c.newTurtle("t1");
	TurtleController t2 = c.newTurtle("t2");

	const float R = 100.f;
	const float zoom = 100.f;
	const float PI = 3.1415926535f;
	const sf::Color color1 = sf::Color::Red;
	const sf::Color color2 = sf::Color::Blue;
	t1.setLinesColor(color1.r, color1.g, color1.b);
	t2.setLinesColor(color2.r, color2.g, color2.b);
	t1.penUp();
	t2.penUp();
	t1.setPosition(0, -2 * R);
	t2.setPosition(0, 2 * R);
	t1.penDown();
	t2.penDown();
	t1.beginFill();
	t2.beginFill();
	t2.setRotation(180.f);
	t1.circle(R, 180.f);
	t1.circle(R, 180.f, 0);
	t2.circle(R, 180.f);
	t2.circle(R, 180.f, 0);
	t1.circle(2 * R, 180, 0);
	t2.circle(2 * R, 180, 0);
	t2.endFill();
	t1.endFill();
	t1.hideTurtle();
	t2.hideTurtle();
}

float func(const float& x) 
{
	return pow((x), 2);
}

int main() 
{
	
	Canvas c(1600, 1000);
	c.newTurtle("turtle");
	float zoom = 10;
	float start = -5;
	start *= zoom;
	float end = -start;
	const float step = 1.f;
	c.getTurtle("turtle").penUp();
	c.getTurtle("turtle").setPosition(start, func(start/zoom)*zoom);
	c.getTurtle("turtle").penDown();
	c.getTurtle("turtle").plotFunction([zoom](const float& x)->float
		{
			return func(x / zoom) * zoom;
		}, start, end);

	c.run();
	return 0;
}