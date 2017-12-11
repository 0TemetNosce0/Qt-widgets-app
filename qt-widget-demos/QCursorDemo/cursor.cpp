#include "cursor.h"

#include <QGridLayout>

Cursor::Cursor( )
    : QDialog()
{  
    setWindowTitle(tr("Change Mouse Cursor"));
    
    PushButtonArrow = new QPushButton( );
    PushButtonArrow->setText( tr( "Arrow" ) ); 
    PushButtonArrow->setIcon(QPixmap(":/images/cursor-arrow.png"));

    PushButtonBusy = new QPushButton( );
    PushButtonBusy->setText( tr( "Busy" ) ); 
    PushButtonBusy->setIcon(QPixmap(":/images/cursor-busy.png"));
    
    PushButtonClosedHand = new QPushButton( );
    PushButtonClosedHand->setText( tr( "ClosedHand" ) );     
	PushButtonClosedHand->setIcon(QPixmap(":/images/cursor-closedhand.png"));
	
    PushButtonCross = new QPushButton( );
    PushButtonCross->setText( tr( "Cross" ) ); 
    PushButtonCross->setIcon(QPixmap(":/images/cursor-cross.png"));
    
    PushButtonForbidden = new QPushButton( );
    PushButtonForbidden->setText( tr( "Forbidden" ) );         
    PushButtonForbidden->setIcon(QPixmap(":/images/cursor-forbidden.png"));
    
    PushButtonHand = new QPushButton( );
    PushButtonHand->setText( tr( "Hand" ) ); 
    PushButtonHand->setIcon(QPixmap(":/images/cursor-hand.png"));
    
    PushButtonHSplit = new QPushButton( );
    PushButtonHSplit->setText( tr( "HSplit" ) ); 
    PushButtonHSplit->setIcon(QPixmap(":/images/cursor-hsplit.png"));
    
    PushButtonIbeam = new QPushButton( );
    PushButtonIbeam->setText( tr( "Ibeam" ) ); 
    PushButtonIbeam->setIcon(QPixmap(":/images/cursor-ibeam.png"));
    
    PushButtonOpenHand = new QPushButton( );
    PushButtonOpenHand->setText( tr( "OpenHand" ) ); 
    PushButtonOpenHand->setIcon(QPixmap(":/images/cursor-openhand.png"));
    
    PushButtonSizeAll = new QPushButton( );
    PushButtonSizeAll->setText( tr( "SizeAll" ) ); 
    PushButtonSizeAll->setIcon(QPixmap(":/images/cursor-sizeall.png"));
    
    PushButtonSizeB = new QPushButton( );
    PushButtonSizeB->setText( tr( "SizeB" ) ); 
    PushButtonSizeB->setIcon(QPixmap(":/images/cursor-sizeb.png"));
    
    PushButtonSizeF = new QPushButton( );
    PushButtonSizeF->setText( tr( "SizeF" ) ); 
    PushButtonSizeF->setIcon(QPixmap(":/images/cursor-sizef.png"));
    
    PushButtonSizeH = new QPushButton( );
    PushButtonSizeH->setText( tr( "SizeH" ) ); 
    PushButtonSizeH->setIcon(QPixmap(":/images/cursor-sizeh.png"));
    
    PushButtonSizeV = new QPushButton( );
    PushButtonSizeV->setText( tr( "SizeV" ) ); 
    PushButtonSizeV->setIcon(QPixmap(":/images/cursor-sizev.png"));
    
    PushButtonUpArrow = new QPushButton( );
    PushButtonUpArrow->setText( tr( "UpArrow" ) ); 
    PushButtonUpArrow->setIcon(QPixmap(":/images/cursor-uparrow.png"));
    
    PushButtonVSplit = new QPushButton( );
    PushButtonVSplit->setText( tr( "VSplit" ) ); 
    PushButtonVSplit->setIcon(QPixmap(":/images/cursor-vsplit.png"));
    
    PushButtonWait = new QPushButton( );
    PushButtonWait->setText( tr( "Wait" ) ); 
    PushButtonWait->setIcon(QPixmap(":/images/cursor-wait.png"));
    
    PushButtonWhatsThis = new QPushButton( );
    PushButtonWhatsThis->setText( tr( "WhatsThis" ) );  
    PushButtonWhatsThis->setIcon(QPixmap(":/images/cursor-whatsthis.png"));

    PushButtonBlank = new QPushButton( );
    PushButtonBlank->setText( tr( "Blank" ) );

    PushButtonCustom = new QPushButton( );
    PushButtonCustom->setText( tr( "Custom" ) );  
    
    QGridLayout* layout = new QGridLayout( this );  
    layout->addWidget( PushButtonArrow, 0, 0 );	
    layout->addWidget( PushButtonBusy, 0, 1 );
    layout->addWidget( PushButtonClosedHand, 0, 2 );
    layout->addWidget( PushButtonCross, 1, 0 );
    layout->addWidget( PushButtonForbidden, 1, 1 );
    layout->addWidget( PushButtonHand, 1, 2 );
    layout->addWidget( PushButtonHSplit, 2, 0 );	
    layout->addWidget( PushButtonIbeam, 2, 1 );
    layout->addWidget( PushButtonOpenHand, 2, 2 );
    layout->addWidget( PushButtonSizeAll, 3, 0 );
    layout->addWidget( PushButtonSizeB, 3, 1 );
    layout->addWidget( PushButtonSizeF, 3, 2 );
    layout->addWidget( PushButtonSizeH, 4, 0 );	
    layout->addWidget( PushButtonSizeV, 4, 1 );
    layout->addWidget( PushButtonUpArrow, 4, 2 );
    layout->addWidget( PushButtonVSplit, 5, 0 );
    layout->addWidget( PushButtonWait, 5, 1 );
    layout->addWidget( PushButtonWhatsThis, 5, 2 );
    layout->addWidget( PushButtonBlank, 6, 0);
    layout->addWidget( PushButtonCustom,7, 0, 1, 3 );
        
    layout->setMargin(15);
    layout->setSpacing(10);                
    
    connect(PushButtonArrow,SIGNAL(clicked()),this,SLOT(slotArrow())); 
    connect(PushButtonBusy,SIGNAL(clicked()),this,SLOT(slotBusy())); 
    connect(PushButtonClosedHand,SIGNAL(clicked()),this,SLOT(slotCloseHand())); 
    connect(PushButtonCross,SIGNAL(clicked()),this,SLOT(slotCross())); 
    connect(PushButtonForbidden,SIGNAL(clicked()),this,SLOT(slotForbidden())); 
    connect(PushButtonHand,SIGNAL(clicked()),this,SLOT(slotHand())); 
    connect(PushButtonHSplit,SIGNAL(clicked()),this,SLOT(slotHSplit())); 
    connect(PushButtonIbeam,SIGNAL(clicked()),this,SLOT(slotIbeam())); 
    connect(PushButtonOpenHand,SIGNAL(clicked()),this,SLOT(slotOpenHand())); 
    connect(PushButtonSizeAll,SIGNAL(clicked()),this,SLOT(slotSizeAll())); 
    connect(PushButtonSizeB,SIGNAL(clicked()),this,SLOT(slotSizeB())); 
    connect(PushButtonSizeF,SIGNAL(clicked()),this,SLOT(slotSizeF())); 
    connect(PushButtonSizeH,SIGNAL(clicked()),this,SLOT(slotSizeH())); 
    connect(PushButtonSizeV,SIGNAL(clicked()),this,SLOT(slotSizeV())); 
    connect(PushButtonUpArrow,SIGNAL(clicked()),this,SLOT(slotUpArrow())); 
    connect(PushButtonVSplit,SIGNAL(clicked()),this,SLOT(slotVSplit())); 
    connect(PushButtonWait,SIGNAL(clicked()),this,SLOT(slotWait())); 
    connect(PushButtonWhatsThis,SIGNAL(clicked()),this,SLOT(slotWhatsThis()));                                               
    connect(PushButtonBlank,SIGNAL(clicked()),this,SLOT(slotBlank()));
    connect(PushButtonCustom,SIGNAL(clicked()),this,SLOT(slotCustom()));
}

Cursor::~Cursor()
{

}

void Cursor::slotArrow()
{
    setCursor(Qt::ArrowCursor);
}
void Cursor::slotBusy()
{
	setCursor(Qt::BusyCursor);
}
void Cursor::slotCloseHand()
{
	setCursor(Qt::ClosedHandCursor);
}
void Cursor::slotCross()
{
	setCursor(Qt::CrossCursor);
}
void Cursor::slotForbidden()
{
	setCursor(Qt::ForbiddenCursor);
}
void Cursor::slotHand()
{
	setCursor(Qt::PointingHandCursor);
}
void Cursor::slotHSplit()
{
	setCursor(Qt::SplitHCursor);
}
void Cursor::slotIbeam()
{
	setCursor(Qt::IBeamCursor);
}
void Cursor::slotOpenHand()
{
	setCursor(Qt::OpenHandCursor);
}
void Cursor::slotSizeAll()
{
	setCursor(Qt::SizeAllCursor);
}
void Cursor::slotSizeB()
{
	setCursor(Qt::SizeBDiagCursor);
}
void Cursor::slotSizeF()
{
	setCursor(Qt::SizeFDiagCursor);
}
void Cursor::slotSizeH()
{
	setCursor(Qt::SizeHorCursor);
}
void Cursor::slotSizeV()
{
	setCursor(Qt::SizeVerCursor);
}
void Cursor::slotUpArrow()
{
	setCursor(Qt::UpArrowCursor);
}
void Cursor::slotVSplit()
{
	setCursor(Qt::SplitVCursor);
}
void Cursor::slotWait()
{
	setCursor(Qt::WaitCursor);
}

void Cursor::slotWhatsThis()
{
    setCursor(Qt::WhatsThisCursor);
}

void Cursor::slotBlank()
{
    setCursor(Qt::BlankCursor);
}

void Cursor::slotCustom()
{
    QCursor *myCursor= new QCursor(QPixmap(":/images/cursor-self.png"),-1,-1);
	setCursor(*myCursor);
}
