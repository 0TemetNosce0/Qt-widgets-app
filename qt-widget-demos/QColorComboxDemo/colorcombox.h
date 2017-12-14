#ifndef COLORCOMBOX_H
#define COLORCOMBOX_H

#include <QToolButton>

class ColorCombox : public QToolButton
{
    Q_OBJECT

public:
    ColorCombox(QWidget *parent = 0);
    ~ColorCombox();

    void setButtonIcon(const QString &imageFile, QColor color);

private:
    QMenu* createColorMenu(const char *slot, const char *slotColorBoard);
    QIcon createColorToolButtonIcon(const QString &imageFile, QColor color);
    QIcon createColorIcon(QColor color);

signals:
    void sigColorChanged(QColor color);

private slots:
    void OnColorChanged();           // �ı���ɫ����
    void OnShowColorBoard();         // ��ɫ��
};

#endif // COLORCOMBOX_H
