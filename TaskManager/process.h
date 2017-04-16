#ifndef PROCESS_H
#define PROCESS_H
#include <cstdlib>
#include <QString>
#define RANDOM_PROCESS 1
#define MAX_DURATION 50
#define MAX_START_TIME 50
#define FIRST_ID 0
#define FIRST_COLOR 3
#define LAST_COLOR 19
#define MAX_COLOR 20
enum{
    WAIT=1,
    EXECUTING,
    FINISH
};

class Process
{
private:

   int id;
   int executionTime;
   int startTime;
   int returnTime;
   QString color;
   int status;
   int timeRemainig;
   static int idAct;
   static int colorAct;
   QString colors[MAX_COLOR];
public:

   Process();
   Process(int,int);
   Process(int);
    void setStartTime(int);
    void setExecutionTime(int);
    void setReturnTime(int);
    void setStatus(int);
    QString getColor();
    int getId();
    int getStartTime();
    int getExecutionTime();
    int getReturnTime();
    int getStatus();
    int getTimeRemainig();
    void increaseTimeRemainig();
    static bool compareLessStartTime(Process*,Process*);
    void initColors();
private:
    int rdtsc();

};

#endif // PROCESS_H
