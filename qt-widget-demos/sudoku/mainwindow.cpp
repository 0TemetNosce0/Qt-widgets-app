#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    settingsdialog = new SettingsDialog(this);
    sudokuTable = new SudokuTable(this);
    setCentralWidget(sudokuTable);
    setWindowTitle(QStringLiteral("����������"));
    setWindowIcon(QIcon(":/images/sudoku.png"));
    createActions();
    createToolBar();
    setFixedHeight(351);
    setFixedWidth(317);

    connect(sudokuTable, SIGNAL(setNextEnabled(bool)),
            this, SLOT(setNextActionEnabled(bool)));
    connect(sudokuTable, SIGNAL(setPreviousEnabled(bool)),
            this, SLOT(setPreviousActionEnabled(bool)));

    previousAction->setEnabled(false);
}

void MainWindow::createActions()
{
    newPuzzleAction = new QAction(QStringLiteral("����"), this);
    newPuzzleAction->setIcon(QIcon(":/images/newPuzzle.png"));
    connect(newPuzzleAction, SIGNAL(triggered()), sudokuTable, SLOT(newPuzzle()));

    previousAction = new QAction(QStringLiteral("��һ����"), this);
    previousAction->setIcon(QIcon(":/images/previous.png"));
    connect(previousAction, SIGNAL(triggered()), sudokuTable, SLOT(previous()));

    nextAciton = new QAction(QStringLiteral("��һ����"), this);
    nextAciton->setIcon(QIcon(":/images/next.png"));
    connect(nextAciton, SIGNAL(triggered()), sudokuTable, SLOT(next()));

    eraseAction = new QAction(QStringLiteral("�����"), this);
    eraseAction->setIcon(QIcon(":/images/erase.png"));
    connect(eraseAction, SIGNAL(triggered()), sudokuTable, SLOT(erase()));

    clearAction = new QAction(QStringLiteral("���"), this);
    clearAction->setIcon(QIcon(":/images/clear.png"));
    connect(clearAction, SIGNAL(triggered()), sudokuTable, SLOT(clear()));

    eyeModeAction = new QAction(QStringLiteral("����ģʽ"), this);
    eyeModeAction->setIcon(QIcon(":/images/eyeOn.png"));
    connect(eyeModeAction, SIGNAL(triggered()), this, SLOT(setEyeMode()));

    settingsAction = new QAction(QStringLiteral("����"), this);
    settingsAction->setIcon(QIcon(":/images/settings.png"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(settings()));

    helpAction = new QAction(QStringLiteral("����"), this);
    helpAction->setIcon(QIcon(":/images/help.png"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    aboutAction = new QAction(QStringLiteral("����"), this);
    aboutAction->setIcon(QIcon(":/images/about.png"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    xiakeAction = new QAction(QStringLiteral("���ͷ��ƴ�"), this);
    xiakeAction->setIcon(QIcon(":/images/xiake.png"));
    connect(xiakeAction, SIGNAL(triggered()), this, SLOT(xiake()));
}

void MainWindow::createToolBar()
{
    toolBar = addToolBar(tr("ToolBar"));
    toolBar->addAction(newPuzzleAction);
    toolBar->addAction(previousAction);
    toolBar->addAction(nextAciton);
    toolBar->addAction(eraseAction);
    toolBar->addAction(clearAction);
    toolBar->addAction(eyeModeAction);
    toolBar->addAction(settingsAction);
    toolBar->addAction(helpAction);
    toolBar->addAction(aboutAction);
    toolBar->addAction(xiakeAction);
    toolBar->setMovable(false);
}

//public slots:
void MainWindow::setPreviousActionEnabled(bool flag)
{
    previousAction->setEnabled(flag);
}

void MainWindow::setNextActionEnabled(bool flag)
{
    nextAciton->setEnabled(flag);
}

//private:
void MainWindow::setEyeMode()
{
    if (sudokuTable->eyeMode())
    {
        sudokuTable->setEyeMode(false);
        eyeModeAction->setIcon(QIcon(":/images/eyeOff.png"));
    }
    else
    {
        sudokuTable->setEyeMode(true);
        eyeModeAction->setIcon(QIcon(":/images/eyeOn.png"));
    }
}

void MainWindow::settings()
{
    settingsdialog->setSolutions(sudokuTable->dataSolutions());
    if (settingsdialog->exec())
        sudokuTable->setDataSolutions(settingsdialog->solutions());
}

void MainWindow::help()
{
    QMessageBox::information(this, QStringLiteral("����"),
                             QStringLiteral("<h2> ������Ϸ���� </h2> \
                                            <p>1.ÿһ����д1-9�����ظ���\
                                                                 <p>2.ÿһ����д1-9�����ظ���\
                                                                                      <p>3.ÿ������д1-9�����ظ���\
                                                                                                           <p>4.�����ص�ǰ������Ҫ���£��������е����֣���������пո����д�����֡�"));
}

                                                                                                                                                  void MainWindow::about()
    {
                                                                                                                                                  QMessageBox::about(this, QStringLiteral("����"),
                                                                                                                                                                     QStringLiteral("<h2> ���������� V0.9 </h2> \
                                                                                                                                                                                    <p>������������������������⣬Ҳ�������������⡣ \
                                                                                                                                                                                                                 <p>�����ʹ��Qt��д��\
                                                                                                                                                                                                                                 <p>����: ���� \
                                                                                                                                                                                                                                             <p>QQ��1099965906"));
}

                                                                                                                                                                                                                                                   void MainWindow::xiake()
    {
                                                                                                                                                                                                                                                   QMessageBox::information(this, QStringLiteral("���ͷ��ƴ�"),
                                                                                                                                                                                                                                                                            QStringLiteral("<h2> ����������Ϸ�����ͷ��ƴ����Ѿ���ʼԤ�ۣ� </h2> \
                                                                                                                                                                                                                                                                                           <p> �����ͷ��ƴ���Ϊ���幤���������ĵ��Ĳ�������Ϸ��ǰ��Ϊ������Ⱥ��������\
                                                                                                                                                                                                                                                                                                                                     <p> ���幤���������������������������ֱ��ǣ�����ӹȺ��������������Ⱥ��������������Ⱥ��������\
                                                                                                                                                                                                                                                                                                                                                                                        ��������Ϊ����ԭ�����ɢ�ˣ�ʮ����󣬹��������飬�����������ͷ��ƴ�����\
                                                                                                                                                                                                                                                                                                                                                                                                                               <p> �����ͷ��ƴ����ǡ�����Ⱥ�����������ư棬���������ư棬������ʮ�㣨���ٸ�����ô��Ϊ����\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 ��ӳ���һ�����ϵľ��飬����׷���������ӵ�ʮλ���ϣ��Ը����ɶ�Ϊ��ɫ��û��Ű�ĵı��磬��û�����ĵ�ˢ�֡�\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        <p> ������Ϊ�����ͷ��ƴ���һ�����ڲ�ͬ�ĵ�����Ϸ��ս������ֻռ20%��ʣ�µ�80%���Ƿḻ�����ݣ�������ԣ����㣬�ڿ�\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ���������ѡ������黭��������������֧·�ľ���ȵȣ���Ҫ�����ǽ�һ������С��ɳ�Ϊһ�������Ĺ��£���ȻҲ��������ؤ����\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      <p> �����ͷ��ƴ�������6��1�տ�ʼԤ�ۣ�����7��28�տ�ʼ��ʽ���ۣ���ͨ��steam����֮�⣬���ְ滹û����������50Ԫ���ң���һ����Ӱ�ļ۸񣩡�\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    <p> ���ܸ��˾��úܰ�������ȷ���������Ƿ�Ҳϲ���������ͣ���������ǰ��������Ⱥ������������Ϸ��2d���棩��\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             ���߿����ٷ�������Ƶ�����ߵ���ʽ���ۺ������ѽ������棬�����������������飬��ٶȣ����ͷ��ƴ�������"));
}
