#include "process.h"
Process::Process()
{
    initColors();
    id=idAct++;
    colorAct=(colorAct==LAST_COLOR)? FIRST_COLOR:colorAct+1;
    color=colors[colorAct];
    startTime=0;
    executionTime=0;
    returnTime=0;
    timeRemainig=executionTime;
    status=WAIT;
}
Process::Process(int startTime,int executionTime){
    initColors();
    this->startTime=startTime;
    this->executionTime=executionTime;
    id=idAct++;
    timeRemainig=executionTime;
    colorAct=(colorAct==LAST_COLOR)? FIRST_COLOR:colorAct+1;
    color=colors[colorAct];
    returnTime=startTime+executionTime;
    status=WAIT;
}
Process::Process(int initializeType){
    initColors();
    id=idAct++;
    colorAct=(colorAct==LAST_COLOR)? FIRST_COLOR:colorAct+1;
    color=colors[colorAct];
    status=WAIT;
    switch (initializeType) {
    case RANDOM_PROCESS:
        srand(rdtsc());
        executionTime=rand()%MAX_DURATION+1;
        startTime=rand()%MAX_START_TIME+1;
        returnTime=startTime+executionTime;
        timeRemainig=executionTime;
        break;
    default:
        break;
    }

}
int Process::getExecutionTime(){
    return executionTime;
}
int Process::getId(){
    return id;
}
int Process::getStartTime(){
    return startTime;
}
void Process::setReturnTime(int returnTime){
    this->returnTime=returnTime;
}
void Process::setExecutionTime(int executionTime){
    this->executionTime=executionTime;
}
void Process::setStartTime(int startTime){
    this->startTime=startTime;
}
void Process::setStatus(int status){
    this->status=status;
}

int Process::getReturnTime(){
    return returnTime;
}
QString Process::getColor(){
    return color;
}
int Process::getStatus(){
    return status;
}
int Process::getTimeRemainig(){
    return timeRemainig;
}
void Process::increaseTimeRemainig(){
    timeRemainig--;
   if(timeRemainig==0) status=FINISH;
}

bool Process::compareLessStartTime(Process* a,Process* b){
    return a->getStartTime()<b->getStartTime();
}
void Process::initColors(){
    colors[0]="color0";
    colors[1]="color1";
    colors[2]="black";
    colors[3]="white";
    colors[4]="darkGray";
    colors[5]="gray";
    colors[6]="ligthGray";
    colors[7]="red";
    colors[8]="green";
    colors[9]="blue";
    colors[10]="cyan";
    colors[11]="magenta";
    colors[12]="yellow";
    colors[13]="darkRed";
    colors[14]="darkGreen";
    colors[15]="darkBlue";
    colors[16]="darkCyan";
    colors[17]="darkMagenta";
    colors[18]="darkYellow";
    colors[19]="transparent";
}

int Process::rdtsc()
{
   __asm__ __volatile__("rdtsc");
}
