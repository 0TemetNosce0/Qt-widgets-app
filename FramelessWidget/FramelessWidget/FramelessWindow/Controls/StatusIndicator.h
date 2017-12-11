#ifndef STATUSINDICATOR_H
#define STATUSINDICATOR_H

#include <QAbstractButton>
#include <QList>

class CStatusIndicator : public QAbstractButton
{
    Q_OBJECT

public:
    CStatusIndicator(QWidget *parent = nullptr);
    ~CStatusIndicator();
    enum IndicateMode{
        CheckedMode,
        StatusMode
    };

    void setIndicateMode(IndicateMode mode);
    void addStatus(QString strStatus, QColor color);
    void setInnerFactor(double factor);
    void setCheckable(bool);
    void setChecked(bool checked);
    bool isChecked();

public slots:
    void setCurrentStatus(QString strStatus);

signals:
    void statusChanged(QString strStatus);

public:
    QSize sizeHint();
    QSize minimumSizeHint();

protected:
    void paintEvent(QPaintEvent *);

private:
    void initMembers();

private:
    IndicateMode mo_mode;
    QString mo_strCurrentStatus;
    QStringList mo_strlstStatus;
    QList<QColor> mo_lstColor;
    double mo_dblFactor;
    bool mo_blChecked;
};

#endif // STATUSINDICATOR_H
