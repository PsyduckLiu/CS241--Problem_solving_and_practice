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

int station[81]={0};
int paytype[4]={0};
int device[3650]={0};
int lines[3]={0};

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

    QDir mydir;
    QString mystring=QFileDialog::getExistingDirectory(this,"one","/home");
    mydir.setPath(mystring);
    mydir.setFilter(QDir::Files|QDir::NoSymLinks);

    QFileInfoList list=mydir. entryInfoList();
    QString str;
    for(int i=0;i<list.length();i++)    {
        QFileInfo fileinfo=list.at(i);
        str="C:/Users/ASUS/Desktop/dataset/"+fileinfo.baseName()+".csv";
        ui->textEdit->textCursor().insertText(str+"\n");
        loadFile(str);
    }
}

void MainWindow::loadFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream stream(&file);

    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            //paytype[pieces.value(6).toInt()]++;
            //station[pieces.value(2).toInt()]++;
            //device[pieces.value(3).toInt()]++;

            if (pieces.value(1)=="A") lines[0]++;
            if (pieces.value(1)=="B") lines[1]++;
            if (pieces.value(1)=="C") lines[2]++;
        }
    }
    file.close();
/*
    ui->tableWidget->setRowCount(81);
    ui->tableWidget->setColumnCount(1);
    for (int i=0;i<81;i++) {
        QString tmp = QString::number(station[i]);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tmp));
    }
*/

/*
    ui->tableWidget->setRowCount(4);
    ui->tableWidget->setColumnCount(1);
    for (int i=0;i<4;i++) {
        QString tmp = QString::number(paytype[i]);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tmp));
    }
*/

/*
    ui->tableWidget->setRowCount(3650);
    ui->tableWidget->setColumnCount(1);
    for (int i=0;i<3650;i++) {
        QString tmp = QString::number(device[i]);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tmp));
    }
*/

    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(1);
    for (int i=0;i<3;i++) {
        QString tmp = QString::number(lines[i]);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tmp));
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
/*
    for (int i = 0; i < 81; ++i) {

        QStringList pieces;
        QString tmp = QString::number(i);
        QString temp = QString::number(station[i]);
        pieces.append(tmp);
        pieces.append(temp);

        stream << pieces.join(',') << "\n";
    }
*/

/*
    for (int i = 0; i < 4; ++i) {

        QStringList pieces;
        QString tmp = QString::number(i);
        QString temp = QString::number(paytype[i]);
        pieces.append(tmp);
        pieces.append(temp);

        stream << pieces.join(',') << "\n";
    }
*/

/*
    for (int i = 0; i < 3650; ++i) {

        QStringList pieces;
        QString tmp = QString::number(i);
        QString temp = QString::number(device[i]);
        pieces.append(tmp);
        pieces.append(temp);

        stream << pieces.join(',') << "\n";
    }
*/

    for (int i = 0; i < 3; ++i) {

        QStringList pieces;
        QString tmp = QString::number(i);
        QString temp = QString::number(lines[i]);
        pieces.append(tmp);
        pieces.append(temp);

        stream << pieces.join(',') << "\n";
    }

    file.close();
}
