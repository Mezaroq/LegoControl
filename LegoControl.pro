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
    Model/ActionModel.cpp \
    Model/ButtonModel.cpp \
    Model/LabelModel.cpp \
    Model/LightModel.cpp \
    Model/ObjectModel.cpp \
    Model/RailModel.cpp \
    Model/SensorModel.cpp \
    Model/SliderModel.cpp \
    Model/StationModel.cpp \
    Model/SwitchModel.cpp \
    Model/TrafficManagerButtonModel.cpp \
    Model/TrafficManagerLabelModel.cpp \
    Model/TrafficMapModel.cpp \
    Model/TrafficTimetableModel.cpp \
    Model/TrainModel.cpp \
    View/GraphicsView.cpp \
    View/MainWindow.cpp \
    View/SceneView.cpp \
    ViewModel/DataViewModel.cpp \
    ViewModel/MainProvider.cpp \
    ViewModel/MainViewModel.cpp \
    ViewModel/TrafficManagerPanelViewModel.cpp \
    ViewModel/TrafficManagerViewModel.cpp \
    main.cpp

HEADERS += \
    Model/ActionModel.h \
    Model/ButtonModel.h \
    Model/LabelModel.h \
    Model/LightModel.h \
    Model/ObjectModel.h \
    Model/RailModel.h \
    Model/SensorModel.h \
    Model/SliderModel.h \
    Model/StationModel.h \
    Model/SwitchModel.h \
    Model/TrafficManagerButtonModel.h \
    Model/TrafficManagerLabelModel.h \
    Model/TrafficMapModel.h \
    Model/TrafficTimetableModel.h \
    Model/TrainModel.h \
    View/GraphicsView.h \
    View/MainWindow.h \
    View/SceneView.h \
    ViewModel/DataViewModel.h \
    ViewModel/MainProvider.h \
    ViewModel/MainViewModel.h \
    ViewModel/TrafficManagerPanelViewModel.h \
    ViewModel/TrafficManagerViewModel.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
