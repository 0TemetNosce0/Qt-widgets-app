/*
 * QRoundProgressBar - a circular progress bar Qt widget.
 *
 * Sintegrial Technologies (c) 2015-now
 *
 * The software is freeware and is distributed "as is" with the complete source codes.
 * Anybody is free to use it in any software projects, either commercial or non-commercial.
 * Please do not remove this copyright message and remain the name of the author unchanged.
 *
 * It is very appreciated if you produce some feedback to us case you are going to use
 * the software.
 *
 * Please send your questions, suggestions, and information about found issues to the
 *
 * sintegrial@gmail.com
 *
 */

#ifndef QROUNDPROGRESSBAR_H
#define QROUNDPROGRESSBAR_H

#include <QWidget>

/**
 * @brief The QRoundProgressBar class represents a circular progress bar and maintains its API
 * similar to the QProgressBar.
 *
 * QRoundProgressBar currently supports Donut, Pie and Line styles (see setBarStyle()).
 *
 * Generally QRoundProgressBar uses its palette and font attributes to define how it will look.
 *
 * The following QPalette members are considered:
 * - QPalette::Window   background of the whole widget (normally should be set to Qt::NoBrush)
 * - QPalette::Base     background of the non-filled progress bar area (should be set to Qt::NoBrush to make it transparent)
 * - QPalette::AlternateBase  background of the central circle where the text is shown (for Donut style)
 * - QPalette::Shadow        foreground of the non-filled progress bar area (i.e. border color)
 * - QPalette::Highlight      background of the filled progress bar area
 * - QPalette::Text           color of the text shown in the center
 *
 * By default, font size will be adjusted automatically to fit the inner circle of the widget.
 */
class QRoundProgressBar : public QWidget
{
    Q_OBJECT
public:    
    explicit QRoundProgressBar(QWidget *parent = 0);

    static const double PositionLeft;
    static const double PositionTop;
    static const double PositionRight;
    static const double PositionBottom;

    /**
     * @brief Return position (in degrees) of minimum value.
     * \sa setNullPosition
     */
    double nullPosition() const { return m_nullPosition; }
    /**
     * @brief Defines position of minimum value.
     * @param position position on the circle (in degrees) of minimum value
     * \sa nullPosition
     */
    void setNullPosition(double position);

    /**
     * @brief The BarStyle enum defines general look of the progress bar.
     */
    enum BarStyle
    {
        /// Donut style (filled torus around the text)
        StyleDonut,
        /// Pie style (filled pie segment with the text in center)
        StylePie,
        /// Line style (thin round line around the text)
        StyleLine
    };
    /**
     * @brief Sets visual style of the widget.
     * \sa barStyle
     */
    void setBarStyle(BarStyle style);
    /**
     * @brief Returns current progree bar style.
     * \sa setBarStyle
     */
    BarStyle barStyle() const { return m_barStyle; }

    /**
     * @brief Sets width of the outline circle pen.
     * @param penWidth width of the outline circle pen (in pixels)
     */
    void setOutlinePenWidth(double penWidth);
    /**
     * @brief Returns width of the outline circle pen.
     */
    double outlinePenWidth() const { return m_outlinePenWidth; }

    /**
     * @brief Sets width of the data circle pen.
     * @param penWidth width of the data circle pen (in pixels)
     */
    void setDataPenWidth(double penWidth);
    /**
     * @brief Returns width of the data circle pen.
     */
    double dataPenWidth() const { return m_dataPenWidth; }

    /**
     * @brief Defines the string used to generate the current text.
     * If no format is set, no text will be shown.
     * @param format see QProgressBar's format description
     * \sa setDecimals
     */
    void setFormat(const QString& format);
    /**
     * @brief Sets format string to empty string. No text will be shown therefore.
     * See setFormat() for more information.
     */
    void resetFormat();
    /**
     * @brief Returns the string used to generate the current text.
     */
    QString format() const { return m_format; }

    /**
     * @brief Sets number of decimals to show after the comma (default is 1).
     * \sa setFormat
     */
    void setDecimals(int count);
    int decimals() const { return m_decimals; }

    /**
     * @brief Returns current value shown on the widget.
     * \sa setValue()
     */
    double value() const { return m_value; }
    /**
     * @brief Returns minimum of the allowed value range.
     * \sa setMinimum, setRange
     */
    double minimum() const { return m_min; }
    /**
     * @brief Returns maximum of the allowed value range.
    * \sa setMaximum, setRange
     */
    double maximum() const { return m_max; }

public Q_SLOTS:
    /**
     * @brief Defines minimum und maximum of the allowed value range.
     * If the current value does not fit into the range, it will be automatically adjusted.
     * @param max minimum of the allowed value range
     * @param min maximum of the allowed value range
     */
    void setRange(double max, double min);
    /**
     * @brief Defines minimum of the allowed value range.
     * If the current value does not fit into the range, it will be automatically adjusted.
     * @param min maximum of the allowed value range
     * \sa setRange
     */
    void setMinimun(double min);
    /**
     * @brief Defines maximum of the allowed value range.
     * If the current value does not fit into the range, it will be automatically adjusted.
     * @param max minimum of the allowed value range
     * \sa setRange
     */
    void setMaximun(double max);
    /**
     * @brief Sets a value which will be shown on the widget.
     * @param val must be between minimum() and maximum()
     */
    void setValue(double val);
    /**
     * @brief Integer version of the previous slot.
     * @param val must be between minimum() and maximum()
     */
    void setValue(int val);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void drawBackground(QPainter& p, const QRectF& baseRect);
    virtual void drawBase(QPainter& p, const QRectF& baseRect);
    virtual void drawValue(QPainter& p, const QRectF& baseRect, double value, double arcLength);
    virtual void calculateInnerRect(const QRectF& baseRect, double outerRadius, QRectF& innerRect, double& innerRadius);
    virtual void drawInnerBackground(QPainter& p, const QRectF& innerRect);
    virtual void drawText(QPainter& p, const QRectF& innerRect, double innerRadius, double value);
    virtual QString valueToText(double value) const;
    virtual void valueFormatChanged();

    virtual QSize minimumSizeHint() const { return QSize(32,32); }

    virtual bool hasHeightForWidth() const { return true; }
    virtual int heightForWidth(int w) const { return w; }

    double m_min, m_max;
    double m_value;

    double m_nullPosition;
    BarStyle m_barStyle;
    double m_outlinePenWidth, m_dataPenWidth;

    QString m_format;
    int m_decimals;

    static const int UF_VALUE = 1;
    static const int UF_PERCENT = 2;
    static const int UF_MAX = 4;
    int m_updateFlags;
};

#endif // QROUNDPROGRESSBAR_H
