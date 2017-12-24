#ifndef WINDOW
#define WINDOW

#include "HitCircles.h"
#include "SongData.h"
#include "Coordinates.h"

class Window
{
public:
	Window();
	~Window();
	int returnHeight();
	int returnWidth();
	bool initWindow();
	bool initSettings();
	SDL_Texture* loadTexture(string);
	bool returnQuit();
	bool checkQuit();
	void setPlaying(bool);
	bool getPlaying();
	bool fileExists(const string& filename);
protected:
	int screenHeight, screenWidth;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Event e;

	bool quit;
	bool playing;

	//Prot variables for gameEngine.
	bool firstLaunch, fulltrue, visualizerTrue, cheats, console;
	int volumeNum;
	int tempSW, tempSH;
	string keyOne, keyTwo;
};

#endif
