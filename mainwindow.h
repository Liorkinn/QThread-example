#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    QStringList getList() {
        QStringList listData = {"One", "Two", "Three", "Two", "Three", "Two", "Three"};
        return listData;
    }
    void createUI(const QStringList &headers);

signals:
    void workRequested(int row, int column, QString value);

private slots:
    void onAddItemTable(int row, int column, QString value);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    tableThread* tableThrd;
    QThread *thread;

};
#endif // MAINWINDOW_H
