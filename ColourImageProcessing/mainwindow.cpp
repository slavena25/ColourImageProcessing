#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWidget();
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//initialize widgets
void MainWindow::initWidget(){

    this->setWindowTitle("Image Colour Processing");

    //to be implemented --> app icon
    //this->setWindowIcon(QIcon("icons/icon.png"));

    ui_centralWidget = new QWidget();

    //------------------ImageViewer Layout------------------

    openPath = new QLineEdit();
    openPath->setPlaceholderText("choose an image to open...");
    openPath->setReadOnly(true);

    openImage = new QPushButton("Open");
    saveImage = new QPushButton("Save");

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(openPath);
    buttonLayout->addWidget(openImage);
    buttonLayout->addWidget(saveImage);

    imageViewer = new QLabel();
    imageViewer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageViewer->setMinimumSize(350,350);

    imageScroller = new QScrollArea();
    imageScroller->setBackgroundRole(QPalette::Base);
    imageScroller->setWidget(imageViewer);

    imageViewerLayout = new QVBoxLayout();
    imageViewerLayout->addLayout(buttonLayout);
    imageViewerLayout->addWidget(imageScroller);


    //------------------ColourModel Layout------------------

    colourModelComboBox = new QComboBox();
    colourModelComboBox->addItem("RGB");
    colourModelComboBox->addItem("CMY");
    colourModelComboBox->addItem("CMYK");
    colourModelComboBox->addItem("HSI");

    RGB_histogram = new RGBHistogramWidget();

    colourModelLayout = new QVBoxLayout();
    colourModelLayout->addWidget(colourModelComboBox);
    colourModelLayout->addWidget(RGB_histogram);

    //------------------Image and ColourModel Layout------------------

    decorativeLine1 = new QFrame();
    decorativeLine1->setFrameShape(QFrame::VLine);
    decorativeLine1->setFrameShadow(QFrame::Sunken);

    widgetLayout = new QHBoxLayout();
    widgetLayout->addLayout(imageViewerLayout, 1);
    widgetLayout->addWidget(decorativeLine1);
    widgetLayout->addLayout(colourModelLayout, 1);

    //------------------Widget Layout------------------

    header = new QLabel("Colour Image Processing Application");

    QFont headerFont("Segou", 11, QFont::Bold);
    header->setFont(headerFont);

    decorativeLine2 = new QFrame();
    decorativeLine2->setFrameShape(QFrame::HLine);
    decorativeLine2->setFrameShadow(QFrame::Sunken);

    centralWidgetLayout = new QVBoxLayout;
    centralWidgetLayout->addWidget(header);
    centralWidgetLayout->addWidget(decorativeLine2);
    centralWidgetLayout->addLayout(widgetLayout, 1);

    ui_centralWidget->setLayout(centralWidgetLayout);
    this->setCentralWidget(ui_centralWidget);
}

//connect signals
void MainWindow::connectSignals(){
    QObject::connect(openImage, SIGNAL(clicked()), this, SLOT(on_Open_Clicked()));
    QObject::connect(saveImage, SIGNAL(clicked()), this, SLOT(on_Save_Clicked()));
}

void MainWindow::on_Open_Clicked(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png *.jpg *.bmp *.tiff)");
    if(fileName.isEmpty()){
        return;
    }

    openPath->insert(fileName);
    openPath->setCursorPosition(0);
    openPath->setToolTip(fileName);

    QImage image(fileName);
    if(image.isNull()){
        QMessageBox::warning(this, "Error", "Failed to open image.");
    }else{
        //display the image
        imageViewer->setPixmap(QPixmap::fromImage(image));
        imageViewer->resize(image.size());

        //display the histogram
        //IDEA:: use the CurrentIndexChanged signal for QComboBox
        //The signal will detect every time the QComboBox is opened and a different option is choosen
        //The comboBox will be initally empty or will have a PlaceholderText --> "Choose Model"
        //Leave an if/else here, that will check if anything is selected in the QComboBox upon opening an image
        //and call the CurrentIndexChanged signal if needed
        QString colourModel = colourModelComboBox->currentText();
                        if (colourModel == "RGB") {
                            RGB_histogram->setImage(image);
                        } else if (colourModel == "CMY") {
                            //Apply CMY image processing
                            //...
                        } else if (colourModel == "CMYK") {
                            // Apply CMYK image processing
                            // ...
                        } else if (colourModel == "HSI") {
                            // Apply HSI image processing
                            // ...
                        }

    }
}

void MainWindow::on_Save_Clicked(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Image Files (*.png *.jpg *.bmp *.tiff)");
    if(fileName.isEmpty()){
        return;
    }

    QImage image = imageViewer->pixmap().toImage();
    if (image.save(fileName)) {
        QMessageBox::information(this, "Save Image", "Image saved successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save image.");
    }

}
