/**
 * @file	Coordinates.cpp
 *
 * @brief	Implements the coordinates class.
 */

#include "stdafx.h"
#include "Coordinates.h"

 /// <summary>
 /// Pre: None.
 /// Post: Initialized Coordinates.
 /// Initializes a new instance of the <see cref="Coordinates"/> class.
 /// </summary>
Coordinates::Coordinates()
{
	x = 0;
	y = 0;
	maxed = false;
}

/// <summary>
/// Pre: None.
/// Post: Initalized Coordinates based on parameters.
/// Initializes a new instance of the <see cref="Coordinates"/> class.
/// </summary>
/// <param name="foo">The foo.</param>
/// <param name="bar">The bar.</param>
Coordinates::Coordinates(int foo, int bar)
{
	x = foo;
	y = bar;
	maxed = false;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Deletes certain variables.
/// Finalizes an instance of the <see cref="Coordinates"/> class.
/// </summary>
Coordinates::~Coordinates()
{
	x = 0;
	y = 0;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Gets x.
/// Gets the x.
/// </summary>
/// <returns></returns>
int Coordinates::getX()
{
	return x;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Gets y.
/// Gets the y.
/// </summary>
/// <returns></returns>
int Coordinates::getY()
{
	return y;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Sets x.
/// Sets the x.
/// </summary>
/// <param name="foo">The foo.</param>
void Coordinates::setX(int foo)
{
	x = foo;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Sets y.
/// Sets the y.
/// </summary>
/// <param name="foo">The foo.</param>
void Coordinates::setY(int foo)
{
	y = foo;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Sets maxed.
/// Sets if the coordinate was maxed.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void Coordinates::setMaxed(bool foo)
{
	maxed = foo;
}

/// <summary>
/// Pre: Initialized Coordinates.
/// Post: Gets maxed.
/// Gets if the coordinate was maxed.
/// </summary>
/// <returns></returns>
bool Coordinates::getMaxed()
{
	return maxed;
}