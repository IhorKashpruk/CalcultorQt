import QtQuick 2.6
import QtQuick.Controls 2.0

RadioButton {
    id: control
    text: qsTr("RadioButton")
    checked: true

    indicator: Rectangle {
        implicitWidth: 20
        implicitHeight: 20
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        border.color: control.checked ? "#17a81a" : "#9E9E9E"

        Rectangle {
            width: 8
            height: 8
            x: 6
            y: 6
            radius: 7
            color: control.checked ? "#17a81a" : "#9E9E9E"
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.checked ? "#17a81a" : "#9E9E9E"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
