#include "QuickThread.h"
#include <QDebug>

DummyThreadingObject::DummyThreadingObject(const ThreadFunc &f, QThread *t)
    : _Func(f)
    , _Thread(t)
{

}

void DummyThreadingObject::run()
{
    _Func();
    _Thread->quit();
}

QuickThread::QuickThread(const ThreadFunc &f, QObject *parent) :
    QObject(parent)
  , _Func(f)
  , _Thread(new QThread())
{
    connect(_Thread, SIGNAL(finished()), _Thread, SLOT(deleteLater()));
}

void QuickThread::run()
{
    DummyThreadingObject *o = new DummyThreadingObject(_Func, _Thread);

    connect(_Thread, SIGNAL(destroyed()), o, SLOT(deleteLater()));
    connect(_Thread, SIGNAL(started()),
            o, SLOT(run()), Qt::DirectConnection);

    _Thread->start();
    qDebug() << "Starging";
}

void QuickThread::runAndWait()
{
    run();
    _Thread->wait();
}

void QuickThread::runInThisThread()
{
    _Func();
}
