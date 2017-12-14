#include "custommenu.h"

#include <QPainter>
#include <QContextMenuEvent>
//#include "dwmapi.h"
//#pragma comment( lib, "dwmapi.lib" )
#include <windows.h>

TestDialog::TestDialog(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet("TestDialog {background-color: #99AAC1}");
}

TestDialog::~TestDialog()
{

}

void TestDialog::contextMenuEvent(QContextMenuEvent *event)
{
    auto *menu = new CCustomMenu(this);
    auto item1 = new QAction(QIcon(":/CustomMenu/E16.png"), "&item1...", this);
    auto itme2 = new QAction("&item2...", this);
    auto item3 = new QAction("&itme3...", this);
    auto item4 = new QAction(QIcon(":/CustomMenu/E16.png"), "&item4...", this);

    menu->addAction(item1);
    menu->addAction(itme2);
    menu->addSeparator();
    auto pSubMenu = menu->addMenu(QIcon(":/CustomMenu/E16.png"), "sub menu");
    pSubMenu->addAction(item3);
    pSubMenu->addAction(item4);
    menu->exec(event->globalPos());
}


CCustomMenu::CCustomMenu(const QString &title, QWidget *parent /*= 0*/ )
    : QMenu(title, parent)
{
    init();
}

CCustomMenu::CCustomMenu(QWidget *parent /*= 0*/ )
    : QMenu(parent)
{
    init();
}

CCustomMenu::~CCustomMenu()
{

}

bool CCustomMenu::event(QEvent *event)
{
    static bool class_amended = false;

    if (event->type() == QEvent::WinIdChange)
    {
        HWND hwnd = reinterpret_cast<HWND>(winId());
        if (class_amended == false)
        {
            class_amended = true;
            DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
            class_style &= ~CS_DROPSHADOW;
            ::SetClassLong(hwnd, GCL_STYLE, class_style);
        }
        // dwn代码实现阴影, 要求vista+, 开启aero
        //DWMNCRENDERINGPOLICY val = DWMNCRP_ENABLED;
        //::DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &val, sizeof(DWMNCRENDERINGPOLICY));

        //// This will turn OFF the shadow
        //// MARGINS m = {0};
        //// This will turn ON the shadow
        //MARGINS m = {-1};
        //HRESULT hr = ::DwmExtendFrameIntoClientArea(hwnd, &m);
        //if( SUCCEEDED(hr) )
        //{
        //	//do more things
        //}
    }
    return QWidget::event(event);
}

QAction * CCustomMenu::addMenu(CCustomMenu *menu)
{
    return QMenu::addMenu(menu);
}

CCustomMenu * CCustomMenu::addMenu(const QString &title)
{
    CCustomMenu *menu = new CCustomMenu(title, this);
    addAction(menu->menuAction());
    return menu;
}

CCustomMenu * CCustomMenu::addMenu(const QIcon &icon, const QString &title)
{
    CCustomMenu *menu = new CCustomMenu(title, this);
    menu->setIcon(icon);
    addAction(menu->menuAction());
    return menu;
}

void CCustomMenu::init()
{
    // 必须设置popup, 因为QMenuPrivate::activateAction中使用QApplication::activePopupWidget()函数
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setObjectName("CustomMenu");  // 以objectname 区分Qt内置菜单和CCustomMenu
}

/*  add checkable menu item in menu
QIcon checkMenuIcon(const QPixmap& sourcePmap, QSize& iconSize)
{
    // Create and return a QIcon composed from two modified versions of
    // the given "source" QPixmap -- for ON and OFF states -- suitable for
    // checkable QActions (menu items) having an icon. [In Qt 4.8.5,
    // checkable QActions with icons don't show a drawn check indicator].
    //
    // The computed pixmaps have additional space to the left where a
    // bullet (filled black circle) is drawn on the "ON" image. This
    // appearance is intended for exclusive (radio button type)
    // QActions (menu items) -- and looks like the Cleanlooks style.
    //
    // The QSize of the computed pixmaps (including a check indicator area)
    // is returned in the iconSize reference parameter.

    const QSize srcSize = sourcePmap.size();
    const int srcWid = srcSize.width();
    const int srcHgt = srcSize.height();
    const int indWid = srcHgt; // indicator width

    iconSize = QSize (srcWid + indWid, srcHgt);
    QPixmap iconPmap (iconSize);
    iconPmap.fill (Qt::transparent);

    QPainter painter(&iconPmap);
    painter.drawPixmap(indWid, 0, sourcePmap);

    QIcon retIcon;
    retIcon.addPixmap(iconPmap, QIcon::Normal, QIcon::Off);

    const double radius(indWid / 8.0);
    const QPointF cen(indWid/2.0, srcHgt/2.0);
    painter.setBrush(QBrush(Qt::black));
    painter.drawEllipse(cen, radius, radius);

    retIcon.addPixmap(iconPmap, QIcon::Normal, QIcon::On);
    return retIcon;
}


QPixmap windowIconPixmap(const QString& iconName)
{

}

QStringList windowIconNames()
{

}

void addWindowIconActions(QMenu* menu, QActionGroup* actGrp)
{
    actGrp->setExclusive(true);
    QSize maxIconSize;

    // Create a checkable Icon QAction (menu item) for each available
    // application window icon; insert into the given QMenu and QActionGroup.

    const QStringList iconNames = windowIconNames();
    const int cnt = iconNames.count();

    for (int inx = 0; inx < cnt; ++inx)
    {
        const QString iconName = iconNames[inx];

        QSize iconSize;
        const QPixmap pmap = windowIconPixmap(iconName);
        const QIcon menuIcon = checkMenuIcon(pmap, iconSize); // SEE ABOVE
        maxIconSize = maxIconSize.expandedTo(iconSize);

        QAction* winIconAction = new QAction(actGrp);
        winIconAction -> setObjectName (iconName);
        winIconAction -> setIcon(menuIcon);
        winIconAction -> setData(QVariant (inx));
        winIconAction -> setCheckable(true);
        winIconAction -> setChecked(false);

        menu->addAction(winIconAction);
    }
}
*/
