#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include <QMenu>
#include <QImage>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QSpinBox>
#include <QToolBar>
#include <QComboBox>
#include <QMainWindow>
#include <QToolButton>
#include <QFontComboBox>
#include <QTextCharFormat>
#include "showwidget.h"

namespace Ui {
class ImgProcessor;
}

class ImgProcessor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImgProcessor(QWidget *parent = 0);
    ~ImgProcessor();

    void createActions();                           //��������
    void createMenus();                             //�����˵�
    void createToolBars();                          //����������

    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);

private:
    Ui::ImgProcessor *ui;

    QMenu *fileMenu;                                //����˵���
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;

    QImage img;
    QString fileName;
    ShowWidget *showWidget;

    QAction *openFileAction;                        //�ļ��˵���
    QAction *NewFileAction;
    QAction *PrintTextAction;
    QAction *PrintImageAction;
    QAction *exitAction;

    QAction *copyAction;                            //�༭�˵���
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    QAction *rotate90Action;                        //��ת�˵���
    QAction *rotate180Action;
    QAction *rotate270Action;

    QAction *mirrorVerticalAction;                  //����˵���
    QAction *mirrorHorizontalAction;

    QAction *undoAction;
    QAction *redoAction;

    QToolBar *fileTool;                             //������
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;

    QToolBar *doToolBar;

    QLabel *fontLabel1;                             //����������
    QFontComboBox *fontComboBox;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;

    QToolBar *fontToolBar;                          //���幤����

    QLabel *listLabel;                              //����������
    QComboBox *listComboBox;
    QActionGroup *actGrp;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;

    QToolBar *listToolBar;                          //���򹤾���

protected slots:
    void ShowNewFile();
    void ShowOpenFile();
    void ShowPrintText();
    void ShowPrintImage();
    void ShowZoomIn();
    void ShowZoomOut();
    void ShowRotate90();
    void ShowRotate180();
    void ShowRotate270();
    void ShowMirrorVertical();
    void ShowMirrorHorizontal();

    void ShowFontComboBox(QString comboStr);
    void ShowSizeSpinBox(QString spinValue);
    void ShowBoldBtn();
    void ShowItalicBtn();
    void ShowUnderlineBtn();
    void ShowColorBtn();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

    void ShowList(int);
    void ShowAlignment(QAction *act);
    void ShowCursorPositionChanged();
};

#endif // IMGPROCESSOR_H
