#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <string.h>


#define WIDTH 800
#define HEIGHT 600

// Physics / units
#define squareLength  20              // pixels per meter (tune to taste)
#define WIDTH_L  (WIDTH / squareLength)
#define HEIGHT_L (HEIGHT / squareLength)

#define UPDATE_INTERVAL 0.5 //ms

// int grid[WIDTH_L][HEIGHT_L];
// int successorGrid[WIDTH_L][HEIGHT_L];

enum GameState { ChoosingGrid, Simulating } state = ChoosingGrid;

void update();
void draw();
void getMouseClick();
void simulate();
void init();


int ** grid;
int ** successorGrid;


// gcc main.c -g -o main -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

// https://www.raylib.com/cheatsheet/cheatsheet.html

double total_time = 0.0;
double delta_time;
int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Conway's Game of Life - Raylib C17");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose())
    {
        delta_time = GetFrameTime();
        total_time += delta_time;
        // printf("%f\n",delta_time);

        update();
        BeginDrawing();
            ClearBackground(BLACK);
            draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void init()
{
    grid = malloc(sizeof(int*) * WIDTH_L);
    successorGrid = malloc(sizeof(int*) * WIDTH_L);

    for (int i = 0; i < WIDTH_L; i++)
    {
        grid[i] = malloc( sizeof(int) * HEIGHT_L);
        memset(grid[i],0, sizeof(int) * HEIGHT_L);

        successorGrid[i] = malloc( sizeof(int) * HEIGHT_L);
        memset(successorGrid[i],0, sizeof(int) * HEIGHT_L);
    }
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
    case ChoosingGrid:
        printf("reading input\n");
        getMouseClick();
        break;
    case Simulating:
        if(total_time >= UPDATE_INTERVAL)
        {
            printf("SIMULATING\n");
            simulate();
            total_time = 0.0;
        }
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

    if(IsKeyPressed(KEY_ENTER))
    {
        state = Simulating;
    }
}

void simulate()
{
    for (int i = 0; i < WIDTH_L - 1; i++)
    {
        for (int j = 0; j < HEIGHT_L - 1; j++)
        {
            if(grid[i][j] == 1)
            {
                successorGrid[i+1][j+1] = 1;
            }
            
        }
    }

    int ** temp = grid;
    grid = successorGrid;
    successorGrid = temp;

}
