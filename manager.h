#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDebug>
#include "calculator.h"

class Manager : public QObject
{
    Q_OBJECT

public slots:
    QString calculate(const QString& str);
public:
    explicit Manager();
private:
    Calculator calc;
};

#endif // MANAGER_H
