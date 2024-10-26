#include "eye.hh"

float Eye::calculateGazeAngle(float dx, float dy, float distance, float eye_offset) {
    // Determine if cursor is between the eyes
    bool is_between_eyes = abs(dx) < abs(eye_offset);
    
    // Base angle from eye center to cursor
    float base_angle = atan2(dy, dx);
    
    if (is_between_eyes) {
        // When cursor is between eyes, create mirrored convergence effect
        // For left eye (negative offset), angle moves toward 0
        // For right eye (positive offset), angle moves toward PI
        float target_angle = (eye_offset < 0) ? 0.0f : M_PI;
        float blend_factor = 1.0f - (abs(dx) / abs(eye_offset));
        return base_angle * (1.0f - blend_factor) + target_angle * blend_factor;
    } else {
        // When cursor is outside, both eyes track in parallel
        return base_angle;
    }
}

void Eye::draw(int cursor_y, int cursor_x, float eye_offset) {
    // Draw larger eye frame
    mvprintw(center_y - 1, center_x - 3, ",---.");
    mvprintw(center_y, center_x - 3, "|   |");
    mvprintw(center_y + 1, center_x - 3, "`---'");

    // Calculate direction to cursor
    float dx = cursor_x - center_x;
    float dy = cursor_y - center_y;
    float distance = sqrt(dx*dx + dy*dy);

    // Get tracking angle
    float angle = calculateGazeAngle(dx, dy, distance, eye_offset);

    // Position pupil on the eye perimeter
    // PUPIL_RADIUS defines the size of our circular tracking path
    int pupil_y = center_y + (int)(PUPIL_RADIUS * sin(angle));
    int pupil_x = center_x + (int)(PUPIL_RADIUS * cos(angle));

    // Draw larger pupil
    mvaddch(pupil_y, pupil_x, '@' | A_BOLD);
}