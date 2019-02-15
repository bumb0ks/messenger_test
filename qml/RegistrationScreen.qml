import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle {
    id: root

    signal registrationButtonClicked()
    signal loginButtonClicked(string jwt)

    property string phoneNumber: phoneEdit.text
    property string code: codeEdit.text

    color: lighterColor
    anchors.fill: parent
    anchors.margins: 5
    radius: 3

    function disablePhoneEdit()
    {
        phoneLabel.enabled = false;
        phoneEditRect.enabled = false;
        registerButton.enabled = false;

        jwtEditRect.enabled = false;
        jwtLabel.enabled = false;
        loginButton.enabled = false;

        jwtEditRect.opacity = 0.5;
        jwtLabel.opacity = 0.5;
        loginButton.opacity = 0.5;

        phoneLabel.opacity = 0.5;
        phoneEditRect.opacity = 0.5;
        registerButton.opacity = 0.5;
    }

    function enableCodeEdit()
    {
        codeLabel.visible = true;
        codeEditRect.visible = true;
        registerButton.enabled = true;
        registerButton.opacity = 1.0;

        codeEdit.focus = true;

        registerButton.text = "Send code";
    }

    function disableCodeEdit()
    {
        codeLabel.enabled = false;
        codeEditRect.enabled = false;
        registerButton.enabled = false;
        codeLabel.opacity = 0.5;
        codeEditRect.opacity = 0.5;
        registerButton.opacity = 0.5;
    }


    Column
    {
        spacing: 25
        anchors.centerIn: parent

        Label {
            id: phoneLabel
            text: "Enter phone:"
            font: defaultFont

            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: phoneEditRect

            width: 250
            height: 50
            color: lightColor
            radius: 5

            TextInput {
                id: phoneEdit

                anchors.centerIn: parent
                font: defaultFont
                focus: true

                validator: IntValidator{}
                inputMask: "0(000)000-00-00"
                maximumLength: 11

                inputMethodHints: Qt.ImhDigitsOnly
            }
        }

        Label {
            id: codeLabel

            text: "Enter code:"
            font: defaultFont

            visible: false

            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: codeEditRect

            width: 250
            height: 50
            color: lightColor
            radius: 5

            visible: false

            TextInput {
                id: codeEdit

                anchors.centerIn: parent
                font: defaultFont

                validator: IntValidator{}
                inputMask: "0000"
                maximumLength: 4

                inputMethodHints: Qt.ImhDigitsOnly
            }
        }

        Button {
            id: registerButton

            text: "Register"
            font: defaultFont

            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                color: lightColor
                radius: 2
            }

            onClicked: {
                root.registrationButtonClicked()
            }
        }

        Label {
            id: jwtLabel
            text: "or login with JWT code!"
            font: defaultFont

            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: jwtEditRect

            width: 300
            height: 100
            color: lightColor
            radius: 5
            clip: true

            visible: true

            TextEdit {
                id: jwtEdit

                wrapMode: TextEdit.WrapAnywhere

                anchors.fill: parent
                font: defaultFont
            }
        }

        Button {
            id: loginButton

            text: "Login"
            font: defaultFont

            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                color: lightColor
                radius: 2
            }

            onClicked: {
                root.loginButtonClicked(jwtEdit.text)
                disablePhoneEdit()
            }
        }
    }
}
