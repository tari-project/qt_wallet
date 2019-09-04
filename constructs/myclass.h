#ifndef MYCLASS_H
#define MYCLASS_H
#include <QObject>
#include <QtDebug>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);

signals:

public slots:
    void saveText(const QString &event) {
        qDebug() << event;
    }
};

#endif // MYCLASS_H
