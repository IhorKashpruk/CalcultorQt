#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include <sstream>
#include <bitset>
#include <QMessageBox>
#include <QDebug>

class Converter : public QObject
{
    Q_OBJECT
public:
    Converter(const QString& text = "");
public slots:
//Dec
    QString fromDecToBin();
    int fromDecToOct();
    QString fromDecToHex();
//Dec(EX)
    QString fromDecToBin(int);
    int fromDecToOct(int);
    QString fromDecToHex(int);
//Bin
    int fromBinToDec();
    int fromBinToOct();
    QString fromBinToHex();
//Oct
    int fromOctToDec();
    QString fromOctToBin();
    QString fromOctToHex();
//Hex
    int fromHexToDec();
    QString fromHexToBin();
    int fromHexToOct();
//Verification
    bool binVer();
    bool octVer();
    bool hexVer();
    bool numberVer();
    int numberOfError();

    void setQStr(const QString& value);

private:
    QString qstr;
    int num;
    std::string str;
    std::stringstream ss;
};

#endif // CONVERTER_H
