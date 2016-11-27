import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

import calculator.history 1.0
import org.calculator 1.0

import "qrc:/js/Functions.js" as Functions

ApplicationWindow {
    id: root
    color: "#fcfdff"
    visible: true
    width: 450
    height: 440
    title: qsTr("Calculator")
    maximumHeight: 440
    maximumWidth: 450
    minimumHeight: 440
    minimumWidth: 450
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2

    History{ id: history }
    Calculator{ id: calculator }

Column{
    anchors.fill: parent
    spacing: 5
    anchors.margins: 5

    CustomSwitch{
        text: "Converter"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        border.color: "lightgray"
        width: grid.width
        height: 150

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 0
            ScrollView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                ListView {
                    id: view
                    model: history
                    anchors.margins: 3

                    delegate: MouseArea{
                        width: view.width
                        height: 20
                        onClicked: {
                            view.currentIndex = index
                            view.focus = true
                        }

                        Row{
                            spacing: 5
                            CustomText{
                                text: " "+model.expression
                                width: view.width - 120
                            }
                            CustomText { text: " = " }

                            CustomText{
                                text: model.result
                                width: 67
                                horizontalAlignment: Text.AlignRight
                            }

                            CustomButton{
                                width: 18; height: 18
                                text: "x"
                                backgroundObj.radius: 10
                                textColor: "tomato"

                                onClicked: {
                                    // make this delegate the current item
                                    view.currentIndex = index
                                    view.focus = true
                                    history.remove(index)
                                }
                            }
                        }
                    }
                    highlight: Rectangle { border.color: "lightgray";}
                    // some fun with transitions :-)
                    add: Transition {
                        // applied when entry is added
                        NumberAnimation {
                            properties: "x"; from: -view.width;
                            duration: 250; easing.type: Easing.InCirc
                        }
                        NumberAnimation { properties: "y"; from: view.height;
                            duration: 250; easing.type: Easing.InCirc
                        }
                    }
                    remove: Transition {
                        // applied when entry is removed
                        NumberAnimation {
                            properties: "x"; to: view.width;
                            duration: 250; easing.type: Easing.InBounce
                        }
                    }
                    displaced: Transition {
                        // applied when entry is moved
                        // (e.g because another element was removed)
                        SequentialAnimation {
                            // wait until remove has finished
                            PauseAnimation { duration: 250 }
                            NumberAnimation { properties: "y"; duration: 75}
                        }
                    }
                }
            }
            CustomTextField{
                id: myTextField
                Layout.fillWidth: true
            }
        }


    }

    CustomText{
        id: errorField
        Layout.fillWidth: true
        height: 20
        horizontalAlignment: Text.AlignRight
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 8
        color: "tomato"
        text: " "
    }

    Grid{
        id: grid
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 6
        rows: 5
        spacing: 3

        OtherButton{
            text: "Pi"
            onClicked: { Functions.addTextWithFocus(myTextField, "3.14159265359"); }
        }

        OtherButton{
            text: "()"
            onClicked: { Functions.addTextAndMoveCursor(myTextField, "( )"); }
        }
        Repeater{
            model: ["(", ")"]
            OtherButton{
                text: modelData;
                onClicked: { Functions.addTextWithFocus(myTextField, text); }
            }
        }
        OtherButton{
            text: "<-"
            onClicked: { myTextField.remove(myTextField.cursorPosition, myTextField.cursorPosition-1);}
        }
        OtherButton{
            text: "CE"
            onClicked: { myTextField.text = "";}
        }
        OtherButton{
            text: "x!"
            onClicked: {
                Functions.addTextAndMoveCursor(myTextField, " !");
            }
        }
        OtherButton{
            text: "ln"
            onClicked: {
                Functions.addTextAndMoveCursor(myTextField, "ln( )");
            }
        }
        Repeater{
            model: ["7", "8", "9"]
            NumberButton{
                text: modelData;
                onClicked: { Functions.addTextWithFocus(myTextField, text);}
            }
        }
        OtherButton{
            text: "/"
            onClicked: { Functions.addTextWithFocus(myTextField, text); }
        }
        OtherButton{
            text: "sin"
            onClicked: {Functions.addTextAndMoveCursor(myTextField, "sin( )");}
        }
        OtherButton{
            text: "log"
            onClicked: {Functions.addTextAndMoveCursor(myTextField, "log( )");}
        }
        Repeater{
            model: ["4", "5", "6"]
            NumberButton{
                text: modelData;
                onClicked: { Functions.addTextWithFocus(myTextField, text);}
            }
        }
        OtherButton{
            text: "*"
            onClicked: { Functions.addTextWithFocus(myTextField, text); }
        }
        OtherButton{
            text: "cos"
            onClicked: { Functions.addTextAndMoveCursor(myTextField, "cos( )");}
        }
        OtherButton{
            text: "sqrt"
            onClicked: {Functions.addTextAndMoveCursor(myTextField, "sqrt( )");}
        }
        Repeater{
            model: ["1", "2", "3"]
            NumberButton{
                text: modelData;
                onClicked: { Functions.addTextWithFocus(myTextField, text); }
            }
        }
        OtherButton{
            text: "-"
            onClicked: { Functions.addTextWithFocus(myTextField, text); }
        }
        OtherButton{
            text: "tan"
            onClicked: {Functions.addTextAndMoveCursor(myTextField, "tan( )");}
        }

        OtherButton{
            text: "x^y"
            onClicked: { Functions.addTextWithFocus(myTextField, "^ ");
                Functions.moveCursorSelection(myTextField, 1);
            }
        }
        NumberButton{
            text: "0"
            onClicked: { Functions.addTextWithFocus(myTextField, text); }
        }
        NumberButton{
            text: "."
            onClicked: { Functions.addTextWithFocus(myTextField, text); }
        }
        NumberButton{
            text: "="; textColor: "white"; font.pointSize: 14;
            onClicked: {
                var  result = calculator.calculate(myTextField.text);
                if(result.charAt(0) !== 'E'){
                    history.append(myTextField.text, result);
                    errorField.text = " "
                    myTextField.text = result
                }else
                    errorField.text = result;

            }
        }
        OtherButton{
            text: "+"
            onClicked: { Functions.addTextWithFocus(myTextField, text); }
        }
    }
}
}
