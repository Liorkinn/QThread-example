#include "tablethread.h"
#include "mainwindow.h"

tableThread::tableThread(MainWindow *mainWindow, QObject *parent)
    : QObject(parent),
      m_mainWindow(mainWindow)
{

}
