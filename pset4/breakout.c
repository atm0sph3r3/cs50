//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//Paddle dimensions
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 40

//Y HEIGHT
#define Y_POSITION HEIGHT*0.75

//BRICK DIMENSIONS
#define BRICK_HEIGHT 10
#define BRICK_WIDTH 37.8
#define BRICK_SPACING 2

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball's initial velocity
    double xVelocity = 0.025;
    double yVelocity = drand48() * xVelocity;
    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        /* waits for mouse event. doesn't allow paddle
         * to cross the window boundaries on the 
         * x-axis.
        */
        GMouseEvent event = getNextEvent(MOUSE_EVENT);
        
        if(event != NULL){
            if(getEventType(event) == MOUSE_MOVED){
                double x = getX(event);
                if(PADDLE_WIDTH + x >= WIDTH){
                    x = WIDTH - PADDLE_WIDTH; 
                }
                setLocation(paddle,x,Y_POSITION);
            }
        }
        
        //move the ball
        move(ball,xVelocity,yVelocity);
        
        //Reverse x-velocity if the ball strikes the wall
        if(getX(ball) + getWidth(ball) >= WIDTH){
            xVelocity = -xVelocity;
        } else if(getX(ball) <= 0){
            xVelocity = -xVelocity;
        }
        
        //Reverse y-velocity if the ball strikes the wall
        if(getY(ball) <= 0){
            yVelocity = -yVelocity;
        } else if(getY(ball) + RADIUS*2 >= HEIGHT){
            --lives;
            if(lives == 0){
                break;
            } else {
                waitForClick();
                ball = initBall(window);
            }
        }
        
        //Determine if ball has struck the paddle
        //Reverse direction if so
        GObject ballPaddle = detectCollision(window,ball);
        if(ballPaddle != NULL && ballPaddle == paddle){
            yVelocity = -yVelocity;
        }
        
        //Determine if bricks were struck. If so, remove them,
        //increase score, and update scoreboard.
        GObject ballBrick = detectCollision(window,ball);
        if(ballBrick != NULL){
            if(strcmp(getType(ballBrick), "GRect") == 0 && ballBrick != paddle){
                removeGWindow(window,ballBrick);
                yVelocity = -yVelocity;
                --bricks;
                ++points;
                updateScoreboard(window,label,points);
            }
        }
    }
    
    //Remove score and show win or lose
    removeGWindow(window,label);
    
    if(bricks == 0){
        removeGWindow(window,label);
        GLabel newLabel = newGLabel("Win!");
        setFont(newLabel, "SansSerif-32");
        setLocation(newLabel,WIDTH / 2 - getWidth(newLabel) / 2, HEIGHT/2 - getHeight(newLabel)/2);
        add(window,newLabel);
    } else {
        GLabel newLabel = newGLabel("Lose!");
        setFont(newLabel, "SansSerif-32");
        setLocation(newLabel,WIDTH / 2 - getWidth(newLabel) / 2, HEIGHT/2 - getHeight(newLabel)/2);
        add(window,newLabel);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < 10; j++){ 
            int x = (BRICK_WIDTH + BRICK_SPACING) * j + BRICK_SPACING;
            int y = i * (BRICK_HEIGHT + 10) + 50;
            GRect rect = newGRect(x,y,BRICK_WIDTH,BRICK_HEIGHT);
            setFilled(rect,true);
            switch(i){
                case (0):
                    setColor(rect,"RED");
                    break;
                case (1):
                    setColor(rect,"GREEN");
                    break;
                case (2):
                    setColor(rect,"BLUE");
                    break;
                case (3):
                    setColor(rect,"YELLOW");
                    break;
                case (4):
                    setColor(rect,"BLACK");
                    break;
                default:
                    setColor(rect,"BLACK");
            }
            
            
            add(window,rect);
        }
    }    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval oval = newGOval((WIDTH / 2) - RADIUS,HEIGHT/2 - RADIUS,RADIUS*2,RADIUS*2);
    setFilled(oval,true);
    setColor(oval,"BLACK");
    add(window,oval);
    return oval;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect(WIDTH / 2 - PADDLE_WIDTH / 2, getHeight(window) * 0.75, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(rect,true);
    setColor(rect,"BLACK");
    add(window,rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif-32");
    setLocation(score,WIDTH / 2 - getWidth(score) / 2, HEIGHT / 2 - getHeight(score) / 2);
    add(window,score);
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
