#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raymath.h"
#include "raygui/src/raygui.h"


#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void UpdateDrawFrame(void);
void DrawGameGrid(int rows, int cols, int cellWidth, int cellHeight, Color color);
void DrawCell(int posX, int posY, Color color);
int CountNeighbours(int x, int y);
void ApplyRules(int x, int y);
Vector2 GetMouseGridPosition(int cellWidth, int cellHeight);
void DrawGUI(void);

const int gridWidth = 100, gridHeight = 100;
const int blockWidth = 10, blockHeight = 10;
unsigned int maxFPS = 60;

bool gameGrid[2][gridWidth][gridHeight] = { false };

bool drawGrid = true;
bool showFPS = true;
bool simulating = false;
bool showUI = false;

int currentBuffer = 0;

int main(void)
{
    // Initialization
    InitWindow(blockWidth * gridWidth, blockHeight * gridHeight, "Conway's Game of Life");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(maxFPS);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();
    return 0;
}

void InitGame(void) {
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            gameGrid[currentBuffer][x][y] = false;
        }
    }

    // Initialize some live cells
    gameGrid[currentBuffer][10][10] = true;
    gameGrid[currentBuffer][11][10] = true;
    gameGrid[currentBuffer][12][10] = true;
    gameGrid[currentBuffer][11][11] = true;
    gameGrid[currentBuffer][12][12] = true;
}

void UpdateGame(void) {

    SetTargetFPS(maxFPS);

    if (IsKeyPressed(KEY_SPACE)) {
        simulating = !simulating;
    }

    if (simulating) {
        int nextBuffer = (currentBuffer + 1) % 2; // Switch buffer for next state

        for (int x = 0; x < gridWidth; x++) {
            for (int y = 0; y < gridHeight; y++) {
                ApplyRules(x, y); // Apply Conway's rules to each cell
            }
        }

        // Swap buffers
        currentBuffer = nextBuffer;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouseGridPos = GetMouseGridPosition(blockWidth, blockHeight);
        int x = (int)mouseGridPos.x;
        int y = (int)mouseGridPos.y;
        gameGrid[currentBuffer][x][y] = true; // Toggle cell state
    } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 mouseGridPos = GetMouseGridPosition(blockWidth, blockHeight);
        int x = (int)mouseGridPos.x;
        int y = (int)mouseGridPos.y;
        gameGrid[currentBuffer][x][y] = false; // Toggle cell state
    }

    if (IsKeyPressed(KEY_TAB)){
        showUI = !showUI;
    }

}

void DrawGame(void) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (drawGrid) {
        DrawGameGrid(gridHeight, gridWidth, blockWidth, blockHeight, GRAY);
    }

    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            if (gameGrid[currentBuffer][x][y]) {
                DrawCell(x * blockWidth, y * blockHeight, RAYWHITE);
            }
        }
    }

    if (showFPS) {
        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
    }

    if (showUI){
        DrawGUI();
    }

    EndDrawing();
}

void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}

void DrawGameGrid(int rows, int cols, int cellWidth, int cellHeight, Color color) {
    for (int i = 0; i <= rows; ++i) {
        DrawLine(0, i * cellHeight, cols * cellWidth, i * cellHeight, color);
    }

    for (int j = 0; j <= cols; ++j) {
        DrawLine(j * cellWidth, 0, j * cellWidth, rows * cellHeight, color);
    }
}

void DrawCell(int posX, int posY, Color color) {
    DrawRectangle(posX, posY, blockWidth, blockHeight, color);
}

int CountNeighbours(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the center cell
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight && gameGrid[currentBuffer][nx][ny]) {
                count++;
            }
        }
    }
    return count;
}

void ApplyRules(int x, int y) {
    int neighbours = CountNeighbours(x, y);
    if (gameGrid[currentBuffer][x][y]) {
        gameGrid[(currentBuffer + 1) % 2][x][y] = (neighbours == 2 || neighbours == 3);
    } else {
        gameGrid[(currentBuffer + 1) % 2][x][y] = (neighbours == 3);
    }
}

Vector2 GetMouseGridPosition(int cellWidth, int cellHeight) {
    Vector2 mousePosition = GetMousePosition();

    int gridX = (int)(mousePosition.x / cellWidth);
    int gridY = (int)(mousePosition.y / cellHeight);

    // Clamp values to grid boundaries
    gridX = Clamp(gridX, 0, gridWidth - 1);
    gridY = Clamp(gridY, 0, gridHeight - 1);

    return (Vector2){ gridX, gridY };
}

void DrawGUI(void){
    GuiSliderBar((Rectangle){600,40,120,20}, "Max FPS", NULL, (float *) &maxFPS, 0, 100);
    GuiCheckBox((Rectangle) { 600, 320, 20, 20 }, "Draw Grid", &drawGrid);
}
