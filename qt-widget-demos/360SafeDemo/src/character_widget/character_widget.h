#ifndef PREVIEW360_H
#define PREVIEW360_H

#include "../common.h"
#include "../clabel/clabel.h"
#include "../push_button/push_button.h"

class CharacterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterWidget(QWidget *parent = 0);
    ~CharacterWidget();
    void translateLanguage();

    enum EButtonMouseState
    {
        EButtonMouseDefault = 0,
        EButtonMouseEnter,
        EButtonMousePress,
        EButtonMouseNone
    };

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private slots:
    void changeCurrentPage(CLabel *);

private:
    void changeCurrentButton();
    void setLabelMove(bool);
    void moveCurrentPage(bool);

    QStringList name_list;
    QPoint m_mouseSrcPos;
    QPoint m_mouseDstPos;
    int current_pos_x;
    bool mouse_press;
    bool mouse_move;
    bool label_move;

    QLabel *background_label; //����ͼƬ
    int current_index;        //��ǰͼƬ�±�
    QLabel *total_label;      //ͼƬ������壩
    CLabel *label_array[4];   //�洢ͼƬ������
    PushButton *close_button; //�رհ�ť
};

#endif // PREVIEW360_H
