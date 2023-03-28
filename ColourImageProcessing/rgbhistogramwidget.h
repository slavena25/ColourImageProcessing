#ifndef RGBHISTOGRAMWIDGET_H
#define RGBHISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPainter>

#include "colorconversion.h"


class RGBHistogramWidget : public QWidget
{
public:
    RGBHistogramWidget(QWidget *parent = nullptr);
    void setImageRGB(const QImage &image);
    void setImageCMY(const QImage &image);
    void setImageCMYK(const QImage &image);
    void setImageHSI(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> m_redValues;
    QVector<int> m_greenValues;
    QVector<int> m_blueValues;
    ColorConversion *_colorConversion;
    ColourModel_RGB *rgb_main;
//    ColourModel_RGB *rgb_converted;
    ColourModel_CMY *cmy;
    ColourModel_CMYK *cmyk;
    ColourModel_HSI *hsi;

};

#endif // RGBHISTOGRAMWIDGET_H
