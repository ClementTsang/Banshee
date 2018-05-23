#ifndef GAMEENGINE
#define GAMEENGINE

#include "Window.h"
class GameEngine :
	public Window
{
public:
	GameEngine();
	~GameEngine();

	//Override
	void destroyGame();

	void setVar();
	bool initMedia();
	void destroyProtVar();
	bool createWindow();
	void updateScreen();
	void updateGame();
	void renderHitCircles();
	void passTimeStamps(vector <TimeStamp*> &foo);
	void mouseDetect();
	void keyDetect();
	void checkEvent();
	void renderGameTexture();
	void renderMouse();
	void renderMenu();
	void renderSelectScreen();
	void selectScreenDetect();
	void menuDetect();
	void renderOption();
	void optionDetect();
	char* getsongName();
	void pauseTheGame();
	void pauseDetect();
	bool getPaused();
	void setPaused(bool);
	void pauseFreeze();
	void hitDetect();
	string makeTime();
	void getClock();
	void renderFail();
	bool getFail();
	void setFail(bool);
	void setRetry(bool);
	bool getRetry();
	void failDetect();
	void renderPass();
	void passDetect();
	void setPass(bool);
	bool getPass();
	void passFile(bool, string, string, int, char*);
	void sortFiles();
	void highScore();
	void drawGraph();
	void passGraph(float*);
	int getVol();
	void setOldInt(int);
	void setUpdateFile(bool);
	bool getUpdateFile();
	void renderTutorial();
	void detectTutorial();
	void tutRewrite();

private:
	int mouseX, mouseY;
	float multiX, multiY;
	vector <HitCircles> hitcircle;
	vector <HitCircles> hitPoint;
	vector <TimeStamp*> hitTimes;
	size_t numObjects;
	TimeStamp* tempStamp;

	char* songName;

	SDL_Texture* hitmarker, *hitWhite, *hitRed, *hitGreen, *hitBlue, *hitYellow;
	SDL_Texture* cursor, *press, *tempCursor, *circle;
	SDL_Texture* numOne, *numTwo, *numThree, *numFour, *numFive, *numSix, *numSeven, *numEight, *numNine, *numZero;
	SDL_Texture *comZ, *comOne, *comTwo, *comThree, *comFour, *comFive, *comSix, *comSeven, *comEight, *comNine, *comX;
	SDL_Texture *scoreHund, *scoreFif, *scoreMiss, *failRed, *failGrey;
	SDL_Texture *playButton, *pauseOver, *optionMenu, *exitButton, *menuButton, *failBack, *pauseStop, *pauseCont, *pauseRetry, *pauseMarker, *youFailed;
	SDL_Texture *scoreTexture, *replay, *accuracy, *scoreAcc, *finScore, *visualizer;
	SDL_Texture *optionSelectButt, *optSlide, *saveexit, *optExit, *optKeyBut, *optVolNum;
	SDL_Texture *menuBG, *menuTwo, *menuThree, *menuFour, *gameIcon, *highScText, *winText, *yesText, *noText, *WYKtextO, *WYKtextT, *tutArrow;
	vector <SDL_Texture*> menuText;
	vector <SongData> songList;
	vector <SDL_Texture*> songLength;
	vector <SDL_Texture*> songArtist;
	vector <SDL_Texture*> songHigh;
	vector <SDL_Texture*> optionText;
	vector <SDL_Texture*> optionOp;
	vector <SDL_Texture*> optionList;
	vector <SDL_Texture*> tutorialList;

	TTF_Font *quickSand, *quickSandSmall, *quickSandLarge, *quickSandSmallish, *aileronsSmall, *ailerons, *aileronsLarge;

	Mix_Chunk *hitSound;
	Mix_Music *tempSound = NULL;

	int mouseW, mouseH;
	int mouseBoxX, mouseBoxY;
	int hitW, hitH;
	int indW, indH;
	int scorW, scorH, scorX, scorY;

	int numxW, numxH;
	int maxX, maxY, minX, minY;
	int modX, modY;
	int posX, posY;
	int playW, playH;
	int combW, combH;
	int stopPW, stopPH, pauseSW, pauseRW;
	int optW, optH;
	int failW, failH;
	int failRW, failRH;
	int pauseMW, pauseMH;
	int menuButW, menuButH;
	int exitW, exitH;
	int scoreTexW, scoreTexH;
	int replayW, replayH;
	int accuW, accuH;
	int scorAccW, scorAccH;
	int finScorW, finScorH;
	int visW, visH;

	int pausePx, pausePy, pauseSX, pauseSY, pauseReX, pauseReY;
	int pauseMx, pauseMy;
	int failQx, failQy, failRx, failRy;
	int exitPaX, exitPaY, replayPaX, replayPaY;

	int initTime;
	int seconds, minutes, milli;

	int number, difficulty, diffLevel, colourNum;

	bool mousePress, keyPressD, keyPressF, pausedGame, failLost, retryGame, unpauseGame, quitFail;
	bool playMenu, completeGame, calcAccu, optionTrue, openFile, updateFile, highNew;
	int oldInt;
	int mouseClock, keyClock;

	int leniency;
	int songListOffset;

	int score, combo, failCount;
	int tempClock;

	int fpsDelay, fpsCount;
	int scrollY, realScrollY;

	double totAcc, finAcc, numBeats;

	vector <Coordinates> menuCoord;
	vector <float> graphPoints;
	vector <Coordinates> graphPrep;

	int optionX, optionY;

	bool rendFull, rendRes, rendVis, rendLeft, rendRight;
	bool upFull, upResH, upVis, upKey, upVol, upResW;
	int rendVol, dontRend;
	int oldW, oldH, oldVol;
	bool oldFull, oldVis;

	//Animation
	bool moveMenu, selectPlay, selectOption;
	int tempHa = 0;  //Named so as I'm laughing at how this is actually working.

	//Tutorial
	bool newTutFalse, playTutorial, displayCirc = true;
	int tutTime, tutDiv, tutCount, senpTut;
};

#endif