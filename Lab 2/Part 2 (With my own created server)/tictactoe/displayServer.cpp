#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

#include "tictactoe.h"
#include "gameState.h"

// Function prototype for playMove
void playMove(gameState&);

// The display server function

int displayServer() {

    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* ECE244 Student: The loading of the X image is shown. Repreat for the rest of the images                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("/share/copy/ece244f/lab2/data/X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);

    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("/share/copy/ece244f/lab2/data/O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);

    // Get the blank image
    sf::Texture Blank_texture;
    if (!Blank_texture.loadFromFile("/share/copy/ece244f/lab2/data/B.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite Blank_sprite(Blank_texture);

    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Blank) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them

    // The tile size is the size of the images
    const int tileSize = O_texture.getSize().x;

    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3
    const int barWidth = tileSize / 20;
    const int barHeight = boardSize * tileSize + (boardSize - 1) * barWidth;

    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize * tileSize + (boardSize - 1) * barWidth;

    // Create the main window: it has a title bar and a close button, but is not resizable
    // ECE244 Student: you should replace ECE244 in the title of the window by your login ID
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic-Tac_Toe (narwalbi Display Server)", sf::Style::Titlebar | sf::Style::Close);

    // Set the Icon that appears in the task bar when the window is minimized
    // load the icon image
    sf::Image windowIcon;
    if (!windowIcon.loadFromFile("/share/copy/ece244f/lab2/data/icon.jpg")) {
        return EXIT_FAILURE;
    }
   
    // set the icon image
    window.setIcon(windowIcon.getSize().x,
            windowIcon.getSize().y,
            windowIcon.getPixelsPtr());

    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // create vertical1
    sf::RectangleShape vertical1(sf::Vector2f(barWidth, barHeight));
    vertical1.setPosition(tileSize,0);
    vertical1.setFillColor(sf::Color::Black);
   
    //create vertical2
    sf::RectangleShape vertical2(sf::Vector2f(barWidth, barHeight));
    vertical2.setPosition(tileSize*2 + barWidth,0);
    vertical2.setFillColor(sf::Color::Black);

    //create horizontal1
    sf::RectangleShape horizontal1(sf::Vector2f(barHeight, barWidth));
    horizontal1.setPosition(0,tileSize);
    horizontal1.setFillColor(sf::Color::Black);

    //create horizontal2
    sf::RectangleShape horizontal2(sf::Vector2f(barHeight, barWidth));
    horizontal2.setPosition(0,tileSize*2 + barWidth);
    horizontal2.setFillColor(sf::Color::Black);

    // drawing all the borders
    window.draw(vertical1);
    window.draw(vertical2);
    window.draw(horizontal1);
    window.draw(horizontal2);

    /************************************************************************************************************/
    /* Create and initialize the game state object                                                              */
    /************************************************************************************************************/
    gameState game_state;

    game_state.set_clickedRow(0);
    game_state.set_clickedColumn(0);
    game_state.set_moveValid(true); // This must start out as true
    game_state.set_gameOver(false);
    game_state.set_winCode(0);
    game_state.set_turn(true); // X always plays first
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            game_state.set_gameBoard(i, j, Empty);
        }
    }

    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/

    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;

        // Process the events
        while (window.pollEvent(event)) {

            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Left mouse button pressed: get the click position and update the game
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !game_state.get_gameOver()) {
                // left mouse button is pressed: get the coordinates in pixels
                sf::Vector2i localPosition = Mouse::getPosition(window);
               
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                int rowPosition = localPosition.x / tileSize;
                int columnPosition = localPosition.y / tileSize;
               
                // game state is already doing this actually
                if (columnPosition<3 && columnPosition>=0 && rowPosition<3 && rowPosition>=0) {
                    game_state.set_moveValid(true);
                }
               
                // Update the game state object with the coordinates
                game_state.set_clickedColumn(columnPosition);
                game_state.set_clickedRow(rowPosition);

                // Update the game with the new move
                // since all criterias have been set, its time to play the game
                playMove(game_state);
            }
        }

        // If the move is invalid, go to next event
        if (!game_state.get_moveValid()) continue;

        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (game_state.get_gameBoard(i,j) == X) {
                    window.draw(X_sprite);
                    X_sprite.setPosition(tileSize*i + barWidth*i,tileSize*j + barWidth*j);
                }
               
                if (game_state.get_gameBoard(i,j) == O) {
                    window.draw(O_sprite);
                    O_sprite.setPosition(tileSize*i + barWidth*i,tileSize*j + barWidth*j);
                }

               
                if (game_state.get_gameBoard(i,j) == Empty) {
                    window.draw(Blank_sprite);
                    Blank_sprite.setPosition(tileSize*i + barWidth*i,tileSize*j + barWidth*j);
                }
            }
        }

        int winCode = game_state.get_winCode();
       
        if (winCode==1) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setRotation(90);
            winLine.setPosition(tileSize/2,0);
            window.draw(winLine);
        }

        if (winCode==2) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setRotation(90);
            winLine.setPosition(tileSize/2 + tileSize + barWidth,0);
            window.draw(winLine);
        }

        if (winCode==3) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setRotation(90);
            winLine.setPosition(tileSize/2 + tileSize*2 + barWidth*2,0);
            window.draw(winLine);
        }

        if (winCode==4) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setPosition(0,tileSize/2);
            window.draw(winLine);
        }

        if (winCode==5) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setPosition(0,tileSize/2 + tileSize + barWidth);
            window.draw(winLine);
        }

        if (winCode==6) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setPosition(0,tileSize/2 + tileSize*2 + barWidth*2);
            window.draw(winLine);
        }

        if (winCode==7) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setScale(sf::Vector2f(2,1));
            winLine.setRotation(45);
            winLine.setOrigin(boardSize/2,boardSize/2);
            window.draw(winLine);
        }

        if (winCode==8) {
            sf::RectangleShape winLine(sf::Vector2f(windowSize, 10));
            winLine.setFillColor(sf::Color::White);
            winLine.setScale(sf::Vector2f(2,1));
            winLine.setRotation(135);
            winLine.setPosition(3*tileSize + 2*barWidth,0);
            window.draw(winLine);
        }
       
        // Display to the window
        window.display();
    }

    return EXIT_SUCCESS;
}
