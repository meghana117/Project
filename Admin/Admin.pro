#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T15:54:17
#
#-------------------------------------------------

QT       += core gui
QT+=sql
QT+= printsupport
QT+=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Admin
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWidget.cpp \
    Db_Class.cpp \
    Login.cpp \
    Welcome.cpp \
    Admin.cpp \
    Add_Student_UI.cpp \
    Student.cpp \
    Search_Student.cpp \
    Training.cpp \
    training_object.cpp \
    placement_object.cpp \
    Placement.cpp \
    company.cpp \
    company_object.cpp \
    Placed.cpp \
    placed_object.cpp \
    paper.cpp \
    add_papers.cpp \
    contact_object.cpp \
    Contacts.cpp \
    SelectStudents.cpp \
    criteria_object.cpp \
    Update_Result.cpp

HEADERS += \
        MainWidget.h \
    Db_Class.h \
    Login.h \
    Welcome.h \
    Admin.h \
    Add_Student_UI.h \
    Student.h \
    Search_Student.h \
    Training.h \
    training_object.h \
    placement_object.h \
    Placement.h \
    company.h \
    company_object.h \
    Placed.h \
    placed_object.h \
    paper.h \
    add_papers.h \
    contact_object.h \
    Contacts.h \
    SelectStudents.h \
    criteria_object.h \
    Update_Result.h

DISTFILES += \
    ../../StyleSheet.qss

RESOURCES += \
    resource_file.qrc
