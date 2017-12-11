#include "ColorPopup.h"
#include "ColorGrid.h"

ColorPopup::ColorPopup(ColorGrid *grid)
    : QFrame(0, Qt::Popup)
    , m_grid(0)
{
	setAttribute(Qt::WA_WindowPropagation);
    setAttribute(Qt::WA_DeleteOnClose);

    //m_oldParent = m_grid->parentWidget();
	//m_grid->setParent(this);

    m_grid = new ColorGrid(this);
    m_grid->setClickMode(ColorGrid::CM_RELEASE);
    if (grid)
    {
		m_grid->setCellSize(grid->cellSize());
		m_grid->setWidthInCells(grid->widthInCells());
		m_grid->setPickByDrag(grid->pickByDrag());
		m_grid->setScheme(grid->scheme());
	}

	m_grid->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    m_vbl = new QVBoxLayout(this);
	m_vbl->setMargin(0);
	m_vbl->setSpacing(0);
    m_vbl->addWidget(m_grid);

    connect(m_grid, SIGNAL(picked(const QColor &)), this, SIGNAL(picked(const QColor&)));
    connect(m_grid, SIGNAL(accepted()), this, SLOT(close()));
    connect(m_grid, SIGNAL(rejected()), this, SLOT(close()));
}

ColorPopup::~ColorPopup()
{
    //m_vbl->removeWidget(m_grid);
    //m_grid->setParent(m_oldParent);
}

void ColorPopup::show(const QPoint &point)
{
    move(point);
	setFixedSize(m_grid->minimumSizeHint());
    QFrame::show();
}

