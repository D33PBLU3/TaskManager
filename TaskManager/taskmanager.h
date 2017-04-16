#ifndef TASKMANEGER_H
#define TASKMANEGER_H

#include <QMainWindow>
#include <QList>
#include <QTimer>
#include "process.h"
#define SIMULATION_SPEED 500
#define COLUMN_RETURN_TIME 1
enum{
    COLUMN_ID=0,
    COLUMN_START_TIME,
    COLUMN_DURATION
};
namespace Ui {
class TaskManager;
}

class TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit TaskManager(QWidget *parent = 0);
    ~TaskManager();

private slots:

    void on_btnStart_clicked();
    void simulate();
private:
    QList<Process*> processList;
    QList<Process*> processListByReturnTime;
    int globalTime;
    QTimer* timeSimulation;
    Ui::TaskManager *ui;
    void createRandomProcess(int);
    void initScreen();
    void startSimulation();
    void updateScreen();
    void sortProcessByStartTime();
    int maxReturnTime();
    void resizeExecuntionTable();

};

#endif // TASKMANEGER_H
