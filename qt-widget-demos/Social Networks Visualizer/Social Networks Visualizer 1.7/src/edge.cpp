/***************************************************************************
 SocNetV: Social Network Visualizer
 version: 1.7
 Written in Qt

                        edge.cpp  -  description
                             -------------------
    copyright            : (C) 2005-2015 by Dimitris B. Kalamaras
    email                : dimitris.kalamaras@gmail.com
 ***************************************************************************/

/*******************************************************************************
*     This program is free software: you can redistribute it and/or modify     *
*     it under the terms of the GNU General Public License as published by     *
*     the Free Software Foundation, either version 3 of the License, or        *
*     (at your option) any later version.                                      *
*                                                                              *
*     This program is distributed in the hope that it will be useful,          *
*     but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*     GNU General Public License for more details.                             *
*                                                                              *
*     You should have received a copy of the GNU General Public License        *
*     along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
********************************************************************************/

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>    //used for qDebug messages
#include <cmath>

#include "edge.h"
#include "node.h"
#include "edgeweight.h"
#include "graphicswidget.h"


static const double Pi = 3.14159265;
static double TwoPi = 2.0 * Pi;


Edge::Edge(GraphicsWidget *gw, Node *from, Node *to, float weight, int nodeSize,
           QString color, bool reciprocal, bool drawArrows, bool bez): graphicsWidget(gw)
{

    qDebug("Edge: Edge()");
    Q_UNUSED(nodeSize);
    graphicsWidget->scene()->addItem(this);  //add edge to scene to be displayed

    from->addOutLink( this );	//adds this Edge to sourceNode
    to->addInLink( this );		//adds this Edge to targetNode

    source = from;			//saves the sourceNode
    target = to;			//Saves the targetNode
    m_color = color;
    m_drawArrows = drawArrows;
    m_reciprocal = reciprocal;
    m_startOffset = source->size();  //used to offset edge from the centre of node
    m_endOffset = target->size();  //used to offset edge from the centre of node
    //qDebug("Edge() m_startOffset %i",(int) m_startOffset);
    //qDebug("Edge() m_endOffset %i",(int) m_endOffset);

    m_arrowSize = 4;		//controls the width of the edge arrow

    eFrom = source->nodeNumber() ;
    eTo = target->nodeNumber() ;
    m_weight = weight ;
    m_Bezier = bez;
    adjust();
}

void Edge::showArrows(bool drawArrows)
{
    prepareGeometryChange();
    m_drawArrows=drawArrows;
}

void Edge::removeRefs()
{
    //FIXME Need to disconnect signals from node to this "erased" edge
    qDebug("Edge: removeRefs()");
    source->deleteOutLink(this);
    target->deleteInLink(this);
}


void Edge::setColor( QString str)
{
    m_color=str;
    prepareGeometryChange();
}

QString Edge::color()
{
    return m_color;
}

/**
 * @brief Edge::colorToPajek
 * Called from Graph::saveGraphToPajekFormat()
 * @return
 */
QString Edge::colorToPajek()
{
    if (m_color.startsWith("#"))
    {
        return ("RGB" + m_color.right(m_color.size()-1)).toUpper();
    }

    return m_color;
}

/**
 * @brief Edge::setWeight
 * Called from MW when user wants to change an edge's weight.
    Updates both the width and the EdgeWeight
 * @param w
 */
void Edge::setWeight(float w)
{
    m_weight = w;

    foreach (EdgeWeight *wgt, weightList)//update the edgeWeight of this edge as well.
    {
        wgt->setPlainText (QString::number(w));
    }
}

float Edge::weight()
{
    return m_weight;
}


void Edge::setStartOffset(int offset)
{
    m_startOffset=offset;
}

void Edge::setEndOffset(int offset)
{
    m_endOffset=offset;
}


Node *Edge::sourceNode() const
{
    return source;
}

void Edge::setSourceNode(Node *node)
{
    source = node;
    adjust();
}

Node *Edge::targetNode() const
{
    return target;
}

void Edge::setTargetNode(Node *node)
{
    target = node;
    adjust();
}

int Edge::sourceNodeNumber ()
{
    return eFrom;
}

int Edge::targetNodeNumber()
{
    return eTo;
}


/**
 * @brief Edge::addWeight
 * Called from EdgeWeight objects to 'connect' them to this edge.
 * @param canvasWeight
 */
void Edge::addWeight(EdgeWeight* canvasWeight)
{
    weightList.push_back( canvasWeight);
}

void Edge::clearWeightList()
{
    foreach (EdgeWeight *wgt, weightList) 		//Delete this weight
    {
        wgt->deleteLater();
    }

    weightList.clear();
}


/**
 * @brief Edge::adjust
 * leaves some empty space (offset) from node -
 * make the edge weight appear on the centre of the edge
 */
void Edge::adjust()
{
    // qDebug("Edge: adjust()");
    if (!source || !target)
    {
        return;
    }

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(target, 0, 0));
    QPointF edgeOffset;

    if (source != target)
    {
        qreal length = line.length();
        edgeOffset = QPointF((line.dx() * m_endOffset) / length, (line.dy() *m_endOffset) / length);
    }
    else
    {
        edgeOffset = QPointF(0, 0);
    }

    prepareGeometryChange();

    sourcePoint = line.p1() + edgeOffset;
    targetPoint = line.p2() - edgeOffset;
    //qDebug()<<"----Edge: adjust() "<< sourcePoint.x()<< " "<<sourcePoint.y();
    foreach (EdgeWeight *wgt, weightList)//Move the weight of this edge
    {
        wgt->setPos((source->x()+target->x())/2.0, (source->y()+target->y())/2.0);
    }
}



/**
 * @brief Edge::shape
 * Returns the shape of this edge as a QPainterPath in local coordinates.
 * The shape is used for many things, including collision detection, hit tests,
 * and for the QGraphicsScene::items() functions.
 * The default implementation calls boundingRect() to return a simple rectangular shape,
 * but we reimplement it to return a more accurate shape for non-rectangular items.
 * @return QPainterPath
 */
QPainterPath Edge::shape () const
{
    //qDebug()<<"Edge::shape()";		//too many debug messages...
    QPainterPath path;
    qreal extra = (width() + m_arrowSize);
    QLineF line(sourcePoint, targetPoint);
    QPolygonF poly;
    line.translate(extra,extra);
    poly.push_back(line.p1());
    poly.push_back(line.p2());
    line.translate(-extra,-extra);
    poly.push_back(line.p1());
    poly.push_back(line.p2());
    path.addPolygon(poly);
    path.closeSubpath();
    //path.addRegion(boundingRegion(QTransform()));
    //   path.addRect(boundingRect());
    return path;
} 


/**
 * @brief Edge::boundingRect
 * Defines the outer bounds of the edge as a rectangle;
 * All painting will be restricted to inside the edge's bounding rect.
 * Qt uses this bounding rect to determine whether the edge requires redrawing.
 * @return
 */
QRectF Edge::boundingRect() const
{
    if (!source || !target)
    {
        return QRectF();
    }

    qreal penWidth = 1;
    qreal extra = ( penWidth + m_arrowSize) / 2.0;

    QRectF a = QRectF(sourcePoint, QSizeF(targetPoint.x() - sourcePoint.x(), targetPoint.y() - sourcePoint.y())
                      ).normalized().adjusted(-extra, -extra, extra, extra);
    //qDebug()<<"Edge::boundingRect() extra = " << extra << "QSizeF width "<< a.width() << " QSizeF height "<< a.height();
    if (source == target)
    {   //self-edge has different bounding rect.
        return QRectF(sourcePoint-QPointF(30, 30), QSizeF(60,30)).normalized().adjusted(-extra, -extra, extra, extra);
    }

    return a;
}

void Edge::makeReciprocal()
{
    qDebug("Edge::makeReciprocal()");
    prepareGeometryChange();
    m_reciprocal= true;
}

void Edge::unmakeReciprocal()
{
    qDebug("Edge::unmakeReciprocal()");
    prepareGeometryChange();
    m_reciprocal= false;
}

bool Edge::isReciprocal()
{
    return m_reciprocal;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    if (!source || !target)
    {
        return;
    }

    Q_UNUSED(option); //	painter->setClipRect( option->exposedRect );
    // qDebug() <<"@@@ Edge::paint()";

    //    qDebug()<<endl <<"@@@ Edge::paint() edge from "<< sourceNodeNumber()
    //           << " at (" <<(sourceNode())->x() <<","<< (sourceNode())->y()
    //           << ") to node "<<targetNodeNumber() << " at ("<<(targetNode())->x()
    //           <<","<< (targetNode())->y() << ") of weight "<< m_weight;

    //Define the path upon which we' ll draw the line
    QPainterPath line(sourcePoint);

    //Construct the path
    if (source!=target)
    {
        if ( !m_Bezier)
        {
            //   qDebug()<< "*** Edge::paint(). Constructing a line";
            line.lineTo(targetPoint);
        }
        else
        {
            qDebug() << "*** Edge::paint(). Constructing a bezier curve";
        }
    }
    else
    { //self-link
        QPointF c1 = QPointF( targetPoint.x() -30,  targetPoint.y() -30 );
        QPointF c2 = QPointF( targetPoint.x() +30,  targetPoint.y() -30 );
        //        qDebug()<< "*** Edge::paint(). Constructing a bezier self curve c1 "
        //                <<c1.x()<<","<<c1.y()  << " and c2 "<<c2.x()<<","<<c2.y();
        line.cubicTo( c1, c2, targetPoint);
    }

    //Prepare the pen
    //	qDebug()<<"*** Edge::paint(). Preparing the pen with width "<< width();
    if (m_weight > 0)
    {
        painter->setPen(QPen(QColor(m_color), width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter->setPen(QPen(QColor(m_color), width(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    }


    //Draw the arrows only if we have different nodes.
    if (m_drawArrows && source!=target)
    {
        angle = 0;
        line_length = line.length();
        line_dx = targetPoint.x()-sourcePoint.x();
        line_dy = targetPoint.y()-sourcePoint.y();

        if(line.length() >0)
        {
            angle = ::acos( line_dx / line_length );
        }
        //		qDebug() << " acos() " << ::acos( line_dx  / line_length ) ;

        if (line_dy >= 0)
        {
            angle = TwoPi - angle;
        }

        //		qDebug() << "*** Edge::paint(). Constructing arrows. First Arrow at target node"
        //					<< "target-source: " << line_dx
        //					<< " length: " << line_length
        //					<< " angle: "<< angle;

        QPointF destArrowP1 = targetPoint + QPointF(sin(angle - Pi / 3) * m_arrowSize,
                                                    cos(angle - Pi / 3) * m_arrowSize);
        QPointF destArrowP2 = targetPoint + QPointF(sin(angle - Pi + Pi / 3) * m_arrowSize,
                                                    cos(angle - Pi + Pi / 3) * m_arrowSize);
        //		qDebug() << "*** Edge::paint() destArrowP1 "
        //                 <<  destArrowP1.x() << "," << destArrowP1.y()
        //                  << "  destArrowP2 " <<  destArrowP2.x() << "," << destArrowP2.y();
        painter->setBrush(QColor(m_color));
        QPolygonF destP;
        destP << targetPoint << destArrowP1 << destArrowP2;
        line.addPolygon ( destP);
        //painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
        if(m_reciprocal)
        {
            //            qDebug() << "**** Edge::paint() This edge is SYMMETRIC! "
            //                     << " So, we need to create Arrow at src node as well";
            QPointF srcArrowP1 = sourcePoint + QPointF(sin(angle +Pi / 3) * m_arrowSize,
                                                       cos(angle +Pi / 3) * m_arrowSize);
            QPointF srcArrowP2 = sourcePoint + QPointF(sin(angle +Pi - Pi  / 3) * m_arrowSize,
                                                       cos(angle +Pi - Pi / 3) * m_arrowSize);
            //			qDebug() << "*** Edge::paint() srcArrowP1 " <<  srcArrowP1.x() << "," << srcArrowP1.y()
            //									<< "  srcArrowP2 " <<  srcArrowP2.x() << "," << srcArrowP2.y();
            QPolygonF srcP;
            srcP << sourcePoint<< srcArrowP1<< srcArrowP2;
            line.addPolygon ( srcP);

            //			painter->drawPolygon(QPolygonF() << line.p1() << srcArrowP1 << srcArrowP2);
        }
        else
        {
            // qDebug() << "*** Edge::paint() Not symmetric edge. Finish";
        }
    }
    else
    {
        //        qDebug()<< "*** Edge::paint(). This edge is self-link - CONTINUE!";
    }
    //	qDebug()<< "### Edge::paint(). DrawPath now....";
    painter->drawPath(line);
}


/** 
    Controls the width of the edge; is a function of edge weight
*/
float Edge::width() const
{
    // qDebug()<< "Edge::width() will return "<< fabs(m_weight);
    if (fabs(m_weight) > 1)
    {
        return 1 + fabs(m_weight)/10;
    }

    return 1;//Default, if  m_weight in (-1, 1) space
}




/** handles the events of a click on an edge*/
void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("Edge: pressEvent() emitting edgeClicked");
    graphicsWidget->edgeClicked(this);

    if (event->button()==Qt::LeftButton)
    {
        qDebug() << "Edge: edge pressEvent() left click > ";
        //graphicsWidget->startNodeMovement(0);
    }

    if (event->button()==Qt::RightButton)
    {
        qDebug("Edge: Right-click on an edge,  at %i, %i", event->screenPos().x(), event->screenPos().y());
        graphicsWidget->openEdgeContextMenu();
    }
}

Edge::~Edge()
{
    qDebug() << "\n\n\n *** ~EDGE() " << sourceNodeNumber()<< "->" << targetNodeNumber();
    removeRefs();
    weightList.clear();
    this->hide();
}

