/**
 * @file	GameEngine.cpp
 *
 * @brief	Implements the game engine class.
 */

#include "stdafx.h"
#include "GameEngine.h"

 /// <summary>
 /// Pre: None.
 /// Post: Variables set.
 /// Initializes a new instance of the <see cref="GameEngine" /> class.
 /// </summary>
GameEngine::GameEngine()
{
	hitmarker = NULL;

	hitSound = NULL;
	quit = false;
	multiX = 100;
	multiY = 5;
	numObjects = 0;
	tempStamp = new TimeStamp(0, 0, 0, 0, 0, 0);
	hitcircle.clear();

	maxX = 0;
	maxY = 0;
	minX = 0;
	minY = 0;
	modX = 0;
	modY = 0;
	posX = 0;
	posY = 0;
	initTime = clock();
	tempClock = 0;
	number = 1;
	colourNum = 1;

	scrollY = 0;
	songListOffset = 0;

	seconds = 0;
	milli = 0;
	minutes = 0;

	mousePress = true;
	keyPressD = true;
	keyPressF = true;
	pausedGame = false;
	failLost = false;
	retryGame = false;
	quitFail = true;
	playMenu = false;
	completeGame = false;
	calcAccu = false;
	optionTrue = false;
	openFile = false;
	mouseClock = 0;
	keyClock = 0;

	rendFull = false;
	rendRes = false;
	rendVis = false;
	rendLeft = false;
	rendRight = false;
	upFull = upResH = upVis = upKey = upVol = upResW = false;
	rendVol = 0;

	moveMenu = false;
	updateFile = false;
	newTutFalse = true;

	fpsDelay = 1;
	fpsCount = 120;	//Set to 30/60/120.

	pauseSX = pauseSY = pausePy = pausePx = pauseReX = pauseReY = 0;

	score = 0;
	combo = 0;
	failCount = 0;

	totAcc = 0;
	finAcc = 0;
	dontRend = -1;
	oldInt = 0;

	diffLevel = 0;	//<----- MOVE TO ANOTHER FUNCTION

	if (diffLevel == 0) difficulty = 4;
	else if (diffLevel == 1) difficulty = 5;
	else if (diffLevel == 2) difficulty = 8;
	else if (diffLevel == 3) difficulty = 10;

	playing = false;
}

/// <summary>
/// Pre: GameEngine must be initialized.
/// Post: Clears certain elements.
/// Finalizes an instance of the <see cref="GameEngine" /> class.
/// </summary>
GameEngine::~GameEngine()
{
	hitSound = NULL;
	hitmarker = NULL;
	quit = true;
	SDL_RenderClear(renderer);
	SDL_DestroyTexture(hitmarker);
	SDL_DestroyTexture(cursor);
	SDL_DestroyTexture(press);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);

	TTF_CloseFont(quickSand);

	Mix_FreeChunk(hitSound);
	mouseX = 0;
	mouseY = 0;
	mouseBoxX = 0;
	mouseBoxY = 0;
	realScrollY = 0;
	scrollY = 0;

	playW = 0;
	playH = 0;

	Window::~Window();
}

/// <summary>
/// Pre: Read from options file.
/// Post: Sets certain variables.
/// Sets the variables for those that are dependent on specific values that may require the game to be fully set up prior to
/// doing so.
/// </summary>
void GameEngine::setVar()
{
	graphPrep.clear();
	for (int i = 0; i < screenWidth / 35 + 2; ++i)
	{
		graphPrep.push_back(Coordinates(0, screenHeight));
	}

	optionOp.at(10) = (SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, keyOne.c_str(), { 255, 255, 255, 255 })));
	optionOp.at(11) = (SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, keyTwo.c_str(), { 255, 255, 255, 255 })));

	Mix_VolumeChunk(hitSound, volumeNum);
	rendVol = (int)((double)volumeNum / 128 * 176);

	string tempVolOpt = to_string((int)((double)rendVol / 176 * 100));
	optVolNum = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, tempVolOpt.c_str(), { 255, 255, 255, 255 }));

	if (fulltrue)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_GetWindowSize(window, &screenWidth, &screenHeight);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		screenWidth = tempSW;
		screenHeight = tempSH;
		SDL_SetWindowSize(window, screenWidth, screenHeight);
	}
	if (newTutFalse) newTutFalse = firstLaunch;

	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	cout << "SET VAR DONE" << endl;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Sets certain variables to empty strings, NULL, or 0.
/// Destroys game variables.
/// </summary>
void GameEngine::destroyGame()
{
	multiX = 0;
	multiY = 0;
	numObjects = 0;
	maxX = 0;
	maxY = 0;
	minX = 0;
	minY = 0;
	modX = 0;
	modY = 0;
	posX = 0;
	posY = 0;
	initTime = clock();
	number = 1;
	colourNum = 1;
	seconds = 0;
	milli = 0;
	minutes = 0;
	mousePress = true;
	keyPressD = true;
	pausedGame = false;
	completeGame = false;
	quitFail = true;
	calcAccu = false;
	mouseClock = 0;
	combo = 0;
	hitcircle.clear();
	hitPoint.clear();
	hitTimes.clear();
	graphPoints.clear();
	setVar();
	failCount = 0;
}

/// <summary>
/// Pre: Initialized variables.
/// Post: Sets variables to 0.
/// Destroys protected variables.
/// </summary>
void GameEngine::destroyProtVar()
{
	numBeats = 0;
	score = 0;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Returns true if all elements are properly loaded.
/// Creates the window.
/// </summary>
/// <returns></returns>
bool GameEngine::createWindow()
{
	if (initWindow())
	{
		if (initMedia())
		{
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			setVar();
			return true;
		}
	}
	return false;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Returns true if all media is properly loaded.
/// Initializes the media (images, ttf)
/// </summary>
/// <returns></returns>
bool GameEngine::initMedia()
{
	//IMAGES
	SDL_SetHintWithPriority("SDL_HINT_RENDER_SCALE_QUALITY", "0", SDL_HINT_OVERRIDE);

	hitmarker = loadTexture("..//res//images//hitcircle.png");
	hitWhite = loadTexture("..//res//images//hitcirclewhite.png");
	hitBlue = loadTexture("..//res//images//hitcircleblue.png");
	hitRed = loadTexture("..//res//images//hitcirclered.png");
	hitGreen = loadTexture("..//res//images//hitcirclegreen.png");
	hitYellow = loadTexture("..//res//images//hitcircleyellow.png");

	cursor = loadTexture("..//res//images//cursor.png");
	press = loadTexture("..//res//images//press.png");
	circle = loadTexture("..//res//images//approachcircle.png");

	numOne = loadTexture("..//res//images//hit1.png");
	numTwo = loadTexture("..//res//images//hit2.png");
	numThree = loadTexture("..//res//images//hit3.png");
	numFour = loadTexture("..//res//images//hit4.png");
	numFive = loadTexture("..//res//images//hit5.png");
	numSix = loadTexture("..//res//images//hit6.png");
	numSeven = loadTexture("..//res//images//hit7.png");
	numEight = loadTexture("..//res//images//hit8.png");
	numNine = loadTexture("..//res//images//hit9.png");
	numZero = loadTexture("..//res//images//hit0.png");

	comX = loadTexture("..//res//images//combox.png");
	comZ = loadTexture("..//res//images//combo0.png");
	comOne = loadTexture("..//res//images//combo1.png");
	comTwo = loadTexture("..//res//images//combo2.png");
	comThree = loadTexture("..//res//images//combo3.png");
	comFour = loadTexture("..//res//images//combo4.png");
	comFive = loadTexture("..//res//images//combo5.png");
	comSix = loadTexture("..//res//images//combo6.png");
	comSeven = loadTexture("..//res//images//combo7.png");
	comEight = loadTexture("..//res//images//combo8.png");
	comNine = loadTexture("..//res//images//combo9.png");

	scoreMiss = loadTexture("..//res//images//score0.png");
	scoreFif = loadTexture("..//res//images//score50.png");
	scoreHund = loadTexture("..//res//images//score100.png");
	failRed = loadTexture("..//res//images//failRed.png");
	failGrey = loadTexture("..//res//images//failGrey.png");

	menuBG = loadTexture("..//res//images//menu.png");
	menuTwo = loadTexture("..//res//images//menuTwo.png");
	menuThree = loadTexture("..//res//images//menuThree.png");
	menuFour = loadTexture("..//res//images//menuFour.png");
	failBack = loadTexture("..//res//images//fail_back.png");
	pauseOver = loadTexture("..//res//images//pause_overlay.png");
	pauseStop = loadTexture("..//res//images//pause_exit.png");
	pauseCont = loadTexture("..//res//images//pause_back.png");
	pauseRetry = loadTexture("..//res//images//pause_retry.png");
	//playButton = loadTexture("..//res//images//play.png");
	//optionMenu = loadTexture("..//res//images//option.png");
	//exitButton = loadTexture("..//res//images//exit.png");
	youFailed = loadTexture("..//res//images//failed.png");
	pauseMarker = loadTexture("..//res//images//pauseHit.png");
	menuButton = loadTexture("..//res//images//menu-button.png");
	//scoreTexture = loadTexture("..//res//images//score.png");
	//replay = loadTexture("..//res//images//replay.png");
	//accuracy = loadTexture("..//res//images//accuracy.png");
	visualizer = loadTexture("..//res//images//visualizer.png");
	optionSelectButt = loadTexture("..//res//images//optButton.png");
	optSlide = loadTexture("..//res//images//optionSlide.png");
	optKeyBut = loadTexture("..//res//images//optKeyBut.png");
	gameIcon = loadTexture("..//res//images//bansheeicon2x.png");
	tutArrow = loadTexture("..//res//images//selectArrow.png");
	tempCursor = cursor;

	//SOUNDS
	hitSound = Mix_LoadWAV("..//res//sfx//hitsound.wav");
	Mix_VolumeChunk(hitSound, volumeNum);

	//FONTS
	quickSand = TTF_OpenFont("..//res//fonts//Quicksand-Regular.ttf", 46);
	quickSandSmallish = TTF_OpenFont("..//res//fonts//Quicksand-Regular.ttf", 25);
	quickSandSmall = TTF_OpenFont("..//res//fonts//Quicksand-Regular.ttf", 18);
	quickSandLarge = TTF_OpenFont("..//res//fonts//Quicksand-Regular.ttf", 60);
	ailerons = TTF_OpenFont("..//res//fonts//ailerons.ttf", 46);
	aileronsLarge = TTF_OpenFont("..//res//fonts//ailerons.ttf", 70);
	aileronsSmall = TTF_OpenFont("..//res//fonts//ailerons.ttf", 18);

	////TEXT////

	////GENERAL////
	exitButton = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Exit", { 255, 255, 255, 255 }));
	scoreTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Score", { 255, 255, 255, 255 }));
	replay = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Replay", { 255, 255, 255, 255 }));
	accuracy = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Accuracy", { 255, 255, 255, 255 }));
	playButton = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Play", { 255, 255, 255, 255 }));
	optionMenu = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Options", { 255, 255, 255, 255 }));
	highScText = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "New High Score!", { 255, 255, 255, 255 }));
	winText = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, "Complete!", { 255, 255, 255, 255 }));
	yesText = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Yes", { 255, 255, 255, 255 }));
	noText = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "No", { 255, 255, 255, 255 }));
	WYKtextO = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsSmall, "I see this is your first time running", { 255, 255, 255, 255 }));
	WYKtextT = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsSmall, "Banshee.  Would you like to run the tutorial?", { 255, 255, 255, 255 }));

	////OPTIONS////
	//OPTION TEXT
	optionText.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Fullscreen Mode: ", { 255, 255, 255, 255 })));
	optionText.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Resolution: ", { 255, 255, 255, 255 })));
	optionText.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Volume: ", { 255, 255, 255, 255 })));
	optionText.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Enable Visualizer: ", { 255, 255, 255, 255 })));
	optionText.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Left Click Key: ", { 255, 255, 255, 255 })));
	optionText.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Right Click Key: ", { 255, 255, 255, 255 })));

	//SAVING EXITS FOR TEXT
	saveexit = (SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Save and Exit", { 255, 255, 255, 255 })));
	optExit = (SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Exit", { 255, 255, 255, 255 })));

	//OPTION TEXT VARIABLES
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Fullscreen", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Windowed", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "1920x1080", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "1366x768", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "1280x1024", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "1250x705", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Custom", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Enabled", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Disabled", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, "Press key to set", { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, keyOne.c_str(), { 255, 255, 255, 255 })));
	optionOp.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, keyTwo.c_str(), { 255, 255, 255, 255 })));

	////TUTORIAL TEXT////
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Welcome to Banshee!", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "This is a simple rhythm game based on games such as osu! and Audiosurf.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "This tutorial will cover some basics.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "First, let's make sure we have the right tools.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "You will require either a mouse, touchpad, touchscreen, or a drawing tablet.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "A keyboard is also recommended.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Make sure your volume isn't too low - listening helps a lot here!", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "First, let's try moving the cursor around!", { 255, 255, 255, 255 })));  //7
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Also, try clicking both the left and right buttons.", { 255, 255, 255, 255 })));  //8
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Now that we've got the basics down, let's try our first hit circle!", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "A hitcircle looks something like this:", { 255, 255, 255, 255 }))); //10
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "While listening to a song, these hitcircles will periodically generate.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Your goal is to click on them on beat.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "You can do this through listening and watching the indicator.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Got that?  Let's try a few.  Don't worry, you can't fail.", { 255, 255, 255, 255 })));  //14
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Good job!", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "You can also use the keyboard as a substitute for the left and right buttons.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "By default, these keys are \"d\" and \"f\", as left and right respectively.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "At the top right, you can see your score.", { 255, 255, 255, 255 }))); //18
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "A successfully hit hitcircle awards 100 points, a close hit 50 points, and a miss 0.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "At the bottom left, you can see your multiplier.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Successfully hitting consecutive hitcircles increases the multiplier.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Incoming points are multiplied by this.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Careful though, missing resets the multiplier.", { 255, 255, 255, 255 }))); //23
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "At the top left, you can see the lifebar.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "If you miss 5 consecutive hitcircles, you will fail the song.", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Don't worry, hitting one hitcircle will reset it.", { 255, 255, 255, 255 }))); //26
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Got it?  If you want to watch this tutorial again, just play the \"Tutorial\" song!", { 255, 255, 255, 255 })));
	tutorialList.push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmallish, "Good luck!", { 255, 255, 255, 255 })));

	////END TEXT////
	////SETTING VARIABLES////
	SDL_QueryTexture(cursor, NULL, NULL, &mouseW, &mouseH);
	SDL_QueryTexture(hitmarker, NULL, NULL, &hitW, &hitH);
	SDL_QueryTexture(circle, NULL, NULL, &indW, &indH);
	SDL_QueryTexture(numOne, NULL, NULL, &numxW, &numxH);
	SDL_QueryTexture(scoreHund, NULL, NULL, &scorW, &scorH);
	SDL_QueryTexture(playButton, NULL, NULL, &playW, &playH);
	SDL_QueryTexture(comNine, NULL, NULL, &combW, &combH);
	SDL_QueryTexture(pauseCont, NULL, NULL, &stopPW, &stopPH);
	SDL_QueryTexture(pauseRetry, NULL, NULL, &pauseRW, &stopPH);
	SDL_QueryTexture(pauseStop, NULL, NULL, &pauseSW, &stopPH);
	SDL_QueryTexture(optionMenu, NULL, NULL, &optW, &optH);
	SDL_QueryTexture(youFailed, NULL, NULL, &failW, &failH);
	SDL_QueryTexture(failRed, NULL, NULL, &failRW, &failRH);
	SDL_QueryTexture(pauseMarker, NULL, NULL, &pauseMW, &pauseMH);
	SDL_QueryTexture(menuButton, NULL, NULL, &menuButW, &menuButH);
	SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreTexW, &scoreTexH);
	SDL_QueryTexture(replay, NULL, NULL, &replayW, &replayH);
	SDL_QueryTexture(accuracy, NULL, NULL, &accuW, &accuH);
	SDL_QueryTexture(exitButton, NULL, NULL, &exitW, &exitH);
	SDL_QueryTexture(visualizer, NULL, NULL, &visW, &visH);

	SDL_SetTextureAlphaMod(hitWhite, 150);
	SDL_SetTextureAlphaMod(hitBlue, 150);
	SDL_SetTextureAlphaMod(hitGreen, 150);
	SDL_SetTextureAlphaMod(hitRed, 150);
	SDL_SetTextureAlphaMod(hitYellow, 150);
	SDL_SetTextureAlphaMod(pauseOver, 220);

	if (hitW > 128) hitW /= 2;
	if (hitH > 128) hitH /= 2;

	scorW /= 2;
	scorH /= 2;

	combW /= 2;
	combH /= 2;

	stopPW /= 2;
	pauseRW /= 2;
	pauseSW /= 2;
	stopPH /= 2;

	leniency = mouseW / 4;
	return true;
}

/// <summary>
/// Pre: Initialized GameEngine.  
/// Post: Screen elements updated.
/// Updates the screen, depending on certain variables.  Basically updates on screen elements.
/// </summary>
void GameEngine::updateScreen()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	checkEvent();

	if (playing)
	{
		if (pausedGame)
		{
			pauseFreeze();
			if (!unpauseGame) pauseTheGame();
		}
		else updateGame();
	}
	else
	{
		if (!failLost)
		{
			if (!playMenu)
			{
				if (!completeGame)
				{
					if (optionTrue) renderOption();
					else renderMenu();
				}
				else renderPass();
			}
			else if (playMenu) renderSelectScreen();
		}
		else renderFail();
	}
	if (firstLaunch) renderTutorial();

	renderMouse();

	SDL_RenderPresent(renderer);
	//SDL_Delay(8);  //Originally 8.
}

/// <summary>
/// Pre: Initialized GameEngine, game is being played.
/// Post: Updates certain game elements.
/// Updates the game portion of Banshee.
/// </summary>
void GameEngine::updateGame()
{
	SDL_RenderCopy(renderer, menuFour, NULL, NULL);
	if (visualizerTrue) drawGraph();
	if (displayCirc) renderHitCircles();
	renderGameTexture();
}

/// <summary>
/// Pre: Initialized GameEngine, game is being played, tutorial is not being played.
/// Post: Updates and sets hitcircles.
/// Loads the hitcircles, and renders them to be displayed for the screen, in addition to any other hitcircle-related
/// elements.
/// </summary>
void GameEngine::renderHitCircles()
{
	SDL_Rect hitR;
	hitR.w = hitW;
	hitR.h = hitH;
	int timeShut = 1000;

	SDL_Rect indic;
	bool tempBool = true;

	if (hitTimes.size() > 1)  //3
	{
		if (tempStamp != hitTimes.back())
		{
			HitCircles tempHit = HitCircles(hitTimes.back());
			hitcircle.push_back(tempHit);
			tempStamp = hitTimes.back();
			tempBool = false;
		}
		for (size_t i = 0; i < hitcircle.size(); ++i)
		{
			string boop = makeTime();
			int tempTime = clock();

			int hitTime, clockTime;
			hitTime = hitcircle.at(i).getMilli() + (hitcircle.at(i).getSec() + hitcircle.at(i).getMin() * 60) * 1000;
			clockTime = milli + (seconds + minutes * 60) * 1000;

			if (clockTime >= hitTime - 150)
			{
				if (tempTime - hitcircle.at(i).getTime() <= timeShut + hitcircle.at(i).getDelay() - 150)
				{
					if (hitcircle.at(i).getType() == 0 && !hitcircle.at(i).getDrawn())
					{
						hitR.x = (int)((400000 * hitcircle.at(i).getDom() + 150) / 200 + (100 / hitcircle.at(i).getDom() * posX));
						hitR.y = (int)((60000 * hitcircle.at(i).getBeat() + 150) / 220 + (50 * hitcircle.at(i).getBeat() * posY));

						bool wentOver = false;

						if (hitR.x > screenWidth - hitW - 25)
						{
							hitR.x = screenWidth - hitW - 25;
							maxX++;
							wentOver = true;
						}
						else if (hitR.x < 0)
						{
							hitR.x = hitW + 25;
							minX++;
						}
						else
						{
							maxX = 0;
							minX = 0;
						}
						if (hitR.y > screenHeight - hitH - 125)
						{
							hitR.y = screenHeight - hitH - 125;
							maxY++;
							wentOver = true;
						}
						else if (hitR.y < 0 + 5)
						{
							hitR.y = hitH + 25 + 5;
							minY++;
						}
						else
						{
							maxY = 0;
							minY = 0;
						}

						if (maxX >= 2)
						{
							posX--;
							maxX = 0;
						}
						else if (minX >= 2)
						{
							posX++;
							minX = 0;
						}
						if (maxY >= 2)
						{
							posY--;
							maxY = 0;
						}
						else if (minY >= 2)
						{
							posY++;
							minY = 0;
						}

						//Anticollision
						if (hitcircle.size() > 1)
						{
							while (sqrt(pow((hitcircle.at(i - 1).getX() - hitR.x), 2) + pow((hitcircle.at(i - 1).getY() - hitR.y), 2)) <= 2 * hitW)
							{
								if (wentOver)
								{
									hitR.x--;
									hitR.y--;
								}
								else
								{
									hitR.x++;
									hitR.y++;
								}
								//cout << "COLLISION! " << endl;
							}
							if (sqrt(pow((hitcircle.at(i - 1).getX() - hitR.x), 2) + pow((hitcircle.at(i - 1).getY() - hitR.y), 2)) > 5 * hitW)
							{
								if (hitcircle.at(i - 1).getX() > hitR.x) hitR.x += hitW;
								else if (hitcircle.at(i - 1).getX() < hitR.x)hitR.x -= hitW;

								if (hitcircle.at(i - 1).getY() > hitR.y) hitR.y += hitH;
								else if (hitcircle.at(i - 1).getY() < hitR.y)hitR.y -= hitH;
							}
						}
						if (hitR.x > screenWidth - hitW - 25) hitR.x = screenWidth - hitW - 25;
						else if (hitR.x < 0) hitR.x = hitW + 25;
						if (hitR.y > screenHeight - hitH - 125) hitR.y = screenHeight - hitH - 125;
						else if (hitR.y < 0 + 5) hitR.y = hitH + 25 + 5;

						wentOver = false;

						//Commit x and y
						hitcircle.at(i).setX(float(hitR.x));
						hitcircle.at(i).setY(float(hitR.y));
						SDL_RenderCopy(renderer, hitmarker, NULL, &hitR);
						hitcircle.at(i).setType(1);
						hitcircle.at(i).setDrawn(true);
						hitcircle.at(i).setNumber(number);
						hitcircle.at(i).setColour(colourNum);
						number++;
						if (number > difficulty)
						{
							number = 1;
							colourNum++;
						}
						if (colourNum > 5) colourNum = 1;

						cout << "(x, y): " << hitR.x << ", " << hitR.y << " - at " << boop << endl;
					}
					else if (hitcircle.at(i).getType() != 0 && !hitcircle.at(i).getDrawn())
					{
						hitR.x = (int)hitcircle.at(i).getX();
						hitR.y = (int)hitcircle.at(i).getY();
						if (tempBool == false) cout << "(x, y): " << hitR.x << ", " << hitR.y << " - at " << boop << endl;
						SDL_RenderCopy(renderer, hitmarker, NULL, &hitR);
						hitcircle.at(i).setDrawn(true);
					}

					//Bigger = Slower
					indic.w = (int)(indW * (double)((timeShut)-(tempTime - hitcircle.at(i).getTime()) + 70) / 500);
					indic.h = (int)(indH * (double)((timeShut)-(tempTime - hitcircle.at(i).getTime()) + 70) / 500);
					if (indic.w <= hitR.w + 4)
					{
						if (indic.h <= hitR.h + 4)
						{
							indic.w = 0;
							indic.h = 0;
							hitcircle.at(i).setType(2);
						}
					}
					else if ((tempTime - hitcircle.at(i).getTime() >= timeShut / 2))
					{
						hitcircle.at(i).setType(3);
					}
					if (tempTime - hitcircle.at(i).getTime() >= timeShut + hitcircle.at(i).getDelay() - 150)
					{
						hitcircle.at(i).setType(4);
					}

					hitcircle.at(i).setIndW((float)indic.w);
					hitcircle.at(i).setIndH((float)indic.h);

					indic.x = hitR.x + hitR.w / 2 - indic.w / 2;
					indic.y = hitR.y + hitR.h / 2 - indic.h / 2;
					SDL_RenderCopy(renderer, circle, NULL, &indic);

					SDL_Rect hitnumber;
					hitnumber.h = numxH;
					hitnumber.w = numxW;
					hitnumber.x = hitR.x + hitW / 2 - numxW / 2;
					hitnumber.y = hitR.y + hitH / 2 - numxH / 2;

					if (hitcircle.at(i).getNumber() == 1)
						SDL_RenderCopy(renderer, numOne, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 2)
						SDL_RenderCopy(renderer, numTwo, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 3)
						SDL_RenderCopy(renderer, numThree, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 4)
						SDL_RenderCopy(renderer, numFour, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 5)
						SDL_RenderCopy(renderer, numFive, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 6)
						SDL_RenderCopy(renderer, numSix, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 7)
						SDL_RenderCopy(renderer, numSeven, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 8)
						SDL_RenderCopy(renderer, numEight, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 9)
						SDL_RenderCopy(renderer, numNine, NULL, &hitnumber);
					else if (hitcircle.at(i).getNumber() == 0)
						SDL_RenderCopy(renderer, numZero, NULL, &hitnumber);

					if (hitcircle.at(i).getColour() == 1) SDL_RenderCopy(renderer, hitWhite, NULL, &hitR);
					else if (hitcircle.at(i).getColour() == 2) SDL_RenderCopy(renderer, hitRed, NULL, &hitR);
					else if (hitcircle.at(i).getColour() == 3) SDL_RenderCopy(renderer, hitGreen, NULL, &hitR);
					else if (hitcircle.at(i).getColour() == 4) SDL_RenderCopy(renderer, hitBlue, NULL, &hitR);
					else if (hitcircle.at(i).getColour() == 5) SDL_RenderCopy(renderer, hitYellow, NULL, &hitR);
				}
				else
				{
					hitPoint.push_back(hitcircle.at(i));
					hitPoint.back().setType(102); //<-Means 0 points, obviously :/
					hitPoint.back().setTime(clock());
					combo = 0;
					hitcircle.erase(hitcircle.begin()) + i;
					if (quitFail) failCount++;
					cout << "MISS!" << endl;
				}
			}
		}
	}
	for (size_t i = 0; i < hitcircle.size(); ++i)
	{
		hitcircle.at(i).setDrawn(false);
	}
}

/// <summary>
/// Pre: A song that returns timestamps
/// Post: Sets hitTimes to foo.
/// Passes the time stamps from the BeatDetector.
/// </summary>
/// <param name="foo">The foo.</param>
void GameEngine::passTimeStamps(vector<TimeStamp*> &foo)
{
	hitTimes = foo;
	numBeats = foo.size() - 1;
}

/// <summary>
/// Pre: None
/// Post: Returns mouse location and what happens when mouse actions occur.
/// Detects mouse inputs.
/// </summary>
void GameEngine::mouseDetect()
{
	SDL_ShowCursor(0);
	if (e.type == SDL_MOUSEMOTION)
	{
		mouseX = e.motion.x;
		mouseY = e.motion.y;
		mouseBoxX = mouseX - mouseW / 2;
		mouseBoxY = mouseY - mouseH / 2;
	}

	if (e.type == SDL_MOUSEBUTTONDOWN && mousePress && !e.key.repeat && (e.button.button == SDL_BUTTON_RIGHT || e.button.button == SDL_BUTTON_LEFT))
	{
		if (playing)
		{
			if (!pausedGame) {
				hitDetect();
			}
			else if (pausedGame) {
				pauseDetect();
			}
		}
		else if (!playing && !moveMenu) {
			if (!failLost)
			{
				if (!completeGame)
					if (optionTrue) optionDetect();
					else
						if (newTutFalse) detectTutorial();
						else menuDetect();
				else
					passDetect();
			}
			else if (failLost) failDetect();		//<------LOSEGAME
		}
		mousePress = false;
		mouseClock = clock();
	}
	else if (e.type == SDL_MOUSEBUTTONUP && !mousePress)	//Techincally not needed (works fine without it), but this forces holding to not work otherwise.
	{
		mousePress = true;
	}

	if (playMenu)
	{
		if (e.type == SDL_MOUSEWHEEL)
		{
			if (e.wheel.y < 0)
			{
				scrollY++;
				//cout << "MOUSE : WHEEL DOWN: " << scrollY << endl;
			}
			else
			{
				scrollY--;
				//cout << "MOUSE : WHEEL UP: " << scrollY << endl;
			}
			selectScreenDetect();
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Key actions depending on the situation.
/// Detects key input based on other variables.
/// </summary>
void GameEngine::keyDetect()
{
	if (playing) /////PLAYING
	{
		/////MAIN KEY INPUTS
		SDL_Keycode keyCOne = SDL_GetKeyFromName(keyOne.c_str()), keyCTwo = SDL_GetKeyFromName(keyTwo.c_str());
		if (e.type == SDL_KEYDOWN && keyPressD && !e.key.repeat)
		{
			if (e.key.keysym.sym == keyCOne)
			{
				if (!pausedGame)
					hitDetect();
				else if (pausedGame && unpauseGame)
					pauseDetect();
				keyPressD = false;
				keyClock = clock();
			}
		}
		else if (e.type == SDL_KEYUP && !keyPressD)
		{
			if (e.key.keysym.sym == keyCOne)
			{
				keyPressD = true;
			}
		}
		if (e.type == SDL_KEYDOWN && keyPressF && !e.key.repeat)
		{
			if (e.key.keysym.sym == keyCTwo)
			{
				if (!pausedGame)
					hitDetect();
				else if (pausedGame && unpauseGame)
					pauseDetect();
				keyPressF = false;
				keyClock = clock();
			}
		}
		else if (e.type == SDL_KEYUP && !keyPressF)
		{
			if (e.key.keysym.sym == keyCTwo)
			{
				keyPressF = true;
			}
		}

		if (e.type == SDL_KEYDOWN && !e.key.repeat)
		{
			switch (e.key.keysym.sym)
			{
				/////ESCAPE
			case SDLK_ESCAPE:
				if (!pausedGame)
				{
					pausedGame = true;
					tempClock = clock();
					cout << "PAUSE" << endl;
				}
				else
				{
					unpauseGame = true;
					cout << "UNPAUSE" << endl;
				}
				break;
			}
		}

		if (cheats)
		{
			/////TEST KEY INPUTS
			if (e.type == SDL_KEYDOWN && !e.key.repeat) //REMOVE
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_q:
					quitFail = false;
					break;
				case SDLK_p:
					numBeats = 78;
					totAcc = 23;
					score = 124567;
					completeGame = true;
					break;
				}
			}
		}
	}
	else /////NOT PLAYING
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if (!playing && !completeGame && !failLost)
				{
					if (optionTrue)
					{
						moveMenu = true;
						rendFull = rendRes = rendVis = rendLeft = rendRight = false;
						dontRend = -1;

						screenWidth = oldW;
						screenHeight = oldH;
						volumeNum = oldVol;
						visualizerTrue = oldVis;
						fulltrue = oldFull;
						tempSH = oldH;
						tempSW = oldW;

						openFile = false;
					}
					else if (playMenu)
					{
						moveMenu = true;
					}
					else quit = true;
				}
				else
				{
					moveMenu = true;
					//cout << "COMPLETE HIT!" << endl;
				}
				break;
			case SDLK_RETURN:
				if (playMenu)
				{
					playMenu = false;
					playing = true;
					cout << "BEGIN PLAYING!" << endl;
					return;
				}
			case SDLK_UP:
				if (playMenu)
				{
					scrollY--;
					selectScreenDetect();
				}
				//cout << "!" << endl;
				break;
			case SDLK_DOWN:
				if (playMenu)
				{
					scrollY++;
					selectScreenDetect();
				}
				//cout << "?" << endl;
				break;
			}
			if (optionTrue)
			{
				if (rendLeft)
				{
					keyOne = e.key.keysym.sym;
					cout << "KEYONE: " << keyOne << endl;
					rendLeft = false;
					setVar();
					dontRend = -1;
					upKey = true;
				}
				else if (rendRight)
				{
					keyTwo = e.key.keysym.sym;
					rendRight = false;
					setVar();
					dontRend = -1;
					upKey = true;
				}
			}
		}
	}
}

/// <summary>
/// Checks the event.
/// </summary>
void GameEngine::checkEvent()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (!checkQuit())
		{
			mouseDetect();
			keyDetect();
			SDL_FlushEvent(SDL_KEYDOWN | SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP);
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine, game is being played.
/// Post: Rendered game elements.
/// Renders certain game textures when the game is being played.
/// </summary>
void GameEngine::renderGameTexture()
{
	//Render lines
	if (hitcircle.size() >= 2)
	{
		if (clock() - hitcircle.at(0).getTrueTime() > 700 + hitcircle.at(0).getDelay())
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, (int)hitcircle.at(1).getX() + hitW / 2, (int)hitcircle.at(1).getY() + hitH / 2, (int)hitcircle.at(0).getX() + hitW / 2, (int)hitcircle.at(0).getY() + hitH / 2);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}

	//Render point shown when hit/miss
	SDL_Rect pointR;
	pointR.w = scorW;
	pointR.h = scorH;
	for (size_t i = 0; i < hitPoint.size(); ++i)
	{
		int tempTime = clock();
		if (tempTime - hitPoint.at(i).getTime() <= 150 - hitPoint.at(i).getDelay())
		{
			if (hitPoint.at(i).getType() < 200)
			{
				hitPoint.at(i).setX(hitPoint.at(i).getX() + 12);
				hitPoint.at(i).setY(hitPoint.at(i).getY() + 12);
				hitPoint.at(i).setType(hitPoint.at(i).getType() + 100);
			}
			pointR.x = (int)hitPoint.at(i).getX();
			pointR.y = (int)hitPoint.at(i).getY();
			if (hitPoint.at(i).getType() == 200)
				SDL_RenderCopy(renderer, scoreHund, NULL, &pointR);
			else if (hitPoint.at(i).getType() == 201)
				SDL_RenderCopy(renderer, scoreFif, NULL, &pointR);
			else if (hitPoint.at(i).getType() == 202)
				SDL_RenderCopy(renderer, scoreMiss, NULL, &pointR);
		}
	}

	//Render Points
	SDL_Rect totalPoiR;
	totalPoiR.w = numxW / 2;
	totalPoiR.h = numxH / 2;
	int scorePlaceX = screenWidth - 10, scorePlaceY = 5, tempPoints = score, finScoreTemp = score;	//<<<<<------ SCALE WITH SCREEN SIZE

	for (int i = 0; i < 10; ++i)
	{
		scorePlaceX -= (20);
		totalPoiR.x = scorePlaceX;
		totalPoiR.y = scorePlaceY;

		int numTemp = tempPoints % 10;
		tempPoints /= 10;

		switch (numTemp)
		{
		case 0:
			SDL_RenderCopy(renderer, numZero, NULL, &totalPoiR);
			break;
		case 1:
			SDL_RenderCopy(renderer, numOne, NULL, &totalPoiR);
			break;
		case 2:
			SDL_RenderCopy(renderer, numTwo, NULL, &totalPoiR);
			break;
		case 3:
			SDL_RenderCopy(renderer, numThree, NULL, &totalPoiR);
			break;
		case 4:
			SDL_RenderCopy(renderer, numFour, NULL, &totalPoiR);
			break;
		case 5:
			SDL_RenderCopy(renderer, numFive, NULL, &totalPoiR);
			break;
		case 6:
			SDL_RenderCopy(renderer, numSix, NULL, &totalPoiR);
			break;
		case 7:
			SDL_RenderCopy(renderer, numSeven, NULL, &totalPoiR);
			break;
		case 8:
			SDL_RenderCopy(renderer, numEight, NULL, &totalPoiR);
			break;
		case 9:
			SDL_RenderCopy(renderer, numNine, NULL, &totalPoiR);
			break;
		}
	}
	//Render Multiplier
	int multX = 130, multY = screenHeight - 60, tempMult = combo; //<<<<<------ SCALE WITH SCREEN SIZE

	SDL_Rect multR;
	multR.w = combW;
	multR.h = combH;
	multR.y = multY;

	for (int i = 0; i < 4; ++i)
	{
		multX -= 30;
		multR.x = multX;

		int combTemp = tempMult % 10;
		tempMult /= 10;

		switch (combTemp)
		{
		case 0:
			SDL_RenderCopy(renderer, comZ, NULL, &multR);
			break;
		case 1:
			SDL_RenderCopy(renderer, comOne, NULL, &multR);
			break;
		case 2:
			SDL_RenderCopy(renderer, comTwo, NULL, &multR);
			break;
		case 3:
			SDL_RenderCopy(renderer, comThree, NULL, &multR);
			break;
		case 4:
			SDL_RenderCopy(renderer, comFour, NULL, &multR);
			break;
		case 5:
			SDL_RenderCopy(renderer, comFive, NULL, &multR);
			break;
		case 6:
			SDL_RenderCopy(renderer, comSix, NULL, &multR);
			break;
		case 7:
			SDL_RenderCopy(renderer, comSeven, NULL, &multR);
			break;
		case 8:
			SDL_RenderCopy(renderer, comEight, NULL, &multR);
			break;
		case 9:
			SDL_RenderCopy(renderer, comNine, NULL, &multR);
			break;
		}
	}
	SDL_Rect comboR;
	comboR.w = combW;
	comboR.h = combH;
	comboR.x = 130;
	comboR.y = multY;
	SDL_RenderCopy(renderer, comX, NULL, &comboR);

	//Render failCount
	SDL_Rect failX;
	failX.h = failRH;
	failX.w = failRW;
	failX.y = 6;
	int failXPos = 155, failNum = failCount;

	for (int i = 0; i < 5; ++i)
	{
		failXPos -= 30;
		failX.x = failXPos;

		if (failNum > 0)
		{
			SDL_RenderCopy(renderer, failRed, NULL, &failX);
			failNum--;
		}
		else
			SDL_RenderCopy(renderer, failGrey, NULL, &failX);
	}

	if (quitFail)
	{
		if (failCount >= 5)
		{
			failLost = true;
			playing = false;
			renderFail();
		}
	}
	else if (!quitFail && !firstLaunch)
	{
		SDL_Rect failZ;
		failZ.h = failRH;
		failZ.w = failRW;
		failZ.x = 3;
		failZ.y = 40;
		SDL_RenderCopy(renderer, failRed, NULL, &failZ);
	}
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Rendered game cursor.
/// Renders the cursor based on position and if it is being clicked or not.
/// </summary>
void GameEngine::renderMouse()
{
	if (clock() - keyClock <= 70 || clock() - mouseClock <= 70) cursor = press;
	else cursor = tempCursor;

	//Render cursor
	SDL_Rect mouseR;
	mouseR.w = mouseW;
	mouseR.h = mouseH;
	mouseR.x = mouseBoxX;
	mouseR.y = mouseBoxY;
	SDL_RenderCopy(renderer, cursor, NULL, &mouseR);
}

/// <summary>
/// Pre: Initialized GameEngine, game not being played.
/// Post: Rendered menu.
/// Renders the menu.
/// </summary>
void GameEngine::renderMenu()
{
	Mix_HaltMusic();

	SDL_Rect optR;
	optR.x = 0;
	optR.y = 0;

	SDL_Rect menuR;
	menuR.x = 0;
	menuR.y = 0;
	if (moveMenu)
	{
		menuR.x = tempHa;
		menuR.x += (int)round(screenWidth / 30);
		tempHa = menuR.x;
		optR.x = -1 * (screenWidth / 2) + tempHa;
		if (menuR.x > screenWidth / 2)
		{
			menuR.x = screenWidth / 2;
			if (selectPlay)
				playMenu = true;
			else if (selectOption)
				optionTrue = true;
			selectOption = selectPlay = false;
			moveMenu = false;
			tempHa = 0;
		}
	}

	optR.w = screenWidth;
	optR.h = screenHeight;
	SDL_RenderCopy(renderer, menuTwo, NULL, &optR);

	menuR.w = screenWidth;
	menuR.h = screenHeight;
	SDL_RenderCopy(renderer, menuThree, NULL, &menuR);

	if (!optionTrue && !playMenu)
	{
		SDL_Rect playR;
		playR.w = playW;
		playR.h = playH;
		playR.x = 3 * screenWidth / 4 - playW / 2 + tempHa;
		playR.y = screenHeight / 4 - playH / 2;
		SDL_RenderCopy(renderer, playButton, NULL, &playR);

		playR.w = exitW;
		playR.h = exitH;
		playR.y = 3 * screenHeight / 4 - exitH / 2;
		SDL_RenderCopy(renderer, exitButton, NULL, &playR);

		playR.x = 3 * screenWidth / 4 - optW / 2 + tempHa;
		playR.y = 2 * screenHeight / 4 - optH / 2;
		playR.w = optW;
		playR.h = optH;
		SDL_RenderCopy(renderer, optionMenu, NULL, &playR);

		/////ICON/////
		SDL_Rect menuIconR;
		SDL_QueryTexture(gameIcon, NULL, NULL, &menuIconR.w, &menuIconR.h);
		menuIconR.x = screenWidth / 4 - menuIconR.w / 2 + tempHa;
		menuIconR.y = screenHeight / 2 - menuIconR.h / 2;
		SDL_RenderCopy(renderer, gameIcon, NULL, &menuIconR);

	}
}

/// <summary>
/// Pre: Initialized GameEngine, selection screen has been selected to be loaded.
/// Post: Rendered selection screen elements.
/// Renders the game selection screen.
/// </summary>
void GameEngine::renderSelectScreen()
{
	////RENDER ANIMATION////
	SDL_Rect optR;
	optR.x = 0;
	optR.y = 0;

	SDL_Rect menuR;
	menuR.x = 0;
	menuR.y = 0;
	if (moveMenu)
	{
		menuR.x = tempHa;
		menuR.x -= (int)round(screenWidth / 30);
		tempHa = menuR.x;
		optR.x = (screenWidth / 2) + tempHa;
		if (menuR.x < -1 * (screenWidth / 2))
		{
			menuR.x = -1 * (screenWidth / 2);
			playMenu = false;
			moveMenu = false;

			int zr = 0;
			DIR *dir;
			struct dirent *ent;
			if ((dir = opendir("..//res//music//")) != NULL) {
				/* print all the files and directories within directory */
				while ((ent = readdir(dir)) != NULL) {
					if (!S_ISDIR(ent->d_type))
					{
						zr++;
					}
				}
			}
			if (zr != oldInt)
				updateFile = true;
			else cout << "NO NEW FILES!" << endl;
			closedir(dir);
			oldInt = zr;
			tempHa = 0;
		}
	}

	optR.w = screenWidth;
	optR.h = screenHeight;
	SDL_RenderCopy(renderer, menuThree, NULL, &optR);

	menuR.w = screenWidth;
	menuR.h = screenHeight;
	SDL_RenderCopy(renderer, menuTwo, NULL, &menuR);

	////RENDER SELECTION SCREEN////
	if (playMenu)
	{
		SDL_Rect textR, menuButR, metaDatR;
		textR.y = screenHeight / 2 - menuButH / 2 - menuButH * (1 + scrollY);

		for (int i = 0; i < scrollY + songListOffset; ++i)
		{
			SDL_QueryTexture(menuText.at(i), NULL, NULL, &textR.w, &textR.h);

			if (i != scrollY)
			{
				int scaling = (int)fabs(scrollY - i);
				SDL_SetTextureAlphaMod(menuButton, 150 - 40 * scaling);
				SDL_SetTextureAlphaMod(menuText.at(i), 150 - 40 * scaling);
				SDL_SetTextureAlphaMod(songArtist.at(i), 150 - 40 * scaling);
				SDL_SetTextureAlphaMod(songLength.at(i), 150 - 40 * scaling);
				SDL_SetTextureAlphaMod(songHigh.at(i), 150 - 40 * scaling);
				menuButR.w = menuButW - 15 * scaling;
				menuButR.h = menuButH - 15 * scaling;
			}
			else
			{
				SDL_SetTextureAlphaMod(menuButton, 255);
				SDL_SetTextureAlphaMod(menuText.at(i), 255);
				SDL_SetTextureAlphaMod(songArtist.at(i), 255);
				SDL_SetTextureAlphaMod(songLength.at(i), 255);
				SDL_SetTextureAlphaMod(songHigh.at(i), 255);
				menuButR.w = menuButW;
				menuButR.h = menuButH;
			}
			textR.x = screenWidth / 4 - textR.w / 2 + tempHa;
			textR.y += menuButH;

			menuButR.x = screenWidth / 4 - menuButR.w / 2 + tempHa;
			menuButR.y = textR.y - menuButR.h / 4;

			if (textR.y > (-1 * menuButH) && textR.y < screenHeight)
			{
				int scaling = (int)fabs(scrollY - i);
				SDL_RenderCopy(renderer, menuButton, NULL, &menuButR);
				SDL_RenderCopy(renderer, menuText.at(i), NULL, &textR);

				SDL_QueryTexture(songArtist.at(i), NULL, NULL, &metaDatR.w, &metaDatR.h);
				metaDatR.x = menuButR.x + 20;
				metaDatR.y = int(menuButR.y + menuButR.h - 15 + 4.5 * scaling - metaDatR.h);
				SDL_RenderCopy(renderer, songArtist.at(i), NULL, &metaDatR);

				SDL_QueryTexture(songLength.at(i), NULL, NULL, &metaDatR.w, &metaDatR.h);
				metaDatR.x = menuButR.x + menuButR.w - 20 - metaDatR.w;
				SDL_RenderCopy(renderer, songLength.at(i), NULL, &metaDatR);

				SDL_QueryTexture(songHigh.at(i), NULL, NULL, &metaDatR.w, &metaDatR.h);
				metaDatR.x = menuButR.x + menuButR.w / 2 - metaDatR.w / 2;
				SDL_RenderCopy(renderer, songHigh.at(i), NULL, &metaDatR);
			}

			menuCoord.push_back(Coordinates(menuButR.x, menuButR.y));
		}

		/////PLAY SOUND/////
		songName = songList.at(scrollY).getSongPath();
		if (Mix_PlayingMusic() == 0)
		if (Mix_PlayMusic(tempSound, -1) == -1) printf("Mix_PlayMusic(tempSound, -1): %s\n", Mix_GetError());

		/////RENDER ICON/////
		SDL_Rect menuIconR;
		SDL_QueryTexture(gameIcon, NULL, NULL, &menuIconR.w, &menuIconR.h);
		menuIconR.x = 3 * screenWidth / 4 - menuIconR.w / 2 + tempHa;
		menuIconR.y = screenHeight / 2 - menuIconR.h / 2;
		SDL_RenderCopy(renderer, gameIcon, NULL, &menuIconR);
	}
}

/// <summary>
/// Pre: Initialized GameEngine, selection screen has been declared to be loaded.
/// Post: Certain actions occur based on mouse inputs.
/// Detects selection screen inputs
/// </summary>
void GameEngine::selectScreenDetect()
{
	if (scrollY >= (int)songList.size()) scrollY = (int)songList.size() - 1;
	else if (scrollY < 0) scrollY = 0;
	songListOffset = (int)songList.size() - scrollY;
	menuCoord.clear();

	Mix_HaltMusic();
	Mix_FreeMusic(tempSound);
	tempSound = Mix_LoadMUS(songList.at(scrollY).getSongPath());
}

/// <summary>
/// Pre: Initialized GameEngine, game not being played.
/// Post: Certain actions occur mased on mouse inputs.
/// Detects the menu inputs
/// </summary>
void GameEngine::menuDetect()
{
	if (playMenu)
	{
		int tempX = screenWidth / 4 - menuButW / 2, tempY = screenHeight / 2 - menuButH / 2 - menuButH / 4;
		if (mouseX >= tempX && mouseX <= tempX + menuButW && mouseY >= tempY && mouseY <= tempY + menuButH)
		{
			Mix_HaltMusic();
			Mix_FreeMusic(tempSound);
			string temp = "Banshee - " + songList.at(scrollY).getFullName();
			SDL_SetWindowTitle(window, temp.c_str());
			SDL_SetWindowGrab(window, SDL_TRUE);

			if (strcmp(songName, "..//res//music//Tutorial.mp3") == 0)
			{
				newTutFalse = false;
				playMenu = false;
				playing = true;
				quitFail = false;
				playTutorial = true;
				visualizerTrue = false;
				firstLaunch = true;
				tutTime = clock();
				tutDiv = 3000;
				tutCount = 0;
				cout << "DAMN TUTORIAL " << endl;
			}
			else
			{
				playMenu = false;
				playing = true;
				cout << "BEGIN PLAYING!" << endl;
			}
			return;
		}
		else
		{
			for (size_t i = 0; i < menuCoord.size(); ++i)
			{
				int scaling = (int)fabs(scrollY - i), menuTempW = menuButW - 18 * scaling, menuTempH = menuButH - 18 * scaling;

				if (mouseX >= menuCoord.at(i).getX() && mouseX <= menuCoord.at(i).getX() + menuTempW && mouseY >= menuCoord.at(i).getY() && mouseY <= menuCoord.at(i).getY() + menuTempH)
				{
					//move scroll up or down.  Further test
					scrollY = i;
					selectScreenDetect();
				}
			}
		}
	}
	else if (!playMenu)
	{
		if (mouseX >= 3 * screenWidth / 4 - playW / 2 - leniency && mouseX <= 3 * screenWidth / 4 - playW / 2 + playW + leniency && mouseY >= screenHeight / 4 - playH / 2 - leniency && mouseY <= screenHeight / 4 - playH / 2 + playH + leniency)
		{
			cout << "HIT PLAYING BUTTON!" << endl;
			selectPlay = true;
			moveMenu = true;
			//playMenu = true;
			//playing = true;
		}
		else if (mouseX >= 3 * screenWidth / 4 - optW / 2 - leniency && mouseX <= 3 * screenWidth / 4 - optW / 2 + optW + leniency && mouseY >= 2 * screenHeight / 4 - optH / 2 - leniency && mouseY <= 2 * screenHeight / 4 - optH / 2 + optH + leniency)
		{
			cout << "OPTIONS!" << endl;
			selectOption = true;
			moveMenu = true;
			//optionTrue = true;
		}
		else if (mouseX >= 3 * screenWidth / 4 - exitW / 2 - leniency && mouseX <= 3 * screenWidth / 4 - exitW / 2 + exitW + leniency && mouseY >= 3 * screenHeight / 4 - exitH / 2 - leniency && mouseY <= 3 * screenHeight / 4 - exitH / 2 + exitH + leniency)
		{
			cout << "EXIT!" << endl;
			playing = false;
			quit = true;
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine, option screen declared to be loaded, variables from option file must be loaded.
/// Post: Rendered option screen.
/// Renders the option screen.
/// </summary>
void GameEngine::renderOption()
{
	////RENDER ANIMATION////
	SDL_Rect optR;
	optR.x = 0;
	optR.y = 0;

	SDL_Rect menuR;
	menuR.x = 0;
	menuR.y = 0;
	if (moveMenu)
	{
		menuR.x = tempHa;
		menuR.x -= (int)round(screenWidth / 30);
		tempHa = menuR.x;
		optR.x = (screenWidth / 2) + tempHa;
		if (menuR.x < -1 * (screenWidth / 2))
		{
			menuR.x = -1 * (screenWidth / 2);
			optionTrue = false;
			moveMenu = false;
			tempHa = 0;
		}
	}

	optR.w = screenWidth;
	optR.h = screenHeight;
	SDL_RenderCopy(renderer, menuThree, NULL, &optR);

	menuR.w = screenWidth;
	menuR.h = screenHeight;
	SDL_RenderCopy(renderer, menuTwo, NULL, &menuR);

	if (optionTrue)
	{
		/////RENDER INIT/////
		SDL_Rect optionR, optTextR, exitSR, exitR;
		SDL_QueryTexture(optionSelectButt, NULL, NULL, &optionR.w, &optionR.h);
		int tempX = optionR.w, tempY = optionR.h;

		if (!openFile)
		{
			oldW = screenWidth;
			oldH = screenHeight;
			oldVol = volumeNum;
			oldFull = fulltrue;
			oldVis = visualizerTrue;

			//cout << "OPENED FILE...YEAH" << endl;

			openFile = true;
		}

		/////RENDER OPTION LIST/////
		for (size_t i = 0; i < optionText.size(); ++i)
		{
			SDL_QueryTexture(optionSelectButt, NULL, NULL, &optionR.w, &optionR.h);
			SDL_QueryTexture(optionText.at(i), NULL, NULL, &optTextR.w, &optTextR.h);
			optionR.x = 250 + optionR.w / 2 + tempHa;
			optionR.y = (i + 1) * screenHeight / 11 - optionR.h / 2;

			optTextR.x = 250 - optionR.w / 2 + tempHa;
			optTextR.y = optionR.y;

			if (dontRend != i)
			{
				SDL_SetTextureAlphaMod(optionSelectButt, 200);
				SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);
				switch (i)
				{
				case 0:
					if (fulltrue)
					{
						SDL_QueryTexture(optionOp.at(0), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(0), NULL, &optionR);
					}
					else
					{
						SDL_QueryTexture(optionOp.at(1), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(1), NULL, &optionR);
					}
					break;
				case 1:
					if (screenWidth == 1920)
					{
						SDL_QueryTexture(optionOp.at(2), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(2), NULL, &optionR);
					}
					else if (screenWidth == 1366)
					{
						SDL_QueryTexture(optionOp.at(3), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(3), NULL, &optionR);
					}
					else if (screenWidth == 1280)
					{
						SDL_QueryTexture(optionOp.at(4), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(4), NULL, &optionR);
					}
					else if (screenWidth == 1250)
					{
						SDL_QueryTexture(optionOp.at(5), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(5), NULL, &optionR);
					}
					else
					{
						SDL_QueryTexture(optionOp.at(6), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(6), NULL, &optionR);
					}
					break;
				case 3:
					if (visualizerTrue)
					{
						SDL_QueryTexture(optionOp.at(7), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(7), NULL, &optionR);
					}
					else
					{
						SDL_QueryTexture(optionOp.at(8), NULL, NULL, &optionR.w, &optionR.h);
						SDL_RenderCopy(renderer, optionOp.at(8), NULL, &optionR);
					}
					break;
				case 4:
					SDL_QueryTexture(optionOp.at(10), NULL, NULL, &optionR.w, &optionR.h);
					SDL_RenderCopy(renderer, optionOp.at(10), NULL, &optionR);
					break;
				case 5:
					SDL_QueryTexture(optionOp.at(11), NULL, NULL, &optionR.w, &optionR.h);
					SDL_RenderCopy(renderer, optionOp.at(11), NULL, &optionR);
					break;
				}
			}
			SDL_RenderCopy(renderer, optionText.at(i), NULL, &optTextR);
		}

		/////SAVE OR EXIT/////
		SDL_QueryTexture(saveexit, NULL, NULL, &exitSR.w, &exitSR.h);
		SDL_QueryTexture(optExit, NULL, NULL, &exitR.w, &exitR.h);

		exitSR.y = (optionText.size() + 2) * screenHeight / 11 - exitSR.h / 2;
		exitR.y = (optionText.size() + 3) * screenHeight / 11 - exitR.h / 2;
		exitSR.x = 250 - tempX / 2 + tempHa;
		exitR.x = 250 - tempX / 2 + tempHa;

		SDL_RenderCopy(renderer, saveexit, NULL, &exitSR);
		SDL_RenderCopy(renderer, optExit, NULL, &exitR);

		////VOLUME NUMBER/////
		SDL_QueryTexture(optSlide, NULL, NULL, &optionR.w, &optionR.h);
		optionR.x = 250 + tempX / 2 + rendVol + tempHa;
		optionR.y = (3) * screenHeight / 11 - optionR.h / 2;
		SDL_RenderCopy(renderer, optSlide, NULL, &optionR);

		SDL_Rect volR;
		SDL_QueryTexture(optVolNum, NULL, NULL, &volR.w, &volR.h);
		volR.x = optionR.x + 200 - rendVol;
		volR.y = optionR.y + 1;
		SDL_RenderCopy(renderer, optVolNum, NULL, &volR);

		/////RENDER ICON/////
		SDL_Rect menuIconR;
		SDL_QueryTexture(gameIcon, NULL, NULL, &menuIconR.w, &menuIconR.h);
		menuIconR.x = 3 * screenWidth / 4 - menuIconR.w / 2 + tempHa;
		menuIconR.y = screenHeight / 2 - menuIconR.h / 2;
		SDL_RenderCopy(renderer, gameIcon, NULL, &menuIconR);

		/////RENDER OPTION BARS/////
		SDL_SetTextureAlphaMod(optionSelectButt, 255);
		SDL_QueryTexture(optionSelectButt, NULL, NULL, &optionR.w, &optionR.h);
		if (rendFull)
		{
			optionR.x = 250 + optionR.w / 2;
			optionR.y = (2) * screenHeight / 22 - optionR.h / 2;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);
			optionR.y = (3) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);

			optionR.y = (2) * screenHeight / 22 - optionR.h / 2;
			SDL_QueryTexture(optionOp.at(0), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(0), NULL, &optionR);

			optionR.y = (3) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_QueryTexture(optionOp.at(1), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(1), NULL, &optionR);
			dontRend = 0;
		}
		else if (rendRes)
		{
			optionR.x = 250 + optionR.w / 2;
			optionR.y = (4) * screenHeight / 22 - optionR.h / 2;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);
			optionR.y = (5) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);
			optionR.y = (6) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);
			optionR.y = (7) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);

			optionR.y = (4) * screenHeight / 22 - optionR.h / 2;
			SDL_QueryTexture(optionOp.at(2), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(2), NULL, &optionR);

			optionR.y = (5) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_QueryTexture(optionOp.at(3), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(3), NULL, &optionR);

			optionR.y = (6) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_QueryTexture(optionOp.at(4), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(4), NULL, &optionR);

			optionR.y = (7) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_QueryTexture(optionOp.at(5), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(5), NULL, &optionR);


			dontRend = 1;
		}
		else if (rendVis)
		{
			optionR.x = 250 + optionR.w / 2;
			optionR.y = (8) * screenHeight / 22 - optionR.h / 2;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);
			optionR.y = (9) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_RenderCopy(renderer, optionSelectButt, NULL, &optionR);

			optionR.y = (8) * screenHeight / 22 - optionR.h / 2;
			SDL_QueryTexture(optionOp.at(7), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(7), NULL, &optionR);

			optionR.y = (9) * screenHeight / 22 - optionR.h / 2 - 5;
			SDL_QueryTexture(optionOp.at(8), NULL, NULL, &optionR.w, &optionR.h);
			SDL_RenderCopy(renderer, optionOp.at(8), NULL, &optionR);

			dontRend = 3;
		}
		else if (rendLeft)
		{
			SDL_SetTextureAlphaMod(menuBG, 240);
			SDL_RenderCopy(renderer, menuBG, NULL, NULL);

			SDL_Rect setButR;
			SDL_QueryTexture(optKeyBut, NULL, NULL, &setButR.w, &setButR.h);
			setButR.w /= 2;
			setButR.h /= 2;
			setButR.x = (screenWidth - setButR.w) / 2;
			setButR.y = (screenHeight - setButR.h) / 2;
			SDL_RenderCopy(renderer, optKeyBut, NULL, &setButR);

			SDL_QueryTexture(optionOp.at(9), NULL, NULL, &setButR.w, &setButR.h);
			setButR.x = (screenWidth - setButR.w) / 2;
			setButR.y = (screenHeight - setButR.h) / 2;
			SDL_RenderCopy(renderer, optionOp.at(9), NULL, &setButR);

			SDL_SetTextureAlphaMod(menuBG, 255);
		}
		else if (rendRight)
		{
			SDL_SetTextureAlphaMod(menuBG, 240);
			SDL_RenderCopy(renderer, menuBG, NULL, NULL);

			SDL_Rect setButR;
			SDL_QueryTexture(optKeyBut, NULL, NULL, &setButR.w, &setButR.h);
			setButR.w /= 2;
			setButR.h /= 2;
			setButR.x = (screenWidth - setButR.w) / 2;
			setButR.y = (screenHeight - setButR.h) / 2;
			SDL_RenderCopy(renderer, optKeyBut, NULL, &setButR);

			SDL_QueryTexture(optionOp.at(9), NULL, NULL, &setButR.w, &setButR.h);
			setButR.x = (screenWidth - setButR.w) / 2;
			setButR.y = (screenHeight - setButR.h) / 2;
			SDL_RenderCopy(renderer, optionOp.at(9), NULL, &setButR);

			SDL_SetTextureAlphaMod(menuBG, 255);
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine, option screen declared to be opened.
/// Post: Certain actions occur based on mouse inputs.
/// Detects inputs for the options screen based on mouse inputs.
/// </summary>
void GameEngine::optionDetect()
{
	int optionW, optionH;
	SDL_Rect exitSR, exitR;
	SDL_QueryTexture(optionSelectButt, NULL, NULL, &optionW, &optionH);
	SDL_QueryTexture(saveexit, NULL, NULL, &exitSR.w, &exitSR.h);
	SDL_QueryTexture(optExit, NULL, NULL, &exitR.w, &exitR.h);

	//Options
	int optXT;
	vector <int> optYT;
	string tempVolOpt;
	if (rendFull)
	{
		optXT = 250 + optionW / 2;
		optYT.push_back((2) * screenHeight / 22 - optionH / 2);
		optYT.push_back((3) * screenHeight / 22 - optionH / 2 - 5);

		for (int i = 0; i < (int)optYT.size(); ++i)
		{
			if (mouseX >= optXT && mouseX <= optXT + optionW && mouseY >= optYT.at(i) && mouseY <= optYT.at(i) + optionH)
			{
				switch (i)
				{
				case 0:
					fulltrue = true;
					tempSW = screenWidth;
					tempSH = screenHeight;
					break;
				case 1:
					fulltrue = false;
					break;
				}
				i = (int)optYT.size();
				upFull = true;
			}
		}

		rendFull = false;
		dontRend = -1;
	}
	else if (rendRes)
	{
		optXT = 250 + optionW / 2;
		optYT.push_back((4) * screenHeight / 22 - optionH / 2);
		optYT.push_back((5) * screenHeight / 22 - optionH / 2 - 5);
		optYT.push_back((6) * screenHeight / 22 - optionH / 2 - 5);
		optYT.push_back((7) * screenHeight / 22 - optionH / 2 - 5);

		for (int i = 0; i < (int)optYT.size(); ++i)
		{
			if (mouseX >= optXT && mouseX <= optXT + optionW && mouseY >= optYT.at(i) && mouseY <= optYT.at(i) + optionH)
			{
				switch (i)
				{
				case 0:
					screenWidth = 1920;
					screenHeight = 1080;
					break;
				case 1:
					screenWidth = 1366;
					screenHeight = 768;
					break;
				case 2:
					screenWidth = 1280;
					screenHeight = 1024;
					break;
				case 3:
					screenWidth = 1250;
					screenHeight = 705;
					break;
				}
				i = (int)optYT.size();
				upResH = true;
				upResW = true;
			}
		}

		tempSW = screenWidth;
		tempSH = screenHeight;
		rendRes = false;
		dontRend = -1;
	}
	else if (rendVis)
	{
		optXT = 250 + optionW / 2;
		optYT.push_back((8) * screenHeight / 22 - optionH / 2);
		optYT.push_back((9) * screenHeight / 22 - optionH / 2 - 5);

		for (int i = 0; i < (int)optYT.size(); ++i)
		{
			if (mouseX >= optXT && mouseX <= optXT + optionW && mouseY >= optYT.at(i) && mouseY <= optYT.at(i) + optionH)
			{
				switch (i)
				{
				case 0:
					visualizerTrue = true;
					break;
				case 1:
					visualizerTrue = false;
					break;
				}
				//cout << "VISUALZER: " << visualizerTrue << ".  " << endl;
				i = (int)optYT.size();
				upVis = true;
			}
		}

		rendVis = false;
		dontRend = -1;
	}
	else
	{
		//Buttons
		for (size_t i = 0; i < optionText.size(); ++i)
		{
			int tempX = 250 + optionW / 2, tempY = (int)(i + 1) * screenHeight / 11 - optionH / 2;
			if (mouseX >= tempX && mouseX <= tempX + optionW && mouseY >= tempY && mouseY <= tempY + optionH)
			{
				//cout << "SOMETHING HAPPENED - " << i << " " << endl;
				switch (i)
				{
				case 0:
					rendFull = true;
					rendRes = rendVis = rendLeft = rendRight = false;
					break;
				case 1:
					rendRes = true;
					rendFull = rendVis = rendLeft = rendRight = false;
					break;
				case 2:
					rendVol = mouseX - (250 + optionW / 2 + optionW) + (250 - optionW / 2) + 17;
					volumeNum = (int)((double)rendVol / 176 * 128);
					if (volumeNum > 128) volumeNum = 128;
					else if (volumeNum < 0) volumeNum = 0;
					upVol = true;
					tempVolOpt = to_string((int)((double)rendVol / 176 * 100));
					optVolNum = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, tempVolOpt.c_str(), { 255, 255, 255, 255 }));
					break;
				case 3:
					rendVis = true;
					rendFull = rendRes = rendLeft = rendRight = false;
					break;
				case 4:
					rendLeft = true;
					rendFull = rendRes = rendVis = rendRight = false;
					break;
				case 5:
					rendRight = true;
					rendFull = rendRes = rendVis = rendLeft = false;
					break;
				}
				i = optionText.size() + 1;
				return;
			}
		}
	}

	optYT.clear();

	//Exit and save
	if (mouseX >= 250 - optionW / 2 && mouseX <= 250 - optionW / 2 + exitSR.w &&
		mouseY >= (int)(optionText.size() + 2) * screenHeight / 12 - optionH / 2 &&
		mouseY <= (int)(optionText.size() + 2) * screenHeight / 12 - exitSR.h / 2 + exitSR.w)
	{
		//If exit is pressed, save settings.  Otherwise, don't.
		string fileName = "..//res//options//options.txt";
		vector <string> stringVec;

		fstream optionF(fileName, fstream::in);
		stringstream buffer;
		string line;

		while (getline(optionF, line))
		{
			istringstream iss(line);
			string temp, use;
			iss >> temp;

			string uploadBuff;

			if (temp == "fullscreen")
			{
				if (upFull)
				{
					uploadBuff = "fullscreen = " + to_string(fulltrue);
					buffer << (uploadBuff.c_str());  //Replace with value
					upFull = false;
				}
				else
				{
					buffer << line;
				}
			}
			else if (temp == "screenheight")
			{
				if (upResH)
				{
					uploadBuff = "screenheight = " + to_string(screenHeight);
					buffer << (uploadBuff.c_str());  //Replace with value				
					upResH = false;
				}
				else
				{
					buffer << line;
				}

			}
			else if (temp == "screenwidth")
			{
				if (upResW)
				{
					uploadBuff = "screenwidth = " + to_string(screenWidth);
					buffer << (uploadBuff.c_str());  //Replace with value
					upResW = false;
				}
				else
				{
					buffer << line;
				}

			}
			else if (temp == "visualizer")
			{
				if (upVis)
				{
					uploadBuff = "visualizer = " + to_string(visualizerTrue);
					buffer << (uploadBuff.c_str());  //Replace with value				
					upVis = false;
				}
				else
				{
					buffer << line;
				}

			}
			else if (temp == "volume")
			{
				if (upVol)
				{
					uploadBuff = "volume = " + to_string(volumeNum);
					buffer << (uploadBuff.c_str());  //Replace with value
					upVol = false;
				}
				else
				{
					buffer << line;
				}
			}
			else if (temp == "mouseOne")
			{
				if (upKey)
				{
					uploadBuff = "mouseOne = " + keyOne;
					buffer << (uploadBuff.c_str());  //Replace with value
				}
				else
				{
					buffer << line;
				}
			}
			else if (temp == "mouseTwo")
			{
				if (upKey)
				{
					uploadBuff = "mouseTwo = " + keyTwo;
					buffer << (uploadBuff.c_str());  //Replace with value
					upKey = false;
				}
				else
				{
					buffer << line;
				}
			}
			else
			{
				buffer << line;
			}
			buffer << endl;
		}
		optionF.close();
		optionF.clear();

		optionF.open(fileName, fstream::out);
		optionF << buffer.str();
		optionF.close();


		/*
		fullscreen = 0
		screenheight = 705
		screenwidth = 1250
		newplayer = 1
		volume = 50
		visualizer = 1
		*/
		//SDL_SetWindowSize(window, optionX, optionX);

		playMenu = false;
		moveMenu = true;
		//optionTrue = false;
		completeGame = false;
		rendFull = rendRes = rendVis = rendLeft = rendRight = false;
		dontRend = -1;
		openFile = false;
		cout << "SAVED. " << endl;
	}
	else if (mouseX >= 250 - optionW / 2 && mouseX <= 250 - optionW / 2 + exitSR.w &&
		mouseY >= (int)(optionText.size() + 3) * screenHeight / 12 - exitR.h / 2 &&
		mouseY <= (int)(optionText.size() + 3) * screenHeight / 12 - exitR.h / 2 + exitSR.w)
	{
		playMenu = false;
		moveMenu = true;
		//optionTrue = false;
		completeGame = false;
		rendFull = rendRes = rendVis = rendLeft = rendRight = false;
		dontRend = -1;

		screenWidth = oldW;
		screenHeight = oldH;
		volumeNum = oldVol;
		visualizerTrue = oldVis;
		fulltrue = oldFull;
		tempSH = oldH;
		tempSW = oldW;

		openFile = false;

		cout << "EXITED." << endl;
	}
	else
	{
		rendFull = rendRes = rendVis = rendLeft = rendRight = false;
		dontRend = -1;
	}
	setVar();
}

/// <summary>
/// Pre: Initialized GameEngine, songName must have a value.
/// Post: Returns the value of "songName".
/// Returns songName.
/// </summary>
/// <returns></returns>
char* GameEngine::getsongName()
{
	return songName;
}

/// <summary>
/// Pre: Initialized GameEngine, game must be being played, pause must have been called.
/// Post: Rendered elements based on pre-paused game.
/// Captures rendered elements of the game when paused to be rendered while paused, and renders them.
/// </summary>
void GameEngine::pauseTheGame()
{
	SDL_Rect pauseR;
	pauseR.w = stopPW;
	pauseR.h = stopPH;

	SDL_RenderCopy(renderer, pauseOver, NULL, NULL);

	pausePx = pauseR.x = screenWidth / 4 - stopPW / 2;
	pausePy = pauseR.y = screenHeight / 4 - stopPH / 2;
	SDL_RenderCopy(renderer, pauseCont, NULL, &pauseR);

	pauseR.w = pauseRW;
	pauseReX = pauseR.x = 2 * screenWidth / 4 - pauseRW / 2;
	pauseReY = pauseR.y = 2 * screenHeight / 4 - stopPH / 2;
	SDL_RenderCopy(renderer, pauseRetry, NULL, &pauseR);

	pauseR.w = pauseSW;
	pauseSX = pauseR.x = 3 * screenWidth / 4 - pauseSW / 2;
	pauseSY = pauseR.y = 3 * screenHeight / 4 - stopPH / 2;
	SDL_RenderCopy(renderer, pauseStop, NULL, &pauseR);
}

/// <summary>
/// Pre: Initialized GameEngine, game must be being played, game must have been paused.
/// Post: Returns actions based on mouse inputs.
/// Detects paused actions based on mouse inputs.
/// </summary>
void GameEngine::pauseDetect()
{
	if (!unpauseGame)
	{
		if (mouseX >= pausePx - leniency && mouseX <= pausePx + stopPW + leniency && mouseY >= pausePy && mouseY <= pausePy + stopPH + leniency)
		{
			//pausedGame = false;
			//getClock();
			if (!playTutorial) unpauseGame = true;
			else if (playTutorial)
			{
				getClock();
				pausedGame = false;
			}
			cout << "RESUMING" << endl;
		}
		else if (mouseX >= pauseReX - leniency && mouseX <= pauseReX + pauseRW + leniency && mouseY >= pauseReY - leniency && mouseY <= pauseReY + stopPH + leniency)
		{
			playing = false;
			retryGame = true;

			newTutFalse = false;
			playMenu = false;
			quitFail = false;
			playTutorial = true;
			visualizerTrue = false;
			tutTime = clock();
			tutDiv = 3000;
			tutCount = 0;
			cout << "RETRY! " << endl;
		}
		else if (mouseX >= pauseSX - leniency && mouseX <= pauseSX + pauseSW + leniency && mouseY >= pauseSY - leniency && mouseY <= pauseSY + stopPH + leniency)
		{
			SDL_SetWindowTitle(window, "Banshee");
			SDL_SetWindowGrab(window, SDL_FALSE);

			newTutFalse = false;
			firstLaunch = false;
			playing = false;
			playTutorial = false;
			visualizerTrue = true;
			displayCirc = true;

			tutRewrite();

			cout << "BACK TO MENU!" << endl;
		}
	}
	else if (unpauseGame)
	{
		if (mouseX >= pauseMx && mouseX <= pauseMx + pauseMW && mouseY >= pauseMy && mouseY <= pauseMy + pauseMH)
		{
			pausedGame = false;
			getClock();
			unpauseGame = false;
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine, "paused" must have a value.
/// Post: Returns the value of "paused".
/// Returns "paused".
/// </summary>
/// <returns></returns>
bool GameEngine::getPaused()
{
	return pausedGame;
}

/// <summary>
/// Pre: Initialized GameEngine, foo must have a value of either true or false.
/// Post: Whether the game is paused or not is set.
/// Sets "paused".
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void GameEngine::setPaused(bool foo)
{
	pausedGame = false;
}

/// <summary>
/// Pre: Initialized GameEngine, game must be being played, game must be paused.
/// Post: Sets and renders elements when game is paused.
/// Freezes game elements for the pause screen.
/// </summary>
void GameEngine::pauseFreeze()
{
	SDL_Rect hitR;
	hitR.w = hitW;
	hitR.h = hitH;

	SDL_Rect indic;

	for (size_t i = 0; i < hitcircle.size(); ++i)
	{
		hitR.x = (int)hitcircle.at(i).getX();
		hitR.y = (int)hitcircle.at(i).getY();
		SDL_RenderCopy(renderer, hitmarker, NULL, &hitR);

		indic.w = (int)hitcircle.at(i).getIndW();
		indic.h = (int)hitcircle.at(i).getIndH();
		indic.x = hitR.x + hitR.w / 2 - indic.w / 2;
		indic.y = hitR.y + hitR.h / 2 - indic.h / 2;
		SDL_RenderCopy(renderer, circle, NULL, &indic);

		SDL_Rect hitnumber;
		hitnumber.h = numxH;
		hitnumber.w = numxW;
		hitnumber.x = hitR.x + hitW / 2 - numxW / 2;
		hitnumber.y = hitR.y + hitH / 2 - numxH / 2;

		if (hitcircle.at(i).getNumber() == 1)
			SDL_RenderCopy(renderer, numOne, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 2)
			SDL_RenderCopy(renderer, numTwo, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 3)
			SDL_RenderCopy(renderer, numThree, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 4)
			SDL_RenderCopy(renderer, numFour, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 5)
			SDL_RenderCopy(renderer, numFive, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 6)
			SDL_RenderCopy(renderer, numSix, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 7)
			SDL_RenderCopy(renderer, numSeven, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 8)
			SDL_RenderCopy(renderer, numEight, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 9)
			SDL_RenderCopy(renderer, numNine, NULL, &hitnumber);
		else if (hitcircle.at(i).getNumber() == 0)
			SDL_RenderCopy(renderer, numZero, NULL, &hitnumber);

		if (hitcircle.at(i).getColour() == 1) SDL_RenderCopy(renderer, hitWhite, NULL, &hitR);
		else if (hitcircle.at(i).getColour() == 2) SDL_RenderCopy(renderer, hitRed, NULL, &hitR);
		else if (hitcircle.at(i).getColour() == 3) SDL_RenderCopy(renderer, hitGreen, NULL, &hitR);
		else if (hitcircle.at(i).getColour() == 4) SDL_RenderCopy(renderer, hitBlue, NULL, &hitR);
		else if (hitcircle.at(i).getColour() == 5) SDL_RenderCopy(renderer, hitYellow, NULL, &hitR);
	}

	if (unpauseGame)
	{
		SDL_Rect orangeR;
		orangeR.w = pauseMW;
		orangeR.h = pauseMH;

		if (hitcircle.size() >= 1)
		{
			orangeR.x = (int)hitcircle.at(0).getX();
			orangeR.y = (int)hitcircle.at(0).getY() - 25;
		}
		else
		{
			orangeR.x = screenWidth / 2 - pauseMW / 2;
			orangeR.y = screenHeight / 2 - pauseMH / 2;
		}

		if (orangeR.y < 0) orangeR.y = pauseMH;
		else if (orangeR.y > screenHeight) orangeR.y = screenHeight - pauseMH;

		pauseMx = orangeR.x;
		pauseMy = orangeR.y;

		SDL_RenderCopy(renderer, pauseMarker, NULL, &orangeR);
	}
}

/// <summary>
/// Pre: Initialized GameEngine, game must be being played.
/// Post: Certain actions occur when hitcircles are being hit.
/// Detects hitcircles being hit.
/// </summary>
void GameEngine::hitDetect()
{
	if (hitcircle.size() >= 1)  //NEEDED TO STOP CALLING UNAVALIABLE HITCIRCLES
	{
		if (mouseX >= hitcircle.at(0).getX() && mouseX <= hitcircle.at(0).getX() + hitW)
		{
			if (mouseY >= hitcircle.at(0).getY() && mouseY <= hitcircle.at(0).getY() + hitH)
			{
				hitPoint.push_back(hitcircle.at(0));
				if (hitPoint.back().getType() == 2)
				{
					cout << "HIT!" << endl;
					Mix_PlayChannel(-1, hitSound, 0);
					hitPoint.back().setType(100); //<-Means 100 points, obviously :/
					hitPoint.back().setTime(clock());
					combo++;
					score += 100 * combo;
					failCount = 0;
					hitcircle.erase(hitcircle.begin());
					totAcc++;
				}
				else if (hitPoint.back().getType() == 3)
				{
					cout << "Hit... sort of." << endl;
					Mix_PlayChannel(-1, hitSound, 0);
					hitPoint.back().setType(101); //<-Means 50 points, obviously :p
					hitPoint.back().setTime(clock());
					combo++;
					score += 50 * combo;
					failCount = 0;
					hitcircle.erase(hitcircle.begin());
					totAcc += 0.5;
				}
				else if (hitPoint.back().getType() == 1)
				{
					cout << "MISS!" << endl;
					combo = 0;
					hitPoint.back().setType(102); //<-Means 0 points, obviously :3
					hitPoint.back().setTime(clock());
					hitcircle.erase(hitcircle.begin());
					if (quitFail) failCount++;
				}
			}
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine.  Game must be being played.
/// Post: Returns time.
/// Returns time.  For debugging.
/// </summary>
/// <returns></returns>
string GameEngine::makeTime()  //<- For Debugging purposes only.  
{
	milli = clock() - initTime;
	seconds = (milli / 1000);
	milli = milli - (seconds * 1000);
	minutes = seconds / 60;
	seconds = seconds - (minutes * 60);

	return to_string(minutes) + ":" + to_string(seconds) + ":" + to_string(milli);
}

/// <summary>
/// Pre: Initialized GameEngine, game must be being played, game must have been paused.
/// Post: Fixes time values when game is paused.
/// Gets the correct time values for hitcircles after pausing.
/// </summary>
void GameEngine::getClock()
{
	int numClock = clock() - tempClock;
	for (size_t i = 0; i < hitcircle.size(); ++i)
	{
		hitcircle.at(i).addDelay(numClock);
	}
	for (size_t i = 0; i < hitPoint.size(); ++i)
	{
		hitPoint.at(i).addDelay(numClock);
	}
}

/// <summary>
/// Pre: Initialized GameEngine, game must have failed.
/// Post: Rendered elements on window.
/// Render the window when user fails.
/// </summary>
void GameEngine::renderFail()
{
	////RENDER ANIMATION////
	SDL_Rect optR;
	optR.x = 0;
	optR.y = 0;

	SDL_Rect menuR;
	menuR.x = 0;
	menuR.y = 0;
	if (moveMenu)
	{
		menuR.x = tempHa;
		menuR.x += (int)round(screenWidth / 30);
		tempHa = menuR.x;
		optR.x = -1 * (screenWidth / 2) + tempHa;
		if (menuR.x > screenWidth / 2)
		{
			menuR.x = screenWidth / 2;
			playing = false;
			completeGame = false;
			failLost = false;
			moveMenu = false;
			tempHa = 0;
		}
		optR.w = screenWidth;
		optR.h = screenHeight;
		SDL_RenderCopy(renderer, menuThree, NULL, &optR);
	}

	menuR.w = screenWidth;
	menuR.h = screenHeight;
	SDL_RenderCopy(renderer, failBack, NULL, &menuR);

	if (failLost)
	{
		SDL_Rect failOptionR;
		failOptionR.h = stopPH;

		failOptionR.w = pauseRW;
		failRx = failOptionR.x = 2 * screenWidth / 4 - pauseRW / 2 + tempHa;
		failRy = failOptionR.y = 2 * screenHeight / 4 - stopPH / 2;
		SDL_RenderCopy(renderer, pauseRetry, NULL, &failOptionR);

		failOptionR.w = pauseSW;
		failQx = failOptionR.x = 2 * screenWidth / 4 - pauseSW / 2 + tempHa;
		failQy = failOptionR.y = 3 * screenHeight / 4 - stopPH / 2;
		SDL_RenderCopy(renderer, pauseStop, NULL, &failOptionR);

		SDL_Rect failR;
		failR.h = failH;
		failR.w = failW;
		failR.x = screenWidth / 2 - failW / 2 + tempHa;
		failR.y = screenHeight / 6 - failH / 2;
		SDL_RenderCopy(renderer, youFailed, NULL, &failR);
	}
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Returns "failLost".
/// Gets if the game has failed.
/// </summary>
/// <returns></returns>
bool GameEngine::getFail()
{
	return failLost;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Gets "failLost".
/// Sets if the game has failed.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void GameEngine::setFail(bool foo)
{
	failLost = foo;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Gets "retry".
/// Sets if the game was retried.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void GameEngine::setRetry(bool foo)
{
	retryGame = foo;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Sets "retry".
/// Gets if the game was retried.
/// </summary>
/// <returns></returns>
bool GameEngine::getRetry()
{
	return retryGame;
}

/// <summary>
/// Pre: Initialized GameEngine, game must have been failed.
/// Post: Actions occur based on failing and mouse inputs.
/// Detect mouse inputs after failing the game.
/// </summary>
void GameEngine::failDetect()
{
	if (mouseX >= failRx - leniency && mouseX <= failRx + pauseRW + leniency && mouseY >= failRy && mouseY <= failRy - leniency + stopPH + leniency)
	{
		retryGame = true;
		failLost = false;
		playing = true;
		cout << "RETRY" << endl;
	}
	else if (mouseX >= failQx - leniency && mouseX <= failQx + pauseSW + leniency && mouseY >= failQy && mouseY <= failQy - leniency + stopPH + leniency)
	{
		//failLost = false;
		moveMenu = true;
		SDL_SetWindowTitle(window, "Banshee");
		SDL_SetWindowGrab(window, SDL_FALSE);
		cout << "BACK TO MENU" << endl;
	}
}

/// <summary>
/// Pre: Initialized GameEngine, game must have been passed.
/// Post: Renders elements based on passing the game.
/// Renders the pass elements.
/// </summary>
void GameEngine::renderPass()
{
	////RENDER ANIMATION////
	SDL_Rect optR;
	optR.x = 0;
	optR.y = 0;

	SDL_Rect menuR;
	menuR.x = 0;
	menuR.y = 0;
	if (moveMenu)
	{
		menuR.x = tempHa;
		menuR.x -= (int)round(screenWidth / 30);
		tempHa = menuR.x;
		optR.x = (screenWidth / 2) + tempHa;
		if (menuR.x < -1 * (screenWidth / 2))
		{
			menuR.x = -1 * (screenWidth / 2);
			playing = false;
			completeGame = false;
			failLost = false;
			moveMenu = false;
			tempHa = 0;
			highNew = false;
		}
	}

	optR.w = screenWidth;
	optR.h = screenHeight;
	SDL_RenderCopy(renderer, menuThree, NULL, &optR);

	menuR.w = screenWidth;
	menuR.h = screenHeight;
	SDL_RenderCopy(renderer, menuTwo, NULL, &menuR);

	////RENDER OTHER STUFF////
	if (completeGame)
	{
		//Calculate Accuracy once
		if (!calcAccu)
		{
			finAcc = round((totAcc / numBeats) * 10000) / 100;
			string tempAcc = to_string(finAcc);
			scoreAcc = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSand, tempAcc.substr(0, tempAcc.find(".") + 3).c_str(), { 255, 255, 255, 255 }));
			SDL_QueryTexture(scoreAcc, NULL, NULL, &scorAccW, &scorAccH);

			string scoreStr = to_string(score);
			finScore = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSand, scoreStr.c_str(), { 255, 255, 255, 255 }));
			SDL_QueryTexture(finScore, NULL, NULL, &finScorW, &finScorH);
			calcAccu = true;

			for (size_t i = 0; i < songList.size(); ++i)
			{
				if (songList.at(i).getSongPath() == songName)
				{
					highNew = (stoi(scoreStr) > stoi(songList.at(i).getHighScore()));
					songList.at(i).setHighScore(scoreStr);
					//cout << "SONG: " << songList.at(i).getFullName() << ", SCORE: " << songList.at(i).getHighScore() << endl;
					i = songList.size() + 1;
					highScore();
				}
			}

			//cout << "NUMBER OF BEATS: " << numBeats << ", TOTAL ACC: " << totAcc << endl;

			numBeats = 0;
			finAcc = 0;
			totAcc = 0;
			score = 0;
		}

		//Render accuracy
		SDL_Rect scoreAccR;
		scoreAccR.h = scorAccH;
		scoreAccR.w = scorAccW;
		scoreAccR.x = 11 * screenWidth / 32 - accuW / 2 + tempHa;
		scoreAccR.y = 5 * screenHeight / 16 - scorAccH / 2;
		SDL_RenderCopy(renderer, scoreAcc, NULL, &scoreAccR);

		//Render accuracy text
		SDL_Rect accuR;
		accuR.w = accuW;
		accuR.h = accuH;
		accuR.x = 11 * screenWidth / 32 - accuW / 2 + tempHa;
		accuR.y = 3 * screenHeight / 16 - scorAccH / 2;
		SDL_RenderCopy(renderer, accuracy, NULL, &accuR);

		//Render score
		SDL_Rect scoreR;
		scoreR.w = finScorW;
		scoreR.h = finScorH;
		scoreR.x = 2 * screenWidth / 16 - accuW / 2 + tempHa;
		scoreR.y = 5 * screenHeight / 16 - scorAccH / 2;
		SDL_RenderCopy(renderer, finScore, NULL, &scoreR);

		//Render score text
		SDL_Rect scrTxtR;
		scrTxtR.w = scoreTexW;
		scrTxtR.h = scoreTexH;
		scrTxtR.x = 2 * screenWidth / 16 - accuW / 2 + tempHa;
		scrTxtR.y = 3 * screenHeight / 16 - scorAccH / 2;
		SDL_RenderCopy(renderer, scoreTexture, NULL, &scrTxtR);

		//Render exit text
		SDL_Rect exitR;
		exitR.w = exitW;
		exitR.h = exitH;
		exitPaX = exitR.x = screenWidth / 8 - accuW / 2 + tempHa;
		exitPaY = exitR.y = 7 * screenHeight / 8 - scorAccH / 2;
		SDL_RenderCopy(renderer, exitButton, NULL, &exitR);

		//Render replay text
		SDL_Rect replayR;
		replayR.w = replayW;
		replayR.h = replayH;
		replayPaX = replayR.x = screenWidth / 8 - accuW / 2 + tempHa;
		replayPaY = replayR.y = 6 * screenHeight / 8 - scorAccH / 2;
		SDL_RenderCopy(renderer, replay, NULL, &replayR);

		//Render High Score
		if (highNew)
		{
			SDL_Rect highR;
			SDL_QueryTexture(highScText, NULL, NULL, &highR.w, &highR.h);
			highR.x = 2 * screenWidth / 8 - highR.w / 2 + tempHa;
			highR.y = 9 * screenHeight / 16 - highR.h / 2;
			SDL_RenderCopy(renderer, highScText, NULL, &highR);
		}

		/////RENDER ICON/////
		SDL_Rect menuIconR;
		SDL_QueryTexture(gameIcon, NULL, NULL, &menuIconR.w, &menuIconR.h);
		menuIconR.x = 3 * screenWidth / 4 - menuIconR.w / 2 + tempHa;
		menuIconR.y = screenHeight / 2 - menuIconR.h / 2;
		SDL_RenderCopy(renderer, gameIcon, NULL, &menuIconR);
	}
}

/// <summary>
/// Pre: Initialized GameEngine, game must have been passed.
/// Post: Actions occur based on mouse inputs for passing the game.
/// Detects mouse input for passing the game.
/// </summary>
void GameEngine::passDetect()
{
	if (mouseX >= exitPaX - leniency && mouseX <= exitPaX + exitW + leniency && mouseY >= exitPaY - leniency && mouseY <= exitPaY + exitH + leniency)
	{
		//playing = false;
		//completeGame = false;
		moveMenu = true;
		SDL_SetWindowTitle(window, "Banshee");
		SDL_SetWindowGrab(window, SDL_FALSE);
		cout << "EXIT - PASS!" << endl;
	}
	else if (mouseX >= replayPaX - leniency && mouseX <= replayPaX + replayW + leniency && mouseY >= replayPaY - leniency && mouseY <= replayPaY + replayH + leniency)
	{
		retryGame = true;
		completeGame = false;
		playing = true;
		cout << "REPLAY - PASS!" << endl;
	}
}

/// <summary>
/// Sets the pass.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void GameEngine::setPass(bool foo)
{
	completeGame = foo;
}

/// <summary>
/// Gets the pass.
/// </summary>
/// <returns></returns>
bool GameEngine::getPass()
{
	return completeGame;
}

/// <summary>
/// Pre: Initialized GameEngine, variables must be passed.
/// Post: Songdata vector is filled.
/// Passes the filelist variables to a Songdata vector.
/// </summary>
/// <param name="bar">if set to <c>true</c> [bar].</param>
/// <param name="songName">Name of the song.</param>
/// <param name="songArtist">The song artist.</param>
/// <param name="length">The length.</param>
/// <param name="filePath">The file path.</param>
void GameEngine::passFile(bool bar, string songName, string songArtist, int length, char* filePath)
{
	if (bar)
	{
		songList.clear();
	}
	SongData temp = SongData(songName, songArtist, length, filePath);
	songList.push_back(temp);
}

/// <summary>
/// Pre: Initialized GameEngine, SongData vector must be populated.
/// Post: Sorted SongData vector.
/// Sorts the files in the SongData vector.
/// </summary>
void GameEngine::sortFiles()
{
	vector <string> tempList;
	sort(songList.begin(), songList.end());

	for (size_t i = 0; i < songList.size(); ++i)
	{
		tempList.push_back(songList.at(i).getSongName());
	}

	songLength.clear();
	songArtist.clear();
	menuText.clear();
	scrollY = 0;

	songListOffset = (int)tempList.size();

	highScore();

	for (size_t i = 0; i < tempList.size(); ++i)
	{
		char* tempChar = (_strdup(tempList.at(i).c_str()));
		SDL_Texture *testText = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(aileronsLarge, tempChar, { 255, 255, 255, 255 }));
		menuText.push_back(testText);

		string tempArtS = "Artist: " + songList.at(i).getArtist();
		string tempLenS = "Length: " + songList.at(i).getSongLength();
		string tempHigS = "Highscore: " + songList.at(i).getHighScore();
		SDL_Texture *tempArtist = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, tempArtS.c_str(), { 255, 255, 255, 255 }));
		SDL_Texture *tempLength = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, tempLenS.c_str(), { 255, 255, 255, 255 }));
		SDL_Texture *tempHigh = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(quickSandSmall, tempHigS.c_str(), { 255, 255, 255, 255 }));
		songLength.push_back(tempLength);
		songArtist.push_back(tempArtist);
		songHigh.push_back(tempHigh);
	}

	/*cout << "SIZES: MENU: " << menuText.size() << ", LENGTH: "
		<< songLength.size() << ", ARTIST: " << songArtist.size()
		<< ", OFFSET: " << songListOffset << ", " << endl;
	*/
	tempSound = Mix_LoadMUS(songList.at(0).getSongPath());
	if (!tempSound)
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
	tempList.clear();
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Text file is filled based on if there is a new high score.
/// Passes high score values to the text file.
/// </summary>
void GameEngine::highScore()
{
	////HIGH SCORE PASSING////
	string fileName = "..//res//options//highscore.txt";
	vector <string> stringVec;
	stringstream buffer;
	string line;

	if (!fileExists(fileName))
	{
		fstream mystream(fileName, ios::out);
		mystream.close();
	}
	else
	{
		ifstream myStream;
		myStream.open(fileName);
		while (getline(myStream, line))
		{
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			replace(line.begin(), line.end(), '=', ' ');

			istringstream iss(line);
			string temp, use;
			iss >> temp;
			iss >> use;
			stringVec.push_back(use);

			for (size_t i = 0; i < songList.size(); ++i)
			{
				if (songList.at(i).getTrimmedName() == temp)
				{
					if (songList.at(i).getHighScore() == "0")
					{
						songList.at(i).setHighScore(use);
						//cout << "LIST: " << songList.at(i).getFullName() << ", USE: " << use << endl;
					}
				}
			}

			line = "";
		}
	}

	for (size_t i = 0; i < songList.size(); ++i)
	{
		buffer << songList.at(i).getFullName() + " = " + songList.at(i).getHighScore() + "\n";
		//cout << "LIST: " << songList.at(i).getFullName() << endl;
	}

	fstream optionF(fileName, fstream::in | fstream::out);
	optionF << buffer.str();
	optionF.close();
}

/// <summary>
/// Pre: Initialized GameEngine, passed frequency vectors.
/// Post: Renders a graph based on passed frequency vectors.
/// Draws the graph.
/// </summary>
void GameEngine::drawGraph()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (graphPoints.size() >= graphPrep.size())
	{
		for (size_t i = 0; i < graphPrep.size(); ++i)
		{
			if (i > 0)
			{
				SDL_Rect graphR;
				graphR.x = (35 * (i - 1) - 1);
				graphR.y = graphPrep.at(i).getY() + 10;
				graphR.w = (35 * i - 1) - (35 * (i - 1) - 1);
				graphR.h = (int)(screenHeight - graphPrep.at(i).getY() + 10);
				if (graphR.x >= screenWidth / 30 && graphR.x + graphR.w <= 29 * screenWidth / 30)
				{
					SDL_RenderCopy(renderer, visualizer, NULL, &graphR);
				}
				//cout << "RENDER AT X, Y: " << (35 * (i - 1) - 1) << ", " << graphPrep.at(i).getY() + 10 << endl;
				//cout << "SIZE: " << graphPrep.size() << endl;
			}

			if (graphPrep.at(i).getMaxed())
			{
				if (graphPrep.at(i).getY() < screenHeight) graphPrep.at(i).setY(graphPrep.at(i).getY() + 7);
				else graphPrep.at(i).setMaxed(false);
			}
			else
			{
				if (graphPrep.at(i).getY() > graphPoints.at(i))
				{
					graphPrep.at(i).setY(graphPrep.at(i).getY() - 35);
				}
				else
				{
					graphPrep.at(i).setMaxed(true);
					graphPoints.at(i) = (float)(screenHeight + 1); //HERE?
				}
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

/// <summary>
/// Pre: Initialized GameEngine, frequency array.
/// Post: Populated frequency vector.
/// Passes the frequency array to the vector.
/// </summary>
/// <param name="foo">The foo.</param>
void GameEngine::passGraph(float * foo)
{
	int size = 216 - (screenWidth / 35 + 2) / 2;
	graphPoints.clear();
	for (int i = size; i < screenWidth / 35 + 2 + size; ++i)
	{
		float temp = 0;
		if (foo[i] > 0)
		{
			temp = 10 / foo[i];
			if (temp > screenHeight)
			{
				temp /= 500;
				temp += screenHeight / 2;
			}
			else if (temp < 0)
			{
				temp *= 500;
				temp += screenHeight / 2;
			}

			graphPoints.push_back(temp);
		}
		/*while (graphPoints.size() > (size_t)(screenWidth / 35 + 2))
		{
			graphPoints.erase(graphPoints.begin());
		}*/
		//cout << "VALUE OF FOO: " << graphPoints.back() << ", I: " << i << endl;
	}
	for (size_t j = 0; j < graphPrep.size(); ++j)
	{
		graphPrep.at(j).setMaxed(false);
	}
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Returns volume.
/// Returns the game's volume.
/// </summary>
/// <returns></returns>
int GameEngine::getVol()
{
	return volumeNum;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Sets volume.
/// Sets the game's volume.
/// </summary>
/// <param name="foo">The foo.</param>
void GameEngine::setOldInt(int foo)
{
	oldInt = foo;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Sets whether or not the song files have been updated.
/// Sets if song files have been updated or not.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void GameEngine::setUpdateFile(bool foo)
{
	updateFile = foo;
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Gets if song files have been updated.
/// Gets if song files have been updated or not.
/// </summary>
/// <returns></returns>
bool GameEngine::getUpdateFile()
{
	return updateFile;
}

/// <summary>
/// Pre: Initialized GameEngine, tutorial has been selected to be played.
/// Post: Returns elements for the tutorial.
/// Renders the tutorial.
/// </summary>
void GameEngine::renderTutorial()
{
	if (newTutFalse)
	{
		SDL_SetTextureAlphaMod(menuBG, 240);
		SDL_RenderCopy(renderer, menuBG, NULL, NULL);
		SDL_SetTextureAlphaMod(menuBG, 255);

		SDL_Rect setButR;
		SDL_QueryTexture(optKeyBut, NULL, NULL, &setButR.w, &setButR.h);
		setButR.w /= 2;
		int tempW = setButR.w += 60;
		setButR.h /= 2;
		int tempH = setButR.h += 50;
		setButR.x = (screenWidth - setButR.w) / 2;
		setButR.y = (screenHeight - setButR.h) / 2;
		SDL_RenderCopy(renderer, optKeyBut, NULL, &setButR);

		setButR.w = tempW / 4;
		setButR.h = tempH / 4;
		setButR.x = screenWidth / 2 - tempW / 2 + 50;
		setButR.y = screenHeight / 2 + tempH / 2 - 5;
		SDL_RenderCopy(renderer, optKeyBut, NULL, &setButR);

		SDL_QueryTexture(yesText, NULL, NULL, &setButR.w, &setButR.h);
		setButR.x = screenWidth / 2 - tempW / 2 + 50 + setButR.w / 2;
		SDL_RenderCopy(renderer, yesText, NULL, &setButR);

		setButR.w = tempW / 4;
		setButR.h = tempH / 4;
		setButR.x = screenWidth / 2 + tempW / 2 - 50 - setButR.w;
		SDL_RenderCopy(renderer, optKeyBut, NULL, &setButR);

		SDL_QueryTexture(noText, NULL, NULL, &setButR.w, &setButR.h);
		setButR.x = screenWidth / 2 + tempW / 2 - 50 - tempW / 4 + setButR.w / 2;
		SDL_RenderCopy(renderer, noText, NULL, &setButR);

		SDL_QueryTexture(WYKtextO, NULL, NULL, &setButR.w, &setButR.h);
		setButR.x = (screenWidth - setButR.w) / 2;
		setButR.y = (screenHeight - setButR.h) / 2 - setButR.h;
		SDL_RenderCopy(renderer, WYKtextO, NULL, &setButR);
		SDL_QueryTexture(WYKtextT, NULL, NULL, &setButR.w, &setButR.h);
		setButR.x = (screenWidth - setButR.w) / 2;
		setButR.y = (screenHeight - setButR.h) / 2 + setButR.h;
		SDL_RenderCopy(renderer, WYKtextT, NULL, &setButR);
	}
	else if (!newTutFalse && playing && playTutorial && !pausedGame)
	{
		//Longer at 7,8,14	

		SDL_Rect setTextR;
		if (tutCount == 7)
		{
			if (senpTut == 0) senpTut = clock();
			if (clock() - senpTut < 2000) tutCount = 7;
			else
			{
				tutTime = tutTime + (clock() - senpTut) - 1000;
				senpTut = 0;
				tutCount = (int)(clock() - tutTime) / tutDiv;
			}
		}
		else if (tutCount == 8)
		{
			if (senpTut == 0) senpTut = clock();
			if (clock() - senpTut < 2000) tutCount = 8;
			else
			{
				tutTime = tutTime + (clock() - senpTut) - 1000;
				senpTut = 0;
				tutCount = (int)(clock() - tutTime) / tutDiv;
			}
		}
		else if (tutCount == 10)
		{
			tutCount = (int)(clock() - tutTime) / tutDiv;
			SDL_SetTextureAlphaMod(menuBG, 240);
			SDL_RenderCopy(renderer, menuBG, NULL, NULL);
			SDL_SetTextureAlphaMod(menuBG, 255);
			tutDiv = 3000;

			SDL_Rect hitR;
			SDL_Rect hitnumber;
			SDL_QueryTexture(hitmarker, NULL, NULL, &hitR.w, &hitR.h);
			SDL_QueryTexture(numZero, NULL, NULL, &hitnumber.w, &hitnumber.h);

			hitR.x = (screenWidth - hitR.w) / 2;
			hitnumber.x = (screenWidth - hitnumber.w) / 2;
			hitR.y = 3 * screenHeight / 4 - hitR.h / 2;
			hitnumber.y = 3 * screenHeight / 4 - hitnumber.h / 2;

			SDL_RenderCopy(renderer, hitmarker, NULL, &hitR);
			SDL_RenderCopy(renderer, numZero, NULL, &hitnumber);
		}
		else if (tutCount == 14)
		{
			if (senpTut == 0) senpTut = clock();
			if (clock() - senpTut < 6000)
			{
				tutCount = 14;
			}

			else
			{
				tutTime = tutTime + (clock() - senpTut) - 1000;
				senpTut = 0;
				tutCount = (int)(clock() - tutTime) / tutDiv;
			}
			displayCirc = true;
		}
		else if (tutCount >= 18 && tutCount <= 26)
		{
			tutCount = (int)(clock() - tutTime) / tutDiv;
			tutDiv = 3000;

			SDL_Rect hitR;
			SDL_QueryTexture(tutArrow, NULL, NULL, &hitR.w, &hitR.h);
			hitR.w /= 2;
			hitR.h /= 2;
			if (tutCount == 18 || tutCount == 19)
			{
				hitR.x = screenWidth - 60;
				hitR.y = 50;
				SDL_RenderCopy(renderer, tutArrow, NULL, &hitR);
			}
			else if (tutCount > 19 && tutCount <= 23)
			{
				hitR.x = 60;
				hitR.y = screenHeight - 100;
				SDL_RenderCopyEx(renderer, tutArrow, NULL, &hitR, 180, NULL, SDL_FLIP_NONE);
			}
			else if (tutCount > 23 && tutCount <= 26)
			{
				hitR.x = 60;
				hitR.y = 50;
				SDL_RenderCopy(renderer, tutArrow, NULL, &hitR);
			}
		}
		else
		{
			tutCount = (int)(clock() - tutTime) / tutDiv;
			SDL_SetTextureAlphaMod(menuBG, 240);
			SDL_RenderCopy(renderer, menuBG, NULL, NULL);
			SDL_SetTextureAlphaMod(menuBG, 255);
			tutDiv = 3000;
			displayCirc = false;
		}

		if (tutCount < (int)tutorialList.size())
		{
			SDL_QueryTexture(tutorialList.at(tutCount), NULL, NULL, &setTextR.w, &setTextR.h);
			setTextR.x = screenWidth / 2 - setTextR.w / 2;
			setTextR.y = screenHeight / 2 - setTextR.h / 2;
			SDL_RenderCopy(renderer, tutorialList.at(tutCount), NULL, &setTextR);
		}
		else
		{
			playing = false;
			playTutorial = false;
			visualizerTrue = true;
			displayCirc = true;
			firstLaunch = false;
			tutRewrite();
			cout << "TUTORIAL COMPLETE, SIZE: " << tutCount << endl;
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine, tutorial must have been selected to be played.
/// Post: Actions occur if the tutorial is being played, and based on mouse actions.
/// Detects the tutorial's actions.
/// </summary>
void GameEngine::detectTutorial()
{
	if (newTutFalse)
	{
		int tempW = 0, tempH = 0;
		SDL_QueryTexture(optKeyBut, NULL, NULL, &tempW, &tempH);
		tempW = tempW / 2 + 60;
		tempH = tempH / 2 + 50;
		int tempXO = screenWidth / 2 - tempW / 2 + 50;
		int tempY = screenHeight / 2 + tempH / 2 - 5;
		int tempXT = screenWidth / 2 + tempW / 2 - 50 - tempW / 4;
		if (mouseX >= tempXO && mouseX <= tempXO + tempW / 4 && mouseY >= tempY && mouseY <= tempY + tempH / 4)
		{
			//Yes
			newTutFalse = false;
			playMenu = false;
			playing = true;
			quitFail = false;
			playTutorial = true;
			visualizerTrue = false;
			tutTime = clock();
			tutDiv = 3000;
			tutCount = 0;
			songName = "..//res//music//Tutorial.mp3";
		}
		else if (mouseX >= tempXT && mouseX <= tempXT + tempW / 4 && mouseY >= tempY && mouseY <= tempY + tempH / 4)
		{
			//No
			newTutFalse = false;
			firstLaunch = false;
			playing = false;
			playTutorial = false;
			visualizerTrue = true;
			displayCirc = true;
			tutRewrite();
		}
	}
}

/// <summary>
/// Pre: Initialized GameEngine.
/// Post: Set if tutorial has been played.
/// SEts if tutorial has been played in text file.
/// </summary>
void GameEngine::tutRewrite()
{
	string fileName = "..//res//options//options.txt";
	vector <string> stringVec;
	fstream optionF(fileName, fstream::in);
	stringstream buffer;
	string line;
	while (getline(optionF, line))
	{
		istringstream iss(line);
		string temp, use;
		iss >> temp;
		string uploadBuff;

		if (temp == "newplayer")
		{
			uploadBuff = "newplayer = 0";
			buffer << (uploadBuff.c_str());  //Replace with value
		}
		else
		{
			buffer << line;
		}
		buffer << endl;
	}
	optionF.close();
	optionF.clear();
	optionF.open(fileName, fstream::out);
	optionF << buffer.str();
	optionF.close();
}
