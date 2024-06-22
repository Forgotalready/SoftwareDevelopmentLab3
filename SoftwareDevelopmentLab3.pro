QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Domain/Context.cpp \
    Domain/DirectoryTraversal/BySizeTraversal.cpp \
    Domain/DirectoryTraversal/ByTypeTraversal.cpp \
    Domain/DirectoryTraversal/TraversalStrategy.cpp \
    Model/FileSystemModel.cpp \
    Model/IDataTransformer.cpp \
    main.cpp \
    View/MainWindow.cpp

HEADERS += \
    Domain/Context.h \
    Domain/DirectoryTraversal/BySizeTraversal.h \
    Domain/DirectoryTraversal/ByTypeTraversal.h \
    Domain/DirectoryTraversal/TraversalStrategy.h \
    Model/FileSystemModel.h \
    Model/IDataTransformer.h \
    View/MainWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
