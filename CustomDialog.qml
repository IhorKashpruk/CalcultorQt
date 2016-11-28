import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

import converter.converter 1.0
import "qrc:/js/Functions.js" as Functions

Window {
    visible: true
    title: "Converter"
    width: 310
    height: 350
    minimumHeight: 350
    minimumWidth: 310
    maximumHeight: 350
    maximumWidth: 310
    flags: Qt.WindowTitleHint
    color: "#fcfdff"

    Converter{
        id: converter
    }

    Rectangle {
        implicitWidth: 210
        implicitHeight: 350
        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 20
            CustomText{
                id: label
                text: "Enter numeber to convert:"
            }
            CustomTextField{
                id: input
                anchors.top: label.bottom
                horizontalAlignment: Text.AlignLeft
                width: 270
                backgroundObj.border.color: "#9E9E9E"
                font.pointSize: 10
            }
            RowLayout{
                anchors.topMargin: 10
                anchors.top: input.bottom
                GroupBox{
                    title: "From"
                    Column {
                           spacing: 2
                           CustomRadioButton {
                               id: decimalButtonFrom
                               text: "Decimal"
                               checked: true
                           }
                           CustomRadioButton {
                               id: binaryButtonFrom
                               text: "Binary"
                               checked: false
                           }
                           CustomRadioButton {
                               id: octalButtonFrom
                               text: "Octal"
                               checked: false
                           }

                           CustomRadioButton {
                               id: hexButtomFrom
                               text: "Hexadecimal"
                               checked: false
                           }
                       }
                }
                GroupBox{
                    width: 310
                    title: "To"
                    Column {
                           spacing: 2
                           CustomRadioButton {
                               id: decimalButtonTo
                               text: "Decimal"
                               checked: true
                           }
                           CustomRadioButton {
                               id: binaryButtonTo
                               text: "Binary"
                               checked: false
                           }
                           CustomRadioButton {
                               id: octalButtonTo
                               text: "Octal"
                               checked: false
                           }

                           CustomRadioButton {
                               id: hexButtomTo
                               text: "Hexadecimal"
                               checked: false
                           }
                       }
                }
            }
            CustomText{
                id: resultLabel
                text: "Result:"
            }
            CustomTextField{
                id: resultField
                anchors.top: resultLabel.bottom
                horizontalAlignment: Text.AlignLeft
                width: 270
                backgroundObj.border.color: "#9E9E9E"
                placeholderText: ""
                readOnly: true
            }

            CustomButton{
                text: "Convert"
                backgroundObj.implicitWidth: resultField.width
                width: resultField.width
                textColor: "#17a81a"
                onClicked: {
                    var str = input.text;
                    resultField.font.pointSize = 10
                    if(str.length != 0){
                        converter.setQStr(str);
                        if(decimalButtonFrom.checked && converter.numberVer()){
                            if(binaryButtonTo.checked)
                                resultField.text = converter.fromDecToBin();
                            else if(octalButtonTo.checked)
                                resultField.text = converter.fromDecToOct();
                            else if(hexButtomTo.checked)
                                resultField.text = converter.fromDecToHex();
                            else resultField.text = str;
                            return;
                        }
                        if(binaryButtonFrom.checked && converter.binVer()){
                            if(decimalButtonTo.checked)
                                resultField.text = converter.fromBinToDec();
                            else if(octalButtonTo.checked)
                                resultField.text = converter.fromBinToOct();
                            else if(hexButtomTo.checked)
                                resultField.text = converter.fromBinToHex();
                            else resultField.text = str;
                            return;
                        }
                        if(octalButtonFrom.checked && converter.octVer()){
                            if(decimalButtonTo.checked)
                                resultField.text = converter.fromOctToDec();
                            else if(binaryButtonTo.checked)
                                resultField.text = converter.fromOctToBin();
                            else if(hexButtomTo.checked)
                                resultField.text = converter.fromOctToHex();
                            else resultField.text = str;
                            return;
                        }
                        if(hexButtomFrom.checked && converter.hexVer()){
                            if(decimalButtonTo.checked)
                                resultField.text = converter.fromHexToDec();
                            else if(octalButtonTo.checked)
                                resultField.text = converter.fromHexToOct();
                            else if(binaryButtonTo.checked)
                                resultField.text = converter.fromHexToBin();
                            else resultField.text = str;
                            return;
                        }
                        resultField.font.pointSize = 8
                        resultField.text = "Please enter the correct data in the field";
                    }
                }
            }

        }
    }
}
