#include "rgbhistogramwidget.h"
#include <algorithm>

//constructor
RGBHistogramWidget::RGBHistogramWidget(QWidget *parent) : QWidget(parent)
{
    //call the initalization function
    HistogramWidgetInit();
}

//init widget
void RGBHistogramWidget::HistogramWidgetInit(){
    //intialize colorConversion class
    _colorConversion = new ColorConversion();

    //set up the layout
    grLayout = new QGridLayout();
    this->setLayout(grLayout);

    //set up BarSeries
    frstColorSet = new QBarSet("");
    scndColorSet = new QBarSet("");
    thrdColorSet = new QBarSet("");
    fourthColorSet = new QBarSet("");

    frstColorSet->setColor(Qt::transparent);
    scndColorSet->setColor(Qt::transparent);
    thrdColorSet->setColor(Qt::transparent);
    fourthColorSet->setColor(Qt::transparent);

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

    //add the series to the chart
    histogramChart->addSeries(stackedSeries);

    //set up the chartView
    histogramChartView = new QChartView();

    //display the chart using the chartView
    histogramChartView->setChart(histogramChart);
    histogramChartView->setRenderHint(QPainter::Antialiasing);

    //add the chartView to the layout
    grLayout->addWidget(histogramChartView);
}

//destructor
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
void RGBHistogramWidget::setImageRGB(QImage &image)
{
    //clear the chart, before updating it
    clearColourSets();

    //resize vectors, depending on the colour model
    frst_Values.resize(256);
    scnd_Values.resize(256);
    thrd_Values.resize(256);
    fourth_Values.resize(256);

    //fill vectors with zeros
    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.fill(0);

    for (int row = 0; row < image.height(); ++row) {
        QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(row));
        for (int col = 0; col < image.width(); ++col) {
            QRgb &model = line[col];
            int red = qRed(model);
            int green = qGreen(model);
            int blue = qBlue(model);

            ++frst_Values[red];
            ++scnd_Values[green];
            ++thrd_Values[blue];
        }
    }

    //initialize needed colours
    frstColor = Qt::red;
    scndColor = Qt::green;
    thrdColor = Qt::blue;
    fourthColor = Qt::transparent;

    frstColorName = "Red";
    scndColorName = "Green";
    thrdColorName = "Blue";
    fourthColorName = "";

    //set chart
    setChart();
}

//set cmy histogram
QImage RGBHistogramWidget::setImageCMY(QImage &image)
{
    //clear the chart, before updating it
    clearColourSets();

    frst_Values.resize(101);
    scnd_Values.resize(101);
    thrd_Values.resize(101);
    fourth_Values.resize(101);

    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.fill(0);

    for (int row = 0; row < image.height(); ++row) {
        QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(row));
        for (int col = 0; col < image.width(); ++col) {
            QRgb &model = line[col];
            double red = qRed(model);
            double green = qGreen(model);
            double blue = qBlue(model);

            //get cmy values
            cmy = new ColourModel_CMY(_colorConversion->RGBtoCMY(new ColourModel_RGB(red,green,blue)));

            //get cmy values
            double cyan = abs(cmy->getCyan());
            double magenta = abs(cmy->getMagenta());
            double yellow = abs(cmy->getYellow());

            //add cmy values to vector, multiplied by 100, because cmy values <= 1
            ++frst_Values[magenta];
            ++scnd_Values[yellow];
            ++thrd_Values[cyan];

            //used for the change of the pixels in the picture
            rgb = new ColourModel_RGB(_colorConversion->CMYtoRGB(cmy));
            int newRed = rgb->getRed();
            int newGreen = rgb->getGreen();
            int newBlue = rgb->getBlue();

            model = qRgb(newRed, newGreen, newBlue); // update image colour

            //deallocate memory
            delete cmy;
            delete rgb;
        }
    }

    frstColor = Qt::magenta;
    scndColor = Qt::yellow;
    thrdColor = Qt::cyan;
    fourthColor = Qt::transparent;

    frstColorName = "Magenta";
    scndColorName = "Yellow";
    thrdColorName = "Cyan";
    fourthColorName = "";

    setChart();

    return image;
}

//set cmyk histogram
QImage RGBHistogramWidget::setImageCMYK(QImage &image)
{
    //clear the chart, before updating it
    clearColourSets();

    frst_Values.resize(101);
    scnd_Values.resize(101);
    thrd_Values.resize(101);
    fourth_Values.resize(101);

    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);
    fourth_Values.fill(0);

    for (int row = 0; row < image.height(); ++row) {
        QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(row));
        for (int col = 0; col < image.width(); ++col) {
            QRgb &model = line[col];
            double red = qRed(model);
            double green = qGreen(model);
            double blue = qBlue(model);

            cmyk = new ColourModel_CMYK(_colorConversion->RGBtoCMYK(new ColourModel_RGB(red,green,blue)));

            double cyan = abs(cmyk->getCyan());
            double magenta = abs(cmyk->getMagenta());
            double yellow = abs(cmyk->getYellow());
            double black = abs(cmyk->getBlack());

            ++frst_Values[magenta];
            ++scnd_Values[yellow];
            ++thrd_Values[cyan];
            ++fourth_Values[black];

            //used for the change of the pixels in the picture
            rgb = new ColourModel_RGB(_colorConversion->CMYKtoRGB(cmyk));
            int newRed = abs(rgb->getRed());
            int newGreen = abs(rgb->getGreen());
            int newBlue = abs(rgb->getBlue());

            model = qRgb(newRed, newGreen, newBlue); // update pixel colour

            //deallocate memory
            delete cmyk;
            delete rgb;
        }
    }

    frstColor = Qt::magenta;
    scndColor = Qt::yellow;
    thrdColor = Qt::cyan;
    fourthColor = Qt::black;

    frstColorName = "Magenta";
    scndColorName = "Yellow";
    thrdColorName = "Cyan";
    fourthColorName = "Black";

    setChartCMYK();

    return image;
}

//set hsi histogram
QImage RGBHistogramWidget::setImageHSI(QImage &image)
{
    //clear the chart, before updating it
    clearColourSets();

    frst_Values.resize(361);
    scnd_Values.resize(361);
    thrd_Values.resize(361);

    frst_Values.fill(0);
    scnd_Values.fill(0);
    thrd_Values.fill(0);

    for (int row = 0; row < image.height(); ++row) {
        QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(row));
        for (int col = 0; col < image.width(); ++col) {
            QRgb &model = line[col];
            double red = qRed(model);
            double green = qGreen(model);
            double blue = qBlue(model);

            hsi = new ColourModel_HSI(_colorConversion->RGBtoHSI(new ColourModel_RGB(red,green,blue)));

            double hue = hsi->getHue();
            double saturation = hsi->getSaturation();
            double intensity = hsi->getIntensity();

            ++frst_Values[hue];
            ++scnd_Values[saturation];
            ++thrd_Values[intensity];

            double newRed = qRound((hsi->getHue() / 360) * 255);
            double newGreen = qRound((hsi->getSaturation() / 100) * 255);
            double newBlue = hsi->getIntensity();
            model = qRgb(newRed, newGreen, newBlue); // update image

            //deallocate memory
            delete hsi;
        }
    }

    frstColor = Qt::black;
    scndColor = Qt::darkGray;
    thrdColor = Qt::lightGray;
    fourthColor = Qt::transparent;

    frstColorName = "Hue";
    scndColorName = "Saturation";
    thrdColorName = "Intensity";
    fourthColorName = "";

    setChart();

    return image;
}

//clear already loaded set data
void RGBHistogramWidget::clearColourSets(){
    //clear previous data
    frstColorSet->remove(0, 360);
    scndColorSet->remove(0, 360);
    thrdColorSet->remove(0, 360);
    fourthColorSet->remove(0, 360);
}

//set labels and colors to the chart
void RGBHistogramWidget::setColourSets(){
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
}

//set chart axis
void RGBHistogramWidget::setHistogramChartXYAxis(int maxValAxisX, int maxValAxisY){

    //create the default axis
    histogramChart->createDefaultAxes(); // set the axis

    //set x axis
    histogramChart->axes(Qt::Horizontal).back()->setRange(0, maxValAxisX);
    histogramChart->axes(Qt::Horizontal).back()->setTitleText("axis x");
    histogramChart->axes(Qt::Horizontal).back()->setGridLineVisible(false);

    //set y axis
    histogramChart->axes(Qt::Vertical).back()->setRange(0, maxValAxisY);
    histogramChart->axes(Qt::Vertical).back()->setTitleText("axis y");
}

//draw RGB/CMY/HSI histogram
void RGBHistogramWidget::setChart(){

    //set labels and colors to the chart
    setColourSets();

    //get the max element of the vectors, to use to calculate the percentages
    double maxFrstVectorValue = *std::max_element(frst_Values.constBegin(), frst_Values.constEnd());
    double maxScndVectorValue = *std::max_element(scnd_Values.constBegin(), scnd_Values.constEnd());
    double maxThrdVectorValue = *std::max_element(thrd_Values.constBegin(), thrd_Values.constEnd());

    //add the values to the series
    for(int i = 0; i < frst_Values.length() - 1; i++){
        *frstColorSet << (frst_Values.at(i) / maxFrstVectorValue)*100;
        *scndColorSet << (scnd_Values.at(i) / maxScndVectorValue)*100;
        *thrdColorSet << (thrd_Values.at(i) / maxThrdVectorValue)*100;
    }

    //set histogram axis
    setHistogramChartXYAxis(frst_Values.length(), 100);
}

//draw CMYK histogram
void RGBHistogramWidget::setChartCMYK(){

    //set labels and colors to the chart
    setColourSets();

    //get max element from the vectors to calculate the percentages
    double maxFrstVectorValue = *std::max_element(frst_Values.constBegin(), frst_Values.constEnd());
    double maxScndVectorValue = *std::max_element(scnd_Values.constBegin(), scnd_Values.constEnd());
    double maxThrdVectorValue = *std::max_element(thrd_Values.constBegin(), thrd_Values.constEnd());
    double maxFourthVectorValue = *std::max_element(fourth_Values.constBegin(), fourth_Values.constEnd());

    //add the values to the series
    for(int i = 0; i < frst_Values.length() - 1; i++){
        *frstColorSet << ((frst_Values.at(i) / maxFrstVectorValue) * 100);
        *scndColorSet << ((scnd_Values.at(i) / maxScndVectorValue)* 100);
        *thrdColorSet << ((thrd_Values.at(i) / maxThrdVectorValue) * 100);
        *fourthColorSet << ((fourth_Values.at(i) / maxFourthVectorValue) * 100);
    }

    //set histogram axis
    setHistogramChartXYAxis(frst_Values.length(), 100);
}
