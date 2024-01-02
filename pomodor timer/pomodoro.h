// pomodoro.h
#ifndef POMODORO_H
#define POMODORO_H

#include <ncurses.h>
#include <fstream>
#include <cstdio>

class Pomodoro {
private:
    int workduration;
    int breakduration;
    int sessioncompleted;
    int totalworktime;
    bool paused;
    bool working;

public:
    Pomodoro();
    Pomodoro(int n, int m);
    ~Pomodoro();
    bool start_session_end_session(WINDOW *win);
    void changeMinutes(WINDOW *win);
    bool askToChangeMinutes(WINDOW *win);
    void getstatistic(WINDOW *win);
    bool work(WINDOW *win);
    bool break_time(WINDOW *win);
    bool timer(WINDOW *win, const char *message, int n);
    void clearscrean(WINDOW *win);
    bool askToContinue(WINDOW *win);
    void askForStatistic(WINDOW *win);
    void saveStatisticToFile(WINDOW *win);
    void waitForEnterKey(WINDOW *win);
    //void messages(WINDOW *win);
   bool askToSaveFiles(WINDOW *win);
};

#endif // POMODORO_H
