#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
class PaintArea : public QWidget
{
public:
    PaintArea();
    void setImageSize(int width,int height);
    void setImageColor(QColor color);

    bool isModified() const { return modified; }  //�жϻ��������Ƿ񱻸��Ĺ�
    bool saveImage(const QString &fileName, const char *fileFormat); //����ͼƬ
    bool openImage(const QString &fileName);  //��ͼƬ

    QSize getImageSize();
    void doPrint();

    void zoomIn();    //�Ŵ�
    void zoomOut();   //��С
    void zoom_1();    //��ԭ
    void doRotate();   //��ת
    void doShear();    //����
    void doClear();    //���

    void setPenStyle(Qt::PenStyle style); //���û��ʷ��
    void setPenWidth(int width);   //���û��ʿ��
    void setPenColor(QColor color);   //���û�����ɫ
    void setBrushColor(QColor color);   //���������ɫ

    enum ShapeType   //ö�ٱ���������ͼ�ε�ѡ��
    {
        None,     //û��ͼ��
        Line,     //ֱ��
        Rectangle,    //����
        Ellipse    //��Բ
    };
    void setShape(ShapeType shape);  //����Ҫ���Ƶ�ͼ��

protected:
    void paintEvent(QPaintEvent *);   //�ػ��¼�
    void mousePressEvent(QMouseEvent *);  //��갴���¼�
    void mouseMoveEvent(QMouseEvent *);   //����ƶ��¼�
    void mouseReleaseEvent(QMouseEvent *);   //����ͷ��¼�

    void paint(QImage& theImage);   //���л���
private:
    QImage image;    //QImage��������������ϻ�ͼ
    QRgb backColor;  //QRgb��ɫ���󣬴洢image�ı���ɫ

    QPoint lastPoint,endPoint; //��������������������ָ���ǰ����������
    bool modified;   //��־�����Ƿ񱻸��Ĺ�

    qreal scale;   //������
    int angle;     //�Ƕ�
    qreal shear;   //������

    QColor penColor;    //������ɫ
    QColor brushColor;   //�����ɫ
    int penWidth;     //���ʿ��
    Qt::PenStyle penStyle;    //���ʷ��

    ShapeType curShape;    //��ǰͼ��

    QImage tempImage;   //��ʱ��ͼ��
    bool isDrawing;     //�Ƿ��ڻ�������ͼ��
};
#endif // PAINTAREA_H
