#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

// Physics / units
#define squareLength  20              // pixels per meter (tune to taste)
#define WIDTH_L  (WIDTH / squareLength)
#define HEIGHT_L (HEIGHT / squareLength)

int grid[WIDTH_L][HEIGHT_L];

void update();
void draw();
void getMouseClick();

// gcc main.c -g -o main -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

// https://www.raylib.com/cheatsheet/cheatsheet.html
// game states - choosing grid or starting simulation

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Conway's Game of Life - Raylib C17");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // getMouseClick();
        update();
        BeginDrawing();
            ClearBackground(BLACK);
            draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void draw()
{
    for (int i = 0; i < WIDTH_L; i++)
    {
        for (int j = 0; j < HEIGHT_L; j++)
        {
            if(grid[i][j] == 1)
            {
                DrawRectangle(i * squareLength, j * squareLength, squareLength, squareLength, WHITE);
            }else
            {
                DrawRectangle(i * squareLength, j * squareLength, squareLength, squareLength, BLACK);
            }
        }
    }
}

void update()
{
    switch (state)
    {
    case "Choosing Grid":
        getMouseClick();
        break;
    case "Simulating":
        // Simulation logic here
        break;
    default:
        break;
    }
}

void getMouseClick()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();
        int gridX = (int)(mousePos.x / squareLength);
        int gridY = (int)(mousePos.y / squareLength);

        if (gridX >= 0 && gridX < WIDTH_L && gridY >= 0 && gridY < HEIGHT_L)
        {
            grid[gridX][gridY] = 1 - grid[gridX][gridY]; // Toggle cell state
        }
    }
}

