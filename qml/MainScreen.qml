import QtQuick 2.0

Rectangle {
    id: root

    property alias loaderSource: screensLoader.source

    signal loadCompleted()

    anchors.fill: parent

    Loader {
        id: screensLoader
        objectName: "screensLoader"
        anchors.fill: parent
        focus: true

        onLoaded: root.loadCompleted()
    }
}
