#include "mainwindow.h"
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QList>
#include <stdlib.h>
#include <stdio.h>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

bool actiontime=true;
bool actionlineID=true;
bool actionstationID=true;
bool actiondeviceID=true;
bool actionstatus=true;
bool actionuserID=true;
bool actionpayType=true;
int row=0;
int num[7]={0,1,2,3,4,5,6};
int map[81][81];
int start;
int end;
int num_of_roads=0;
int min_road=100;
int least_road[100];
int road[100];
int flag[100];
int customer_station;
int customer=2147483646;
int least_customer[100];
int customer_num[81];
int station_show;
int time_step=3600;
int count=24;
int count_2=24*7;
int block[1000]={0};
int type=0;
int station[81]={0};
int paytype[4]={0};
int device[3650]={0};
int lines[3]={0};
Message message[200000];
QDateTime time_all[700000];
QString fileName;
QString fileName1;
QString fileName2;
QString num_path;
QDateTime time_data[200000];
QString start_time1="2019-01-07 00:00:00";
QString end_time1="2019-01-07 23:59:59";
QString end_time2="2019-01-13 23:59:59";
QDateTime start_time=QDateTime::fromString(start_time1,"yyyy-MM-dd hh:mm:ss");
QDateTime end_time_1=QDateTime::fromString(end_time1,"yyyy-MM-dd hh:mm:ss");
QDateTime end_time_2=QDateTime::fromString(end_time2,"yyyy-MM-dd hh:mm:ss");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->hide();
    ui->roadinformatiion->isReadOnly();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actiontime_triggered()
{
    if (actiontime==true) {
    actiontime=false;
    ui->data_table->setColumnHidden(num[0],true);
    }
    else {
        actiontime=true;
        ui->data_table->showColumn(num[0]);
    }
}


void MainWindow::on_actionlineID_triggered()
{
    if (actionlineID==true) {
    actionlineID=false;
    ui->data_table->setColumnHidden(num[1],true);
    }
    else {
        actionlineID=true;
        ui->data_table->showColumn(num[1]);
    }
}

void MainWindow::on_actionstationID_triggered()
{
    if (actionstationID==true) {
    actionstationID=false;
    ui->data_table->setColumnHidden(num[2],true);
    }
    else {
        actionstationID=true;
        ui->data_table->showColumn(num[2]);
    }
}

void MainWindow::on_actiondeviceID_triggered()
{
    if (actiondeviceID==true) {
    actiondeviceID=false;
    ui->data_table->setColumnHidden(num[3],true);
    }
    else {
        actiondeviceID=true;
        ui->data_table->showColumn(num[3]);
    }
}

void MainWindow::on_actionstatus_triggered()
{
    if (actionstatus==true) {
    actionstatus=false;
    ui->data_table->setColumnHidden(num[4],true);
    }
    else {
        actionstatus=true;
        ui->data_table->showColumn(num[4]);
    }
}

void MainWindow::on_actionuserID_triggered()
{
    if (actionuserID==true) {
    actionuserID=false;
    ui->data_table->setColumnHidden(num[5],true);
    }
    else {
        actionuserID=true;
        ui->data_table->showColumn(num[5]);
    }
}

void MainWindow::on_actionpayType_triggered()
{
    if (actionpayType==true) {
    actionpayType=false;
    ui->data_table->setColumnHidden(num[6],true);
    }
    else {
        actionpayType=true;
        ui->data_table->showColumn(num[6]);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    ui->tabWidget->show();
    fileName = QFileDialog::getOpenFileName(this, tr("Choose a data file"), "", "*.csv");
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::on_actionplan_a_road_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Choose a Metro_roadMap file"), "", "*.csv");
    num_path = QFileDialog::getOpenFileName(this, tr("Choose a station_all file"), "", "*.csv");

    ui->roadinformatiion->textCursor().insertText("The Metro_roadMap you choose is: "+FileName+"\n");
    QFile file(FileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);

    int lines=0;
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);

            if (lines!=0) {
                for (int i=1;i<=81;i++) {
                    map[lines-1][i-1]=pieces.value(i).toInt();
                }
            }
            lines++;
        }
    }
    file.close();
}

void MainWindow::on_actionSave_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save file as"), "", "*.csv");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;

    QTextStream stream(&file);
    for (int i = 0; i < row; ++i) {

        QStringList pieces;

        pieces.append(message[i].time);
        pieces.append(message[i].lineID);
        pieces.append(message[i].stationID);
        pieces.append(message[i].deviceID);
        pieces.append(message[i].status);
        pieces.append(message[i].userID);
        pieces.append(message[i].payType);

        stream << pieces.join(',') << "\n";
    }

    file.close();
}

void MainWindow::loadFile(const QString &path)
{
    row=0;
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    ui->textEdit->textCursor().insertText("The dataset you choose is: "+path+"\n");
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
                message[row].time= pieces.value(0);
                message[row].lineID= pieces.value(1);
                message[row].stationID= pieces.value(2);
                message[row].deviceID= pieces.value(3);
                message[row].status= pieces.value(4);
                message[row].userID= pieces.value(5);
                message[row].payType= pieces.value(6);

                paytype[pieces.value(6).toInt()]++;
                station[pieces.value(2).toInt()]++;
                device[pieces.value(3).toInt()]++;
                if (pieces.value(1)=="A") lines[0]++;
                if (pieces.value(1)=="B") lines[1]++;
                if (pieces.value(1)=="C") lines[2]++;

                row++;
        }
    }
    file.close();

    ui->data_table->setRowCount(row-1);
    ui->data_table->setColumnCount(7);
    ui->data_table->setWindowTitle(fileName);

    QStringList header;
    header<<"time"<<"lineID"<<"stationID"<<"deviceID"<<"status"<<"userID"<<"payType";
    ui->data_table->setHorizontalHeaderLabels(header);


    for (int i=1;i<row;i++) {
    ui->data_table->setItem(i-1,0,new QTableWidgetItem(message[i].time));
    ui->data_table->setItem(i-1,1,new QTableWidgetItem(message[i].lineID));
    ui->data_table->setItem(i-1,2,new QTableWidgetItem(message[i].stationID));
    ui->data_table->setItem(i-1,3,new QTableWidgetItem(message[i].deviceID));
    ui->data_table->setItem(i-1,4,new QTableWidgetItem(message[i].status));
    ui->data_table->setItem(i-1,5,new QTableWidgetItem(message[i].userID));
    ui->data_table->setItem(i-1,6,new QTableWidgetItem(message[i].payType));
    }

    ui->data_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->data_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        quick_sort(message,1,row-1);
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    start=arg1.toInt();
}

void MainWindow::on_spinBox_2_valueChanged(const QString &arg1)
{
    end=arg1.toInt();
}



void MainWindow::findallroads()
{
    QString s = QString::number(start);
    QString e = QString::number(end);
    ui->roadinformatiion->textCursor().insertText("\n");
    ui->roadinformatiion->textCursor().insertText("The the entering station ID is "+s+"\n");
    ui->roadinformatiion->textCursor().insertText("The the exiting station ID is "+e+"\n");
    ui->roadinformatiion->textCursor().insertText("\n");
    init_customer_num();
    dfs(start,end,0);
}

void MainWindow::dfs(int x,int y,int t)
{
    flag[x]=1;
    road[t]=x;
    int tmp_num=0;
    if(x==y) {
        tmp_num=0;
        num_of_roads++;
        QString temp = QString::number(num_of_roads);
        ui->roadinformatiion->textCursor().insertText("Road"+temp+':');

        for(int i=0;i<=t;i++) {
            QString tmp = QString::number(road[i]);
            ui->roadinformatiion->textCursor().insertText(tmp+" ");
            tmp_num+=customer_num[i];
        }

        if (tmp_num<customer) {
            customer=tmp_num;
            for (int j=0;j<=t;j++) least_customer[j]=road[j];
            customer_station=t;
        }

        if (t<min_road) {
            min_road=t;
            for (int j=0;j<=t;j++) least_road[j]=road[j];
        }

        ui->roadinformatiion->textCursor().insertText("\n");
    }

    for(int i=0;i<81;i++) {
        if(map[x][i]!=0&&flag[i]==0) {
            dfs(i,y,t+1);
        }
    }

    flag[x]=0;
}

void MainWindow::on_YesButton_clicked()
{
    num_of_roads=0;
    min_road=100;
    customer=2147483646;
    findallroads();
    QString tmp = QString::number(num_of_roads);
    QString temp = QString::number(min_road);
    ui->roadinformatiion->textCursor().insertText("There are "+tmp+" roads in all"+"\n");

    ui->roadinformatiion->textCursor().insertText("\n");
    ui->roadinformatiion->textCursor().insertText("The least number of passing stations is "+temp+"\n");

    ui->roadinformatiion->textCursor().insertText("\n");

    ui->roadinformatiion->textCursor().insertText("The road with the fewest people is ");
    for(int i=0;i<=customer_station;i++) {
        QString tmp_customer = QString::number(least_customer[i]);
        ui->roadinformatiion->textCursor().insertText(tmp_customer+" ");
    }
    ui->roadinformatiion->textCursor().insertText("\n");
    ui->roadinformatiion->textCursor().insertText("And the num of people is: "+QString::number(customer));
    ui->roadinformatiion->textCursor().insertText("\n");
}

void MainWindow::init_customer_num()
{
    QFile file(num_path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);

    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
                customer_num[pieces.value(0).toInt()]=pieces.value(1).toInt();
        }
    }
    file.close();
}

void MainWindow::on_actionBased_on_the_dataset_you_choose_triggered()
{
    type=0;

    ui->dateTimeEdit->setMaximumDateTime(end_time_1);
    ui->dateTimeEdit->setMinimumDateTime(start_time);
    ui->dateTimeEdit->setDateTime(start_time);

    ui->dateTimeEdit_2->setMaximumDateTime(end_time_1);
    ui->dateTimeEdit_2->setMinimumDateTime(start_time);
    ui->dateTimeEdit_2->setDateTime(end_time_1);
}

void MainWindow::quick_sort(Message s[], int l, int r){
    if (l < r)    {
        int i = l, j = r;
        Message x = s[l];
        while (i < j)        {
            while(i < j && s[j].time >= x.time)
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i].time < x.time)
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);
    }
}

void MainWindow::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    start_time=dateTime;
}

void MainWindow::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    if (type==0) end_time_1=dateTime;
    if (type==1) end_time_2=dateTime;
}

void MainWindow::on_spinBox_3_valueChanged(const QString &arg1)
{
    station_show=arg1.toInt();
}

void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    QString step_time=time.toString();
    QString hour;
    QString minutes;
    hour=QString(step_time[0])+QString(step_time[1]);
    minutes=QString(step_time[3])+QString(step_time[4]);
    time_step=hour.toInt()*3600+minutes.toInt()*60;
    if(time_step!=0&&type==0) {
        count=(end_time_1.toTime_t()-start_time.toTime_t())/time_step+1;
    }
    if(time_step!=0&&type==1) {
        count_2=(end_time_2.toTime_t()-start_time.toTime_t())/time_step+1;
    }
}

void MainWindow::on_pushButton_time_clicked()
{
    if (type==0) {
        plot_in_trend();
        plot_out_trend();
    }
    if (type==1) {
        plot_in_trend_all();
        plot_out_trend_all();
    }

}

void MainWindow::plot_in_trend()
{
    int maxnum=0;
    QChart* Chart = new QChart();
    QSplineSeries *lineseries = new QSplineSeries();
    QDateTimeAxis *axisX = new QDateTimeAxis();
    QValueAxis *axisY = new QValueAxis();

    QChart* Chart2 = new QChart();
    QSplineSeries *lineseries2 = new QSplineSeries();
    QValueAxis *axisX2 = new QValueAxis();
    QValueAxis *axisY2 = new QValueAxis();

    int total=0;
    uint timen;
    int hash=0;
    for (int i=0;i<count;i++) block[i]=0;

    for (int i=1;i<row;i++) {
        QDateTime now_time=QDateTime::fromString(message[i].time,"yyyy-MM-dd hh:mm:ss");
        if (message[i].stationID.toInt()==station_show&&message[i].status=="1") {
                total+=1;
                if (now_time>start_time&&now_time<end_time_1) {
                    timen=now_time.toTime_t();
                    lineseries->append(timen, total);
                    hash=(timen-start_time.toTime_t())/time_step;
                    block[hash]++;
                }
        }
    }

    for (int i=0;i<count;i++) {
        lineseries2->append(i, block[i]);
        if (block[i]>maxnum) maxnum=block[i];
    }

    Chart->setTitle("the trend of traffic inflow depends on the total number of people");
    Chart->addSeries(lineseries);
    Chart->createDefaultAxes();
    Chart->legend()->hide();

    QChartView *view = new QChartView(Chart);
    view->setRenderHint(QPainter::Antialiasing);

    axisX->setRange(start_time,end_time_1);
    axisX->setFormat("hh:mm:ss");
    axisX->setTickCount(10);

    axisY->setRange(0,total);
    axisY->setLabelFormat("%u");

    Chart->setAxisX(axisX);
    Chart->setAxisY(axisY);
    lineseries->attachAxis(axisY);

    Chart2->setTitle("the trend of traffic inflow depends on the number of people over a period of time");
    Chart2->addSeries(lineseries2);
    Chart2->createDefaultAxes();
    Chart2->legend()->hide();

    QChartView *view2 = new QChartView(Chart2);
    view2->setRenderHint(QPainter::Antialiasing);

    axisX2->setRange(0,count-1);
    axisX2->setLabelFormat("%u");
    axisX2->setTickCount(count);

    axisY2->setRange(0,maxnum+10);
    axisY2->setLabelFormat("%u");

    Chart2->setAxisX(axisX2);
    Chart2->setAxisY(axisY2);
    lineseries2->attachAxis(axisY2);

    Chart->setTheme(QChart::ChartThemeBlueCerulean);
    Chart2->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget->setChart(Chart);
    ui->widget_3->setChart(Chart2);
}

void MainWindow::plot_out_trend()
{
    int maxnum=0;
    QChart* chart = new QChart();
    QSplineSeries *lineseries2 = new QSplineSeries();
    QDateTimeAxis *axisX2 = new QDateTimeAxis();
    QValueAxis *axisY2 = new QValueAxis();

    QChart* Chart = new QChart();
    QSplineSeries *lineseries = new QSplineSeries();
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    int total2=0;
    uint timen2;
    int hash=0;
    for (int i=0;i<count;i++) block[i]=0;

    for (int i=1;i<row;i++) {
        QDateTime now_time=QDateTime::fromString(message[i].time,"yyyy-MM-dd hh:mm:ss");
        if (message[i].stationID.toInt()==station_show&&message[i].status=="0") {
                total2+=1;
                if (now_time>start_time&&now_time<end_time_1) {
                timen2=now_time.toTime_t();
                lineseries2->append(timen2, total2);
                hash=(timen2-start_time.toTime_t())/time_step;
                block[hash]++;
                }
        }
    }

    for (int i=0;i<count;i++) {
        lineseries->append(i, block[i]);
        if (block[i]>maxnum) maxnum=block[i];
    }
    chart->setTitle(" the trend of traffic outflow depends on the total number of people");
    chart->addSeries(lineseries2);
    chart->createDefaultAxes();
    chart->legend()->hide();

    QChartView *view2 = new QChartView(chart);
    view2->setRenderHint(QPainter::Antialiasing);

    axisX2->setRange(start_time,end_time_1);
    axisX2->setFormat("hh:mm:ss");
    axisX2->setTickCount(10);

    axisY2->setRange(0,total2);
    axisY2->setLabelFormat("%u");

    chart->setAxisX(axisX2);
    chart->setAxisY(axisY2);
    lineseries2->attachAxis(axisY2);

    Chart->setTitle(" the trend of traffic outflow depends on the number of people over a period of time");
    Chart->addSeries(lineseries);
    Chart->createDefaultAxes();
    Chart->legend()->hide();

    QChartView *view = new QChartView(Chart);
    view->setRenderHint(QPainter::Antialiasing);

    axisX->setRange(0,count-1);
    axisX->setLabelFormat("%u");
    axisX->setTickCount(count);

    axisY->setRange(0,maxnum+10);
    axisY->setLabelFormat("%u");

    Chart->setAxisX(axisX);
    Chart->setAxisY(axisY);
    lineseries->attachAxis(axisY);

    chart->setTheme(QChart::ChartThemeBlueCerulean);
    Chart->setTheme(QChart::ChartThemeBlueCerulean);


    ui->widget_2->setChart(chart);
    ui->widget_4->setChart(Chart);

}


void MainWindow::on_actionBased_on_all_of_the_data_triggered()
{
    type=1;

    ui->dateTimeEdit->setMaximumDateTime(end_time_2);
    ui->dateTimeEdit->setMinimumDateTime(start_time);
    ui->dateTimeEdit->setDateTime(start_time);

    ui->dateTimeEdit_2->setMaximumDateTime(end_time_2);
    ui->dateTimeEdit_2->setMinimumDateTime(start_time);
    ui->dateTimeEdit_2->setDateTime(end_time_2);

}

void MainWindow::plot_in_trend_all()
{
    int line_all=0;

    fileName1 = QFileDialog::getOpenFileName(this, tr("Choose a station_in(1) file"), "", "*.csv");
    QFile file(fileName1);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
                time_all[line_all]= QDateTime::fromString(pieces.value(0),"yyyy-MM-dd hh:mm:ss");
                line_all++;
        }
    }
    file.close();

    quick_sort_2(time_all,0,line_all-1);

    QChart* Chart = new QChart();
    QSplineSeries *lineseries = new QSplineSeries();
    QDateTimeAxis *axisX = new QDateTimeAxis();
    QValueAxis *axisY = new QValueAxis();

    QChart* Chart2 = new QChart();
    QSplineSeries *lineseries2 = new QSplineSeries();
    QValueAxis *axisX2 = new QValueAxis();
    QValueAxis *axisY2 = new QValueAxis();

    int total=0;
    uint timen;
    int hash=0;
    for (int i=0;i<count_2;i++) block[i]=0;

    for (int i=0;i<line_all;i++) {
        QDateTime now_time=time_all[i];
        total+=1;
        if (now_time>start_time&&now_time<end_time_2) {
            timen=now_time.toTime_t();
            lineseries->append(timen, total);
            hash=(timen-start_time.toTime_t())/time_step;
            block[hash]++;
        }
    }

    for (int i=0;i<count_2;i++) lineseries2->append(i, block[i]);

    Chart->setTitle("the trend of traffic inflow depends on the total number of people");
    Chart->addSeries(lineseries);
    Chart->createDefaultAxes();
    Chart->legend()->hide();

    QChartView *view = new QChartView(Chart);
    view->setRenderHint(QPainter::Antialiasing);

    axisX->setRange(start_time,end_time_2);
    axisX->setFormat("yyyy-MM-dd hh:mm:ss");
    axisX->setTickCount(7);

    axisY->setRange(0,total);
    axisY->setLabelFormat("%u");

    Chart->setAxisX(axisX);
    Chart->setAxisY(axisY);
    lineseries->attachAxis(axisY);

    Chart2->setTitle("the trend of traffic inflow depends on the number of people over a period of time");
    Chart2->addSeries(lineseries2);
    Chart2->createDefaultAxes();
    Chart2->legend()->hide();

    QChartView *view2 = new QChartView(Chart2);
    view2->setRenderHint(QPainter::Antialiasing);

    axisX2->setRange(0,count_2-1);
    axisX2->setLabelFormat("%u");
    axisX2->setTickCount(count_2-1);

    axisY2->setLabelFormat("%u");

    Chart2->setAxisX(axisX2);
    Chart2->setAxisY(axisY2);
    lineseries2->attachAxis(axisY2);

    Chart->setTheme(QChart::ChartThemeBlueCerulean);
    Chart2->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget->setChart(Chart);
    ui->widget_3->setChart(Chart2);
}

void MainWindow::plot_out_trend_all()
{
    int line_all=0;

    fileName2 = QFileDialog::getOpenFileName(this, tr("Choose a station_out(0) file"), "", "*.csv");
    QFile file(fileName2);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
                time_all[line_all]= QDateTime::fromString(pieces.value(0),"yyyy-MM-dd hh:mm:ss");
                line_all++;
        }
    }
    file.close();

    quick_sort_2(time_all,0,line_all-1);

    QChart* Chart = new QChart();
    QSplineSeries *lineseries = new QSplineSeries();
    QDateTimeAxis *axisX = new QDateTimeAxis();
    QValueAxis *axisY = new QValueAxis();

    QChart* Chart2 = new QChart();
    QSplineSeries *lineseries2 = new QSplineSeries();
    QValueAxis *axisX2 = new QValueAxis();
    QValueAxis *axisY2 = new QValueAxis();

    int total=0;
    uint timen;
    int hash=0;
    for (int i=0;i<count_2;i++) block[i]=0;

    for (int i=0;i<line_all;i++) {
        QDateTime now_time=time_all[i];
        total+=1;
        if (now_time>start_time&&now_time<end_time_2) {
            timen=now_time.toTime_t();
            lineseries->append(timen, total);
            hash=(timen-start_time.toTime_t())/time_step;
            block[hash]++;
        }
    }

    for (int i=0;i<count_2;i++) lineseries2->append(i, block[i]);

    Chart->setTitle("the trend of traffic outflow depends on the total number of people");
    Chart->addSeries(lineseries);
    Chart->createDefaultAxes();
    Chart->legend()->hide();

    QChartView *view = new QChartView(Chart);
    view->setRenderHint(QPainter::Antialiasing);

    axisX->setRange(start_time,end_time_2);
    axisX->setFormat("yyyy-MM-dd hh:mm:ss");
    axisX->setTickCount(7);

    axisY->setRange(0,total);
    axisY->setLabelFormat("%u");

    Chart->setAxisX(axisX);
    Chart->setAxisY(axisY);
    lineseries->attachAxis(axisY);

    Chart2->setTitle("the trend of traffic outflow depends on the number of people over a period of time");
    Chart2->addSeries(lineseries2);
    Chart2->createDefaultAxes();
    Chart2->legend()->hide();

    QChartView *view2 = new QChartView(Chart2);
    view2->setRenderHint(QPainter::Antialiasing);

    axisX2->setRange(0,count_2-1);
    axisX2->setLabelFormat("%u");
    axisX2->setTickCount(count_2-1);

    axisY2->setLabelFormat("%u");

    Chart2->setAxisX(axisX2);
    Chart2->setAxisY(axisY2);
    lineseries2->attachAxis(axisY2);
    Chart->setTheme(QChart::ChartThemeBlueCerulean);
    Chart2->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget_2->setChart(Chart);
    ui->widget_4->setChart(Chart2);
}

void MainWindow::quick_sort_2(QDateTime s[], int l, int r){
    if (l < r)    {
        int i = l, j = r;
        QDateTime x = s[l];
        while (i < j)        {
            while(i < j && s[j] >= x)
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i] < x)
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort_2(s, l, i - 1);
        quick_sort_2(s, i + 1, r);
    }
}

void MainWindow::on_actionBased_on_the_dataset_you_choose_2_triggered()
{
    ui->Widget_all->setRowCount(3);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"lineID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for (int i=0;i<3;i++) {
        QString tmp = QString::number(lines[i]);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        if (i==0) {
                QString temp ="A";
                ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));

    }
        if (i==1) {
                QString temp ="B";
                ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));

    }
        if (i==2) {
                QString temp ="C";
                ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));

    }
    }

    QPieSeries *series = new QPieSeries();
    series->append("A", lines[0]);
    series->append("B", lines[1]);
    series->append("C", lines[2]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget_5->setRenderHint(QPainter::Antialiasing);
    ui->widget_5->setChart(chart);

}


void MainWindow::on_actionBased_on_all_of_the_data_2_triggered()
{
    QString filename_all = QFileDialog::getOpenFileName(this, tr("Choose a line_all file"), "", "*.csv");
    //QString filename_all="C:/Users/ASUS/Desktop/preprocessed data/line_all.csv";
    int lines_all[3];

    QFile file(filename_all);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            if (pieces.value(0)=="A") lines_all[0]=pieces.value(1).toInt();
            if (pieces.value(0)=="B") lines_all[1]=pieces.value(1).toInt();
            if (pieces.value(0)=="C") lines_all[2]=pieces.value(1).toInt();
        }
    }
    file.close();

    ui->Widget_all->setRowCount(3);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"lineID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for (int i=0;i<3;i++) {
        QString tmp = QString::number(lines_all[i]);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        if (i==0) {
                QString temp ="A";
                ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));

    }
        if (i==1) {
                QString temp ="B";
                ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));

    }
        if (i==2) {
                QString temp ="C";
                ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));

    }
    }

    QPieSeries *series = new QPieSeries();
    series->append("A", lines_all[0]);
    series->append("B", lines_all[1]);
    series->append("C", lines_all[2]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget_5->setRenderHint(QPainter::Antialiasing);
    ui->widget_5->setChart(chart);

}



void MainWindow::on_actionBased_on_the_dataset_you_choose_3_triggered()
{
    QBarSet *set = new QBarSet("station");
    QBarSeries *series = new QBarSeries();
    ui->Widget_all->setRowCount(81);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"stationID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i=0;i<81;i++) {
        QString tmp = QString::number(station[i]);
        QString temp = QString::number(i);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));
        set->append(station[i]);

    }

    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0,80);
    axisX->setLabelFormat("%u");
    axisX->setTickCount(16);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->widget_5->setChart(chart);
}

void MainWindow::on_actionBased_on_all_of_the_data_3_triggered()
{
    QBarSet *set = new QBarSet("station");
    QBarSeries *series = new QBarSeries();

    //QString filename_all="C:/Users/ASUS/Desktop/preprocessed data/station_all.csv";
     QString filename_all = QFileDialog::getOpenFileName(this, tr("Choose a station_all file"), "", "*.csv");
    int station_all[81];
    int line_all=0;

    QFile file(filename_all);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            station_all[line_all]=pieces.value(1).toInt();
            line_all++;
        }
    }
    file.close();

    ui->Widget_all->setRowCount(81);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"stationID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i=0;i<81;i++) {
        QString tmp = QString::number(station_all[i]);
        QString temp = QString::number(i);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));
        set->append(station_all[i]);
    }

    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0,80);
    axisX->setLabelFormat("%u");
    axisX->setTickCount(16);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->widget_5->setChart(chart);
}

void MainWindow::on_actionBased_on_the_dataset_you_choose_4_triggered()
{
    QBarSet *set = new QBarSet("device");
    QBarSeries *series = new QBarSeries();
    ui->Widget_all->setRowCount(3650);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"deviceID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i=0;i<3650;i++) {
        QString tmp = QString::number(device[i]);
        QString temp = QString::number(i);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));
        set->append(device[i]);

    }

    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0,3650);
    axisX->setLabelFormat("%u");
    axisX->setTickCount(30);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->widget_5->setChart(chart);
}

void MainWindow::on_actionBased_on_all_of_the_data_4_triggered()
{
    QBarSet *set = new QBarSet("device");
    QBarSeries *series = new QBarSeries();

    //QString filename_all="C:/Users/ASUS/Desktop/preprocessed data/device_all.csv";
     QString filename_all = QFileDialog::getOpenFileName(this, tr("Choose a device_all file"), "", "*.csv");
    int device_all[3650];
    int line_all=0;

    QFile file(filename_all);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            device_all[line_all]=pieces.value(1).toInt();
            line_all++;
        }
    }
    file.close();

    ui->Widget_all->setRowCount(3650);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"deviceID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for (int i=0;i<3650;i++) {
        QString tmp = QString::number(device_all[i]);
        QString temp = QString::number(i);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));
        set->append(device_all[i]);
    }

    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0,3650);
    axisX->setLabelFormat("%u");
    axisX->setTickCount(30);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->widget_5->setChart(chart);
}



void MainWindow::on_actionBased_on_the_dataset_you_choose_5_triggered()
{
    ui->Widget_all->setRowCount(4);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"paytypeID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for (int i=0;i<4;i++) {
        QString tmp = QString::number(paytype[i]);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        QString temp = QString::number(i);
        ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));
    }

    QPieSeries *series = new QPieSeries();
    series->append("0", paytype[0]);
    series->append("1", paytype[1]);
    series->append("2", paytype[2]);
    series->append("3", paytype[3]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget_5->setRenderHint(QPainter::Antialiasing);
    ui->widget_5->setChart(chart);
}

void MainWindow::on_actionBased_on_all_of_the_data_5_triggered()
{
    QString filename_all = QFileDialog::getOpenFileName(this, tr("Choose a paytype_all file"), "", "*.csv");
    //QString filename_all="C:/Users/ASUS/Desktop/preprocessed data/paytype_all.csv";
    int paytype_all[4];

    QFile file(filename_all);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            paytype_all[pieces.value(0).toInt()]=pieces.value(1).toInt();
        }
    }
    file.close();

    ui->Widget_all->setRowCount(4);
    ui->Widget_all->setColumnCount(2);

    QStringList header;
    header<<"paytypeID"<<"number of people";
    ui->Widget_all->setHorizontalHeaderLabels(header);

    ui->Widget_all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Widget_all->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i=0;i<4;i++) {
        QString tmp = QString::number(paytype_all[i]);
        ui->Widget_all->setItem(i,1,new QTableWidgetItem(tmp));
        QString temp =QString::number(i);
        ui->Widget_all->setItem(i,0,new QTableWidgetItem(temp));
    }

    QPieSeries *series = new QPieSeries();
    series->append("0", paytype_all[0]);
    series->append("1", paytype_all[1]);
    series->append("2", paytype_all[2]);
    series->append("3", paytype_all[3]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    ui->widget_5->setRenderHint(QPainter::Antialiasing);
    ui->widget_5->setChart(chart);
}
