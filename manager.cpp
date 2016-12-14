#include "manager.h"

QString Manager::calculate(const QString &str)
{
    std::string result;
    try{
        Number number = calc.calculate(str.toStdString());
        qDebug() << number.getValueStr().c_str() << "\n";
        return QString(number.getValueStr().c_str());
    }catch(const my::exception& ex){
        return "Error: " + QString(ex.what());
    }
}
{
    try{
        Validator validator("1+2-3+d");
        validator.validate();
    }catch(const my::exception& ex){
        // print error
    }
        
}

Manager::Manager() : QObject()
{
}
