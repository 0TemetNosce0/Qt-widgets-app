#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QList>
#include <QRect>
#include <QWidget>
#include <QPainterPath>

#define DEF_CODECOUNT       4            // ��֤��Ĭ��λ��

#define DEF_NOISYPOINTCOUNT 60           // �������
#define DEF_CONVERSEROTATE  10           // ת���Ƕȷ�Χ
#define DEF_CONVERSESCALE   15           // ת����С��Χ

class CodeArea : public QWidget
{
    Q_OBJECT

public:
    CodeArea(QWidget *parent = 0);
    ~CodeArea();

    /**
     * @brief ������֤��ͼƬ
     */
    void replaceCodePic();

    /**
     * @brief ������֤��λ��
     * @param nCodeCount
     */
    void setCodeCount(int nCodeCount);

    /**
     * @brief �����������
     * @param nNoisyPointCount
     */
    void setNoisyPointCount(int nNoisyPointCount);

    /**
     * @brief ������֤��
     * @param sCode
     * @return
     */
    bool checkCode(QString sCode);

protected:
    void paintEvent(QPaintEvent *event);

private:

    /**
     * @brief ��ʼ����֤�뷶Χ
     */
    inline void initCodeRange();

    /**
     * @brief ��ʼ����֤�������ɫ�б�
     */
    inline void initCodeColorList();

    /**
     * @brief ������֤��
     */
    inline void updateLoginCode();

    /**
     * @brief ������֤��ͼƬ
     */
    inline void updateCodePic();

    /**
     * @brief �����������û��������֤�����Ƚϵ���
     */
    inline void updateCode();

    /**
     * @brief ���Ʊ�Ե���߿�
     * @param painter
     */
    inline void drawOutline(QPainter &painter);

    /**
     * @brief ������֤��
     * @param painter
     * @param nCodeIndex
     */
    inline void drawCode(QPainter &painter, int nCodeIndex);

    /**
     * @brief �������
     * @param painter
     */
    inline void drawNoisyPoint(QPainter &painter);

    /**
     * @brief ����֤����̬ת��
     * @param painter
     */
    inline void drawConversion(QPainter &painter);

    /**
     * @brief ������֤��ͼƬ
     * @param lCodePic
     */
    inline void setCodePic(const QList<QPainterPath *> &lCodePic);

private:
    QString m_sCode;                            // �������û��������֤�����Ƚϵ���
    QStringList m_slCodeRange;                  // ��֤�����ɷ�Χ
    QStringList m_slLoginCode;                  // ��֤���б�����������֤��ͼƬ
    QPainterPath *m_pCodePic;                   // ����λ����֤��ͼƬ
    QList<QPainterPath *> m_lCodePic;           // ��֤��ͼƬ
    QList<Qt::GlobalColor> m_lCodeColor;        // ��֤�������ɫ�б�

    int m_nNoisyPointCount;
    int m_nConverseRotate;
    int m_nConverseScale;
    int m_nCodeCount;
};

#endif // RENDERAREA_H
