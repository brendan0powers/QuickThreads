#ifndef QUICKTHREAD_H
#define QUICKTHREAD_H

#include <QObject>
#include <QThread>
#include <functional>

typedef std::function<void ()> ThreadFunc;

class DummyThreadingObject : public QObject
{
    Q_OBJECT
public:
    DummyThreadingObject(const ThreadFunc &f, QThread *t);

public slots:
    void run();

private:
    ThreadFunc _Func;
    QThread *_Thread;
};

class QuickThread : public QObject
{
    Q_OBJECT
public:
    explicit QuickThread(const ThreadFunc &f, QObject *parent = 0);

public slots:
    void run();
    void runAndWait();
    void runInThisThread();

protected:
    ThreadFunc _Func;
    QThread *_Thread;
};

#endif // QUICKTHREAD_H
