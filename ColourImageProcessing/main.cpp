#include "mainwindow.h"
#include <QtWidgets>
#include <QtGui>
#include <QHBoxLayout>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("Image Processing");
    window.show();

    // Create the file menu
    QMenuBar* menuBar = new QMenuBar(&window);
    QMenu* fileMenu = menuBar->addMenu("&File");


    // Create the "Open" action
    QAction* openAction = new QAction("&Open", &window);
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(openAction);

    //save action
    QAction* saveAction = new QAction("&Save As", &window);
    saveAction->setShortcut(QKeySequence::SaveAs);
    fileMenu->addAction(saveAction);

    QComboBox* colorModelMenu = new QComboBox(&window);
        colorModelMenu->addItem("RGB");
        colorModelMenu->addItem("CMY");
        colorModelMenu->addItem("CMYK");
        colorModelMenu->addItem("HSI");


    // Create the image view widget
    QLabel* imageView = new QLabel(&window);
    imageView->setAlignment(Qt::AlignCenter);
    imageView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);




    // Create the main layout
    QVBoxLayout* layout = new QVBoxLayout(&window);

    layout->addWidget(menuBar);
    layout->addWidget(imageView);
    layout->addWidget(colorModelMenu);




    // Connect the "Open" action to a file dialog
    QObject::connect(openAction, &QAction::triggered, [&]() {
        QString fileName = QFileDialog::getOpenFileName(&window,
            "Open Image", "", "Image Files (*.png *.jpg *.bmp *.tiff)");
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (image.isNull()) {
                QMessageBox::warning(&window, "Error", "Failed to open image.");
            } else {
                QString colorModel = colorModelMenu->currentText();
                                if (colorModel == "RGB") {

                                } else if (colorModel == "CMY") {

                                } else if (colorModel == "CMYK") {
                                    // Apply CMYK image processing
                                    // ...
                                } else if (colorModel == "HSI") {
                                    // Apply HSI image processing
                                    // ...
                                }

                imageView->setPixmap(QPixmap::fromImage(image));
                window.resize(image.size());

            }
        }
    });

    QObject::connect(saveAction, &QAction::triggered, [&]() {
           QString fileName = QFileDialog::getSaveFileName(&window, "Save Image", "", "Image Files (*.png *.jpg *.bmp *.tiff)");
           if (!fileName.isEmpty()) {
               QImage image = imageView->pixmap().toImage();
               if (image.save(fileName)) {
                   QMessageBox::information(&window, "Save Image", "Image saved successfully.");
               } else {
                   QMessageBox::warning(&window, "Error", "Failed to save image.");
               }
           }
       });

    return app.exec();
}
