#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->createUI(QStringList() << ( "Пример" ));

    tableThrd = new tableThread(this);
    thread = new QThread();

    tableThrd->moveToThread(thread); //это означает, что все сигналы и слоты класса tableThread будут выполняться в потоке

    QObject::connect(this, &MainWindow::workRequested, tableThrd, &tableThread::doWork); //Передаются данные из MainWindow::workRequested в tableThread::doWork
    QObject::connect(tableThrd, &tableThread::workDone, this, &MainWindow::onAddItemTable); //tableThread::workDone с данными вызывает MainWindow::onAddItemTable, которая заполняет таблицу
    thread->start(); //тут старт, потому что мы подготавливаем поток.
}

MainWindow::~MainWindow()
{
    delete ui;
    thread->quit(); //останавливает поток
    thread->wait(); //блокировка потока для гарантии, что он завершит свою работу
}

void MainWindow::createUI(const QStringList &headers)
{
    ui->DBTable->setColumnCount(1);
    ui->DBTable->setRowCount(0);
    ui->DBTable->setShowGrid(true);
    ui->DBTable->setHorizontalHeaderLabels(headers);
    ui->DBTable->horizontalHeader()->setStretchLastSection(true);
    ui->DBTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->DBTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DBTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->DBTable->verticalHeader()->setVisible(false);
    ui->DBTable->setRowCount(1);
}

void MainWindow::onAddItemTable(int row, int column, QString value)
{
    QTableWidgetItem *item = new QTableWidgetItem(value);
    ui->DBTable->setItem(row, column, item);
}


void MainWindow::on_pushButton_clicked()
{
    QStringList listData = getList();
    for (int i = 0; i < listData.length(); i++) {
        qDebug() << listData[i];
        ui->DBTable->insertRow(i);
        emit workRequested(i, 0, listData[i]);
    }
}
