#include "stdafx.h"
#include "HitCircles.h"

/// <summary>
/// Pre: None.
/// Post: Initialized HitCircles.
/// Initializes a new instance of the <see cref="HitCircles"/> class.
/// </summary>
HitCircles::HitCircles()
{
	circleX = 0;
	circleY = 0;
	time = 0;
	delay = 0;
	type = 1;
	state = true;
	dom = 0;
	beat = 0;
	drawn = false;

	indw = 0;
	indh = 0;
}

/// <summary>
/// Pre: None.
/// Post: Initialized HitCircles based on parameters.
/// Initializes a new instance of the <see cref="HitCircles"/> class.
/// </summary>
/// <param name="foo">The foo.</param>
HitCircles::HitCircles(TimeStamp* foo)
{
	TimeStamp bar = *foo;
	time = clock();
	type = 0;
	state = true;
	delay = bar.getDelay();
	dom = bar.getDominant();
	beat = bar.getFrequency();
	circleX = 0;
	circleY = 0;
	drawn = false;
	truetime = bar.trueTime();
	number = 0;

	min = bar.getMinutes();
	sec = bar.getSeconds();
	milli = bar.getMilliseconds();

	indw = 0;
	indh = 0;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Destoys HitCircles.
/// Finalizes an instance of the <see cref="HitCircles"/> class.
/// </summary>
HitCircles::~HitCircles()
{
	circleX = 0;
	circleY = 0;
	time = 0;
	delay = 0;
	type = 0;
	indw = 0;
	indh = 0;
	state = false;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: State of the Hitcircles is set.
/// Sets the state of the Hitcircles, whether it is true or false.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void HitCircles::setState(bool foo)
{
	state = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets state of Hitcircles.
/// Gets the state of HitCircles.
/// </summary>
/// <returns></returns>
bool HitCircles::getState()
{
	return state;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets dom. freq.
/// Gets the dominant frequency of the HitCircles.
/// </summary>
/// <returns></returns>
float HitCircles::getDom()
{
	return dom;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets beat.
/// Gets the beat of the HitCircle.
/// </summary>
/// <returns></returns>
float HitCircles::getBeat()
{
	return beat;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets the x coord.
/// Sets the x coordinate.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::setX(float foo)
{
	circleX = foo;
}

/// <summary>7
/// Pre: Initialized HitCircles.
/// Post: Sets the y coord.
/// Sets the y coordinate.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::setY(float foo)
{
	circleY = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the x coord.
/// Gets the x coordinate.
/// </summary>
/// <returns></returns>
float HitCircles::getX()
{
	return circleX;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the y coord.
/// Gets the y coordinate.
/// </summary>
/// <returns></returns>
float HitCircles::getY()
{
	return circleY;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the time.
/// Gets the time the HitCircle spawns.
/// </summary>
/// <returns></returns>
int HitCircles::getTime()
{
	return time + delay;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Adds the delay to the time.
/// Adds the delay to the time after pausing.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::addDelay(int foo)
{
	delay += foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets delay of HitCircles.
/// Gets the delay.
/// </summary>
/// <returns></returns>
int HitCircles::getDelay()
{
	return delay;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the type.
/// Gets the type of HitCircles.
/// </summary>
/// <returns></returns>
int HitCircles::getType()
{
	return type;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets the type.
/// Sets the type of HitCircles.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::setType(int foo)
{
	type = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets drawn.
/// Gets whether or not the HitCircle was previously drawn.
/// </summary>
/// <returns></returns>
bool HitCircles::getDrawn()
{
	return drawn;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets drawn.
/// Sets whether or not the HitCircle was drawn.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void HitCircles::setDrawn(bool foo)
{
	drawn = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Get true time.
/// Gets the true time of the HitCircle.  True time is the clock's time.
/// </summary>
/// <returns></returns>
int HitCircles::getTrueTime()
{
	return truetime;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the minutes.
/// Gets the minutes of the HitCircles.
/// </summary>
/// <returns></returns>
int HitCircles::getMin()
{
	return min;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the milliseconds.
/// Gets the milliseconds of the HitCircles.
/// </summary>
/// <returns></returns>
int HitCircles::getMilli()
{
	return milli;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the seconds.
/// Gets the seconds of the HitCircles.
/// </summary>
/// <returns></returns>
int HitCircles::getSec()
{
	return sec;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets time.
/// Sets the time of the HitCircle.
/// </summary>
/// <param name="bar">The bar.</param>
void HitCircles::setTime(int bar)
{
	milli += bar - time;
	sec = (milli / 1000) % 60;
	min = (sec / 60) % 60;
	sec -= min * 60;
	milli -= sec * 1000;
	time = bar;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets the number.
/// Sets the number of the HitCircle, from 1 to x.
/// </summary>
/// <param name="bar">The bar.</param>
void HitCircles::setNumber(int bar)
{
	number = bar;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the number.
/// Gets the number of the HitCircle, from 1 to x.
/// </summary>
/// <returns></returns>
int HitCircles::getNumber()
{
	return number;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets the colour.
/// Sets the colour of the HitCircle.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::setColour(int foo)
{
	colour = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Gets the colour.
/// Gets the colour of the HitCircle.
/// </summary>
/// <returns></returns>
int HitCircles::getColour()
{
	return colour;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets the width.
/// Sets the width of the HitCircle.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::setIndW(float foo)
{
	indw = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Sets the height.
/// Sets the height of the HitCircle.
/// </summary>
/// <param name="foo">The foo.</param>
void HitCircles::setIndH(float foo)
{
	indh = foo;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Returns width.
/// Gets the width of the HitCircle.
/// </summary>
/// <returns></returns>
float HitCircles::getIndW()
{
	return indw;
}

/// <summary>
/// Pre: Initialized HitCircles.
/// Post: Returns height.
/// Gets the height of the HitCircle.
/// </summary>
/// <returns></returns>
float HitCircles::getIndH()
{
	return indh;
}