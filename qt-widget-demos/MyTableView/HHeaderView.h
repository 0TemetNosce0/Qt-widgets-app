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
    
    //�����ǰ���λ�����ڵ�index
    QModelIndex indexAt(const QPoint &pos) const;

    //����֧��checked
    void setCheckedEnable(int row, int col, bool Flag = true);
    bool isCheckedEnable(int row, int col);
    void setCheckedState(int row, int col, Qt::CheckState state);
    Qt::CheckState checkedState(int row, int col);

    //�����Ƿ�֧������
    void setSortedEnable(int row, int col, bool Flag = true);
    bool isSortedEnable(int row, int col);
    void setSortedDirection(int row, int col, int direction);
    int sortedDirection(int row, int col);

    //�����Ƿ�֧���Զ���menu
    void setCustomMenuEnbale(int row, int col, bool Flag = true);
    bool isCustomMenuEnable(int row, int col);
    void setCustomMenuState(int row, int col, int state);
    int customMenuState(int row, int col);

    //�жϸ����Ƿ�����
    bool isColHide(int col);

    //�жϸõ�Ԫ���Ƿ�ס
    bool isItemPress(int row, int col);

    //�������һ�еĿ�ȣ���tree����ʱ��1����չʱ��1��ʵ��������ͨ���е�resize������������ˮƽͷ��λ�ø��¡�
    //��ͨ�������Ĵ�����tree����չ�������������������غ�չʾʱ��ˮƽͷ��λ�ò���ȷ��
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
    //�Զ���˵�rect
    QRect menuRect(int row, int col);
    //����ǰһ�е�icon��rect
    QRect prevRect(int row, int col);
     //���غ�һ�е�icon��rect
    QRect nextRect(int row, int col);

    void sortUp(int row, int col);
    void sortDown(int row, int col);

private:
    QModelIndex m_hoverIndex;

    QModelIndex m_pressIndex; //���水�µ���

    //��������item�ľ��� key:row  key1:col
    QMap<int, QMap<int, QRect> > m_itemRectMap;

    //����ÿ��item��֧�ֵ�style
    QMap<int, QMap<int, ItemState> > m_itemStateMap;

    QSet<int> m_hideColSet; //���������еļ�¼

private:
    QMenu* m_menu;
    QAction* m_actHideCol; //������
    QAction* m_actsortUp;  //����
    QAction* m_actSortDown; //����
};

#endif // HHEADERVIEW_H
