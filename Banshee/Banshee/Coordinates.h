#ifndef COORD
#define COORD
class Coordinates
{
public:
	Coordinates();
	Coordinates(int, int);
	~Coordinates();
	int getX();
	int getY();

	void setX(int);
	void setY(int);

	void setMaxed(bool);
	bool getMaxed();
private:
	int x;
	int y;

	bool maxed;
};

#endif