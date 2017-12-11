#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>
#include <QPrinter>


class MdiChild;
class QLabel;
class QComboBox;
class QActionGroup;
class QSignalMapper;
class Find_Replace;

namespace Ui {
    class TextEdit;
}


class TextEdit : public QMainWindow
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = 0);
    ~TextEdit();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
  //  bool eventFilter(QObject *, QEvent *);//�¼�������
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::TextEdit *ui;
    Find_Replace *findReplace;
    MdiChild *activeMdiChild();
    void initStatusbar(); //��ʼ��״̬��

    QLabel* firstStatuslabel; //����3����ǩ����������ʾ״̬��Ϣ
    QLabel* secondStatuslabel;
    QLabel* thirdStatuslabel;  //������ʾʱ��

    QToolBar *toolBar;
    QAction *left; //���뷽ʽ
    QAction *center;
    QAction *right;
    QAction *justify;
    QActionGroup *actGrp;

    QLabel *listAlign;//�����ǩ
    QComboBox *listBox;//����������

    QAction *tabbedView;//��ͼģʽ
    QAction *windowView;
    QActionGroup *actViewMode;

    QSignalMapper *windowMapper;//�źŷ���ת����

    void initConnect();

    enum{MaxRecentFiles = 9};

    QAction *recentFileActs[MaxRecentFiles];
    void updateRecentFiles();//����������ļ��б�

    void readSettings();//��ȡ���洰�ڴ�С��λ�õ�����
    void writeSettings();//��¼���ڵĴ�С��λ��

    bool senceF;//�Ƿ����ִ�Сд,1���� 0������
    bool upFindF;//��ǰ����������,1��ǰ 0���
    void doFind(QString findText);//���ҵ�ʵ�ֺ���
    bool doReplaceAllFind(QString findText);//ȫ���滻�Ĳ���ʵ�ֺ���

private slots:
    void on_action_zoomOut_triggered();
    void on_action_zoomIn_triggered();
    void on_action_Replace_triggered();
    void on_action_Find_triggered();
    void on_action_AboutQt_triggered();
    void on_action_About_triggered();
    void on_action_AllClose_triggered();
    void on_action_Close_triggered();
    void on_action_PreviousW_triggered();
    void on_action_NextW_triggered();
    void on_action_Cascade_triggered();
    void on_action_Tile_triggered();
    void on_action_FontColor_triggered();
    void on_action_Font_triggered();
    void on_action_HighLightShow_triggered(bool checked);
    void on_action_StatusBarShow_triggered(bool checked);
    void on_action_ToobarShow_triggered(bool checked);
    void on_action_Switch_triggered(bool checked);
    void on_action_Clear_triggered();
    void on_action_AllSelect_triggered();
    void on_action_Del_triggered();
    void on_action_Paste_triggered();
    void on_action_Copy_triggered();
    void on_action_Cut_triggered();
    void on_action_Redo_triggered();
    void on_action_Undo_triggered();
    void on_action_PDF_triggered();
    void on_action_PrintPreview_triggered();
    void on_action_Print_triggered();
    void on_action_Quit_triggered();
    void on_action_Asave_triggered();
    void on_action_Save_triggered();
    void on_action_Open_triggered();
    void on_action_New_triggered();

    void updateMenus();
    void timerUpDate();  //��ʱ��
    void doCursorchanged(); //��ȡ���λ����Ϣ
    void printPreview(QPrinter *printer);
    void highlightCurrentLine();//������ʾ��ǰ�༭����
    void documentWasModified();//�ĵ����ڱ��޸�
    void slotAlignment(QAction*); //���Ķ��뷽ʽ
    void slotList(int);     //����
    void slotViewMode(QAction*); //��ͼģʽ
    void setActiveSubWindow(QWidget *window);//�����
    void updatemenuSelectw();//���¡�ѡ�񴰿ڡ��˵�
    void openRecentFile();//������ļ��б�ָ���ļ�
    void findNextF();//�����ҡ��ġ�������һ����
    void findNextR();//���滻���ġ�������һ����
    void replace();//�滻
    void replaceAll();//ȫ���滻
};

#endif // TEXTEDIT_H
