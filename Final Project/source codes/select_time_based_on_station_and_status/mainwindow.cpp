#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <QtWidgets>
#include <QMainWindow>
#include<string.h>
#include<stdio.h>

QString tim[1300000];
int num=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    finddata();
}

MainWindow::~MainWindow()
{
    delete ui;
 }

void MainWindow::finddata()
{

    int station=0;
    int status=0;
    QDir mydir;
    QString mystring=QFileDialog::getExistingDirectory(this,"one","/home");
    mydir.setPath(mystring);
    mydir.setFilter(QDir::Files|QDir::NoSymLinks);

    QFileInfoList list=mydir. entryInfoList();
    QString str;
    for (station=0;station<1;station++) {
        for (status=0;status<1;status++) {
    num=0;
    for(int i=0;i<list.length();i++)    {
        QFileInfo fileinfo=list.at(i);
        str="C:/Users/ASUS/Desktop/dataset/"+fileinfo.baseName()+".csv";
        ui->textEdit2->textCursor().insertText(str+"\n");
        loadFile(str,station,status);
    }
    save(station,status);
        }
    }
}

void MainWindow::loadFile(const QString &path,int a,int b)
{

    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);

    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            if (pieces.value(2).toInt()==a&&pieces.value(4).toInt()==b) {
                tim[num]= pieces.value(0);
                num++;
            }

        }
    }
    file.close();
}
void MainWindow::save(int a,int b)
{
    QDir dir;
    QString name1="C:/Users/ASUS/Desktop/data_chosen";
    QString name2=QString::number(a);
    QString name3=QString::number(b);
    QString fileName;
    fileName= name1+"/"+name2+"_"+name3+".csv";

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
      return;

    QTextStream stream(&file);
    for (int i = 0; i < num; ++i) {
        stream << tim[i] << "\n";
    }

    file.close();
}
void MainWindow::on_actionSave_the_file_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save file as"), "", "*.csv");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;

    QTextStream stream(&file);
    for (int i = 0; i < num; ++i) {

        QStringList pieces;
        pieces.append(tim[i]);

        stream << pieces.join(',') << "\n";
    }

    file.close();
}

