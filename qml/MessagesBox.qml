import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property alias model: messagesListView.model

    radius: 10
    color: middleColor

    ColumnLayout {
        anchors.fill: parent

        Rectangle {

            height: 500
            Layout.fillWidth: true
            color: lighterColor

            ListView {
                id: messagesListView
                anchors.fill: parent
                spacing: 2
                verticalLayoutDirection: ListView.BottomToTop

                delegate: Rectangle {
                    id: messageRect
                    width: messagesListView.width
                    height: 50
                    color: "transparent"

                    Label {
                        id: messageLabel
                        anchors.fill: parent
                        font: defaultFont
                        text: message
                        wrapMode: "WordWrap"
                        horizontalAlignment: toMe ? Text.AlignLeft : Text.AlignRight
                    }
                }
            }
        }

        RowLayout {

            Layout.fillHeight: true
            Layout.fillWidth: true

            Rectangle {
                color: lightColor

                width: 500
                Layout.fillHeight: true

                TextEdit {
                    id: messageEdit
                    anchors.fill: parent
                    font: defaultFont

                    wrapMode: TextEdit.WrapAnywhere
                }
            }

            Button {
                font: defaultFont
                text: "SEND"

                Layout.fillHeight: true
                Layout.fillWidth: true

                background: Rectangle {
                    color: lightColor
                    radius: 2
                }
                onClicked: {
                    sendMessage(messageEdit.text)
                    messageEdit.text = ""
                }
            }
        }
    }
}
