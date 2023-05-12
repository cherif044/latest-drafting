#include"mainwindow.h"
#include"names.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <string>
#include <QCoreApplication>
using namespace std;
QString file;

void names::on_pushButton_clicked()
{
        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename1 = file.toStdString();




}

void names::on_pushButton_2_clicked()
{

        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename2 = file.toStdString();



}
