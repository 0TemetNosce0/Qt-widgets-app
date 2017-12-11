#ifndef LABELBTN_H
#define LABELBTN_H

#include <QLabel>

class QMovie;

class LabelBtn : public QLabel
{
	Q_OBJECT

public:
	LabelBtn(const QString& pngFile,const QString& soundFile,QWidget *parent);
	~LabelBtn();

protected:
	void mousePressEvent(QMouseEvent* event);

signals:
	void clicked();

private slots:
    void onClicked();

private:
	QString		m_SoundFile;

};

#endif // LABELBTN_H
