#include <QPushButton>
#include <QStyleOptionButton>

class QDockSideButton : public QPushButton
{
public:
    QDockSideButton(QWidget* parent = 0);
    QDockSideButton(const QString& text, QWidget* parent = 0);
    QDockSideButton(const QIcon& icon, const QString& text, QWidget* parent = 0);
    ~QDockSideButton();

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    bool mirrored() const;
    void setMirrored(bool mirrored);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    QStyleOptionButton getStyleOption() const;
    void init();

    Qt::Orientation orientation_;
    bool mirrored_;
};
