#include <raylib.h>
#include <algorithm>

#define fiv 5
int main() {

    bool board[fiv][fiv]{};
    board[0][0] = true;

	auto new_game = [&](){
		std::fill(&board[0][0],&board[0][0]+fiv*fiv,0);	
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
    const int segments = 16;
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_N)) {
            new_game();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < fiv; i++) {
            for (int j = 0; j < fiv; j++) {

                struct Rectangle cell = {(float)i * cell_size,
                                         (float)j * cell_size, cell_size,
                                         cell_size};

                if (board[i][j]) {
                    DrawRectangleRounded(cell, roundness, segments, active);
                } else {
                    DrawRectangleRounded(cell, roundness, segments, inactive);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
