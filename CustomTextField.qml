import QtQuick 2.0
import QtQuick.Controls 2.0

TextField {
    id: control
    placeholderText: qsTr("Enter expression")
    font.pointSize: 11
    horizontalAlignment: Text.AlignRight

    property alias backgroundObj: rect

    background: Rectangle {
        id: rect
        implicitWidth: 270
        implicitHeight: 30
        color: control.enabled ? "transparent" : "#353637"
        border.color: control.enabled ? "#21be2b" : "transparent"
    }
}
