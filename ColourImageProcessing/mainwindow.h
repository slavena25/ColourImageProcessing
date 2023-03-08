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


private:

    void initWidget();
    void connectSignals();

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
    QLabel* colourModelViewer;

    QScrollArea* imageScroller;

    QFrame* decorativeLine1;
    QFrame* decorativeLine2;

    QComboBox* colourModelComboBox;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
