#include "customstyle.h"
#include <QStyleOptionMenuItem>

#include <QPainter>
#include <QComboBox>
#include <QSize>

// 定制菜单的一些参数

// from windows style
static const int windowsItemFrame        =  2; // menu item frame width
static const int windowsItemHMargin      =  3; // menu item hor text margin
static const int windowsItemVMargin      =  8; // menu item ver text margin
static const int windowsRightBorder      = 15; // right border on windows

static QColor colSeparator(223, 223, 223);						// 分隔符颜色
static QColor colItemBg(244, 244, 244);						    // 默认背景色
static QColor colText(85, 85, 85);								// 字体
static QColor colDisText(153, 153, 153);					    // 禁用时字体
static QColor colIndicatorArrow(156, 156, 156);				    // 子菜单指示符
static QColor colItemHighlight (209, 230, 255);				    // 高亮背景

const QPixmap drawNinePatch(QSize szDst, const QPixmap &srcPix)
{
    // 绘制背景图到, 以九宫格形式
    QPixmap dstPix(szDst);
    dstPix.fill(QColor(255, 255, 255, 0));
    QPainter painter;
    painter.begin(&dstPix);

    int nW = szDst.width();
    int nH = szDst.height();

    int nWBg = srcPix.width();
    int nHBg = srcPix.height();
    QPoint m_ptBgLT(10, 10);
    QPoint m_ptBgRB(19, 19);

    QPoint ptDstLT(m_ptBgLT.x(), m_ptBgLT.y());
    QPoint ptDstRB(nW-(nWBg-m_ptBgRB.x()), nH-(nHBg-m_ptBgRB.y()));

    //LT
    painter.drawPixmap(QRect(0,0,ptDstLT.x(), ptDstLT.y()), srcPix, QRect(0,0,m_ptBgLT.x(), m_ptBgLT.y()));
    //MT
    painter.drawPixmap(QRect(ptDstLT.x(),0, ptDstRB.x()-ptDstLT.x(), ptDstLT.y()), srcPix, QRect(m_ptBgLT.x(),0,m_ptBgRB.x()-m_ptBgLT.x(), m_ptBgLT.y()));
    //RT
    painter.drawPixmap(QRect(ptDstRB.x(),0,nW-ptDstRB.x(), ptDstLT.y()), srcPix, QRect(m_ptBgRB.x(),0,nWBg-m_ptBgRB.x(), m_ptBgLT.y()));
    //LM
    painter.drawPixmap(QRect(0,ptDstLT.y(),ptDstLT.x(), ptDstRB.y()-ptDstLT.y()), srcPix, QRect(0,m_ptBgLT.y(),m_ptBgLT.x(), m_ptBgRB.y()-m_ptBgLT.y()));
    //MM
    painter.drawPixmap(QRect(ptDstLT.x(),ptDstLT.y(),ptDstRB.x()-ptDstLT.x(), ptDstRB.y()-ptDstLT.y()), srcPix, QRect(m_ptBgLT.x(),m_ptBgLT.y(),m_ptBgRB.x()-m_ptBgLT.x(), m_ptBgRB.y()-m_ptBgLT.y()));
    //RM
    painter.drawPixmap(QRect(ptDstRB.x(),ptDstLT.y(), nW-ptDstRB.x(), ptDstRB.y()-ptDstLT.y()), srcPix, QRect(m_ptBgRB.x(),m_ptBgLT.y(), nWBg-m_ptBgRB.x(), m_ptBgRB.y()-m_ptBgLT.y()));
    //LB
    painter.drawPixmap(QRect(0,ptDstRB.y(),ptDstLT.x(), nH-ptDstRB.y()), srcPix, QRect(0,m_ptBgRB.y(),m_ptBgLT.x(), nHBg-m_ptBgRB.y()));
    //MB
    painter.drawPixmap(QRect(ptDstLT.x(),ptDstRB.y(),ptDstRB.x()-ptDstLT.x(),  nH-ptDstRB.y()), srcPix, QRect(m_ptBgLT.x(),m_ptBgRB.y(),m_ptBgRB.x()-m_ptBgLT.x(),  nHBg-m_ptBgRB.y()));
    //RB
    painter.drawPixmap(QRect(ptDstRB.x(),ptDstRB.y(),nW-ptDstRB.x(),  nH-ptDstRB.y()), srcPix, QRect(m_ptBgRB.x(),m_ptBgRB.y(),nWBg-m_ptBgRB.x(),  nHBg-m_ptBgRB.y()));

    painter.end();
    return dstPix;
}

CCustomStyle::CCustomStyle(QStyle *style)
    : QProxyStyle(style)
{
    _pixShadow.load(":/CustomMenu/box-shadow.png");
}

void CCustomStyle::drawPrimitive( PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget ) const
{
    if(element == PE_FrameMenu)
    {
        painter->save();
        {
            if(_pixShadow.isNull() || widget->objectName() != "CustomMenu")  // fix bug: Qt的内置菜单显示不正常(如TextEdit右键菜单)
            {
                painter->restore();
                return QProxyStyle::drawPrimitive(element, option, painter, widget);
            }

            QSize szThis = option->rect.size();
            QPixmap pixShadowBg = drawNinePatch(szThis, _pixShadow);
            painter->drawPixmap(option->rect, pixShadowBg);
        }
        painter->restore();
        return;
    }

    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

int CCustomStyle::pixelMetric(PixelMetric pm, const QStyleOption * opt, const QWidget * widget) const
{
    if (pm == QStyle::PM_SmallIconSize)
    {
        return _iconSize.width();	//返回ICON的大小
    }
    if(pm == PM_MenuPanelWidth)
    {
        return 6;		// 调整边框宽度, 以绘制阴影
    }
    if(pm == PM_MenuScrollerHeight)
    {
        return 2;
    }

    // 其他涉及的参数(未使用)
    //switch(pm)
    //{
    //case PM_DefaultFrameWidth							 :
    //case PM_DockWidgetSeparatorExtent			 :
    //case PM_TextCursorWidth								 :
    //case PM_LayoutHorizontalSpacing				 :
    //case PM_DefaultLayoutSpacing					 :
    //case PM_SmallIconSize									 :
    //case PM_MenuHMargin										 :
    //case PM_MenuVMargin										 :
    //case PM_MenuDesktopFrameWidth					 :
    //case PM_SubMenuOverlap								 :
    //case PM_ToolBarExtensionExtent				 :
    //case PM_MenuPanelWidth								 :
    //case PM_ToolBarIconSize								:
    //case PM_MenuBarPanelWidth						:
    //case PM_LayoutVerticalSpacing				:
    //case PM_MenuBarVMargin								:
    //case PM_MenuBarHMargin								:
    //case PM_MenuBarItemSpacing:
    //	break;
    //default:
    //	break;
    //}
    return QProxyStyle::pixelMetric(pm, opt, widget);
}

static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50)
{
    const int maxFactor = 100;
    QColor tmp = colorA;
    tmp.setRed((tmp.red() * factor) / maxFactor + (colorB.red() * (maxFactor - factor)) / maxFactor);
    tmp.setGreen((tmp.green() * factor) / maxFactor + (colorB.green() * (maxFactor - factor)) / maxFactor);
    tmp.setBlue((tmp.blue() * factor) / maxFactor + (colorB.blue() * (maxFactor - factor)) / maxFactor);
    return tmp;
}

void CCustomStyle::drawControl(ControlElement control, const QStyleOption *option, QPainter *painter, const QWidget *widget ) const
{
    switch(control)
    {
        case CE_MenuItem:
        {
            drawMenuItem(option, painter, widget);
            return;			// 直接返回, 否则会被super::drawcontrol覆盖
        }
    }
    QProxyStyle::drawControl(control, option, painter, widget);
}

void CCustomStyle::drawMenuItem(const QStyleOption *option, QPainter *painter, const QWidget *widget ) const
{
    painter->save();

    if (const QStyleOptionMenuItem *menuItem = qstyleoption_cast<const QStyleOptionMenuItem *>(option))
    {
        // 先绘制一层背景(否则在透明情况下, 会直接透过去);
        painter->setPen(colItemBg);
        painter->setBrush(colItemBg);
        painter->drawRect(option->rect);

        if (menuItem->menuItemType == QStyleOptionMenuItem::Separator)
        {
            int w = 0;

            if (!menuItem->text.isEmpty())
            {
                // 绘制分隔符文字
                painter->setFont(menuItem->font);
                proxy()->drawItemText(painter, menuItem->rect.adjusted(5, 0, -5, 0), Qt::AlignLeft | Qt::AlignVCenter,
                                      menuItem->palette, menuItem->state & State_Enabled, menuItem->text,
                                      QPalette::Text);
                w = menuItem->fontMetrics.width(menuItem->text) + 5;
            }
            painter->setPen(colSeparator);
            bool reverse = menuItem->direction == Qt::RightToLeft;
            painter->drawLine(menuItem->rect.left() + 5 + (reverse ? 0 : w), menuItem->rect.center().y(),
                              menuItem->rect.right() - 5 - (reverse ? w : 0), menuItem->rect.center().y());
            painter->restore();
            return;
        }

        bool selected = menuItem->state & State_Selected && menuItem->state & State_Enabled;

        if (selected)
        {
            QRect r = option->rect;
            painter->fillRect(r, colItemHighlight);
        }

        bool checkable = menuItem->checkType != QStyleOptionMenuItem::NotCheckable;
        bool checked = menuItem->checked;
        bool sunken = menuItem->state & State_Sunken;
        bool enabled = menuItem->state & State_Enabled;

        bool ignoreCheckMark = false;
        int checkcol = qMax(menuItem->maxIconWidth, 20);

        if (qobject_cast<const QComboBox*>(widget))
        {
            ignoreCheckMark = true; //ignore the checkmarks provided by the QComboMenuDelegate
        }

        if (!ignoreCheckMark)
        {
            // Check
            QRect checkRect(option->rect.left() + 7, option->rect.center().y() - 6, 14, 14);
            checkRect = visualRect(menuItem->direction, menuItem->rect, checkRect);
            if (checkable)
            {
                if (menuItem->checkType & QStyleOptionMenuItem::Exclusive)
                {
                    // Radio button 未实现
                    if (checked || sunken)
                    {
                        /*	painter->setRenderHint(QPainter::Antialiasing);
                        painter->setPen(Qt::NoPen);

                        QPalette::ColorRole textRole = !enabled ? QPalette::Text:
                            selected ? QPalette::HighlightedText : QPalette::ButtonText;
                        painter->setBrush(option->palette.brush( option->palette.currentColorGroup(), textRole));
                        painter->drawEllipse(checkRect.adjusted(4, 4, -4, -4));
                        */
                    }
                }
                else
                {
                    // Check box
                    if (menuItem->icon.isNull())
                    {
                        QStyleOptionButton box;
                        box.QStyleOption::operator=(*option);
                        box.rect = checkRect;

                        if (checked)
                        {
                            box.state |= State_On;
                        }

                        proxy()->drawPrimitive(PE_IndicatorCheckBox, &box, painter, widget);
                    }
                }
            }
        }
        else
        {
            //ignore checkmark
            if (menuItem->icon.isNull())
            {
                checkcol = 0;
            }
            else
            {
                checkcol = menuItem->maxIconWidth;
            }
        }

        // Text and icon, ripped from windows style
        bool dis = !(menuItem->state & State_Enabled);
        bool act = menuItem->state & State_Selected;
        const QStyleOption *opt = option;
        const QStyleOptionMenuItem *menuitem = menuItem;

        QPainter *p = painter;
        QRect vCheckRect = visualRect(opt->direction, menuitem->rect, QRect(menuitem->rect.x() + 4, 
			                          menuitem->rect.y(), checkcol, menuitem->rect.height()));

        if (!menuItem->icon.isNull())
        {
            QIcon::Mode mode = dis ? QIcon::Disabled : QIcon::Normal;

            if (act && !dis)
            {
                mode = QIcon::Active;
            }

            QPixmap pixmap;

            int smallIconSize = proxy()->pixelMetric(PM_SmallIconSize, option, widget);
            QSize iconSize(smallIconSize, smallIconSize);

            if (const QComboBox *combo = qobject_cast<const QComboBox*>(widget))
            {
                iconSize = combo->iconSize();
            }

            if (checked)
            {
                pixmap = menuItem->icon.pixmap(iconSize, mode, QIcon::On);
            }
            else
            {
                pixmap = menuItem->icon.pixmap(iconSize, mode);
            }

            int pixw = pixmap.width();
            int pixh = pixmap.height();

            QRect pmr(0, 0, pixw, pixh);
            pmr.moveCenter(vCheckRect.center());
            painter->setPen(colText);//menuItem->palette.text().color()

            if (checkable && checked)
            {
                QStyleOption opt = *option;
                if (act)
                {
                    QColor activeColor = mergedColors(
                                colItemBg, //option->palette.background().color(),
                                colItemHighlight // option->palette.highlight().color());
                                );
                    opt.palette.setBrush(QPalette::Button, activeColor);
                }
                opt.state |= State_Sunken;
                opt.rect = vCheckRect;
                proxy()->drawPrimitive(PE_PanelButtonCommand, &opt, painter, widget);
            }

            painter->drawPixmap(pmr.topLeft(), pixmap);
        }

        if (selected)
        {
            painter->setPen(colText);//menuItem->palette.highlightedText().color()
        }
        else
        {
            painter->setPen(colText); //menuItem->palette.text().color()
        }

        int x, y, w, h;
        menuitem->rect.getRect(&x, &y, &w, &h);
        int tab = menuitem->tabWidth;
        QColor discol;

        if (dis)
        {
            discol = colDisText; //menuitem->palette.text().color()
            p->setPen(discol);
        }

        int xm = windowsItemFrame + checkcol + windowsItemHMargin + 2;
        int xpos = menuitem->rect.x() + xm; //modify text position(if we don't add xm, we can make text left-aligned)

        QRect textRect(xpos, y + windowsItemVMargin, w - xm - windowsRightBorder - tab + 1, h - 2 * windowsItemVMargin);
        QRect vTextRect = visualRect(opt->direction, menuitem->rect, textRect);
        QString s = menuitem->text;

        if (!s.isEmpty())
        {
            // draw text
            p->save();
            int t = s.indexOf(QLatin1Char('\t'));
            int text_flags = Qt::AlignVCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;

            if (!QProxyStyle::styleHint(SH_UnderlineShortcut, menuitem, widget))
            {
                text_flags |= Qt::TextHideMnemonic;
            }

            text_flags |= Qt::AlignLeft;

            if (t >= 0)
            {
                QRect vShortcutRect = visualRect(opt->direction, menuitem->rect,
                                                 QRect(textRect.topRight(), QPoint(menuitem->rect.right(), textRect.bottom())));

                if (dis && !act && proxy()->styleHint(SH_EtchDisabledText, option, widget))
                {
                    p->setPen(colText);//menuitem->palette.light().color()
                    p->drawText(vShortcutRect.adjusted(1, 1, 1, 1), text_flags, s.mid(t + 1));
                    p->setPen(discol);
                }

                p->drawText(vShortcutRect, text_flags, s.mid(t + 1));
                s = s.left(t);
            }

            QFont font = menuitem->font;
            // font may not have any "hard" flags set. We override
            // the point size so that when it is resolved against the device, this font will win.
            // This is mainly to handle cases where someone sets the font on the window
            // and then the combo inherits it and passes it onward. At that point the resolve mask
            // is very, very weak. This makes it stonger.
            font.setPointSizeF(QFontInfo(menuItem->font).pointSizeF());

            if (menuitem->menuItemType == QStyleOptionMenuItem::DefaultItem)
            {
                font.setBold(true);
            }

            p->setFont(font);

            if (dis && !act && proxy()->styleHint(SH_EtchDisabledText, option, widget))
            {
                p->setPen(menuitem->palette.light().color());
                p->drawText(vTextRect.adjusted(1, 1, 1, 1), text_flags, s.left(t));
                p->setPen(discol);
            }

            p->drawText(vTextRect, text_flags, s.left(t));
            p->restore();
        }

        // Arrow 绘制子菜单指示符
        if (menuItem->menuItemType == QStyleOptionMenuItem::SubMenu)
        {
            // draw sub menu arrow
            int dim = (menuItem->rect.height() - 4) / 2;
            PrimitiveElement arrow;
            arrow = option->direction == Qt::RightToLeft ? PE_IndicatorArrowLeft : PE_IndicatorArrowRight;
            int xpos = menuItem->rect.left() + menuItem->rect.width() - 3 - dim;
            QRect  vSubMenuRect = visualRect(option->direction, menuItem->rect,
                                             QRect(xpos, menuItem->rect.top() + menuItem->rect.height() / 2 - dim / 2, dim, dim));
            QStyleOptionMenuItem newMI = *menuItem;
            newMI.rect = vSubMenuRect;
            newMI.state = !enabled ? State_None : State_Enabled;

            if (selected)
            {
                newMI.palette.setColor(QPalette::ButtonText,// 此处futionstyle 有误, QPalette::Foreground改为ButtonText
                                       colIndicatorArrow);  //newMI.palette.highlightedText().color()
            }
            else
            {
                newMI.palette.setColor(QPalette::ButtonText, colIndicatorArrow);
            }

            proxy()->drawPrimitive(arrow, &newMI, painter, widget);
        }
    }

    painter->restore();
}
