QT += quick \
    network
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += D:\Projects\json-develop\include

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    palette.cpp \
    data\user_info.cpp \
    command_server\command_server.cpp \
    command_server\packet_parser.cpp \
    command_server\commands\abstract_command_handler.cpp \
    command_server\commands\hello_command_handler.cpp \
    command_server\commands\request_code_command_handler.cpp \
    command_server\commands\request_jwt_command_handler.cpp \
    command_server\commands\presence_command_handler.cpp \
    command_server\commands\contacts_command_handler.cpp \
    command_server\commands\send_message_command_handler.cpp \
    command_server/payload_handler.cpp \
    command_server/data_emitter.cpp \
    presenters\main_screen_presenter.cpp \
    presenters/abstract_presenter.cpp \
    presenters/registration_screen_presenter.cpp \
    presenters/messenger_screen_presenter.cpp \
    data/session_data.cpp \
    data/message_info.cpp \
    data/contacts_model.cpp \
    data/messages_handler.cpp \
    data/messages_model.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    palette.h \
    data\user_info.h \
    command_server\command_server.h \
    command_server\packet_parser.h \
    command_server\commands\abstract_command_handler.h \
    command_server\commands\hello_command_handler.h \
    command_server\commands\request_code_command_handler.h \
    command_server\commands\request_jwt_command_handler.h \
    command_server\commands\presence_command_handler.h \
    command_server\commands\contacts_command_handler.h \
    command_server\commands\send_message_command_handler.h \
    command_server\commands_traits.h \
    command_server/payload_handler.h \
    command_server/data_emitter.h \
    presenters\main_screen_presenter.h \
    presenters/abstract_presenter.h \
    presenters/registration_screen_presenter.h \
    presenters/messenger_screen_presenter.h \
    data/session_data.h \
    data/message_info.h \
    data/contacts_model.h \
    data/messages_handler.h \
    data/messages_model.h

OTHER_FILES += \
    qml\*.qml

# Для корректного вывода ошибок в консоль

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

#DISTFILES += \
#    qml/RegistrationScreen.qml \
#    qml/MessengerScreen.qml

DISTFILES += \
    qml/ContactsListView.qml \
    qml/MessagesBox.qml
