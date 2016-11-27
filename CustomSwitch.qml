import QtQuick 2.6
import QtQuick.Controls 2.0

Switch {
    id: control
    text: qsTr("Switch")
    onCheckedChanged: {
        if(dialog === null){
            var component = Qt.createComponent("CustomDialog.qml")
            dialog  = component.createObject(root)
        }else{
            dialog.close();
            dialog = null;
        }
    }

    property var dialog: null


    indicator: Rectangle {
        implicitWidth: 42
        implicitHeight: 20
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#17a81a" : "#ffffff"
        border.color: control.checked ? "#17a81a" : "#cccccc"

        Rectangle {
            x: control.checked ? parent.width - width : 0
            width: 20
            height: 20
            radius: 13
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "#17a81a" : "#21be2b"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
