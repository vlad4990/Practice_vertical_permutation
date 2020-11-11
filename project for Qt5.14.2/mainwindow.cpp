#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp rx("[А-я]{1,99}");
     QValidator *validator = new QRegExpValidator(rx, this);
    ui->LineEditKey->setValidator(validator);

    QRegExp rx2("[А-я ]{1,99}");
     QValidator *validator2 = new QRegExpValidator(rx2, this);
    ui->lineEditInput->setValidator(validator2);

    QRegExp rx3("[А-я ]{1,99}");
     QValidator *validator3 = new QRegExpValidator(rx3, this);
    ui->lineEditOutput->setValidator(validator3);

    QRegExp rx4("[А-я ]{1,99}");
     QValidator *validator4 = new QRegExpValidator(rx4, this);
    ui->lineEditCodeOutput->setValidator(validator4);

    QRegExp rx5("[А-я ]{1,99}");
     QValidator *validator5 = new QRegExpValidator(rx5, this);
    ui->lineEditDecodeOutput->setValidator(validator5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonKey_clicked()
{
QString key = "АБВгд";
int n = key[0].toUpper().unicode()-1039/*-QChar('A').unicode()*/;
ui->LineEditKey->setText(QString::number(n));
ui->tableWidgetInput->setRowCount(4); //задание строчек
ui->tableWidgetInput->setColumnCount(5); //задание столбцов
}

void MainWindow::on_LineEditKey_textEdited(const QString &arg1)
{
    ui->lineEditInput->setEnabled(1);
    ui->lineEditOutput->setEnabled(1);
    keyLength =arg1.length();
    QString LabelWord = "";
    QString LabelNumeric = "";
    int keyWordNumeric[keyLength];
    letterSequence = new int[keyLength];
    QString WordInLineEdit = ui->LineEditKey->text();

//--------------------------------------------Создание массива с номерами букв в ключе
    for (int count = 0; count < keyLength; count++)
        {
            keyWordNumeric[count]=WordInLineEdit[count].toUpper().unicode()-1039;
        }

//--------------------------------------------Задание порядковых номеров буквам в ключе
    for (int curentSymbol = 0; curentSymbol < keyLength; curentSymbol++)
        {
            int serialNumber = 1;
            for(int comparisonSymbol = 0; comparisonSymbol < keyLength; comparisonSymbol++)
            {
                if(curentSymbol == comparisonSymbol && comparisonSymbol != keyLength - 1) continue;
                if(keyWordNumeric[curentSymbol] > keyWordNumeric[comparisonSymbol])
                    serialNumber++;
                if(keyWordNumeric[curentSymbol] == keyWordNumeric[comparisonSymbol])
                    if(curentSymbol > comparisonSymbol) serialNumber++;
                if (comparisonSymbol == keyLength - 1)
                    letterSequence[curentSymbol] = serialNumber;
            }
            LabelWord = LabelWord + QString::number(letterSequence[curentSymbol]);
            ui->Label->setText(LabelWord);
        }
}


void MainWindow::on_lineEditInput_textEdited(const QString &arg1)
{
//--------------------------------------------Внесение Предложения для шифрования в таблицу
    ui->lineEditCodeOutput->setEnabled(1);
    QString WordInLineEdit = ui->lineEditInput->text();
    double textLength = arg1.length();
    int symbolCount = 0;
    int numberOfRows = (int)ceil(textLength/keyLength);
    ui->tableWidgetInput->setRowCount(numberOfRows);
    ui->tableWidgetInput->setColumnCount(keyLength);
    ui->tableWidgetInput->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableWidgetInput->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
    for (int rowCount = 0; rowCount < numberOfRows; rowCount++)
    {
        for (int columnCount = 0; columnCount < keyLength; columnCount++)
        {
            QTableWidgetItem *currentItem = new QTableWidgetItem();
            QChar CharInCell = WordInLineEdit[symbolCount];
            currentItem->setText(CharInCell);
            ui->tableWidgetInput->setItem(rowCount,columnCount,currentItem);

            symbolCount++;

        }
    }

    symbolCount = 0;

//--------------------------------------------Шифрование предложения
    QString textOutput = "";
    for (int columnCount = 0; columnCount < keyLength; columnCount++)
    {
        for (int rowCount = 0; rowCount < numberOfRows; rowCount++)
        {
            textOutput[symbolCount] = ui->tableWidgetInput->item(rowCount, letterSequence[columnCount]-1)->text()[0];
            symbolCount++;
        }
    }
    ui->lineEditCodeOutput->setText(textOutput);
}

void MainWindow::on_lineEditOutput_textEdited(const QString &arg1)
{
//--------------------------------------------Дешифрование и внесение предложения в таблицу
    ui->lineEditDecodeOutput->setEnabled(1);
    QString WordInLineEdit = ui->lineEditOutput->text();
    double textLength = arg1.length();
    int numberOfRows = (int)ceil(textLength/keyLength);
    ui->tableWidgetOutput->setRowCount(numberOfRows);
    ui->tableWidgetOutput->setColumnCount(keyLength);
    ui->tableWidgetOutput->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableWidgetOutput->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
    int symbolCount = 0;
    for (int columnCount = 0; columnCount < keyLength; columnCount++)
    {
        for (int rowCount = 0; rowCount < numberOfRows; rowCount++)
        {
            QTableWidgetItem *currentItem = new QTableWidgetItem();
            QChar CharInCell = WordInLineEdit[symbolCount];
            currentItem->setText(CharInCell);
            ui->tableWidgetOutput->setItem(rowCount,letterSequence[columnCount]-1,currentItem);

            symbolCount++;

        }
    }
    symbolCount = 0;
//--------------------------------------------Вывод дешифрованного предложения
    QString textOutput = "";
    for (int rowCount = 0; rowCount < numberOfRows; rowCount++)
    {
        for (int columnCount = 0; columnCount < keyLength; columnCount++)
        {
            textOutput[symbolCount] = ui->tableWidgetOutput->item(rowCount,columnCount)->text()[0];
            symbolCount++;
        }
    }
    ui->lineEditDecodeOutput->setText(textOutput);
}
