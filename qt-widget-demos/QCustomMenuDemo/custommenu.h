#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QMenu>
#include <QWidget>

class TestDialog  : public QWidget
{
    Q_OBJECT

public:
    explicit TestDialog (QWidget *parent = 0);
    ~TestDialog ();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
};

/**
 * @brief 定制化的QMenu
 */
class CCustomMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CCustomMenu(const QString &title, QWidget *parent = 0);
    explicit CCustomMenu(QWidget *parent = 0);

    ~CCustomMenu();

    /**
     * @brief 重写QMenu::addmenu
     * @param menu
     * @return
     */
    QAction *addMenu(CCustomMenu *menu);
    CCustomMenu *addMenu(const QString &title);
    CCustomMenu *addMenu(const QIcon &icon, const QString &title);

protected:
    bool event(QEvent *event);

private:
    void init();
};

#endif // CUSTOMMENU_H
