import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property alias contactsModel: contactsListView.model

    property alias messagesModel: messagesBox.model

    signal selectedContactChanged(int user_id)
    signal sendMessage(string msg)

    color: lighterColor
    anchors.fill: parent
    anchors.margins: 0
    radius: 3

    Rectangle {
        color: middleColor
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10

            spacing: 10

            ContactsListView {
                id: contactsListView
                Layout.fillHeight: true
            }

            MessagesBox {
                id: messagesBox

                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
