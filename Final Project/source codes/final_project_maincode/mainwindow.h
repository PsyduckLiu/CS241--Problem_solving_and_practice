#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

extern bool actiontime;
extern bool actionlineID;
extern bool actionstationID;
extern bool actiondeviceID;
extern bool actionstatus;
extern bool actionuserID;
extern bool actionpayType;
extern int row;
extern int start;
extern int end;
extern int num_of_roads;
extern int min_road;
extern int num[7];
extern int road[100];
extern int flag[100];
extern int customer;
extern int customer_station;
extern int least_road[100];
extern int least_customer[100];
extern int customer_num[81];
extern int map[81][81];
extern int station_show;
extern int time_step;
extern int count;
extern int count_2;
extern int block[1000];
extern int type;
extern int station[81];
extern int paytype[4];
extern int device[3650];
extern int lines[3];
extern QString fileName;
extern QString fileName1;
extern QString fileName2;
extern QString num_path;
extern QDateTime time_data[200000];
extern QString start_time1;
extern QString end_time1;
extern QString end_time2;
extern QDateTime start_time;
extern QDateTime end_time_1;
extern QDateTime end_time_2;
extern QDateTime time_all[700000];

struct Message{
    QString time=nullptr;
    QString lineID=nullptr;
    QString stationID=nullptr;
    QString deviceID=nullptr;
    QString status=nullptr;
    QString userID=nullptr;
    QString payType=nullptr;
};
extern Message message[200000];

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton     *botton_data=nullptr;

private slots:
    void on_actiontime_triggered();

    void on_actionlineID_triggered();

    void on_actionstationID_triggered();

    void on_actiondeviceID_triggered();

    void on_actionstatus_triggered();

    void on_actionuserID_triggered();

    void on_actionpayType_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionplan_a_road_triggered();

    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_YesButton_clicked();

    void on_actionBased_on_the_dataset_you_choose_triggered();

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_time_clicked();

    void on_spinBox_3_valueChanged(const QString &arg1);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_actionBased_on_all_of_the_data_triggered();

    void on_actionBased_on_the_dataset_you_choose_2_triggered();

    void on_actionBased_on_all_of_the_data_2_triggered();

    void on_actionBased_on_the_dataset_you_choose_3_triggered();

    void on_actionBased_on_all_of_the_data_3_triggered();

    void on_actionBased_on_the_dataset_you_choose_4_triggered();

    void on_actionBased_on_all_of_the_data_4_triggered();

    void on_actionBased_on_the_dataset_you_choose_5_triggered();

    void on_actionBased_on_all_of_the_data_5_triggered();

private:
    Ui::MainWindow *ui;
    void loadFile(const QString &path);
    void findallroads();
    void dfs(int x,int y,int t);
    void init_customer_num();
    void quick_sort(Message s[], int l, int r);
    void quick_sort_2(QDateTime s[], int l, int r);
    void plot_in_trend();
    void plot_out_trend();
    void plot_in_trend_all();
    void plot_out_trend_all();
};

#endif // MAINWINDOW_H

