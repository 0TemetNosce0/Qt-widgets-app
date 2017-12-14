#ifndef IMSIMAGELINEEDIT_H
#define IMSIMAGELINEEDIT_H


#include <QLineEdit>

class QLabel;
class ImsImageLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	explicit ImsImageLineEdit(QWidget *parent = 0);  
	explicit ImsImageLineEdit(const QString & contents, QWidget *parent = 0);  
	explicit ImsImageLineEdit(const QString & contents, const QString & pic,QWidget *parent = 0);  
	virtual ~ImsImageLineEdit();

	void setLabelPic(const QString strPic); 
signals:  
	void imageLabelClicked();  
protected:
	void init();
	void changeLabelPosition();
protected: 	
	virtual void resizeEvent(QResizeEvent *event);	
	virtual bool eventFilter(QObject *obj, QEvent *e);
private:
	QString mImagePath;
	QLabel *mImageLabel;
};

#endif // IMSIMAGELINEEDIT_H
