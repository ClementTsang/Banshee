#ifndef _HITCIRCLES_H
#define _HITCIRCLES_H

class HitCircles
{
public:
	HitCircles();
	HitCircles(TimeStamp*);
	~HitCircles();
	void setState(bool);
	bool getState();
	float getDom();
	float getBeat();
	void setX(float);
	void setY(float);
	float getX();
	float getY();
	int getTime();
	void addDelay(int);
	int getDelay();
	int getType();
	void setType(int);
	bool getDrawn();
	void setDrawn(bool);
	int getTrueTime();
	int getMin();
	int getMilli();
	int getSec();
	void setTime(int);
	void setNumber(int);
	int getNumber();
	void setColour(int);
	int getColour();
	void setIndW(float);
	void setIndH(float);
	float getIndW();
	float getIndH();
private:
	float circleX;
	float circleY;
	int time; //When it should be pressed
	int delay;  //How much it should be delayed
	int type;  //How close it was to being pressed.  Type 0 means not drawn.  1 means drawn, very early.  2 means perfect.  3 means early or late.
	bool state; //If it is pressed or not
	float dom;
	float beat;
	bool drawn;
	int truetime;

	int sec;
	int min;
	int milli;

	int number, colour;

	float indw, indh;

	TimeStamp stamp;
};

#endif