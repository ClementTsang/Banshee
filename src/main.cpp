// main.cpp : Defines the entry point for the console application.
// Clement Tsang
// Created: October 30
// Last Edited: 11/23/16
// Banshee

#include "stdafx.h"
#include "BeatDetector.h"
#include "Window.h"
#include "GameEngine.h"


struct StateStruct
{
	void(*StatePointer)();
};

void playSong();
void windowFrame();
void init();
void callMenu();
void loadGame();
void delayGame();
void exitGame();
void quitGame();
void failGame();
void retryGame();
void printFiles();
void passGame();

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

vector <TimeStamp*> timestamps;
GameEngine gameEng;
stack<StateStruct> stateStack;
bool beatAdded = false;
bool startPlay = true;
bool updatedSongs = false;
bool delayEnd = false;
int lastUp = 0;
float vol;
thread tdDelay;

/// <summary>
/// Pre: None.
/// Post: Program begins.
/// The designated start of the program.
/// </summary>
/// <returns></returns>
int main()
{
	Stealth();
	timestamps.clear();
	cout << "Begin running threads..." << endl;
	thread tdWindow(windowFrame), tdPlay(playSong);

	tdWindow.join();
	tdPlay.join();

	cout << "Threads have ended." << endl;
	return 0;
}

/// <summary>
/// Pre: Game is being played.
/// Post: Song begins playing.
/// Plays songs using FMOD, and passes values to the GameEngine.
/// </summary>
void playSong()
{
	char* songName;

	while (!gameEng.returnQuit())
	{
		if (gameEng.getPlaying())
		{
			int tempClock = clock();
			while (clock() - tempClock < 1000)
			{
				if (!gameEng.getPlaying() || gameEng.returnQuit()) break;
			}

			if (gameEng.getPlaying())
			{
				// songName = "..//res//music//Drum80.mp3"; //<--- For testing
				songName = gameEng.getsongName();

				BeatDetector::Instance()->LoadSong(1024, songName);
				BeatDetector::Instance()->loadSongToDelay(1000);
				BeatDetector::Instance()->setVolumeTwo((float)gameEng.getVol() / 128 * 2);

				cout << "Additional info: Song Name: " << BeatDetector::Instance()->getSongName() << ", Artist Name: " << BeatDetector::Instance()->getArtistName() << endl;
				BeatDetector::Instance()->setStarted(true);

				while (BeatDetector::Instance()->isPlaying() && !gameEng.returnQuit())
				{
					if (startPlay)
					{
						tdDelay = thread(delayGame);
						tdDelay.join();
						startPlay = false;
					}
					BeatDetector::Instance()->update();
					if (timestamps.size() < 1)
					{
						timestamps.push_back(BeatDetector::Instance()->getLastBeat());
						beatAdded = true;
					}
					else
					{
						if (BeatDetector::Instance()->getLastBeat() != timestamps.at(timestamps.size() - 1))
						{
							timestamps.push_back(BeatDetector::Instance()->getLastBeat());
							beatAdded = true;
						}
					}
					if (clock() - lastUp >= 300)
					{
						gameEng.passGraph(BeatDetector::Instance()->getCurrentSpectrumTwo());
						lastUp = clock();
					}
				}
				cout << "LOOP ENDED." << endl;
				timestamps.clear();
				startPlay = true;
				delayEnd = false;
			}
		}
		else this_thread::yield();
	}
}

/// <summary>
/// Pre: Main method called.
/// Post: Calls the top stack.
/// Constantly runs the topmost stack until the stack is empty.
/// </summary>
void windowFrame()
{
	init();
	while (!stateStack.empty())
	{
		stateStack.top().StatePointer();
	}
	exitGame();
}

/// <summary>
/// Pre: Main method called.
/// Post: Created window.
/// Creates the game window.
/// </summary>
void init()
{
	if (gameEng.createWindow())
	{
		StateStruct state;
		state.StatePointer = exitGame;
		stateStack.push(state);

		state.StatePointer = callMenu;
		stateStack.push(state);

		cout << "WINDOW SET UP.  " << endl;
	}
}

/// <summary>
/// Pre: Main called, game begins, not being played yet.
/// Post: Calls menu functions.
/// Calls certain menu functions from the GameEngine to render/preform.
/// </summary>
void callMenu()
{
	if (!(gameEng.returnQuit()))
	{
		if (!updatedSongs || gameEng.getUpdateFile())
		{
			BeatDetector::Instance()->loadSystem();
			printFiles();

			updatedSongs = true;
			gameEng.setUpdateFile(false);
		}
		gameEng.updateScreen();
		if (gameEng.getPlaying())
		{
			updatedSongs = false;
			StateStruct temp;
			temp.StatePointer = loadGame;
			stateStack.push(temp);
			BeatDetector::Instance()->loadSystem();
			cout << "BeatDetector Loaded - MENU." << endl;
		}
	}
	else if ((gameEng.returnQuit()))
	{
		quitGame();
	}
}

/// <summary>
/// Pre: Main called, game begins, and is playing.
/// Post: Calls game functions;
/// Loads the game, preforms certain game actions such as rendering and calculations.
/// </summary>
void loadGame()
{
	if (!(gameEng.returnQuit()))
	{
		gameEng.updateScreen();
		if (beatAdded)
		{
			gameEng.passTimeStamps(timestamps);
			beatAdded = false;
		}
		if (!gameEng.getPlaying())
		{
			cout << "NOT PLAYING" << endl;
			BeatDetector::Instance()->unloadSong();
			gameEng.destroyGame();
			stateStack.pop();
			gameEng.destroyProtVar();
			if (gameEng.getFail())
			{
				StateStruct temp;
				temp.StatePointer = failGame;
				stateStack.push(temp);
			}
			else if (gameEng.getRetry())
			{
				retryGame();
			}
			return;
		}
		if (delayEnd) BeatDetector::Instance()->pauseSong(gameEng.getPaused());
		if (BeatDetector::Instance()->getComplete() || gameEng.getPass())
		{
			BeatDetector::Instance()->unloadSong();
			gameEng.destroyGame();
			stateStack.pop();

			gameEng.setPlaying(false);
			gameEng.setPass(true);

			//<---- Lead to finish screen
			StateStruct temp;
			temp.StatePointer = passGame;
			stateStack.push(temp);

			cout << "DONE PLAYING - COMPLETED" << endl;
		}
	}
	else quitGame();
}

/// <summary>
/// Pre: Game called and is playing.  Song playing method must be called.
/// Post: Delayed song output.
/// Delays the song's output to give a delay to match with the hitcircles.
/// </summary>
void delayGame()
{
	this_thread::sleep_for(0.8s); //<--- Delays for 1 second.
	BeatDetector::Instance()->delaySong();
	delayEnd = true;
	cout << "DELAYED!" << endl;
}

/// <summary>
/// Pre: Main called, game was failed.
/// Post: Fails the game.
/// Loads functions and renders elements based on failing.
/// </summary>
void failGame()
{
	if (!(gameEng.returnQuit()))
	{
		gameEng.updateScreen();
		if (!gameEng.getFail())
		{
			stateStack.pop();
		}
		if (gameEng.getRetry())
		{
			retryGame();
		}
	}
	else if ((gameEng.returnQuit()))
	{
		quitGame();
	}
}

/// <summary>
/// Pre: Main called, game failed or paused, retry selected.
/// Post: Retries the game.
/// Retries the game.  Renders and preforms calcualations for retrying.
/// </summary>
void retryGame()
{
	gameEng.setRetry(false);
	gameEng.setFail(false);
	gameEng.setPlaying(true);
	gameEng.setPaused(false);
	gameEng.setPass(false);

	StateStruct temp;
	temp.StatePointer = loadGame;
	stateStack.push(temp);
	BeatDetector::Instance()->loadSystem();

	cout << "BeatDetector Loaded - RETRY." << endl;
}

/// <summary>
/// Pre: Game is quit.
/// Post: Destructs GameEngine.
/// Calls GameEngine destructor.
/// </summary>
void exitGame()
{
	gameEng.~GameEngine();
}

/// <summary>
/// Pre: Game is quit.
/// Post: Removes all stack elements.
/// Removes all stack elements to cause program to quit.
/// </summary>
void quitGame()
{
	while (!stateStack.empty())
	{
		stateStack.pop();
	}
}

/// <summary>
/// Pre: Game initialized.
/// Post: Sends metadata to GameEngine.
/// Reads through files in music directory and gets metadata.
/// </summary>
void printFiles()
{
	bool temp = true;
	int zr = 0;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("..//res//music//")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (!S_ISDIR(ent->d_type))
			{
				string tempName = "..//res//music//";
				tempName.append(ent->d_name);
				BeatDetector::Instance()->LoadSong(1024, _strdup(tempName.c_str()));
				gameEng.passFile(temp, BeatDetector::Instance()->getSongName(), BeatDetector::Instance()->getArtistName(), BeatDetector::Instance()->getTime(), _strdup(tempName.c_str()));
				temp = false;
				zr++;
			}
		}
		closedir(dir);
	}
	gameEng.sortFiles();
	BeatDetector::Instance()->unloadSong();
	gameEng.setOldInt(zr);
	cout << "SONG LIST UPDATED." << endl;
}

/// <summary>
/// Passes the game.
/// </summary>
void passGame()
{
	if (!(gameEng.returnQuit()))
	{
		gameEng.updateScreen();
		if (!gameEng.getPass())
		{
			stateStack.pop();
		}
		if (gameEng.getRetry())
		{
			retryGame();
		}
	}
	else if ((gameEng.returnQuit()))
	{
		quitGame();
	}
}