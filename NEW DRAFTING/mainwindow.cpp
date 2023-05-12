#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <sstream>
#include <QScrollArea>
#include"x_res.h"
#include <QLabel>
#include <QList>
#include <QPair>
#include <QDebug>
#include <QTextEdit>
#include <QScrollArea>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QApplication>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRegularExpression>
#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCursor>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QFont>
#include <QApplication>
#include <QLabel>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include"Main_ahmed.h"

string str{};
string str1{};

#include<iostream>
#include<unordered_set>
#include <utility>
#include "RabinKarp.h"
#include "RKphrases.h"
#include "RKsentences.h"
#include "Main_ahmed.h"





using namespace std;

float jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2) {
    unordered_set<string> intersection;
    unordered_set<string> unionSet;

    // Calculate intersection
    for (const auto& ngram : set1) {
        if (set2.count(ngram) > 0) {
            intersection.insert(ngram);
        }
    }

    // Calculate union
    unionSet = set1;
    for (const auto& ngram : set2) {
        unionSet.insert(ngram);
    }

    float jaccard = static_cast<float>(intersection.size()) / unionSet.size();

    return jaccard;
}

//Get N-Grams for Jaccard
vector<string> generateNGrams(const string& str, int n) {
    vector<string> ngrams;
    for (int i = 0; i <= str.length() - n; i++) {
        ngrams.push_back(str.substr(i, n));
    }
    return ngrams;
}

//Calculates the percentage of similarity in the corpus vs the main using Jaccard Similarity
void similarityPercent(string main, string c1, string c2, string c3) {

    vector<string> suspiciousNGrams = generateNGrams(main, 5);
    std::unordered_set<std::string> suspiciousSet(suspiciousNGrams.begin(), suspiciousNGrams.end());

    vector<string> referenceNGrams = generateNGrams(c1, 5);
    std::unordered_set<std::string> referenceSet(referenceNGrams.begin(), referenceNGrams.end());
    //a lot of plagarism trace it
    float similarity = jaccardSimilarity(suspiciousSet, referenceSet);
    if (similarity >= 0.5) {
        cout << "Similarity of: " << similarity * 100 << "% suggests plagarism";
    }
    else if (similarity <= 0.5 && similarity >= 25) {
        cout << "Similarity of: " << similarity * 100 << "% is slightly high";
    }
    else
        cout << "No Plagarism";

}

list<pair<string, string>> printPoly(unordered_map<string, string> foundPolySentences, unordered_map<string, string> foundPoly4Phrases, unordered_map<string, string> foundPoly3Phrases, unordered_map<string, string> foundPoly2Phrases, int document) {
    list<pair<string, string>> foundList;
    string color{};


    if (document == 1) {
        color = "yellow";
    }
    else if (document == 2) {
        color = "blue";
    }
    else
        color = "red";

    if (foundPoly4Phrases.empty()) {
        std::cout << "foundPoly4Phrases is empty!" << std::endl;
    }

    if (foundPoly3Phrases.empty()) {
        std::cout << "foundPoly3Phrases is empty!" << std::endl;
    }

    if (foundPoly2Phrases.empty()) {
        std::cout << "foundPoly2Phrases is empty!" << std::endl;
    }

    if (foundPolySentences.empty()) {
        std::cout << "foundPolySentences is empty!" << std::endl;
    }

    //make first one color and second string
    for (auto it = foundPoly4Phrases.begin(); it != foundPoly4Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly4Phrases[it->first]});
        //cout<<'\t'<<foundPoly4Phrases[it->first];
    }



    for (auto it = foundPoly3Phrases.begin(); it != foundPoly3Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly3Phrases[it->first]});
    }

    for (auto it = foundPoly2Phrases.begin(); it != foundPoly2Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly2Phrases[it->first] });

    }

    for (auto it = foundPolySentences.begin(); it != foundPolySentences.end(); it++) {
        foundList.push_back({ color , foundPolySentences[it->first]});

    }


    return foundList;
}

void printFinger() {


}

int v;

vector<wstring> RabinKarp::stem(string str, int i, vector<wstring> w) {
    if (i >= str.size()) {
        return w;
    }
    string strShort{};
    strShort = calcBound(str, i, 1);
    strShort = oneremoveSpaces(strShort, 1);
    stemming::english_stem<> StemEnglish;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter; // create a converter object

    wstring wide_str = converter.from_bytes(strShort); // convert narrow string to wide string
    StemEnglish(wide_str);

    w.push_back(wide_str);

    return stem(str, i, w);
}

wstring RabinKarp::stem(string str) {
    string strShort{};
    strShort = oneCalcBound(str, 1);
    strShort = oneremoveSpaces(str, 1);
    stemming::english_stem<> StemEnglish;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter; // create a converter object

    wstring wide_str = converter.from_bytes(strShort); // convert narrow string to wide string
    StemEnglish(wide_str);

  //  stem(str, i);

    return wide_str;
}


void runProgram(string filename1,string filename2) {

    //objects
    RabinKarp rk;
    Phrases p;
    Sentences s;

    //maps
    unordered_map<string, string> found = {};
    unordered_map<string, string> foundPoly4Phrases = {};
    unordered_map<string, string> foundPoly3Phrases = {};
    unordered_map<string, string> foundPoly2Phrases = {};
    unordered_map<string, string> foundPolySentences = {};

    list<pair<string, string>> foundList;




    //files
    //test

    brute_force bf("fff.txt", "ff.txt",2);

    ifstream c1F{filename1};
    string c1 = p.readFile(&c1F);

    cout<<"!!!!!!!!!!!!"<<"ahmed";


    ifstream c2F{filename1};
    string c2 = p.readFile(&c2F);

    ifstream c3F{filename2};
    string c3 = p.readFile(&c3F);

    ifstream infile{filename2};
    string main = p.readFile(&infile);

    vector<wstring> w;


    //w = rk.stem(main, 0, w);
//I have sent the main now I need to make w work with everyhitng else


    //found = rabinKarp(main, c1, c2, c3);

    foundPoly4Phrases = p.rabinKarpPolyPhrases(main, c1, c2, c3, 4);
    foundPoly3Phrases = p.rabinKarpPolyPhrases(main, c1, c2, c3, 3);
    foundPoly2Phrases = p.rabinKarpPolyPhrases(main, c1, c2, c3, 2);
    //still need to fix in sentences
    foundPolySentences = s.rabinKarpPolySentences(main, c1, c2, c3);


    //firgure out how to send doucment
    foundList = printPoly(foundPolySentences, foundPoly4Phrases, foundPoly3Phrases, foundPoly2Phrases, 0);

    for (const auto& p : foundList) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }


    //fingerprint
    //figure out how to writw this normally
    /* for (auto it = found.begin(); it != found.end(); it++) {
         cout << it->first << '\t' << it->second << endl;

     }*/




      similarityPercent(main, c1, c2, c3);

      //Now I have:
      //Jaccard sim working but i need to understand it
      //RK is working with the things need to find a nice way to priont
      // loop i think is solved
      //multiple docs either need to be the same size or I would need to use seperate fucntion or smth else idk yet


}



class MyHighlighter : public QSyntaxHighlighter {
public:
    MyHighlighter(QTextDocument* parent = nullptr) : QSyntaxHighlighter(parent) {
        QTextCharFormat format;
        format.setForeground(QColor(255, 0, 0)); // set text color to red
        QRegularExpression pattern("\\bQt\\b"); // match "Qt" as a whole word
        highlightingRules.append(QPair<QRegularExpression, QTextCharFormat>(pattern, format));
    }

protected:
    void highlightBlock(const QString& text) {
        for (const auto& rule : highlightingRules) {
            QRegularExpressionMatchIterator matchIterator = rule.first.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.second);
            }
        }
    }

private:
    QVector<QPair<QRegularExpression, QTextCharFormat>> highlightingRules;
};

//extern int v;

//extern int myVariable;
x_res *bu;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        QPixmap bkgnd("C:/Users/Hp/Documents/plagiarism checker interface/graph.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    //ui->setupUi(this);
}
double highlightedWordPercentage(QTextEdit* textEdit, QColor color) {
    QTextCharFormat initialFormat = textEdit->textCursor().charFormat();
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(color);

    QTextDocument* doc = textEdit->document();
    QTextOption option = doc->defaultTextOption();
    option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    doc->setDefaultTextOption(option);

    QTextCursor highlightCursor(doc);
    highlightCursor.movePosition(QTextCursor::Start);

    int highlightCount = 0;
    int totalCount = 0;
    while (!highlightCursor.atEnd()) {
        highlightCursor = doc->find(highlightCursor.selectedText(), highlightCursor, QTextDocument::FindWholeWords);

        if (!highlightCursor.isNull()) {
            ++totalCount;

            QTextCharFormat format = highlightCursor.charFormat();
            if (format.background() == color) {
                ++highlightCount;
            }
        } else {
            break;
        }
    }

    double percentage = 0.0;
    if (totalCount > 0) {
        percentage = (double)highlightCount / (double)totalCount * 100.0;
    }
    return percentage;
}
MainWindow::~MainWindow()
{
    delete ui;
}
QString file;

void MainWindow::on_pushButton_clicked()
{
        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename1 = file.toStdString();
        str = this->filename1;
}


void MainWindow::on_pushButton_2_clicked()
{

        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename2 = file.toStdString();
        str1 =  this->filename2;


}

#include <sstream>

#include <sstream>

void output()
{
    std::cout << "cherif" << std::endl;
}
void displayFirsts(const QList<QPair<QString, QString>>& list) {
    for (const auto& pair : list) {
        cout<<pair.first.toStdString();
        cout << "\n";
    }
}
void highlight(const QList<QPair<QString, QString>>& highlightList, QTextEdit *textEdit)
{
    QString labelText = textEdit->toPlainText();


    for (const auto& highlightPair : highlightList)
    {
        const QString& highlightString = highlightPair.first;
        const QString& highlightColor = highlightPair.second;


        QRegularExpression re(highlightString, QRegularExpression::CaseInsensitiveOption);


        QTextCursor cursor(textEdit->document());
        while (!cursor.isNull() && !cursor.atEnd())
        {
            cursor = textEdit->document()->find(re, cursor);
            if (!cursor.isNull()) {
                QTextCharFormat format;
                format.setBackground(QBrush(QColor(highlightColor)));
                cursor.mergeCharFormat(format);
            }
        }
    }
}
void MainWindow::on_pushButton_3_clicked()
{


    brute_force a(filename1,filename2,2);
    if(ui->lineEdit->text().toInt()>0 && ui->lineEdit->text().toInt()<4)
    {
    a=brute_force(filename1,filename2,ui->lineEdit->text().toInt());
    }

    ui->label->setWordWrap(true);

    ui->label->setText("checking every sentence in file 1\n");
  cout<<"sentence check: "<<endl;
    for (int j = 1; j <= a.number_of_phrases_filex(); j++)          // every phrase in filex vector
    {
        vector<logs> plagiarized;
        cout<<"sentence : "<<j <<" of file x check "<<endl;
        for (int i = 1; i <= a.number_of_phrases_filey(); i++)
        {
           cout<<"checking with sentence: "<<i<<" of file y"<<endl;
            vector<char> temp = a.getsentence_filey(i);
            a.trial(temp, a.getsentence_filex(j),i,j,plagiarized);
        }
    }

    ui->label_5->setWordWrap(true);
if(a.filex_authentication())
{
    for(int h=0;h<a.getfilex_vector().size();h++)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText()+ a.getfilex_vector()[h]);
    }
}
else
{
    ui->textEdit->setText("error while opening the file");
}
if(a.filey_authentication())
{
    for(int h=0;h<a.getfiley_vector().size();h++)
    {
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText()+ a.getfiley_vector()[h]);
    }
}
else
{
    ui->textEdit_2->setText("error while opening the file");
}

highlight(a.getnewx(),ui->textEdit);
highlight(a.getnewy(),ui->textEdit_2);
cout<<"X PLAGIARIZED SENDTENCE FINAL"<<endl;
displayFirsts(a.getnewx());
cout<<endl;
cout<<"y PLAGIARIZED SENDTENCE FINAL"<<endl;
displayFirsts(a.getnewy());

ui->label_2->setText(QString::number(highlightedWordPercentage(ui->textEdit,QColor(Qt::yellow)))+ "%");

runProgram(filename1,filename2);

}
















