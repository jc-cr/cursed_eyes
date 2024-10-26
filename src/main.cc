#include <ncurses.h>
#include "eye.hh"
#include <vector>


int main() {
    // Initialize ncurses with proper settings
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    mouseinterval(0);
    
    // Enable mouse tracking
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n");
    
    // Get terminal dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Calculate eye positions and offsets
    int eye_spacing = max_x;  // Distance between eyes
    Eye left_eye(max_y/2, max_x/2 - eye_spacing/2);
    Eye right_eye(max_y/2, max_x/2 + eye_spacing/2);
    
    MEVENT event;
    int mouse_x = max_x/2;
    int mouse_y = max_y/2;
    
    timeout(10);
    
    while (true) {
        // Get input (mouse or keyboard)
        int ch = getch();
        
        // Handle input
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            mouse_x = event.x;
            mouse_y = event.y;
        }
        else if (ch == 'q' || ch == 'Q') {
            break;
        }
        
        // Draw eyes with appropriate offsets
        left_eye.draw(mouse_y, mouse_x, -eye_spacing);
        right_eye.draw(mouse_y, mouse_x, eye_spacing);
        
        // Refresh screen
        refresh();
    }
    
    // Cleanup
    printf("\033[?1003l\n");
    endwin();
    return 0;
}