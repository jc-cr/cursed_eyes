#pragma once
#include <ncurses.h>
#include <cmath>

class Eye {
    public:
        Eye(int y, int x) : center_y(y), center_x(x) {}
        
        // Calculate gaze angle based on target position and distance
        static float calculateGazeAngle(float dx, float dy, float distance, float eye_offset);

        void draw(int cursor_y, int cursor_x, float eye_offset);

    private:
        int center_y, center_x;
        static constexpr float PUPIL_RADIUS = 2.0f;  // Increased radius for more visible movement
};