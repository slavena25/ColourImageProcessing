#include "mainwindow.h"

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

    //------------------Change Colour Channel------------------

    getColourChannelLabel = new QLabel("Get desired colour channel:");
    getColourChannelLabel->setVisible(false);

    getRed = new QLineEdit();
    getRed->setValidator(new QIntValidator(0, 256, this));
    getRed->setPlaceholderText("red");
    getRed->setVisible(false);

    getGreen = new QLineEdit();
    getGreen->setValidator(new QIntValidator(0, 256, this));
    getGreen->setPlaceholderText("green");
    getGreen->setVisible(false);

    getBlue = new QLineEdit();
    getBlue->setValidator(new QIntValidator(0, 256, this));
    getBlue->setPlaceholderText("blue");
    getBlue->setVisible(false);

    getColourChannelLayout = new QHBoxLayout;
    getColourChannelLayout->addWidget(getRed);
    getColourChannelLayout->addWidget(getGreen);
    getColourChannelLayout->addWidget(getBlue);

    setColourChannelLabel = new QLabel("Set desired colour channel:");
    setColourChannelLabel->setVisible(false);

    setRed = new QLineEdit();
    setRed->setValidator(new QIntValidator(0, 256, this));
    setRed->setPlaceholderText("new Red");
    setRed->setVisible(false);

    setGreen = new QLineEdit();
    setGreen->setValidator(new QIntValidator(0, 256, this));
    setGreen->setPlaceholderText("new green");
    setGreen->setVisible(false);

    setBlue = new QLineEdit();
    setBlue->setValidator(new QIntValidator(0, 256, this));
    setBlue->setPlaceholderText("new blue");
    setBlue->setVisible(false);

    setColourChannelLayout = new QHBoxLayout;
    setColourChannelLayout->addWidget(setRed);
    setColourChannelLayout->addWidget(setGreen);
    setColourChannelLayout->addWidget(setBlue);

    changeColourChannelButton = new QPushButton("Change Colour Channel");
    changeColourChannelButton->setVisible(false);

    revertImageButton = new QPushButton("Revert Image to original");
    revertImageButton->setVisible(false);

    colourChangingButtonLayout = new QHBoxLayout;
    colourChangingButtonLayout->addWidget(changeColourChannelButton);
    colourChangingButtonLayout->addWidget(revertImageButton);

    changeColourChannelLayout = new QVBoxLayout;
    changeColourChannelLayout->addWidget(getColourChannelLabel, 0, Qt::AlignHCenter);
    changeColourChannelLayout->addLayout(getColourChannelLayout);
    changeColourChannelLayout->addWidget(setColourChannelLabel, 0, Qt::AlignHCenter);
    changeColourChannelLayout->addLayout(setColourChannelLayout);
    changeColourChannelLayout->addLayout(colourChangingButtonLayout);

    //------------------QShortcut that will hide the colour channel changing section------------------
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT(on_ShortcutHideColourChangingCannel_clicked()));

    //------------------ImageViewer Layout------------------

    openPath = new QLineEdit();
    openPath->setPlaceholderText("choose an image to open...");
    openPath->setReadOnly(true);

    openImage = new QPushButton("Open");
    saveImage = new QPushButton("Save");

    ShowChangeChannelBox = new QPushButton("🎨");
    ShowChangeChannelBox->setFixedHeight(22);
    ShowChangeChannelBox->setFixedWidth(30);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(openPath);
    buttonLayout->addWidget(openImage);
    buttonLayout->addWidget(saveImage);
    buttonLayout->addWidget(ShowChangeChannelBox);

    imageViewer = new QLabel();
    imageViewer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageViewer->setMinimumSize(350,350);

    imageScroller = new QScrollArea();
    imageScroller->setBackgroundRole(QPalette::Base);
    imageScroller->setWidget(imageViewer);

    imageViewerLayout = new QVBoxLayout();
    imageViewerLayout->addLayout(buttonLayout);
    imageViewerLayout->addWidget(imageScroller);
    imageViewerLayout->addLayout(changeColourChannelLayout);

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
    QObject::connect(ShowChangeChannelBox, SIGNAL(clicked()), this, SLOT(on_ShowChangeChannelBox_clicked()));
    QObject::connect(changeColourChannelButton, SIGNAL(clicked()), this, SLOT(on_ChangeColourChannelButton_clicked()));
    QObject::connect(revertImageButton, SIGNAL(clicked()), this, SLOT(on_RevertImageButton_clicked()));
    QObject::connect(colourModelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(colourModelComboBox_CurrentIndexChanged(int)));
}

void MainWindow::on_Open_Clicked(){
    //when opening a file, chech if the qLineEdit, that will display the path is empty
    if(!openPath->text().isEmpty()){
        openPath->clear();
    }

    //open file, if file is empty - do nothing
    fileName = QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png *.jpg *.bmp *.tiff)");
    if(fileName.isEmpty()){
        return;
    }

    //display the path to the file in the qLineEdit
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
        //move this if/else to the CurrentIndexChanged function
        //fix RGBHistogramWidget and make it work with all colour models?
        QString colourModel = colourModelComboBox->currentText();
                        if (colourModel == "RGB") {
                            RGB_histogram->setImageRGB(image);
                        } else if (colourModel == "CMY") {
                            RGB_histogram->setImageCMY(image);
                        } else if (colourModel == "CMYK") {
                            RGB_histogram->setImageCMYK(image);
                        } else if (colourModel == "HSI") {
                            RGB_histogram->setImageHSI(image);
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

void MainWindow::on_ShowChangeChannelBox_clicked(){
    getColourChannelLabel->setVisible(true);
    getRed->setVisible(true);
    getGreen->setVisible(true);
    getBlue->setVisible(true);
    setColourChannelLabel->setVisible(true);
    setRed->setVisible(true);
    setGreen->setVisible(true);
    setBlue->setVisible(true);
    changeColourChannelButton->setVisible(true);
    revertImageButton->setVisible(true);
}

void MainWindow::on_ShortcutHideColourChangingCannel_clicked(){
    getColourChannelLabel->setVisible(false);
    getRed->setVisible(false);
    getGreen->setVisible(false);
    getBlue->setVisible(false);
    setColourChannelLabel->setVisible(false);
    setRed->setVisible(false);
    setGreen->setVisible(false);
    setBlue->setVisible(false);
    changeColourChannelButton->setVisible(false);
    revertImageButton->setVisible(false);
}

void MainWindow::on_ChangeColourChannelButton_clicked(){

    QImage _changedImage(fileName);

    int getR = getRed->text().toInt();
    int getG = getGreen->text().toInt();
    int getB = getBlue->text().toInt();

    int setR = setRed->text().toInt();
    int setG = setGreen->text().toInt();
    int setB = setBlue->text().toInt();

    for(int row = 0; row < _changedImage.height(); row++){
        for(int col = 0; col < _changedImage.width(); col++){
            QColor _pixelColour = _changedImage.pixelColor(col, row);
            QColor _searchColour(getR, getG, getB);
            QColor _newColour(setR, setG, setB);
            if(_pixelColour == _searchColour){
                _changedImage.setPixelColor(col, row, _newColour);
            }
        }
    }

    imageViewer->setPixmap(QPixmap::fromImage(_changedImage));
}

void MainWindow::on_RevertImageButton_clicked(){
    QImage _originalImage(fileName);
    imageViewer->setPixmap(QPixmap::fromImage(_originalImage));
}

void MainWindow::colourModelComboBox_CurrentIndexChanged(int index){
    QImage image(fileName);
    QString colourModel = colourModelComboBox->currentText();
    if (colourModel == "RGB") {
        RGB_histogram->setImageRGB(image);
    } else if (colourModel == "CMY") {
        RGB_histogram->setImageCMY(image);
    } else if (colourModel == "CMYK") {
        RGB_histogram->setImageCMYK(image);
    } else if (colourModel == "HSI") {
        RGB_histogram->setImageHSI(image);
    }
}
