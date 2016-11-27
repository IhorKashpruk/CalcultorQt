#include "converter.h"

Converter::Converter(const QString &text) : QObject()
{
    num = text.toInt();
    str = text.toStdString();
}

//---------Dec(EX)---for BIN, OCT, HEX-----------------------
QString Converter::fromDecToBin(int expression)
{
   std::string str = std::bitset<32>(expression).to_string();
   for(unsigned int i = 0; i < str.size(); i++){
       if(str[i] == '0'){
           str.erase(0,1); i--;
       }else break;
   }
   return ("0"+str).c_str();
}
int Converter::fromDecToOct(int expression)
{
    ss << std::oct << expression;
    std::string rez(ss.str());
     int answ = atoi(rez.c_str());
      return answ;
}
QString Converter::fromDecToHex(int expression)
{
    ss << std::hex << expression;
    return ss.str().c_str();
}
//-------------DEC----------------------
QString Converter::fromDecToBin()
{
    return fromDecToBin(num);
}
int Converter::fromDecToOct()
{
    return fromDecToOct(num);
}
QString Converter::fromDecToHex()
{
    return fromDecToHex(num);
}
//--------------BIN--------------------------
int Converter::fromBinToDec()
{
    binVer();
    int inDec = std::bitset<32>(str).to_ulong();
    return inDec;
}
int Converter::fromBinToOct()
{
    return fromDecToOct(fromBinToDec());
}
QString Converter::fromBinToHex()
{
    return fromDecToHex(fromBinToDec());
}
//----------------OCT------------------------------

int Converter::fromOctToDec()
{
    octVer();
    std::stringstream ssOct;
    ssOct << num; int inDec;
    ssOct >> std::oct >> inDec;
    return inDec;
}
QString Converter::fromOctToBin()
{
    return fromDecToBin(fromOctToDec());
}
QString Converter::fromOctToHex()
{
    return fromDecToHex(fromOctToDec());
}
//----------------HEX--------------------------------
int Converter::fromHexToDec()
{
    hexVer();
    std::stringstream ssHex;
    ssHex << str; int inDec;
    ssHex >> std::hex >> inDec;
    return inDec;
}
QString Converter::fromHexToBin()
{
    return fromDecToBin(fromHexToDec());
}
int Converter::fromHexToOct()
{
    return fromDecToOct(fromHexToDec());
}
//----------------VERIFICATION-----------------------
bool Converter::binVer()
{
    for (unsigned int i = 0; i < str.length(); i++)
        if (str.at(i) > '1')
            return false;
    return true;
}
bool Converter::octVer()
{
    for (unsigned int i = 0; i < str.length(); i++)
        if (str.at(i) > '7')
            return false;
    return true;
}
bool Converter::hexVer()
{
    for (unsigned int i = 0; i < str.length(); i++)
        if (str.at(i) > 'f')
            return false;
    return true;
}
bool Converter::numberVer()
{
    for (unsigned int i = 0; i < str.length(); i++)
        if ((str.at(i) < 'a' || str.at(i) > 'f') && (str.at(i) < '0' || str.at(i) > '9'))
            return false;
    return true;
}
int Converter::numberOfError()
{
//1 - str is empty, 2 - negative number, 3 - out of system(bin = 56), 4 - incorrect number
    if (str.empty())
        return 1;
    else if (!str.empty())
    {
       if (str.at(0) == '-' || num < 0)//?
           return 2;
       if (!binVer() || !octVer() || !hexVer())
           return 3;
       if (!numberVer())
           return 4;
    }
    return 0;
}

void Converter::setQStr(const QString &value)
{
    ss.str(std::string());
    num = value.toInt();
    str = value.toStdString();
}
