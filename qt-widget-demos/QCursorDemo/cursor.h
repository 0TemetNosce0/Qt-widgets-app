#ifndef CURSOR_H
#define CURSOR_H

#include <QPushButton>
#include <QDialog>

class Cursor : public QDialog
{
    Q_OBJECT
public:
    Cursor();
    ~Cursor();
private:    
    QPushButton* PushButtonArrow;
    QPushButton* PushButtonBusy;
    QPushButton* PushButtonClosedHand;
    QPushButton* PushButtonCross;
    QPushButton* PushButtonForbidden;
    QPushButton* PushButtonHand;
    QPushButton* PushButtonHSplit;
    QPushButton* PushButtonIbeam;
    QPushButton* PushButtonOpenHand;
    QPushButton* PushButtonSizeAll;
    QPushButton* PushButtonSizeB;  
    QPushButton* PushButtonSizeF;
    QPushButton* PushButtonSizeH;
    QPushButton* PushButtonSizeV;
    QPushButton* PushButtonUpArrow;
    QPushButton* PushButtonVSplit;
    QPushButton* PushButtonWait;
    QPushButton* PushButtonWhatsThis;
    QPushButton* PushButtonBlank;
    QPushButton* PushButtonCustom;                     
private slots:
	void slotArrow();
	void slotBusy();
	void slotCloseHand();
	void slotCross();
	void slotForbidden();
	void slotHand();
	void slotHSplit();
	void slotIbeam();
	void slotOpenHand();
	void slotSizeAll();
	void slotSizeB();
	void slotSizeF();
	void slotSizeH();
	void slotSizeV();
	void slotUpArrow();
	void slotVSplit();
	void slotWait();
	void slotWhatsThis();
    void slotBlank();
	void slotCustom();

};


#endif // CURSOR_H
