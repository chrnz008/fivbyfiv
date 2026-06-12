#include "selector.hpp"
#include <algorithm>
#include <raylib.h>

#include <iostream>

#define fiv 5

int main() {

    bool board[fiv][fiv]{};
    // board[0][0] = true;

    auto new_game = [&]() {
        std::fill(&board[0][0], &board[0][0] + fiv * fiv, 0);
    };

    auto toggle_cross = [&](int x, int y) {
        board[x][y] = !board[x][y];
        if (x != 0) {
            board[x - 1][y] = !board[x - 1][y];
        }
        if (x != 4) {
            board[x + 1][y] = !board[x + 1][y];
        }
        if (y != 0) {
            board[x][y - 1] = !board[x][y - 1];
        }
        if (y != 4) {
            board[x][y + 1] = !board[x][y + 1];
        }
    };

    const int window_width = 400;
    const int window_height = 300;
    InitWindow(window_width, window_height, "5x5");
    SetTargetFPS(60);

    HideCursor();

    const int cell_size = window_height / fiv;
    Color inactive = {0, 101, 6, 255};
    Color active = {71, 224, 81, 255};

    const float roundness = 0.3f;
    const int segments = 4;
    while (!WindowShouldClose()) {

        int focus_x = focus_index / 5;
        int focus_y = focus_index % 5;

        if (IsKeyPressed(KEY_N)) {
            new_game();
        } else if (IsKeyPressed(KEY_ENTER)) { // Toggle
            toggle_cross(focus_x, focus_y);
        } else if (IsKeyPressed(KEY_LEFT)) {
            focus_move_left();
        } else if (IsKeyPressed(KEY_DOWN)) {
            focus_move_down();
        } else if (IsKeyPressed(KEY_UP)) {
            focus_move_up();
        } else if (IsKeyPressed(KEY_RIGHT)) {
            focus_move_right();
        }
        std::cout << focus_index << std::endl;

        BeginDrawing();
        ClearBackground(BLACK);

        const int padding = 5;
        // Drawing
        for (int i = 0; i < fiv; i++) {
            for (int j = 0; j < fiv; j++) {

                struct Rectangle cell = {(float)j * cell_size + padding,
                                         (float)i * cell_size + padding,
                                         cell_size - padding,
                                         cell_size - padding};

                if (board[i][j]) {
                    DrawRectangleRounded(cell, roundness, segments, active);
                } else {
                    DrawRectangleRounded(cell, roundness, segments, inactive);
                }
            }
        }

        struct Rectangle focus_cell = {(float)focus_y * cell_size + padding,
                                       (float)focus_x * cell_size + padding,
                                       cell_size - padding,
                                       cell_size - padding};
        // draw focus
        DrawRectangleRoundedLines(focus_cell, roundness, segments, ORANGE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
