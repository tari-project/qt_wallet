#ifndef MYCLASS_H
#define MYCLASS_H
#include <QObject>
#include <QtDebug>
#include "ffi/ffi.h"

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
private:

signals:

public slots:

};

#endif // MYCLASS_H
