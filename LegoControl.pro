QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/ControlAction.cpp \
    Model/ControlButton.cpp \
    Model/ControlLabel.cpp \
    Model/ControlLight.cpp \
    Model/ControlObject.cpp \
    Model/ControlRail.cpp \
    Model/ControlSensor.cpp \
    Model/ControlSlider.cpp \
    Model/ControlSwitch.cpp \
    Model/ControlTrain.cpp \
    View/ControlDebugPanel.cpp \
    View/ControlScene.cpp \
    View/ControlView.cpp \
    View/MainWindow.cpp \
    ViewModel/AlieViewModel.cpp \
    ViewModel/ControlDataProvider.cpp \
    ViewModel/ControlProvider.cpp \
    ViewModel/ControlViewModel.cpp \
    main.cpp

HEADERS += \
    Model/ControlAction.h \
    Model/ControlButton.h \
    Model/ControlLabel.h \
    Model/ControlLight.h \
    Model/ControlObject.h \
    Model/ControlRail.h \
    Model/ControlSensor.h \
    Model/ControlSlider.h \
    Model/ControlSwitch.h \
    Model/ControlTrain.h \
    View/ControlDebugPanel.h \
    View/ControlScene.h \
    View/ControlView.h \
    View/MainWindow.h \
    ViewModel/AlieViewModel.h \
    ViewModel/ControlDataProvider.h \
    ViewModel/ControlProvider.h \
    ViewModel/ControlViewModel.h

FORMS += \
    View/controldebugpanel.ui \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
