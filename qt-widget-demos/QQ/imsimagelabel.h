#ifndef IMSIMAGELABEL_H
#define IMSIMAGELABEL_H

#include <QLabel>

class QToolButton;
class ImsImageLabel : public QLabel
{
	Q_OBJECT

public:
	ImsImageLabel ( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	ImsImageLabel ( const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~ImsImageLabel();

	quint32 currentState(){return mCurrentState;}
protected:
	void init();
protected slots:
	void doToolButton();
	void doActionState();
private:	
	QToolButton *mToolButton;
	unsigned int mCurrentState;
};

#endif // IMSIMAGELABEL_H
