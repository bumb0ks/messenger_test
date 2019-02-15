import QtQuick 2.8
import QtQuick.Window 2.2

Window {
    id: mainWindow

    visible: true
    width: 1024
    height: 768
    title: qsTr("Hello Messenger")

    MainScreen {
        id: mainScreen
        objectName: "mainScreen"

        anchors.fill: parent
    }
}
