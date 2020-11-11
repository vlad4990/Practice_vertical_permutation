#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "math.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString russianAplphabet = "АБВГДЕЁЖЗИКЛМНОПРСТУФХЦЧЩЪЫЭЮЯ";
    int keyLength = 0;
    int *letterSequence;

private slots:
    void on_pushButtonKey_clicked();

    void on_LineEditKey_textEdited(const QString &arg1);

    void on_lineEditInput_textEdited(const QString &arg1);

    void on_lineEditOutput_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
