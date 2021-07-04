QT       += core gui sql

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
    add_doctors.cpp \
    add_inspection_items.cpp \
    add_patients.cpp \
    add_payments.cpp \
    add_prescriptions.cpp \
    change_department.cpp \
    change_password.cpp \
    display_beds.cpp \
    display_department.cpp \
    display_doctors.cpp \
    display_patients.cpp \
    display_sickrooms.cpp \
    leave_hospital.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    patientwindow.cpp \
    show_inspection_items.cpp \
    show_list.cpp \
    show_patients.cpp \
    show_prescriptions.cpp

HEADERS += \
    add_doctors.h \
    add_inspection_items.h \
    add_patients.h \
    add_payments.h \
    add_prescriptions.h \
    change_department.h \
    change_password.h \
    display_beds.h \
    display_department.h \
    display_doctors.h \
    display_patients.h \
    display_sickrooms.h \
    leave_hospital.h \
    loginwindow.h \
    mainwindow.h \
    patientwindow.h \
    show_inspection_items.h \
    show_list.h \
    show_patients.h \
    show_prescriptions.h

FORMS += \
    change_password.ui \
    display_beds.ui \
    display_department.ui \
    display_doctors.ui \
    display_patients.ui \
    display_sickrooms.ui \
    loginwindow.ui \
    mainwindow.ui \
    patientwindow.ui \
    show_inspection_items.ui \
    show_list.ui \
    show_patients.ui \
    show_prescriptions.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
