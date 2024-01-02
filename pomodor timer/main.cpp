#include "pomodoro.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <ncurses.h>
void openAndDisplayStatistics(WINDOW *win) {
    std::ifstream inFile("pomodoro_statistics.txt");
    if (inFile.is_open()) {
        std::string line;
        wclear(win);
        wprintw(win, "------------------------Statistics------------------------\n");
        while (std::getline(inFile, line)) {
            wprintw(win, "%s\n", line.c_str());
        }
        inFile.close();
        wprintw(win, "------------------------End of Statistics-----------------\n");
    } else {
        wprintw(win, "No statistics available.\n");
    }

    wrefresh(win);
    Pomodoro pomodoroInstance;
    pomodoroInstance.waitForEnterKey(win);
}

int main() {
    initscr(); // Initialize ncurses
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    WINDOW *mainwin = newwin(24, 80, 0, 0); // Create a new window
    keypad(mainwin, TRUE);
    beep(); // Produce a beep sound
    refresh();
    bool quit = false;

    while (!quit) {
        wclear(mainwin);
        wprintw(mainwin, "------------------------Pomodoro Timer------------------------\n");
        wprintw(mainwin, "1. Start Pomodoro Timer (Default: Work Duration - 25 min, Break Duration - 5 min)\n");
        wprintw(mainwin, "2. Change Work Duration and Break Duration\n");
        wprintw(mainwin, "3. View Statistics\n");
        wprintw(mainwin, "4. Exit\n");

        int choice;
        wrefresh(mainwin);
        wscanw(mainwin, "%d", &choice);
        getch();
        flushinp();

        switch (choice) {
            case 1: {
                Pomodoro p;
                wclear(mainwin);
                wrefresh(mainwin);
                if (!p.start_session_end_session(mainwin)) {
                    break;
                }
                
            }
            case 2: {
                int number, number2;
                do {
                    wclear(mainwin);
                    wprintw(mainwin, "Enter new work duration in minutes: ");
                    wrefresh(mainwin);
                    wscanw(mainwin, "%d", &number);

                    wprintw(mainwin, "Enter new break duration in minutes: ");
                    wrefresh(mainwin);
                    wscanw(mainwin, "%d", &number2);
                    flushinp();
                } while (number > 99 || number <= 0 || number2 > 99 || number2 <= 0);

                Pomodoro p2(number, number2);
                wrefresh(mainwin);
                if (!p2.start_session_end_session(mainwin)) {
                    break;
                }

                // Clear the screen for the next iteration
                wclear(mainwin);
                break;
            }
            case 3: {
                openAndDisplayStatistics(mainwin);
                break;
            }
            case 4: {
                quit = true;
                break;
            }
            default: {
                
                wprintw(mainwin, "Invalid choice. Please enter 1, 2, 3, or 4.\n");
                wrefresh(mainwin);
               
                std::this_thread::sleep_for(std::chrono::seconds(2));
                wclear(mainwin);
                break;
            }
        }
    }

    // End ncurses session
     beep(); // Produce a beep sound
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    delwin(mainwin);
    endwin();
    return 0;
}
