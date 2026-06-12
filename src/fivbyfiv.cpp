#include "selector.hpp"
#include <algorithm>
#include <raylib.h>

#include <iostream>

#define fiv 5

int move_count = 0;
int on_count = 0;

int main() {

    bool board[fiv][fiv]{};

    auto new_game = [&]() {
        std::fill(&board[0][0], &board[0][0] + fiv * fiv, 0);
        move_count = 0;
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

    // winning condition
    auto iswin = [&]() -> bool {
        bool didi = true;
        on_count = 0;
        for (int i = 0; i < fiv; i++) {
            for (int j = 0; j < fiv; j++) {
                if (!board[i][j]) {
                    didi = false; // for on_count
                } else {
                    on_count++; // side effect
                }
            }
        }
        return didi;
    };

    const int window_width = 400;
    const int window_height = 300;
    InitWindow(window_width, window_height, "5x5");
    SetTargetFPS(60);

    HideCursor();

    const int cell_size = window_height / fiv;
    Color inactive = {0, 101, 6, 255};
    Color active = {71, 224, 81, 255};

    // footer
    const std::string game_info = "\n\n\nn: new game\nesc: quit";

    const float roundness = 0.3f;
    const int segments = 4;
    while (!WindowShouldClose()) {

        int focus_x = focus_index / 5;
        int focus_y = focus_index % 5;

        if (IsKeyPressed(KEY_N)) {
            new_game();
        } else if (IsKeyPressed(KEY_ENTER) or
                   IsKeyPressed(KEY_SPACE)) { // Toggle
            toggle_cross(focus_x, focus_y);
            move_count++;
        } else if (IsKeyPressed(KEY_LEFT)) {
            focus_move_left();
        } else if (IsKeyPressed(KEY_DOWN)) {
            focus_move_down();
        } else if (IsKeyPressed(KEY_UP)) {
            focus_move_up();
        } else if (IsKeyPressed(KEY_RIGHT)) {
            focus_move_right();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // check winning
        if (iswin()) {
            DrawText(game_info.c_str(), window_height / 3, 0, 20, WHITE);
        } else {
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
                        DrawRectangleRounded(cell, roundness, segments,
                                             inactive);
                    }
                }
            }

            struct Rectangle focus_cell = {(float)focus_y * cell_size + padding,
                                           (float)focus_x * cell_size + padding,
                                           cell_size - padding,
                                           cell_size - padding};
            // draw focus
            DrawRectangleRoundedLines(focus_cell, roundness, segments, ORANGE);

            // draw seperator
            DrawLine(window_height + padding, 0, window_height + padding,
                     window_height + padding, ORANGE);

            // move_count on_count
            std::string onandmove = "move count: ";
            onandmove += std::to_string(move_count);
            onandmove += "\non count: ";
            onandmove += std::to_string(on_count);
            std::string move_info = "\n\n\nret/spc :toggle\narrows :move\n";
            onandmove += move_info + game_info;
            DrawText(onandmove.c_str(), window_height + 2 * padding,
                     2 * padding, 10, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
