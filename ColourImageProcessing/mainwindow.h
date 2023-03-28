#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QFrame>
#include <QMessageBox>
#include <QFileDialog>
#include <QPalette>
#include <QDebug>

#include "rgbhistogramwidget.h"
#include "ui_mainwindow.h"
#include "colourmodel_rgb.h"
#include "colourmodel_cmy.h"
#include "colourmodel_cmyk.h"
#include "colourmodel_hsi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Open_Clicked();
    void on_Save_Clicked();
    void colourModelComboBox_CurrentIndexChanged(int index);

private:
    //functions
    void initWidget();
    void connectSignals();

    //UI Widget initialization
    QWidget* ui_centralWidget;

    QHBoxLayout* widgetLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* imageViewerLayout;
    QVBoxLayout* colourModelLayout;
    QVBoxLayout* centralWidgetLayout;

    QLineEdit* openPath;

    QPushButton* openImage;
    QPushButton* saveImage;

    QLabel* header;
    QLabel* imageViewer;

    QScrollArea* imageScroller;

    QFrame* decorativeLine1;
    QFrame* decorativeLine2;

    QComboBox* colourModelComboBox;

    QString fileName;

    RGBHistogramWidget* RGB_histogram; //HistogramWidget

    //colourModels
    ColourModel_RGB* primary_RGB = new ColourModel_RGB(0, 0, 0);
    ColourModel_RGB* derived_RGB = new ColourModel_RGB(0, 0, 1);

    ColourModel_CMY* primary_CMY = new ColourModel_CMY(0,0,0);
    ColourModel_CMY* derived_CMY = new ColourModel_CMY(0,0,1);

    ColourModel_CMYK* primary_CMYK = new ColourModel_CMYK(0,0,0,0);
    ColourModel_CMYK* derived_CMYK = new ColourModel_CMYK(0,0,0,1);

    ColourModel_HSI* primary_HSI = new ColourModel_HSI(0,0,0);
    ColourModel_HSI* derived_HSI = new ColourModel_HSI(0,0,1);

    //colours
    int red;
    int green;
    int blue;

    double cyan;
    double magenta;
    double yellow;
    double black;

    double hue;
    double saturation;
    double intensity;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
