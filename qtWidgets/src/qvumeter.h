#ifndef __qvumeter_h_INCLUDED__
#define __qvumeter_h_INCLUDED__

#include <QObject>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QString>
#include <QWidget>


// a simple VU-meter (AKA volume visualizer) control
// it has 2 states: active and dimmed -- useful for indicating listening vs. not-listenting modes
// it has 3 adjustable color ranges: green (bottom), yellow (middle) and red (high)
// user clicking on it sets the "selection" level -- useful for user-adjustable threshold value

class QVUMeter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(float minimum READ minimum WRITE setMinimum NOTIFY rangeChanged)
    Q_PROPERTY(float maximum READ maximum WRITE setMaximum NOTIFY rangeChanged)
    Q_PROPERTY(float selection READ selection WRITE setSelection NOTIFY selectionChanged)
    Q_PROPERTY(bool dimmed READ dimmed WRITE setDimmed NOTIFY dimmedChanged)

public:
    QVUMeter(QWidget *parent = NULL);
    float value();
    float minimum();
    float maximum();
    float selection();
    bool dimmed();

public Q_SLOTS:
    void setValue(float val);
    void setMinimum(float m);
    void setMaximum(float m);
    void setRange(float min, float max);
    void setThresholds(float yellow, float red);
    void setSelection(float val);
    void setDimmed(bool dimmed);

Q_SIGNALS:
    void valueChanged(float);
    void rangeChanged(float min, float max);
    void thresholdsChanged(float yellow, float red);
    void selectionChanged(float);
    void dimmedChanged(bool);

protected:
    void init();
    void mouseMoveEvent(QMouseEvent *pEvent); // Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *pEvent); // Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *pEvent); // Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event); // Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event); // Q_DECL_OVERRIDE;

private:
    float _value, _peak, _selection;
    float _min, _yellowStep, _redStep, _max;
    unsigned _tickSize;
    bool _selectable;
    bool _showSelection;
    bool _dimmed;
    QBasicTimer _timer;
};

#endif // __qvumeter_h_INCLUDED__
