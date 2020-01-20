#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern int row;
extern int station[81];
extern int paytype[4];
extern int device[3650];
extern int lines[3];

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void loadFile(const QString &path);
};
#endif // MAINWINDOW_H
