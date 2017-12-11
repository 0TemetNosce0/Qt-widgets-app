#include "mainwindow.h"
#include "treemodel.h"
#include <QHeaderView>
#include <QFile>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QListView>
#include <WindowsX.h>
#include "ItemDelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_height(30)
    , m_shadowSize(5)
    , m_menu(NULL)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowIcon(QIcon("./Resources/Images/icon.png"));

    m_comboBox = new QComboBox(this);
    QStringList strList;
    strList << QStringLiteral("样式一") << QStringLiteral("样式二") << QStringLiteral("样式三");
    for (int i = 0; i < strList.count(); ++i)
    {
        m_comboBox->addItem(strList.at(i));
    }
    m_comboBox->setFixedSize(100, 25);
    m_comboBox->setView(new QListView());

    connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeStyle(int)));

    m_treeView = new QTreeView(this);
    ItemDelegate *delegate = new ItemDelegate(this);
    TreeModel *model = new TreeModel(this);

    model->setXML(Util::exePath() + "/Resources/ToolsConfig.xml");

    m_treeView->setHeaderHidden(true);
    m_treeView->setAnimated(true);
    m_treeView->setMouseTracking(true);
    m_treeView->setExpandsOnDoubleClick(true);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_treeView->setModel(model);
    delegate->setView(m_treeView);
    m_treeView->setItemDelegate(delegate);

    connect(delegate, SIGNAL(expanded(const QModelIndex &)), this, SLOT(expanded(const QModelIndex &)));

    m_label = new QLabel(this);
    m_closeButton = new QPushButton(this);
    m_closeButton->setFixedSize(27, 22);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setToolTip(QStringLiteral("关闭"));

    m_label->setObjectName("titleLabel");
    m_label->setText(QStringLiteral("自定义TreeView"));

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget(m_label);
    titleLayout->addStretch();
    titleLayout->addWidget(m_closeButton);
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(5, 0, 5, 0);

    QHBoxLayout *styleLayout = new QHBoxLayout();
    styleLayout->addWidget(m_comboBox);
    styleLayout->addStretch();
    styleLayout->setSpacing(0);
    styleLayout->setContentsMargins(20, 0, 0, 0);

    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addWidget(m_treeView);
    centerLayout->setSpacing(0);
    centerLayout->setContentsMargins(25, 0, 25, 25);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(styleLayout);
    mainLayout->addLayout(centerLayout);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(5, 3, 5, 7);

    this->setLayout(mainLayout);

    QDesktopWidget *pDesktop = QApplication::desktop();
    m_rect = pDesktop->availableGeometry();

    connect(m_treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeViewCustomContextMenuRequested(QPoint)));
    connect(m_closeButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    m_treeView->expandAll();
    this->changeStyle(0);
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeStyle(int index)
{
    QString styleOne = "QTreeView{\
        border: 1px solid lightgray;\
    }\
    QTreeView::item {\
            height: 40px;\
            border-radius: 2px;\
            border: 1px solid transparent;\
            background: transparent;\
            color: black;\
    }\
    QTreeView::item:hover {\
            border: 1px solid rgb(185, 215, 250);\
    }\
    QTreeView::item:selected {\
            border: 1px solid rgb(170, 190, 230);\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250), stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));\
    }\
    QTreeView::branch:open:has-children {\
            image: url(./Resources/Images/branchOpen.png);\
    }\
    QTreeView::branch:closed:has-children {\
            image: url(./Resources/Images/branchClose.png);\
    }";

    QString styleTwo = "QTreeView{\
            border: 1px solid lightgray;\
    }\
    QTreeView::item {\
            height: 40px;\
            border-radius: 2px;\
            border: 1px solid transparent;\
            background: transparent;\
            color: black;\
    }\
    QTreeView::item:has-children {\
            border: none;\
            border-bottom: 1px solid lightgray;\
    }\
    QTreeView::item:hover {\
            border: 1px solid rgb(170, 190, 230);\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250), stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));\
    }\
    QTreeView::item:selected {\
            border: 1px solid rgb(170, 190, 230);\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250), stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));\
    }\
    QTreeView::branch:open:has-children {\
            image: url(./Resources/Images/branchOpen2.png);\
    }\
    QTreeView::branch:closed:has-children {\
            image: url(./Resources/Images/branchClose2.png);\
    }";

    QString styleThree = "QTreeView{\
            border: 1px solid lightgray;\
    }\
    QTreeView::item {\
            height: 25px;\
            border: none;\
            background: transparent;\
            color: black;\
    }\
    QTreeView::item:hover {\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(255, 220, 130), stop: 0.5 rgb(255, 220, 130), stop: 1.0 rgb(255, 230, 150));\
    }\
    QTreeView::item:selected {\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(255, 200, 100), stop: 0.5 rgb(255, 230, 150), stop: 1.0 rgb(255, 240, 150));\
    }\
    QTreeView::branch:open:has-children {\
            image: url(./Resources/Images/branchOpen.png);\
    }\
    QTreeView::branch:closed:has-children {\
            image: url(./Resources/Images/branchClose.png);\
    }";

    if (index == 0)
    {
        m_treeView->setStyleSheet(styleOne);
    }
    else if (index == 1)
    {
        m_treeView->setStyleSheet(styleTwo);
    }
    else
    {
        m_treeView->setStyleSheet(styleThree);
    }
}

void MainWindow::expanded(QModelIndex index)
{
    bool bExpanded = m_treeView->isExpanded(index);
    if (!bExpanded)
    {
        m_treeView->expand(index);
    }
    else
    {
        m_treeView->collapse(index);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QString strPath = QCoreApplication::applicationDirPath() + "/Resources/Images/windowShadow.png";

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect titleRect = QRect(5, 3, this->width() - 10, m_height);

    QPixmap m_shadow(strPath);

    QRect bottom(5, 136, 200, 7);
    QRect top(5, 0, 200, 3);
    QRect left(0, 3, 5, 133);
    QRect right(205, 3, 5, 133);
    QRect topRight(205, 0, 5, 3);
    QRect topLeft(0, 0, 5, 3);
    QRect bottomLeft(0, 136, 5, 7);
    QRect bottomRight(205, 136, 5, 7);

    QRect tBottom(5, this->height() - 7, this->width() - 10, 7);
    QRect tTop(5, 0, this->width() - 10, 3);
    QRect tLeft(0, 3, 5, this->height() - 10);
    QRect tRight(this->width() - 5, 3, 5, this->height() - 10);
    QRect tTopLeft(0, 0, 5, 3);
    QRect tTopRight(this->width() - 5, 0, 5, 3);
    QRect tBottomLeft(0, this->height() - 7, 5, 7);
    QRect tBottomRight(this->width() - 5, this->height() - 7, 5, 7);

    painter.drawPixmap(tBottom, m_shadow, bottom);
    painter.drawPixmap(tTop, m_shadow, top);
    painter.drawPixmap(tLeft, m_shadow, left);
    painter.drawPixmap(tRight, m_shadow, right);
    painter.drawPixmap(tTopRight, m_shadow, topRight);
    painter.drawPixmap(tTopLeft, m_shadow, topLeft);
    painter.drawPixmap(tBottomLeft, m_shadow, bottomLeft);
    painter.drawPixmap(tBottomRight, m_shadow, bottomRight);

    painter.restore();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(5, 3, this->width() - 10, this->height() - 10);

    painter.restore();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(20, 150, 210));
    painter.drawRect(titleRect);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if (this->minimumHeight() >= this->maximumHeight()
            && this->minimumWidth() >= this->maximumWidth())
    {
        return QWidget::nativeEvent(eventType, message, result);
    }

    Q_UNUSED(eventType)

    MSG *param = static_cast<MSG*>(message);
    switch (param->message)
    {
    case WM_NCHITTEST:
    {
        HWND hWnd = (HWND)this->winId();
        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

        //指定标题栏区域
        if (this->childAt(nX, nY))
        {
            return false;
        }
        else
        {
            *result = HTCAPTION;
        }

        //如果窗口最大化了，则不支持resize
        if (IsZoomed(hWnd))
            return true;

        if (isMaximized())
            return true;

        if (nX > 0 && nX < this->m_shadowSize)
            *result = HTLEFT;
        if (nX > this->width() - this->m_shadowSize && nX < this->width())
            *result = HTRIGHT;
        if (nY > 0 && nY < this->m_shadowSize)
            *result = HTTOP;
        if (nY > this->height() - this->m_shadowSize && nY < this->height())
            *result = HTBOTTOM;
        if (nX > 0 && nX < this->m_shadowSize && nY > 0 && nY < this->m_shadowSize)
            *result = HTTOPLEFT;
        if (nX > this->width() - this->m_shadowSize && nX < this->width() && nY > 0 && nY < this->m_shadowSize)
            *result = HTTOPRIGHT;
        if (nX > 0 && nX < this->m_shadowSize && nY > this->height() - this->m_shadowSize && nY < this->height())
            *result = HTBOTTOMLEFT;
        if (nX > this->width() - this->m_shadowSize && nX < this->width()
                && nY > this->height() - this->m_shadowSize && nY < this->height())
            *result = HTBOTTOMRIGHT;
        return true;
    }
    }

    return false;
}

void MainWindow::treeViewCustomContextMenuRequested(const QPoint &pos)
{
    if (m_menu == NULL)
    {
        m_menu = new QMenu(this);

        QAction *expandAllAction = new QAction(m_menu);
        QAction *unExpandAllAction = new QAction(m_menu);
        expandAllAction->setText(QStringLiteral("全部展开"));
        unExpandAllAction->setText(QStringLiteral("全部折叠"));
        m_menu->addAction(expandAllAction);
        m_menu->addAction(unExpandAllAction);

        connect(expandAllAction, SIGNAL(triggered()), m_treeView, SLOT(expandAll()));
        connect(unExpandAllAction, SIGNAL(triggered()), m_treeView, SLOT(collapseAll()));
    }

    m_menu->exec(this->mapToGlobal(pos));
}
