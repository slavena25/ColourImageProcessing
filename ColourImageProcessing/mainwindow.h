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
#include <QShortcut>

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
    void on_ShowRedChannelChangeBox_clicked();
    void on_ChangeRedChannelButton_clicked();
    void on_ShowGreenChannelChangeBox_clicked();
    void on_ChangeGreenChannelButton_clicked();
    void on_ShowBlueChannelChangeBox_clicked();
    void on_ChangeBlueChannelButton_clicked();
    void on_ShowSwapPixelColourBox_clicked();
    void on_ChangePixelColourButton_clicked();
    void on_ShortcutHideColourChangingCannel_clicked();
    void on_RevertImageButton_clicked();
    void colourModelComboBox_CurrentIndexChanged(int index);

private:

    //functions
    void initWidget();
    void connectSignals();
    void setVisiblePixelColourSwapLayout(bool visible);
    void setVisibleRedChannelChangeLayout(bool visible);
    void setVisibleGreenChannelChangeLayout(bool visible);
    void setVisibleBlueChannelChangeLayout(bool visible);
    QImage returnModifiedImage();

    //UI Widget initialization
    QWidget* ui_centralWidget;

    QHBoxLayout* widgetLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* imageViewerLayout;
    QVBoxLayout* colourModelLayout;
    QVBoxLayout* centralWidgetLayout;
    QVBoxLayout* changePixelColourLayout;
    QHBoxLayout* getPixelColourLayout;
    QHBoxLayout* setPixelColourLayout;
    QHBoxLayout* redColourChannelLayout;
    QHBoxLayout* greenColourChannelLayout;
    QHBoxLayout* blueColourChannelLayout;
    QVBoxLayout* imageOptionsBarLayout;

    QLineEdit* openPath;
    QLineEdit* getPixelRed;
    QLineEdit* getPixelGreen;
    QLineEdit* getPixelBlue;
    QLineEdit* setPixelRed;
    QLineEdit* setPixelGreen;
    QLineEdit* setPixelBlue;
    QLineEdit* setRedChannel;
    QLineEdit* setGreenChannel;
    QLineEdit* setBlueChannel;

    QPushButton* openImage;
    QPushButton* saveImage;
    QPushButton* showChangePixelColourBox;
    QPushButton* changePixelColourButton;
    QPushButton* revertImageButton;
    QPushButton* showRedChannelChangeBox;
    QPushButton* changeRedChannelButton;
    QPushButton* showGreenChannelChangeBox;
    QPushButton* changeGreenChannelButton;
    QPushButton* showBlueChannelChangeBox;
    QPushButton* changeBlueChannelButton;
    QPushButton* informationButton;

    QLabel* header;
    QLabel* imageViewer;
    QLabel* swapPixelColourLabel;

    QScrollArea* imageScroller;

    QFrame* decorativeLine1;
    QFrame* decorativeLine2;
    QFrame* decorativeLine3;

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
