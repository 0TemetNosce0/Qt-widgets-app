#ifndef COMPONENT_1_H
#define COMPONENT_1_H

#include <QDialog>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

#define CM_TITLE_HEIGHT         30             //ԭ���������߶�

#define DEFAULT_BORDER_WIDTH    5              //�߽���
#define DEFAULT_MAGNETIC_OFFSET 20             //����Ч����Χ
#define DEFAULT_ERROR_RANGE     6              //���������Χ
#define DEFAULT_TOOLBAR_WIDTH   80             //��������ToolBar���
#define DEFAULT_STATUS_HEIGHT   29             //��������StatusBar�߶�

namespace Ui {
class Component;
}

class Component : public QWidget
{
    Q_OBJECT

public:
    explicit Component(const int nComponentId, QWidget *parent = 0);
    ~Component();

    /**
     * @brief ����ԭ���ı߽���
     * @param nBorderWidth
     */
    void setBorderWidth(int nBorderWidth);

    /**
     * @brief ���ô���ЧӦӰ�췶Χ
     * @param nMagneticOffset
     */
    void setMagneticOffset(int nMagneticOffset);

    /**
     * @brief ���ô���ЧӦ����������Χ
     * @param nErrorRange
     */
    void setErrorRange(int nErrorRange);

    /**
     * @brief ������������ToolBar���
     * @param nToolBarWidth
     */
    void setToolBarWidth(int nToolBarWidth);

    /**
     * @brief ������������StatusBar���
     * @param nStatusBarHeight
     */
    void setStatusBarHeight(int nStatusBarHeight);

signals:
    /**
     * @brief ԭ���ر��ź�
     * @param nMyComponentId
     */
    void onComponentClose(int nMyComponentId);

protected:
    bool event(QEvent* evt);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    /**
     * @brief �������resizeʱ����ʽ
     * @param pt
     */
    void setMouseResizeCursor(const QPoint& pt);

private:

    /**
     * @brief ��ʼ������
     */
    inline void initComponent();

    /**
     * @brief ������갴��������������
     * @param event
     */
    inline void updateMousePressedData(QMouseEvent *event);

    /**
     * @brief ��������-���ڱ߿�
     * @param event
     */
    inline void updateDataOnBorder(QMouseEvent *event);

    /**
     * @brief ��������-���ڱ�����
     * @param event
     */
    inline void updateDataOnTitleBar(QMouseEvent *event);

    /**
     * @brief ������������ƶ�������
     */
    inline void updateMouseLeftLimit();

    /**
     * @brief ��������ƶ�����
     */
    inline void limitMouseArea();

    /**
     * @brief ������ק���
     * @param event
     */
    inline void resetDragData(QMouseEvent *event);

    /**
     * @brief ��С�߽���ж��봦��---ԭ��
     * @param parentRect
     * @param bechmarkRect
     * @param targetRect
     * @param event
     */
    inline void minBoundaryToComponent(const QRect &parentRect, const QRect &bechmarkRect, const QRect &targetRect, QMouseEvent *event);

    /**
     * @brief ��С�߽���ж��봦��---����
     * @param bechmarkRect
     * @param targetRect
     * @param event
     */
    inline void minBoundaryToVessel(const QRect &bechmarkRect, const QRect &targetRect, QMouseEvent *event);

    /**
     * @brief �ж���갴��ʱ�����Ƿ��ڱ߿�
     * @param pt
     * @return
     */
    inline bool mouseOnWinBorder(const QPoint& pt);

    /**
     * @brief �ı�ԭ����С
     * @param evt
     */
    inline void changeSize(QMouseEvent* evt);

    /**
     * @brief ����ı����С��͸�
     * @param sizeHint
     * @param minSizeHint
     * @param minSize
     * @param maxSize
     * @param sizePolicy
     * @return
     */
    inline QSize calcMinSize(const QSize &sizeHint, const QSize &minSizeHint,
        const QSize &minSize, const QSize &maxSize,
        const QSizePolicy &sizePolicy);

    inline QRect leftBorder() const;
    inline QRect rightBorder() const;
    inline QRect topBorder() const;
    inline QRect bottomBorder() const;

private slots:

    /**
     * @brief �ر�ԭ����ť��
     */
    void on_btnClose_clicked();

private:
    Ui::Component *ui;

    const int m_nMyComponentId;
    int m_nTitleHeight;              //ԭ���������߶�
    int m_nBorderWidth;              //�߽���
    int m_nMagneticOffset;           //����Ч����Χ
    int m_nErrorRange;               //���������Χ
    int m_nToolBarWidth;             //��������ToolBar���
    int m_nStatusBarHeight;          //��������StatusBar�߶�
    int m_nMoveCount;

    bool m_bMousePressedInTitle;
    bool m_bMousePressedInBorder;

    bool m_bHorRelatived;
    bool m_bVerRelatived;

    bool m_bHorStick_s;
    bool m_bVerStick_s;
    bool m_bHorStick_c;
    bool m_bVerStick_c;

    QPoint m_pDragPosition;                 // �ڴ��ڱ�����갴��ʱ����Ļ����λ��
    QPoint m_pDragMoveOffset;               // ��¼��갴��ʱ�봰�����½ǵ�ƫ������
    QPoint m_qpMousePressPoint;             // ��갴��ʱ��λ��
    QPoint m_qpDiffPos;                     // ����ƶ�ʱ������ƫ������

    QRect m_rParentRect;                    // ��������geometry
    QRect m_rMouseLimitRect;                // �����קʱ�����ƶ�������

    QList<Component*> m_lComponent;         // ��ȡ���������е�ԭ����ͼ�б�

    enum MousePosition
    {
        mpCenter, mpLeft, mpTop, mpRight, mpBottom,
        mpLeftTop, mpLeftBottom, mpRightTop, mpRightBottom
    };

    MousePosition m_eMousePos;
};

#endif // COMPONENT_1_H
