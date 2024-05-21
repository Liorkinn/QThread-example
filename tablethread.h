#ifndef TABLETHREAD_H
#define TABLETHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class MainWindow; //для примера как можно передать MainWindow

class tableThread : public QObject
{
    Q_OBJECT
public:
    explicit tableThread(MainWindow *mainWindow, QObject *parent = nullptr);
    ~tableThread() {}

public slots:
    void doWork(int row, int column, QString value) //для примера как можно передать MainWindow
    {
        emit workDone(row, column, value);
    }

signals:
    void workDone(int row, int column, QString value);

private:
    MainWindow *m_mainWindow;
};

#endif // TABLETHREAD_H
