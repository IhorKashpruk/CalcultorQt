import QtQuick 2.0
import QtQuick.Controls 1.4

Menu {
    title: "Edit"

    property var window: null

    MenuItem {
        text: "Cut"
        shortcut: "Ctrl+X"
        onTriggered: {
            if(window === null){
                var component = Qt.createComponent("CustomDialog.qml")
                window    = component.createObject(root)

            }
        }
    }

    MenuItem {
        text: "Copy"
        shortcut: "Ctrl+C"
        onTriggered: {
            if(window !== null){
                window.close();
                window = null;
            }
        }
    }

    MenuItem {
        text: "Paste"
        shortcut: "Ctrl+V"
    }

    MenuSeparator { }

    Menu {
        title: "More Stuff"

        MenuItem {
            text: "Do Nothing"
        }
    }
}
