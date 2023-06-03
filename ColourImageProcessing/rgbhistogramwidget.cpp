#include "rgbhistogramwidget.h"

RGBHistogramWidget::RGBHistogramWidget(QWidget *parent) : QWidget(parent)
{
    HistogramWidgetInit();
}

void RGBHistogramWidget::HistogramWidgetInit(){
    //universal vectors that will be used in setChart()
    //the vectors will be reset and new values will be added to them every time;
    //resize the vectors to 360, because that is what hsi uses as values
    frst_Values.resize(360);
    scnd_Values.resize(360);
    thrd_Values.resize(360);
    fourth_Values.resize(360);

    //intialize colorConversion class
    _colorConversion = new ColorConversion();

    //set up the layout
    grLayout = new QGridLayout();
    this->setLayout(grLayout);

    //set up BarSeries
    frstColorSet = new QBarSet("frstColor");
    scndColorSet = new QBarSet("scndColor");
    thrdColorSet = new QBarSet("thrdColor");
    fourthColorSet = new QBarSet("");

    //set up QStackedBarSeries
    stackedSeries = new QStackedBarSeries();
    stackedSeries->append(frstColorSet);
    stackedSeries->append(scndColorSet);
    stackedSeries->append(thrdColorSet);
    stackedSeries->append(fourthColorSet);

    //set up chart
    histogramChart = new QChart();
    histogramChart->setTitle(chartTitle); //set title
    histogramChart->setAnimationOptions(QChart::SeriesAnimations); //set animation
    histogramChart->legend()->setVisible(true); //set the legend visible
    histogramChart->legend()->setAlignment(Qt::AlignBottom);

    //set up the chartView
    histogramChartView = new QChartView();

    //display the chart using the chartView
    histogramChartView->setChart(histogramChart);
    histogramChartView->setRenderHint(QPainter::Antialiasing);

    //add the chartView to the layout
    grLayout->addWidget(histogramChartView);
}

RGBHistogramWidget::~RGBHistogramWidget(){

    //layout
    delete grLayout;

    //QBarSets
    delete frstColorSet;
    delete scndColorSet;
    delete thrdColorSet;
    delete fourthColorSet;

    //QStackedBarSeries
    delete stackedSeries;

    //QChart
    delete histogramChart;

    //QChartView
    delete histogramChartView;
}

//set rgb histogram
void RGBHistogramWidget::setImageRGB(const QImage &image)
{
    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.fill(0);

    QVector<double> redValues;
    QVector<double> greenValue;
    QVector<double> blueValue;

    redValues.resize(256); //red
    greenValue.resize(256); //green
    blueValue.resize(256); //blue

    redValues.fill(0);
    greenValue.fill(0);
    blueValue.fill(0);

    for (int row = 0; row < image.height(); row++) {
        for (int col = 0; col < image.width(); col++) {
            QRgb pixel = image.pixel(col, row);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            ++redValues[red];
            ++greenValue[green];
            ++blueValue[blue];
        }
    }

    frst_Values = redValues;
    scnd_Values = greenValue;
    thrd_Values = blueValue;

    frstColor = Qt::red;
    scndColor = Qt::green;
    thrdColor = Qt::blue;
    fourthColor = Qt::transparent;

    frstColorName = "Red";
    scndColorName = "Blue";
    thrdColorName = "Green";

    axisXMax = 255;

    setChart();
}

//set cmy histogram
void RGBHistogramWidget::setImageCMY(const QImage &image)
{
    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.fill(0);

    QVector<double> magentaValues;
    QVector<double> yellowValues;
    QVector<double> cyanValues;

    magentaValues.resize(256);
    yellowValues.resize(256);
    cyanValues.resize(256);

    magentaValues.fill(0);
    yellowValues.fill(0);
    cyanValues.fill(0);

    for (int row = 0; row < image.height(); row++) {
        for (int col = 0; col < image.width(); col++) {
            QRgb pixel = image.pixel(col, row);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            cmy = new ColourModel_CMY(_colorConversion->RGBtoCMY(new ColourModel_RGB(red,green,blue)));
            //used for the change of the pixels in the picture
            //rgb = new ColourModel_RGB(_colorConversion->CMYtoRGB(cmy));

            double cyan = abs(cmy->getCyan());
            double magenta = abs(cmy->getMagenta());
            double yellow = abs(cmy->getYellow());

            //not correct
            ++magentaValues[magenta * 100];
            ++yellowValues[yellow * 100];
            ++cyanValues[cyan * 100];
        }
    }

    frst_Values = magentaValues;
    scnd_Values = yellowValues;
    thrd_Values = cyanValues;

    frstColor = Qt::magenta;
    scndColor = Qt::yellow;
    thrdColor = Qt::cyan;
    fourthColor = Qt::transparent;

    frstColorName = "Magenta";
    scndColorName = "Yellow";
    thrdColorName = "Cyan";

    axisXMax = 100;

    setChart();
}

void RGBHistogramWidget::setImageCMYK(const QImage &image)
{
    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.fill(0);

    QVector<double> magentaValues;
    QVector<double> yellowValues;
    QVector<double> cyanValues;
    QVector<double> blackValues;

    magentaValues.resize(256);
    yellowValues.resize(256);
    cyanValues.resize(256);
    blackValues.resize(256);

    magentaValues.fill(0);
    yellowValues.fill(0);
    cyanValues.fill(0);
    blackValues.fill(0);

    for (int row = 0; row < image.height(); row++) {
        for (int col = 0; col < image.width(); col++) {
            QRgb pixel = image.pixel(col, row);
            double red = qRed(pixel);
            double green = qGreen(pixel);
            double blue = qBlue(pixel);

            cmyk = new ColourModel_CMYK(_colorConversion->RGBtoCMYK(new ColourModel_RGB(red,green,blue)));
            //used for the change of the pixels in the picture
            //rgb = new ColourModel_RGB(_colorConversion->CMYKtoRGB(cmyk));

            double cyan = abs(cmyk->getCyan());
            double magenta = abs(cmyk->getMagenta());
            double yellow = abs(cmyk->getYellow());
            double black = abs(cmyk->getBlack());

            ++magentaValues[magenta * 100];
            ++yellowValues[yellow * 100];
            ++cyanValues[cyan * 100];
            ++blackValues[black * 100];
        }
    }

    frst_Values = magentaValues;
    scnd_Values = yellowValues;
    thrd_Values = cyanValues;
    fourth_Values = blackValues;

    frstColor = Qt::magenta;
    scndColor = Qt::yellow;
    thrdColor = Qt::cyan;
    fourthColor = Qt::black;

    frstColorName = "Magenta";
    scndColorName = "Yellow";
    thrdColorName = "Cyan";
    fourthColorName = "Black";

    axisXMax = 100;

    setChart();
}

void RGBHistogramWidget::setImageHSI(const QImage &image)
{
    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.resize(360);
    fourth_Values.fill(0);

    QVector<double> hueValues;
    QVector<double> saturationValues;
    QVector<double> intensityValues;

    hueValues.resize(360);
    saturationValues.resize(360);
    intensityValues.resize(360);

    hueValues.fill(0);
    saturationValues.fill(0);
    intensityValues.fill(0);

    for (int row = 0; row < image.height(); row++) {
        for (int col = 0; col < image.width(); col++) {
//            if(row == 473 && col == 1041){
//                qDebug() << "Here";
//            }
            QRgb pixel = image.pixel(col, row);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            hsi = new ColourModel_HSI(_colorConversion->RGBtoHSI(new ColourModel_RGB(red,green,blue)));
            rgb = new ColourModel_RGB(_colorConversion->HSItoRGB(hsi));

            double hue = hsi->getHue();
            double saturation = hsi->getSaturation();
            double intensity = hsi->getIntensity();

            ++hueValues[hue];
            ++saturationValues[saturation];
            ++intensityValues[intensity];
        }
    }

    frst_Values = hueValues;
    scnd_Values = saturationValues;
    thrd_Values = intensityValues;

    frstColor = Qt::black;
    scndColor = Qt::darkGray;
    thrdColor = Qt::lightGray;
    fourthColor = Qt::transparent;

    frstColorName = "Hue";
    scndColorName = "Saturation";
    thrdColorName = "Intensity";

    axisXMax = 255;

    setChart();
}

void RGBHistogramWidget::setChart(){
    frstColorSet->remove(0, 360);
    scndColorSet->remove(0, 360);
    thrdColorSet->remove(0, 360);
    fourthColorSet->remove(0, 360);

    //set the labels for all of the colors
    frstColorSet->setLabel(frstColorName);
    scndColorSet->setLabel(scndColorName);
    thrdColorSet->setLabel(thrdColorName);
    fourthColorSet->setLabel(fourthColorName);

    //set the colors for all of the colors
    frstColorSet->setColor(frstColor);
    scndColorSet->setColor(scndColor);
    thrdColorSet->setColor(thrdColor);
    fourthColorSet->setColor(fourthColor);

    //add the values to the series
    for(int i = 0; i < frst_Values.length() - 1; i++){
        *frstColorSet << frst_Values.at(i);
        *scndColorSet << scnd_Values.at(i);
        *thrdColorSet << thrd_Values.at(i);
        *fourthColorSet << fourth_Values.at(i);
    }

    //add the series to the chart
    histogramChart->addSeries(stackedSeries);

    //get the max numerical value from all the vectors
    double maxValue = std::max(
        *std::max_element(frst_Values.constBegin(), frst_Values.constEnd()),
        std::max(
            *std::max_element(scnd_Values.constBegin(), scnd_Values.constEnd()),
            std::max(
                *std::max_element(thrd_Values.constBegin(), thrd_Values.constEnd()),
                *std::max_element(fourth_Values.constBegin(), fourth_Values.constEnd())
                )
            )
        );

    //create the default axis
    histogramChart->createDefaultAxes(); // set the axis
    histogramChart->axes(Qt::Horizontal).back()->setRange(0, axisXMax);
    histogramChart->axes(Qt::Horizontal).back()->setTitleText("axis x");
    histogramChart->axes(Qt::Horizontal).back()->setGridLineVisible(false);

    histogramChart->axes(Qt::Vertical).back()->setRange(0, maxValue);
    histogramChart->axes(Qt::Vertical).back()->setTitleText("axis y");


}
