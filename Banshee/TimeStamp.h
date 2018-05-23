#ifndef TIMESTAMP_H
#define TIMESTAMP_H

class TimeStamp
{
public:
	TimeStamp();
	TimeStamp(int, int, int);
	TimeStamp(int, int, int, float);
	TimeStamp(int, int, int, float, float);
	TimeStamp(int, int, int, float, float, int);
	~TimeStamp();

	void setTime(int, int, int);
	void setSeconds(int);
	void setMinutes(int);
	void setMilliseconds(int);
	void setFrequency(float);

	int getSeconds();
	int getMinutes();
	int getMilliseconds();
	float getFrequency();
	float getDominant();
	int trueTime();

	void setTimeWithFrequency(int, int, int, float);

	void setDelay(int);
	int getDelay();
private:
	int minutes;
	int seconds;
	int milliseconds;
	float beatFrequency;
	float domVal;
	int delay;
};

#endif