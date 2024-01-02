// pomodoro.cpp
#include "pomodoro.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdio>

Pomodoro::Pomodoro() : workduration(25), breakduration(5), working(true), sessioncompleted(0), totalworktime(0), paused(true) {}
Pomodoro::Pomodoro(int n, int m) : workduration(n), breakduration(m), working(true), sessioncompleted(0), totalworktime(0), paused(true) {}
Pomodoro::~Pomodoro() {}

bool Pomodoro::start_session_end_session(WINDOW *win) {
    
    clearscrean(win);
    while (working) {
         clearscrean(win);
        beep(); // Produce a beep sound
        refresh();
        wprintw(win, "Starting Pomodoro Timer...\n");
        wprintw(win, "If you press 'p', you can pause, and with 'q', you can quit.\n");
        wrefresh(win);
        waitForEnterKey(win);
        
        
        if (!work(win)||!break_time(win)) {  
            beep(); // Produce a beep sound
            refresh();
            return false; // If 'q' is pressed during the session, return false to go back to the main loop
       
        }

        sessioncompleted++;
        totalworktime =totalworktime+ workduration;

        
        askForStatistic(win);
        if (askToContinue(win)) {
            if (askToChangeMinutes(win)) {
                changeMinutes(win);
            }
            continue;
        } else {
           
            getstatistic(win);

                if(askToSaveFiles(win)){saveStatisticToFile(win);}
                beep(); // Produce a beep sound
                refresh();
            return false;
            
        }
       
    }
    wrefresh(win);
    beep(); // Produce a beep sound
    refresh();
    return true; // Session completed successfully
}

void Pomodoro::changeMinutes(WINDOW *win) {
    int new_Workduration, new_Breakduration;

    do {
        clearscrean(win);
        wprintw(win, "Enter new work duration in minutes: ");
        wrefresh(win);
        wscanw(win, "%d", &new_Workduration);

        clearscrean(win);
        wprintw(win, "Enter new break duration in minutes: ");
        wrefresh(win);
        wscanw(win, "%d", &new_Breakduration);
    } while (new_Workduration <= 0 || new_Breakduration <= 0);

    workduration = new_Workduration;
    breakduration = new_Breakduration;

    clearscrean(win);
    wprintw(win, "Work and break durations changed. Press Enter to start the next session...\n");
    wrefresh(win);
    waitForEnterKey(win);
}

bool Pomodoro::askToChangeMinutes(WINDOW *win) {
    clearscrean(win);
    wprintw(win, "Do you want to change the work and break durations? (y/n)\n");
    wrefresh(win);
    int ch;
    while ((ch = getch()) == ERR) {
        // Wait for user input
    }

    return (ch == 'y' || ch == 'Y');
}

void Pomodoro::getstatistic(WINDOW *win) {
    clearscrean(win);
    wprintw(win, "Session Summary:\n");
    wprintw(win, "Sessions Completed: %d\n", sessioncompleted);
    wprintw(win, "Total Work Time: %d min\n", totalworktime);
    wrefresh(win);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Display summary for 2 seconds
}

bool Pomodoro::work(WINDOW *win) {
    return timer(win, "Work Time", workduration);
}

bool  Pomodoro::break_time(WINDOW *win) {
   return timer(win, "Break Time", breakduration);
}

bool Pomodoro::timer(WINDOW *win, const char *message, int n) {
    
    const int totalTime = n * 60;
    int remainingTime = totalTime;

    while (remainingTime > 0 && working) {
        clearscrean(win);

        if (paused) {
            int minutes = remainingTime / 60;
            int seconds = remainingTime % 60;
            wprintw(win, "%s: %02d:%02d\n", message, minutes, seconds);
            wrefresh(win);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            remainingTime--;
        } else {
            wprintw(win, "Session Paused. Press 'p' to resume or 'q' to go back to main menu...\n");
            wrefresh(win);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        int ch = getch();
        if (ch != ERR) {
            if (ch == 'p') {
                paused = !paused;
                wprintw(win, "%s %s\n", message, paused ? "Paused" : "Resumed");
                wrefresh(win);
            } else if (ch == 'q') {
                working = !working;
                return false; // User pressed 'q', return false to go back to the main loop
            }
        }
    }

    return true; // Session completed successfully
}

void Pomodoro::clearscrean(WINDOW *win) {
    werase(win);
}

bool Pomodoro::askToContinue(WINDOW *win) {
    wprintw(win, "Do you want to continue? (y/n)\n");
    wrefresh(win);
    int ch;
    while ((ch = getch()) == ERR) {
        // Wait for user input
    }

    return (ch == 'y' || ch == 'Y');
}

void Pomodoro::askForStatistic(WINDOW *win) {
    clearscrean(win);
    wprintw(win, "Session completed! Do you want to see statistics? (y/n)\n");
    wrefresh(win);
    int ch;
    while ((ch = getch()) == ERR) {
        // Wait for user input
    }

    if (ch == 'y' || ch == 'Y') {
        getstatistic(win);
    }
}

void Pomodoro::saveStatisticToFile(WINDOW *win) {
    
     wprintw(win,"do you want to delete the content of the file?(y/n)\n");
    wrefresh(win);
    int ch;
    while ((ch = getch()) == ERR) {
        // Wait for user input
    }

    if (ch == 'y' || ch == 'Y') {
        std::ofstream truncateFile("pomodoro_statistics.txt"   );
        if(truncateFile.is_open()){
            truncateFile.close();
            wprintw(win,"file contents deleted");
            wrefresh(win);
            
        }else{
            wprintw(win, "Unable to open the file for truncating.\n");
            wrefresh(win);
            return;
        }
    }
        std::ofstream outFile("pomodoro_statistics.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Session Summary:\n";
        outFile << "Sessions Completed: " << sessioncompleted << "\n";
        outFile << "Total Work Time: " << totalworktime << " min\n";
        outFile << "------------------------\n";
        outFile.close();
        wprintw(win,"Statistics saved to file.\n") ;
        wrefresh(win);
    } else {
        wprintw(win,"Unable to open the statistics file for writing.\n") ;
    }
}

void Pomodoro::waitForEnterKey(WINDOW *win) {
    wprintw(win, "Press Enter to continue...\n");
    wrefresh(win);
    
    int ch;
    while ((ch = getch()) != '\n') {
        // Wait for Enter key
    }
    
}
bool Pomodoro::askToSaveFiles(WINDOW *win) {
    clearscrean(win);
    wprintw(win, "Do you want to save the files? (y/n)\n");
    wrefresh(win);
    int ch;
    while ((ch = getch()) == ERR) {
        // Wait for user input
    }

    return (ch == 'y' || ch == 'Y');
}




