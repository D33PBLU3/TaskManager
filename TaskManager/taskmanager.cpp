#include "taskmanager.h"
#include "ui_taskmanager.h"
int Process::idAct=FIRST_ID;
int Process::colorAct=FIRST_COLOR;

TaskManager::TaskManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaskManager)
{
    ui->setupUi(this);

    ui->processTable->resizeColumnsToContents();
    ui->executionOrderTable->resizeColumnsToContents();
    // ui->executionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
TaskManager::~TaskManager()
{
    delete ui;
}
void TaskManager::on_btnStart_clicked()
{
    int quant=ui->quantity->text().toInt();
    globalTime=-1;
    createRandomProcess(quant);
    initScreen();
    startSimulation();
}
void TaskManager::createRandomProcess(int quant){
    for(int j=0;j<quant;j++)
        processList.append(new Process(RANDOM_PROCESS));
}
void TaskManager::initScreen(){
    int maxRetTime;
    ui->processTable->resizeColumnsToContents();
    ui->executionOrderTable->resizeColumnsToContents();
    ui->executionTable->setShowGrid(false);
    ui->executionTable->horizontalHeader()->hide();
    ui->executionTable->verticalHeader()->hide();
    ui->executionOrderTable->verticalHeader()->hide();
    ui->processTable->verticalHeader()->hide();
    for(int j=0;j<processList.length();j++){
        ui->processTable->insertRow(j);
        ui->processTable->setItem(j,COLUMN_ID,new QTableWidgetItem((QString::number(
                                                                        processList.value(j)->getId()))));
        ui->processTable->setItem(j,COLUMN_START_TIME,new QTableWidgetItem((QString::number(
                                                                                processList.value(j)->getStartTime()))));
        ui->processTable->setItem(j,COLUMN_DURATION,new QTableWidgetItem((QString::number(
                                                                              processList.value(j)->getExecutionTime()))));
    }
    sortProcessByStartTime();
    for(int j=0;j<processListByReturnTime.length();j++){
        ui->executionOrderTable->insertRow(j);
        ui->executionOrderTable->setItem(j,COLUMN_ID,new QTableWidgetItem((QString::number(
                                                                               processListByReturnTime.value(j)->getId()))));
        ui->executionOrderTable->setItem(j,COLUMN_RETURN_TIME,new QTableWidgetItem((QString::number(
                                                                                        processListByReturnTime.value(j)->getReturnTime()))));
    }
    maxRetTime=maxReturnTime();
    for(int j=0;j<=maxRetTime;j++){
        ui->executionTable->insertColumn(j);

    }
    for(int j=0;j<processList.length();j++)
        ui->executionTable->insertRow(j);
    resizeExecuntionTable();

}
void TaskManager::sortProcessByStartTime(){
    processListByReturnTime=processList;
    std::sort(processListByReturnTime.begin(),processListByReturnTime.end(),Process::compareLessStartTime);
}
void TaskManager::startSimulation(){
    float speedSimulation=ui->speedSim->text().toFloat();
    timeSimulation=new QTimer;
    connect(timeSimulation,SIGNAL(timeout()),this,SLOT(simulate()));
    timeSimulation->start(speedSimulation*1000.0);
}
void TaskManager::simulate(){
    for(int j=0;j<processListByReturnTime.length();j++){
        if(processListByReturnTime.at(j)->getStatus()==EXECUTING)
            processListByReturnTime.at(j)->increaseTimeRemainig();
        if(processListByReturnTime.at(j)->getStartTime()==globalTime)
            processListByReturnTime.at(j)->setStatus(EXECUTING);
    }
    globalTime++;
    updateScreen();
    if(globalTime==maxReturnTime())
        timeSimulation->stop();
}
void TaskManager::updateScreen(){
    for(int j=0;j<processList.length();j++){
        if(processList.at(j)->getStatus()==EXECUTING){
            ui->executionTable->setItem(processList.at(j)->getId(),globalTime,new QTableWidgetItem());
            ui->executionTable->item(processList.at(j)->getId(),globalTime)->
                    setBackgroundColor(*(new QColor(processList.at(j)->getColor())));//For the Dario of the future:
        }                                                                           //remember that setBackgroundColor
    }                                                                                //is deprecated, try to change the function
    ui->lbGlobalTime->setText(QString::number(globalTime));
}
int TaskManager::maxReturnTime(){
    int max=0;
    for(int j=0;j<processList.length();j++){
        if(max<processList.at(j)->getReturnTime())
            max=processList.at(j)->getReturnTime();
    }
    return max;
}
void TaskManager::resizeExecuntionTable(){
    if(maxReturnTime()!=0){
        float columnWidth=ui->executionTable->width()/(maxReturnTime()+1);
        float rowHeigth=ui->executionTable->height()/processList.length();
        for(int j=0;j<ui->executionTable->columnCount();j++)
            ui->executionTable->setColumnWidth(j,columnWidth);
        for(int j=0;j<ui->executionTable->rowCount();j++)
            ui->executionTable->setRowHeight(j,rowHeigth);
    }
}
