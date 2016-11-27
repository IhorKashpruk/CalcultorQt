import QtQuick 2.0
import QtQuick.Controls 2.0

Button {
    id: control
    text: qsTr("Button")
    width: 70

    property alias backgroundColor: br.color
    property alias textColor: txt.color
    property alias backgroundObj: br

    contentItem: Text {
        id: txt
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? Qt.darker("#9E9E9E") : "#9E9E9E"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

    }

    background: Rectangle {
        id: br
        implicitWidth: 70
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        border.color: control.down ? Qt.darker("#9E9E9E") : "#9E9E9E";
        border.width: 1.2
        radius: 2
    }

}
