#ifndef RGBHISTOGRAMWIDGET_H
#define RGBHISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QColor>
#include <QColorDialog>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <stdlib.h>

#include "colorconversion.h"

class RGBHistogramWidget : public QWidget
{
public:
    RGBHistogramWidget(QWidget *parent = nullptr);
    void HistogramWidgetInit();
    void setImageRGB(const QImage &image);
    void setImageCMY(const QImage &image);
    void setImageCMYK(const QImage &image);
    void setImageHSI(const QImage &image);
    void setChart();

//protected:
//    void paintEvent(QPaintEvent *event) override;

private:
    //-------------Chart-------------

    //layout
    QGridLayout *grLayout;

    //QBarSets
    QBarSet *frstColorSet;
    QBarSet *scndColorSet;
    QBarSet *thrdColorSet;
    QBarSet *fourthColorSet;

    //QStackedBarSeries
    QStackedBarSeries *stackedSeries;

    //Colors sets' names
    QString frstColorName = "";
    QString scndColorName = "";
    QString thrdColorName = "";
    QString fourthColorName = "";

    //QChart
    QChart *histogramChart;

    //Title of the chart
    const QString chartTitle = "Histogram Chart";

    //QChartView
    QChartView *histogramChartView;

    //-------------ColorConversion-------------
    //vectors;
    QVector<double> frst_Values;
    QVector<double> scnd_Values;
    QVector<double> thrd_Values;
    QVector<double> fourth_Values;

    //QGradient colors
    QColor frstColor;
    QColor scndColor;
    QColor thrdColor;
    QColor fourthColor;

    //Objects
    ColorConversion *_colorConversion;
    ColourModel_RGB *rgb;
    ColourModel_CMY *cmy;
    ColourModel_CMYK *cmyk;
    ColourModel_HSI *hsi;

};

#endif // RGBHISTOGRAMWIDGET_H
