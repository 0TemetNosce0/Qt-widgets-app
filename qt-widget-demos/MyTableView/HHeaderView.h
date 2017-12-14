#ifndef HHEADERVIEW_H
#define HHEADERVIEW_H

#include <QHeaderView>

class  HHeaderModel;

struct ItemState
{
    bool _isChecked;
    Qt::CheckState _checkedState; //0:unchecked 1:PartiallyChecked 2:Checked

    bool _isSorted;
    int _sortedDirection; //0:up 1:down 2:unSorted

    bool _isCustomMenu;
    int _menuEnabled; //0: unEnable 1: enable

    ItemState()
    {
        _isChecked = false;
        _checkedState = Qt::Unchecked;
        _isSorted = false;
        _sortedDirection = 2;
        _isCustomMenu = false;
        _menuEnabled = 0;
    }
};

class HHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    HHeaderView(Qt::Orientation orientation, QWidget * parent = 0);
    ~HHeaderView();
    static HHeaderView* m_Instance;

    int sectionSizes(int lIndex, int sectionCount);
    
    //算出当前鼠标位置所在的index
    QModelIndex indexAt(const QPoint &pos) const;

    //设置支持checked
    void setCheckedEnable(int row, int col, bool Flag = true);
    bool isCheckedEnable(int row, int col);
    void setCheckedState(int row, int col, Qt::CheckState state);
    Qt::CheckState checkedState(int row, int col);

    //设置是否支持排序
    void setSortedEnable(int row, int col, bool Flag = true);
    bool isSortedEnable(int row, int col);
    void setSortedDirection(int row, int col, int direction);
    int sortedDirection(int row, int col);

    //设置是否支持自定义menu
    void setCustomMenuEnbale(int row, int col, bool Flag = true);
    bool isCustomMenuEnable(int row, int col);
    void setCustomMenuState(int row, int col, int state);
    int customMenuState(int row, int col);

    //判断该列是否隐藏
    bool isColHide(int col);

    //判断该单元格是否按住
    bool isItemPress(int row, int col);

    //重设最后一列的宽度，在tree收缩时加1，伸展时减1。实质上是想通过列的resize函数引起整个水平头的位置更新。
    //不通过这样的处理，在tree的伸展收缩或者整个界面隐藏和展示时会水平头的位置不正确。
    void resizeLastSection(bool increase);

public slots:
    void onSectionResized(int logicalIndex, int oldSize, int newSize);

protected:
    virtual QSize sectionSizeFromContents(int logicalIndex) const;
    virtual void paintEvent(QPaintEvent *event);
    //virtual int sectionSizeHint(int logicalIndex); 

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual bool event ( QEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent(QMouseEvent *event);

    //virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

private:
    //自定义菜单rect
    QRect menuRect(int row, int col);
    //隐藏前一列的icon的rect
    QRect prevRect(int row, int col);
     //隐藏后一列的icon的rect
    QRect nextRect(int row, int col);

    void sortUp(int row, int col);
    void sortDown(int row, int col);

private:
    QModelIndex m_hoverIndex;

    QModelIndex m_pressIndex; //保存按下的列

    //保存所有item的矩形 key:row  key1:col
    QMap<int, QMap<int, QRect> > m_itemRectMap;

    //保存每个item能支持的style
    QMap<int, QMap<int, ItemState> > m_itemStateMap;

    QSet<int> m_hideColSet; //保存隐藏列的记录

private:
    QMenu* m_menu;
    QAction* m_actHideCol; //隐藏列
    QAction* m_actsortUp;  //升序
    QAction* m_actSortDown; //降序
};

#endif // HHEADERVIEW_H
