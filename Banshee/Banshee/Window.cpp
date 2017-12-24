#include "stdafx.h"
#include "Window.h"

/// <summary>
/// Pre: None.
/// Post: Initializes Window.
/// Initializes a new instance of the <see cref="Window"/> class.
/// </summary>
Window::Window()
{
	window = NULL;
	surface = NULL;
	renderer = NULL;

	screenHeight = 0; //720
	screenWidth = 0; //1250

	firstLaunch = fulltrue = visualizerTrue = cheats = false;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);

	cout << "WINDOW CREATED." << endl;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Sets variables to values.
/// Finalizes an instance of the <see cref="Window"/> class.
/// </summary>
Window::~Window()
{
	window = NULL;
	surface = NULL;
	renderer = NULL;
	screenHeight = 0;
	screenWidth = 0;

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Returns screen height.
/// Returns the height.
/// </summary>
/// <returns></returns>
int Window::returnHeight()
{
	return screenHeight;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Returns screen width.
/// Returns the width.
/// </summary>
/// <returns></returns>
int Window::returnWidth()
{
	return screenWidth;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Displayed window, with initialized renderer, SDL png system, SDL font system, and SDL audio system.
/// Initializes the window to be displayed.
/// </summary>
/// <returns></returns>
bool Window::initWindow()
{
	window = SDL_CreateWindow("Banshee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL) cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) cout << "Renderer could not be created! SDL Error: %s\n", SDL_GetError();
		else
		{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) cout << "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError();
			else
			{
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError();
				else
				{
					if (TTF_Init() == -1) cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError();
					else
					{
						if (initSettings())
						{
							SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Sets settings, creates settings file if needed.
/// Initializes the settings.
/// </summary>
/// <returns></returns>
bool Window::initSettings()
{
	string fileName = "..//res//options//options.txt";

	if (fileExists(fileName))
	{
		string tempString;
		vector <string> stringVec;
		int fullScreen = 0;
		ifstream infile;

		infile.open(fileName);

		while (getline(infile, tempString))
		{
			tempString.erase(remove_if(tempString.begin(), tempString.end(), isspace), tempString.end());
			replace(tempString.begin(), tempString.end(), '=', ' ');

			istringstream iss(tempString);
			string temp, use;
			iss >> temp;
			iss >> use;
			stringVec.push_back(use);

			tempString = "";
		}

		for (size_t i = 0; i < stringVec.size(); ++i)
		{
			switch (i)
			{
			case 0:
				if (stoi(stringVec.at(0)) == 1)
				{
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
					SDL_GetWindowSize(window, &screenWidth, &screenHeight);
					fulltrue = true;
				}
				else SDL_SetWindowFullscreen(window, 0);
				break;
			case 1: if (stoi(stringVec.at(0)) != 1) screenHeight = stoi(stringVec.at(1));
				break;
			case 2: if (stoi(stringVec.at(0)) != 1) screenWidth = stoi(stringVec.at(2));
				break;
			case 3:
				firstLaunch = (stoi(stringVec.at(3)) == 1);
				break;
			case 4:
				volumeNum = stoi(stringVec.at(4));
				break;
			case 5:
				keyOne = stringVec.at(5);
				break;
			case 6:
				keyTwo = stringVec.at(6);
				break;
			case 7:
				visualizerTrue = (stoi(stringVec.at(7)) == 1);
				break;
			case 8:
				cheats = (stoi(stringVec.at(8)) == 1);
				break;
			}
		}

		tempSW = screenWidth;
		tempSH = screenHeight;
		SDL_SetWindowSize(window, screenWidth, screenHeight);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		infile.close();

		cout << "READ FROM FILE. " << endl;
	}
	else
	{
		cout << "COULD NOT READ FILE, RESET TO DEFAULTS." << endl;  //In the future make it so it creates file

		/*screenHeight = 720;
		screenWidth = 1250;
		SDL_SetWindowSize(window, screenWidth, screenHeight);
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		firstLaunch = true;*/

		//Instead write to file, recursively call again.
		fstream mystream(fileName, ios::out);
		mystream.close();

		stringstream buffer;

		buffer << "fullscreen = 1\n";
		buffer << "screenheight = 705\n";
		buffer << "screenwidth = 1250\n";
		buffer << "newplayer = 1\n";
		buffer << "volume = 65\n";
		buffer << "mouseOne = d\n";
		buffer << "mouseTwo = f\n";
		buffer << "visualizer = 1\n";
		buffer << "cheats = 0\n";

		mystream.open(fileName, fstream::in | fstream::out);
		mystream << buffer.str();
		mystream.close();

		initSettings();
	}
	return true;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Loaded textures.
/// Loads the texture.
/// </summary>
/// <param name="path">The path.</param>
/// <returns></returns>
SDL_Texture* Window::loadTexture(string path)
{
	SDL_Surface* unoptimized = NULL;
	SDL_Texture* optimized = NULL;

	unoptimized = IMG_Load(path.c_str());
	if (unoptimized == NULL) cout << "Image could not be created! SDL_Error: %s\n", SDL_GetError();
	else
	{
		SDL_ConvertSurface(unoptimized, SDL_GetWindowSurface(window)->format, 0);
		optimized = SDL_CreateTextureFromSurface(renderer, unoptimized);
		if (optimized == NULL) cout << "Image could not be optimized! SDL_Error: %s\n", SDL_GetError();
		SDL_FreeSurface(unoptimized);
	}
	return optimized;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Quits game.
/// Returns if game has been quit.
/// </summary>
/// <returns></returns>
bool Window::returnQuit()
{
	return quit == true;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Quits game if pressed.
/// Checks if exit button in toolbar has been pressed.
/// </summary>
/// <returns></returns>
bool Window::checkQuit()
{
	if (e.type == SDL_QUIT)
	{
		cout << "EXIT" << endl;
		playing = false;
		quit = true;
	}
	return quit;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Sets if game is playing.
/// Sets if gaame is playing.
/// </summary>
/// <param name="foo">if set to <c>true</c> [foo].</param>
void Window::setPlaying(bool foo)
{
	playing = foo;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Gets if game is playing.
/// Gets if the game is playing.
/// </summary>
/// <returns></returns>
bool Window::getPlaying()
{
	return playing;
}

/// <summary>
/// Pre: Initialized Window.
/// Post: Returns true if files exist.
/// Checks if files exist.
/// </summary>
/// <param name="filename">The filename.</param>
/// <returns></returns>
bool Window::fileExists(const string & filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}