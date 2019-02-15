import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Rectangle {
    id: contactsRect

    property alias model: contactsListView.model

    width: 300
    color: lighterColor
    radius: 10

    ListView {
        id: contactsListView
        anchors.fill: parent
        spacing: 2

        delegate: Rectangle {
            id: listDelegate

            property var view: ListView.view
            property var isCurrent: ListView.isCurrentItem

            width: contactsRect.width
            height: 80

            color: isCurrent ? middleColor : lightColor

            ColumnLayout {
                anchors.centerIn: parent
                anchors.margins: 5

                Label {
                    font: defaultFont
                    text: phone
                }

                Item {
                    Layout.fillHeight: true
                }

                RowLayout {

                    Label {
                        font: smallFont
                        text: userId
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        width: 30
                        height: 30
                        radius: 15
                        color: online ? "green" : "red"
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentIndex = model.index
                    selectedContactChanged(userId)
                }
            }
        }
    }
}
