/**
 * @file	TimeStamp.cpp
 *
 * @brief	Implements the time stamp class.
 */

#include "stdafx.h"
#include "TimeStamp.h"

TimeStamp::TimeStamp()
{
	minutes = 0;
	seconds = 0;
	milliseconds = 0;
	beatFrequency = 0.0f;
	domVal = 0.0f;
	delay = 0;
}

/**
 * @fn	TimeStamp::~TimeStamp()
 *
 * @brief	Destructor.
 *
 * @author	Clement
 * @date	15/01/2017
 */
TimeStamp::~TimeStamp()
{
	minutes = 0;
	seconds = 0;
	milliseconds = 0;
	beatFrequency = 0.0f;
	domVal = 0.0f;
	delay = 0;
}

/**
 * @fn	TimeStamp::TimeStamp(int m, int s, int mil)
 *
 * @brief	Constructor.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m  	The int to process.
 * @param	s  	The int to process.
 * @param	mil	The mil.
 */
TimeStamp::TimeStamp(int m, int s, int mil)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = 0.0f;
	domVal = 0.0f;
	delay = 0;
}

/**
 * @fn	TimeStamp::TimeStamp(int m, int s, int mil, float f)
 *
 * @brief	Constructor.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m  	The int to process.
 * @param	s  	The int to process.
 * @param	mil	The mil.
 * @param	f  	The float to process.
 */
TimeStamp::TimeStamp(int m, int s, int mil, float f)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = f;
	domVal = 0.0f;
	delay = 0;
}

/**
 * @fn	TimeStamp::TimeStamp(int m, int s, int mil, float f, float g)
 *
 * @brief	Constructor.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m  	The int to process.
 * @param	s  	The int to process.
 * @param	mil	The mil.
 * @param	f  	The float to process.
 * @param	g  	The float to process.
 */
TimeStamp::TimeStamp(int m, int s, int mil, float f, float g)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = f;
	domVal = g;
	delay = 0;
}

/**
 * @fn	TimeStamp::TimeStamp(int m, int s, int mil, float f, float g, int d)
 *
 * @brief	Constructor.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m  	The int to process.
 * @param	s  	The int to process.
 * @param	mil	The mil.
 * @param	f  	The float to process.
 * @param	g  	The float to process.
 * @param	d  	The int to process.
 */
TimeStamp::TimeStamp(int m, int s, int mil, float f, float g, int d)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = f;
	domVal = g;
	delay = d;
}

/**
 * @fn	void TimeStamp::setTime(int m, int s, int mil)
 *
 * @brief	Sets a time.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m  	The int to process.
 * @param	s  	The int to process.
 * @param	mil	The mil.
 */
void TimeStamp::setTime(int m, int s, int mil)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = 0.0f;
	domVal = 0.0f;
	delay = 0;
}

/**
 * @fn	void TimeStamp::setMinutes(int m)
 *
 * @brief	Sets the minutes.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m	The int to process.
 */
void TimeStamp::setMinutes(int m)
{
	minutes = m;
}

/**
 * @fn	void TimeStamp::setSeconds(int s)
 *
 * @brief	Sets the seconds.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	s	The int to process.
 */
void TimeStamp::setSeconds(int s)
{
	seconds = s;
}

/**
 * @fn	void TimeStamp::setMilliseconds(int mil)
 *
 * @brief	Sets the milliseconds.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	mil	The mil.
 */
void TimeStamp::setMilliseconds(int mil)
{
	milliseconds = mil;
}

/**
 * @fn	void TimeStamp::setFrequency(float f)
 *
 * @brief	Sets a frequency.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	f	The float to process.
 */
void TimeStamp::setFrequency(float f)
{
	beatFrequency = f;
}

/**
 * @fn	void TimeStamp::setTimeWithFrequency(int m, int s, int mil, float f)
 *
 * @brief	Sets time with frequency.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	m  	The int to process.
 * @param	s  	The int to process.
 * @param	mil	The mil.
 * @param	f  	The float to process.
 */
void TimeStamp::setTimeWithFrequency(int m, int s, int mil, float f)
{
	minutes = m;
	seconds = s;
	milliseconds = mil;
	beatFrequency = f;
}

/**
 * @fn	void TimeStamp::setDelay(int foo)
 *
 * @brief	Sets a delay.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @param	foo	The foo.
 */
void TimeStamp::setDelay(int foo)
{
	delay = foo;
}

/**
 * @fn	int TimeStamp::getDelay()
 *
 * @brief	Gets the delay.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	The delay.
 */
int TimeStamp::getDelay()
{
	return delay;
}

/**
 * @fn	int TimeStamp::getMinutes()
 *
 * @brief	Gets the minutes.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	The minutes.
 */
int TimeStamp::getMinutes()
{
	return minutes;
}

/**
 * @fn	int TimeStamp::getSeconds()
 *
 * @brief	Gets the seconds.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	The seconds.
 */
int TimeStamp::getSeconds()
{
	return seconds;
}

/**
 * @fn	int TimeStamp::getMilliseconds()
 *
 * @brief	Gets the milliseconds.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	The milliseconds.
 */
int TimeStamp::getMilliseconds()
{
	return milliseconds;
}

/**
 * @fn	float TimeStamp::getFrequency()
 *
 * @brief	Gets the frequency.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	The frequency.
 */
float TimeStamp::getFrequency()
{
	return beatFrequency;
}

/**
 * @fn	float TimeStamp::getDominant()
 *
 * @brief	Gets the dominant.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	The dominant.
 */
float TimeStamp::getDominant()
{
	return domVal;
}

/**
 * @fn	int TimeStamp::trueTime()
 *
 * @brief	True time.
 *
 * @author	Clement
 * @date	15/01/2017
 *
 * @return	An int.
 */
int TimeStamp::trueTime()
{
	return (milliseconds + seconds * 1000 + minutes * 60 * 1000);
}