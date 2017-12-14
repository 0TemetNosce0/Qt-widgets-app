#ifndef GCORNERTABLEVIEW_H
#define GCORNERTABLEVIEW_H

#include <QPainter>
#include <QTableView>
#include <QAbstractButton>

class GCornerTableView : public QTableView
{
    Q_OBJECT

public:
    explicit GCornerTableView(QWidget *parent = 0);
    void setCornerButtonText(const QString &text);
    void setCornerTextAlignment(Qt::Alignment align);

private:
    QString m_cornerButtonText;

    Q_DECLARE_PRIVATE(QTableView)
};


class GTableCornerButton : public QAbstractButton
{
    Q_OBJECT

public:
    GTableCornerButton(QWidget *parent = 0)
        : QAbstractButton(parent)
    {

    }

    void paintEvent(QPaintEvent*)
    {
        QStyleOptionHeader opt;
        opt.initFrom(this);
        QStyle::State state = QStyle::State_None | QStyle::State_Raised;

        if (isEnabled())
        {
            state |= QStyle::State_Enabled;
        }

        if (isActiveWindow())
        {
            state |= QStyle::State_Active;
        }

        if (isDown())
        {
            state |= QStyle::State_Sunken;
        }

        opt.state = state;
        opt.text = m_text;
        opt.rect = rect();
        opt.position = QStyleOptionHeader::OnlyOneSection;
        opt.textAlignment = m_align;
        QPainter painter(this);
        style()->drawControl(QStyle::CE_Header, &opt, &painter, this);
    }

    void setText(const QString &text) {m_text = text;}
    void setAlignment(Qt::Alignment align) {m_align = align;}

private:
    QString m_text;
    Qt::Alignment m_align;
};

#endif // GCORNERTABLEVIEW_H
