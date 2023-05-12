#ifndef NAMES_H
#define NAMES_H
using namespace std;
#include<string>
#include <QObject>


class names : public QObject{
public:
    string filename1,filename2;
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

};
#endif // NAMES_H
