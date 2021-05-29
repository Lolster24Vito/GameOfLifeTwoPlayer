#include <SFML/Graphics.hpp>
#include<ctime>
#include<iostream>

#include <SFML/Audio.hpp>
#include <string>
#include<SFML/Audio/SoundBuffer.hpp>
#include"Pattern.h"
#include"ButtonSelect.h"
#include<sstream>
const int cellSize = 10;
const int height = 1000;
const int width = 1000;
const int gridHeight = 60;
const int gridWidth = 100;
const int heightOffset=200;

int genRnd(int min, int max) {
	return rand() % (max - min + 1) + min;
}
enum CellState { dead, aliveP1, aliveP2 };

struct vector2 {
	int x;
	int y;
	vector2(int x, int y) {
		this->x = x;
		this->y = y;
	}
	vector2() {
		this->x = 0;
		this->y = 0;
	}
};


CellState genRndCellState() {
	int randomNumb=genRnd(0, 3);
	if (randomNumb == 0) {
		return CellState::dead;
	}
	if (randomNumb == 1) {
		return CellState::aliveP1;
	}
	if (randomNumb == 3) {
		return CellState::aliveP2;
	}
	return CellState::dead;
}

sf::Color randomColor() {
	int r = genRnd(0, 255);
	int g = genRnd(0, 255);
	int b = genRnd(0, 255);

	return sf::Color(r, g, b);
}
bool checkCounterForAlive(int counter) {
	if (counter < 2) {
		return  false;
		//std::cout << "died less than 2-";
	}
	if (counter > 3) {
		return false;
		//std::cout << "died more  than 3-";
	}
	if (counter == 2 || counter == 3) {
		return true;
		//std::cout << "continued to live-";
	}
}
void drawGrid(sf::RenderWindow& window, CellState grid[gridWidth][gridHeight],sf::Text &liveP1Cells,sf::Text &liveP2Cells)
 {
	int P1CellsNumber = 0;
	int P2CellsNumber = 0;

	//window.clear(sf::Color::Black);
	for (int i = 0; i < gridWidth; i++) {
		for (int j = 0; j < gridHeight; j++) {
			//if (grid[i][j]) {
			sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
			rectangle.setPosition(i * cellSize, (j * cellSize)+heightOffset);

			switch (grid[i][j])
			{
			case CellState::aliveP1:
				rectangle.setFillColor(sf::Color::Blue);
				P1CellsNumber++;
				window.draw(rectangle);
				break;
			case CellState::aliveP2:
				rectangle.setFillColor(sf::Color::Red);
				P2CellsNumber++;
				window.draw(rectangle);
				break;
			case CellState::dead:
				//	rectangle.setFillColor(sf::Color::Black);
				break;

			}

			//}
		}

	}
	sf::RectangleShape line(sf::Vector2f(2, 600));
	line.setPosition(width / 2, heightOffset);
	window.draw(line);
	line.setSize(sf::Vector2f(1200, 2));
	line.setPosition(0, heightOffset);
	window.draw(line);
	line.setPosition(0, height-heightOffset);
	window.draw(line);
	std::stringstream temp;
	temp << P1CellsNumber;
	liveP1Cells.setString(temp.str());
	temp.str("");
	temp << P2CellsNumber;
	liveP2Cells.setString(temp.str());

	window.draw(liveP2Cells);
	window.draw(liveP1Cells);

	//window.display();
}

void setPattern(CellState (&grid)[gridWidth][gridHeight],Pattern pat, vector2 gridPositions,CellState whichPlayer) {

	Pattern pat2 = pat;
	//mirror the pattern
	if (whichPlayer == CellState::aliveP2) {
		for (int i = 0; i < 7; i++) {
			int start = 0;
			int end = 6;
			while (start < end) {
				bool temp = pat2.shape[start][i];
				pat2.shape[start][i]= pat2.shape[end][i];
				pat2.shape[end][i] = temp;
				start++;
				end--;
			}
		}

	}

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (pat2.shape[i][j] == true) {
				if(gridPositions.x+i<gridWidth&&gridPositions.y+j<gridHeight)
				grid[gridPositions.x + i][gridPositions.y + j] = whichPlayer;
			}
		}
	}
}
void drawOnGrid(CellState(&grid)[gridWidth][gridHeight],int patternIndex,Pattern pat, vector2 gridPositions, CellState whichPlayer) {
	if (gridPositions.x >= 0 && gridPositions.x <= gridWidth) {
		if (patternIndex == 0) {
			grid[gridPositions.x][gridPositions.y] = whichPlayer;
		}
		else {
			setPattern(grid, pat, gridPositions, whichPlayer);
		}
	}

}
void cleanGrid(CellState(&grid)[gridWidth][gridHeight]) {

	for (int i = 0; i < gridWidth; i++) {
		for (int j = 0; j < gridHeight; j++) {
			grid[i][j] = CellState::dead;
			//grid[i][j] = genRndCellState();
		}
	}
}
void randomizeGrid(CellState(&grid)[gridWidth][gridHeight]) {

	for (int i = 0; i < gridWidth; i++) {
		for (int j = 0; j < gridHeight; j++) {
			//grid[i][j] = CellState::dead;
			grid[i][j] = genRndCellState();
		}
	}
}


int main()
{
	//	buffer.loadFromSamples(&samples[0], samples.size(), 2, 44100);
	//if (!buffer.loadFromFile("sound.wav"))
	//	return -1;

	sf::RenderWindow window(sf::VideoMode(width, height), "Game of Life but its a two player vs game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Clock clock; // starts the clock
	sf::Time elapsed1 = clock.getElapsedTime();
	std::cout << elapsed1.asSeconds() << std::endl;

	bool freezeTime = true;
	bool leftMouseButtonHolding = false;
	bool rightMouseButtonHolding = false;
	//Cvijet cvijet(&window);
	srand(time(nullptr));
	CellState grid[gridWidth][gridHeight];
	
	sf::Font font;
	if (!font.loadFromFile("font123.ttf"))
	{
		std::cout << "oh oh someone deleted my fonts or the program can't find the font \n";
	}

	
	sf::Text player1liveCellsText;
	player1liveCellsText.setPosition(0, 55);
	player1liveCellsText.setFont(font);
	player1liveCellsText.setCharacterSize(25);
	player1liveCellsText.setString("Live Cells Player1:");


	sf::Text player1liveCellsNumber;
	player1liveCellsNumber.setPosition(200, 50);
	player1liveCellsNumber.setFont(font);
	player1liveCellsNumber.setFillColor(sf::Color::Blue);
	player1liveCellsNumber.setString("0");

	

	sf::Text player2liveCellsText;
	player2liveCellsText.setPosition(500, 55);
	player2liveCellsText.setFont(font);
	player2liveCellsText.setCharacterSize(25);
	player2liveCellsText.setString("Live Cells Player2:");


	sf::Text player2liveCellsNumber;
	player2liveCellsNumber.setPosition(700, 50);
	player2liveCellsNumber.setFont(font);
	player2liveCellsNumber.setFillColor(sf::Color::Red);
	player2liveCellsNumber.setString("0");



	




	Pattern patterns[10];
	bool blockPat[7][7] = {
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0},
		{0,0,1,1,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
	};
	bool beeHivePat[7][7] = {
	{0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0},
	{1,0,0,1,0,0,0},
	{0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0}
	};
	bool oscilator[7][7] = {
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,1,1,1,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0}
	};
		bool Toad[7][7] = {
	{0,0,0,0,0,0,0},
	{0,1,1,1,0,0,0},
	{1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0}
	};
		bool Glider[7][7] = {
	{0,1,0,0,0,0,0},
	{0,0,1,0,0,0,0},
	{1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
		};
		bool LightSpaceShip[7][7] = {
{0,0,0,0,0,0,0},
{0,1,0,0,1,0,0},
{0,0,0,0,0,1,0},
{0,1,0,0,0,1,0},
{0,0,1,1,1,1,0},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0},
		};

		bool MediumSpaceShip[7][7] = {
	{0,0,0,1,0,0,0},
	{0,1,0,0,0,1,0},
	{0,0,0,0,0,0,1},
	{0,1,0,0,0,0,1},
	{0,0,1,1,1,1,1},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
		};
		bool Rpentomino[7][7] = {
	{0,0,0,0,0,0,0},
	{0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0},
	{0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
		};
		bool Acorn[7][7] = {
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0},
	{0,0,0,1,0,0,0},
	{1,1,1,0,0,1,1},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
		};


	patterns[0].setName("One block");
	patterns[1].setShape(blockPat);
	patterns[1].setName("Block");
	patterns[2].setShape(beeHivePat);
	patterns[2].setName("Bee hive");
	patterns[3].setShape(oscilator);
	patterns[3].setName("Oscilator");
	patterns[4].setShape(Toad);
	patterns[4].setName("Toad");
	patterns[5].setShape(Glider);
	patterns[5].setName("Glider");
	patterns[6].setShape(LightSpaceShip);
	patterns[6].setName("Light \n SpaceShip");
	patterns[7].setShape(MediumSpaceShip);
	patterns[7].setName("Medium \n SpaceShip");
	patterns[8].setShape(Rpentomino);
	patterns[8].setName("R pentomino");
	patterns[9].setShape(Acorn);
	patterns[9].setName("Acorn");

	ButtonSelect buttonsPatterns[10];



	sf::Texture textures[10];
	for (int i = 0; i < 10; i++) {
		buttonsPatterns[i].setFont(font);
		std::stringstream ss;
		ss << "pattern" << i << ".png";

		if (!textures[i].loadFromFile(ss.str()))
			textures[i].loadFromFile("pattern0.png");
		buttonsPatterns[i].setTexture(textures[i]);
		buttonsPatterns[i].setPosition(sf::Vector2f(i * 100, height - heightOffset));
		buttonsPatterns[i].setName(patterns[i].getName());
	}



	int indexSelectedPattern = 0;
	cleanGrid(grid);
	drawGrid(window, grid, player1liveCellsNumber, player2liveCellsNumber);


	

	while (window.isOpen())
	{
		window.clear(sf::Color(0, 0, 0, 255));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == event.KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					freezeTime = !freezeTime;
				}
				if (event.key.code == sf::Keyboard::C) {
					cleanGrid(grid);
				}
				if (event.key.code == sf::Keyboard::R) {
					randomizeGrid(grid);
				}

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				vector2 gridPositions(localPosition.x / cellSize, (localPosition.y - heightOffset) / cellSize);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					leftMouseButtonHolding = true;
					if (localPosition.y < height - heightOffset) {
						if (localPosition.x < width / 2) {
							drawOnGrid(grid, indexSelectedPattern, patterns[indexSelectedPattern], gridPositions, CellState::aliveP1);
						}
						else {
							drawOnGrid(grid, indexSelectedPattern, patterns[indexSelectedPattern], gridPositions, CellState::aliveP2);
						}
					}

					for (int i = 0; i < 10; i++) {

						if (buttonsPatterns[i].isMouseOver(localPosition.x, localPosition.y)) {
							indexSelectedPattern = i;
						}
					}
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					drawOnGrid(grid, indexSelectedPattern, patterns[indexSelectedPattern], gridPositions, CellState::dead);
					rightMouseButtonHolding = true;

				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					leftMouseButtonHolding = false;
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					rightMouseButtonHolding = false;
				}

			}
			if (event.type == sf::Event::MouseMoved) {
				vector2 gridPositions(event.mouseMove.x / cellSize, (event.mouseMove.y-heightOffset) / cellSize);


				if (leftMouseButtonHolding && event.mouseMove.x < width / 2) {
					if (event.mouseMove.y < height - heightOffset) {
						drawOnGrid(grid, indexSelectedPattern, patterns[indexSelectedPattern], gridPositions, CellState::aliveP1);
						
					}
				}
				if (leftMouseButtonHolding && event.mouseMove.x > width / 2) {
					if (event.mouseMove.y < height - heightOffset) 
					drawOnGrid(grid, indexSelectedPattern, patterns[indexSelectedPattern], gridPositions, CellState::aliveP2);

				}
				if (rightMouseButtonHolding) {
					if (event.mouseMove.y < height - heightOffset) 
					drawOnGrid(grid, indexSelectedPattern, patterns[indexSelectedPattern], gridPositions, CellState::dead);
				}
			}
			
		}
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		vector2 gridPositions(localPosition.x / cellSize, (localPosition.y - heightOffset) / cellSize);


		drawGrid(window, grid, player1liveCellsNumber, player2liveCellsNumber);
		for (int i = 0; i < 10; i++) {
			buttonsPatterns[i].drawTo(window);
		}
		window.draw(player1liveCellsText);
		window.draw(player2liveCellsText);
			
		window.display();

		elapsed1 = clock.getElapsedTime();

			if (!freezeTime&&elapsed1.asMilliseconds()>65) {
				clock.restart();
			CellState nextGrid[gridWidth][gridHeight];
			for (int i = 0; i < gridWidth; i++) {
				for (int j = 0; j < gridHeight; j++) {
					int counterP1 = 0;
					int counterP2 = 0;
					vector2 verticalCheckMinMax(-1, 1);
					vector2 horizontalCheckMinMax(-1, 1);
					if (i == 0) {
						horizontalCheckMinMax.x = 0;
					}
					if (i == gridWidth - 1) {
						horizontalCheckMinMax.y = 0;
					}
					if (j == 0) {
						verticalCheckMinMax.x = 0;
					}
					if (j == gridHeight - 1) {
						verticalCheckMinMax.y = 0;
					}
					for (int m = horizontalCheckMinMax.x; m <= horizontalCheckMinMax.y; m++) {
						for (int l = verticalCheckMinMax.x; l <= verticalCheckMinMax.y; l++) {
							if (m == 0 && l == 0) continue;
							if (grid[m + i][l + j]==CellState::aliveP1) {
								counterP1++;
							}
							if (grid[m + i][l + j] == CellState::aliveP2) {
								counterP2++;
							}
						}
					}

					if (grid[i][j]==CellState::aliveP1|| grid[i][j] == CellState::aliveP2) {
						
						if (!checkCounterForAlive(counterP1) && !checkCounterForAlive(counterP2)) {
							nextGrid[i][j] = CellState::dead;
						}
						if (checkCounterForAlive(counterP1)&&!checkCounterForAlive(counterP2)) {
							nextGrid[i][j] = CellState::aliveP1;
						}
						if (!checkCounterForAlive(counterP1) && checkCounterForAlive(counterP2)) {
							nextGrid[i][j] = CellState::aliveP2;

						}
						if (checkCounterForAlive(counterP1) && checkCounterForAlive(counterP2)) {
							if (counterP1 > counterP2) {
								nextGrid[i][j] = CellState::aliveP1;

							}
							if (counterP2 > counterP1) {
								nextGrid[i][j] = CellState::aliveP2;

							}
							if (counterP1 == counterP2) {
								nextGrid[i][j] = CellState::dead;
							}
						}
						


					}
					else {
						if (counterP1 == 3) {
							nextGrid[i][j] = CellState::aliveP1;
							//std::cout << "came alive from dead--";

						}
						if (counterP2 == 3) {
							nextGrid[i][j] = CellState::aliveP2;
						}
						if (counterP1 == 3 && counterP2 == 3) {
							nextGrid[i][j] = CellState::dead;
						}
						if (counterP1 != 3 && counterP2 != 3) {
							nextGrid[i][j] = CellState::dead;
						}
						//std::cout << "still dead-";


					}
					//std::cout << " [" << i << "," << j << "]:" << counter << "\n";



				}
			}
			for (int i = 0; i < gridWidth; i++) {
				for (int j = 0; j < gridHeight; j++) {
					grid[i][j] = nextGrid[i][j];
				}
			}
			

			//window.draw(rectangle);


		}
	}

	return 0;
}