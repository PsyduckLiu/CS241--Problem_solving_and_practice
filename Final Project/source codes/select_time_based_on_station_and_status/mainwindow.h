#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



extern QString tim[1300000];
extern int num;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSave_the_file_triggered();

private:
    Ui::MainWindow *ui;
    void finddata();
    void loadFile(const QString &path,int a,int b);
    void save(int a,int b);
};
#endif // MAINWINDOW_H
