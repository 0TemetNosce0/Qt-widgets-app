#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class Label : public QLabel
{
	Q_OBJECT

public:
	Label(const QString& text, QWidget *parent);
	~Label();

protected:
	void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent * event);

private:

};
#endif // LABEL_H