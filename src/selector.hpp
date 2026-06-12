static int focus_index = 0;

void focus_clamp() {
    if (focus_index > 24) {
        focus_index = 24;
    } else if (focus_index < 0) {
        focus_index = 0;
    }
}
void focus_move_right() {
    focus_index++;
    focus_clamp();
}
void focus_move_left() {
    focus_index--;
    focus_clamp();
}
void focus_move_down() {
    focus_index += 5;
    focus_clamp();
}
void focus_move_up() {
    focus_index -= 5;
    focus_clamp();
}
