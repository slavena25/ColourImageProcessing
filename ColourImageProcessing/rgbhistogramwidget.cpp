#include "rgbhistogramwidget.h"

RGBHistogramWidget::RGBHistogramWidget(QWidget *parent) : QWidget(parent)
{
    HistogramWidgetInit();
}

void RGBHistogramWidget::HistogramWidgetInit(){
    //universal vectors that will be used in setChart()
    //the vectors will be reset and new values will be added to them every time;
    //resize the vectors to 360, because that is what hsi uses as values
//    frst_Values.resize(360);
//    scnd_Values.resize(360);
//    thrd_Values.resize(360);
//    fourth_Values.resize(360);

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

    ChoosenImageColourType = ImageColourType::RGB;

    frst_Values.resize(256);
    scnd_Values.resize(256);
    thrd_Values.resize(256);
    fourth_Values.resize(256);

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

            QColor newCmyColour(red, green, blue);
            image.setPixelColor(col, row, newCmyColour);

            ++frst_Values[red];
            ++scnd_Values[green];
            ++thrd_Values[blue];
        }
    }

    frstColor = Qt::red;
    scndColor = Qt::green;
    thrdColor = Qt::blue;
    fourthColor = Qt::transparent;

    frstColorName = "Red";
    scndColorName = "Blue";
    thrdColorName = "Green";
    fourthColorName = "";

    setChart();
}

//set cmy histogram
QImage RGBHistogramWidget::setImageCMY(QImage &image)
{
    //clear the chart, before updating it
    clearColourSets();

    ChoosenImageColourType = ImageColourType::CMY;

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

            QColor newCmyColour(newRed, newGreen, newBlue);
            image.setPixelColor(col, row, newCmyColour);
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

    ChoosenImageColourType = ImageColourType::CMYK;

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
            int newRed = rgb->getRed();
            int newGreen = rgb->getGreen();
            int newBlue = rgb->getBlue();
            QColor newCmykColour(newRed, newGreen, newBlue);
            //QColor newCmykColour(red, green, blue, 255);
            //QColor newColor = QColor::fromCmyk(cmyk->getCyan(), cmyk->getMagenta(), cmyk->getYellow(), cmyk->getBlack(), 255);
            image.setPixelColor(col, row, newCmykColour);
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

    ChoosenImageColourType = ImageColourType::HSI;

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

//            rgb = new ColourModel_RGB(_colorConversion->HSItoRGB(hsi));
//            int newRed = abs(rgb->getRed());
//            int newGreen = abs(rgb->getGreen());
//            int newBlue = abs(rgb->getBlue());
//            //QRgb &model = line[col];
//            //model = qRgba(qRed(newRed), qGreen(newGreen), qBlue(newBlue), qAlpha(model));
//            QColor newCmyColour(newRed, newGreen, newBlue);
//            image.setPixelColor(col, row, newCmyColour);
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

void RGBHistogramWidget::clearColourSets(){
    frstColorSet->remove(0, 360);
    scndColorSet->remove(0, 360);
    thrdColorSet->remove(0, 360);
    fourthColorSet->remove(0, 360);
}

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

void RGBHistogramWidget::setHistogramChartXYAxis(int maxValAxisX, int maxValAxisY){

    //create the default axis
    histogramChart->createDefaultAxes(); // set the axis
    histogramChart->axes(Qt::Horizontal).back()->setRange(0, maxValAxisY);
    histogramChart->axes(Qt::Horizontal).back()->setTitleText("axis x");
    histogramChart->axes(Qt::Horizontal).back()->setGridLineVisible(false);

    histogramChart->axes(Qt::Vertical).back()->setRange(0, maxValAxisX);
    histogramChart->axes(Qt::Vertical).back()->setTitleText("axis y");
}

void RGBHistogramWidget::setChart(){

    setColourSets();

    //add the values to the series
    //in every function add the vectors a list and then here have a cycle within the cycle which reads the
    for(int i = 0; i < frst_Values.length() - 1; i++){
        *frstColorSet << frst_Values.at(i);
        *scndColorSet << scnd_Values.at(i);
        *thrdColorSet << thrd_Values.at(i);
    }

    //get the max numerical value from all the vectors
    double maxValue = std::max(
        *std::max_element(frst_Values.constBegin(), frst_Values.constEnd()),
        std::max(
            *std::max_element(scnd_Values.constBegin(), scnd_Values.constEnd()),
                *std::max_element(thrd_Values.constBegin(), thrd_Values.constEnd())
            )
        );

    setHistogramChartXYAxis(maxValue, frst_Values.length() - 1);
}

void RGBHistogramWidget::setChartCMYK(){

    setColourSets();

    //add the values to the series
    //in every function add the vectors a list and then here have a cycle within the cycle which reads the
    for(int i = 0; i < frst_Values.length() - 1; i++){
        *frstColorSet << frst_Values.at(i);
        *scndColorSet << scnd_Values.at(i);
        *thrdColorSet << thrd_Values.at(i);
        *fourthColorSet << fourth_Values.at(i);
    }

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

    setHistogramChartXYAxis(maxValue, frst_Values.length() - 1);
}
