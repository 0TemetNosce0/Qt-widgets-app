#-------------------------------------------------
#
# Project created by QtCreator 2015-01-22T23:18:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets
lessThan(QT_MAJOR_VERSION, 5): QT += phonon

TARGET = 360
TEMPLATE = app


SOURCES += main.cpp \
    src/clean/common/cleanscanbottom.cpp \
    src/common/wenliwidget.cpp \
    src/common/wenlibackwidget.cpp \
    src/common/toptabwidget.cpp \
    src/common/threebutton.cpp \
    src/common/sysbuttongroup.cpp \
    src/common/statictextbutton.cpp \
    src/common/staticbutton.cpp \
    src/common/stackstatuswidget.cpp \
    src/common/speedoutbuttonwidget.cpp \
    src/common/speedoutbutton.cpp \
    src/common/numbersanimwidget.cpp \
    src/common/numanimwidget.cpp \
    src/common/dynamicwidget.cpp \
    src/common/dynamicscaledwidget.cpp \
    src/common/dynamicbutton.cpp \
    src/common/basestylewidget.cpp \
    src/common/animbuttonwidget.cpp \
    src/common/animbuttongroupwidget.cpp \
    src/main/bottom/mainexaminewidget.cpp \
    src/main/common/videowidget.cpp \
    src/main/common/scorewidget.cpp \
    src/main/common/opacitywidget.cpp \
    src/main/common/buttonlabel.cpp \
    src/main/common/backgroundbutton.cpp \
    src/main/top/userwidget.cpp \
    src/main/top/topbottomwidget.cpp \
    src/main/top/mainscorewidget.cpp \
    src/main/mainwindow.cpp \
    src/main/maintopwidget.cpp \
    src/main/mainbottomwidget.cpp \
    src/optimize/common/youhuascanbottom.cpp \
    src/safe/safewidget.cpp \
    src/safe/safetopwidget.cpp \
    src/safe/safebottomwidget.cpp \
    src/safe/common/scanbuttonwidget.cpp \
    src/safe/common/safescanbottom.cpp \
    src/test/mainwidget.cpp \
    src/optimize/common/optimizebutton.cpp \
    src/main/common/shadowwidget.cpp \
    src/clean/common/cleandynamicbuttonwidget.cpp \
    src/clean/cleanwidget.cpp \
    src/common/safebuttonwidget.cpp \
    src/main/bottom/mainbottomfirstwidget.cpp \
    src/optimize/youhuawidget.cpp

HEADERS  += \
    src/clean/common/cleanscanbottom.h \
    src/common/wenlibackwidget.h \
    src/common/toptabwidget.h \
    src/common/threebutton.h \
    src/common/sysbuttongroup.h \
    src/common/staticbutton.h \
    src/common/stackstatuswidget.h \
    src/common/speedoutbuttonwidget.h \
    src/common/speedoutbutton.h \
    src/common/safebuttonwidget.h \
    src/common/numbersanimwidget.h \
    src/common/numanimwidget.h \
    src/common/dynamicwidget.h \
    src/common/dynamicscaledwidget.h \
    src/common/dynamicbutton.h \
    src/common/common.h \
    src/common/animbuttongroupwidget.h \
    src/main/bottom/mainexaminewidget.h \
    src/main/common/videowidget.h \
    src/main/common/shadowwidget.h \
    src/main/common/scorewidget.h \
    src/main/common/opacitywidget.h \
    src/main/common/buttonlabel.h \
    src/main/common/backgroundbutton.h \
    src/main/top/userwidget.h \
    src/main/top/topbottomwidget.h \
    src/main/top/mainscorewidget.h \
    src/main/mainwindow.h \
    src/main/maintopwidget.h \
    src/main/mainbottomwidget.h \
    src/optimize/common/youhuascanbottom.h \
    src/optimize/youhuawidget.h \
    src/safe/safewidget.h \
    src/safe/safetopwidget.h \
    src/safe/safebottomwidget.h \
    src/safe/common/safescanbottom.h \
    src/test/mainwidget.h \
    src/optimize/common/optimizebutton.h \
    src/clean/cleanwidget.h \
    src/main/common/shadowwidget.h \
    src/main/bottom/mainbottomfirstwidget.h \
    src/clean/common/cleandynamicbuttonwidget.h \
    src/common/animbuttonwidget.h \
    src/common/basestylewidget.h \
    src/common/myhelper.h \
    src/common/statictextbutton.h \
    src/common/wenliwidget.h \
    src/safe/common/scanbuttonwidget.h

RESOURCES += \
    resource/360.qrc

#复制视频文件
win32{
    COPY = copy /y
    MKDIR = mkdir
}else{
    COPY = cp
    MKDIR = mkdir -p
}

FILES_COPY_SRC = resource/video/360SafeVideo.wmv


!equals(_PRO_FILE_PWD_, OUT_PWD) {
    for(f, FILES_COPY_SRC){
        orig_file = $$_PRO_FILE_PWD_/$$f
        dist_file = $$OUT_PWD/$$f
        dist = $$dirname(dist_file)
        win32:dist = $$replace(dist, /, \\)
        win32:orig_file = $$replace(orig_file, /, \\)
        !exists($$dist):system($$MKDIR $$dist)
        !exists($$dist_file):system($$COPY $$orig_file $$dist)
    }
}
