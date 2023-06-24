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
    deleteTempImage();
    delete ui;
}

//initialize widgets
void MainWindow::initWidget(){

    this->setWindowTitle("Image Colour Processing");

    //to be implemented --> app icon
    //this->setWindowIcon(QIcon("icons/icon.png"));

    ui_centralWidget = new QWidget();

    //------------------Change Pixel Colour------------------

    //GET PIXEL COLOURS
    swapPixelColourLabel = new QLabel("Swap Pixel Colours");
    swapPixelColourLabel->setVisible(false);

    getPixelRed = new QLineEdit();
    getPixelRed->setValidator(new QIntValidator(0, 255, this));
    getPixelRed->setPlaceholderText("GetRed");
    getPixelRed->setVisible(false);

    getPixelGreen = new QLineEdit();
    getPixelGreen->setValidator(new QIntValidator(0, 255, this));
    getPixelGreen->setPlaceholderText("GetGreen");
    getPixelGreen->setVisible(false);

    getPixelBlue = new QLineEdit();
    getPixelBlue->setValidator(new QIntValidator(0, 255, this));
    getPixelBlue->setPlaceholderText("GetBlue");
    getPixelBlue->setVisible(false);

    getPixelColourLayout = new QHBoxLayout;
    getPixelColourLayout->addWidget(getPixelRed);
    getPixelColourLayout->addWidget(getPixelGreen);
    getPixelColourLayout->addWidget(getPixelBlue);

    //SET PIXEL COLOURS
    setPixelRed = new QLineEdit();
    setPixelRed->setValidator(new QIntValidator(0, 255, this));
    setPixelRed->setPlaceholderText("SetRed");
    setPixelRed->setVisible(false);

    setPixelGreen = new QLineEdit();
    setPixelGreen->setValidator(new QIntValidator(0, 255, this));
    setPixelGreen->setPlaceholderText("SetGreen");
    setPixelGreen->setVisible(false);

    setPixelBlue = new QLineEdit();
    setPixelBlue->setValidator(new QIntValidator(0, 255, this));
    setPixelBlue->setPlaceholderText("SetBlue");
    setPixelBlue->setVisible(false);

    setPixelColourLayout = new QHBoxLayout;
    setPixelColourLayout->addWidget(setPixelRed);
    setPixelColourLayout->addWidget(setPixelGreen);
    setPixelColourLayout->addWidget(setPixelBlue);

    //PIXEL SWAP LAYOUT
    changePixelColourButton = new QPushButton("SWAP!");
    changePixelColourButton->setVisible(false);

    changePixelColourLayout = new QVBoxLayout;
    changePixelColourLayout->addWidget(swapPixelColourLabel, 0, Qt::AlignHCenter);
    changePixelColourLayout->addLayout(getPixelColourLayout);
    changePixelColourLayout->addLayout(setPixelColourLayout);
    changePixelColourLayout->addWidget(changePixelColourButton);

    //------------------QShortcut that will hide the colour channel changing section------------------

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_ShowRedChannelChangeBox_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_G), this, SLOT(on_ShowGreenChannelChangeBox_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_B), this, SLOT(on_ShowBlueChannelChangeBox_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this, SLOT(on_ShowSwapPixelColourBox_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_H), this, SLOT(on_HideOpenOptions_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(on_RevertImageButton_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this, SLOT(on_Information_clicked()));

    //------------------Change Colour Channel------------------

    //Red Colour Channel Change
    setRedChannel = new QLineEdit();
    setRedChannel->setValidator(new QIntValidator(0, 255, this));
    setRedChannel->setPlaceholderText("Red Channel Value");
    setRedChannel->setVisible(false);

    changeRedChannelButton = new QPushButton("Change Red Channel");
    changeRedChannelButton->setFixedHeight(22);
    changeRedChannelButton->setVisible(false);

    redColourChannelLayout = new QHBoxLayout;
    redColourChannelLayout->addWidget(setRedChannel);
    redColourChannelLayout->addWidget(changeRedChannelButton);

    //Red Colour Channel Change
    setGreenChannel = new QLineEdit();
    setGreenChannel->setValidator(new QIntValidator(0, 255, this));
    setGreenChannel->setPlaceholderText("Green Channel Value");
    setGreenChannel->setVisible(false);

    changeGreenChannelButton = new QPushButton("Change Green Channel");
    changeGreenChannelButton->setFixedHeight(22);
    changeGreenChannelButton->setVisible(false);

    greenColourChannelLayout = new QHBoxLayout;
    greenColourChannelLayout->addWidget(setGreenChannel);
    greenColourChannelLayout->addWidget(changeGreenChannelButton);

    //Red Colour Channel Change
    setBlueChannel = new QLineEdit();
    setBlueChannel->setValidator(new QIntValidator(0, 255, this));
    setBlueChannel->setPlaceholderText("Blue Channel Value");
    setBlueChannel->setVisible(false);

    changeBlueChannelButton = new QPushButton("Change Blue Channel");
    changeBlueChannelButton->setFixedHeight(22);
    changeBlueChannelButton->setVisible(false);

    blueColourChannelLayout = new QHBoxLayout;
    blueColourChannelLayout->addWidget(setBlueChannel);
    blueColourChannelLayout->addWidget(changeBlueChannelButton);


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
    imageViewerLayout->addLayout(changePixelColourLayout);
    imageViewerLayout->addLayout(redColourChannelLayout);
    imageViewerLayout->addLayout(greenColourChannelLayout);
    imageViewerLayout->addLayout(blueColourChannelLayout);

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

    //------------------Options' Buttons Layout------------------

    //add a revert image to original button
    //add a question mark button that opens a qtextbox with all of the shortcuts
    showRedChannelChangeBox = new QPushButton("📕");
    showRedChannelChangeBox->setFixedHeight(40);
    showRedChannelChangeBox->setFixedWidth(30);
    showRedChannelChangeBox->setToolTip("Change Red Global Channel");

    showGreenChannelChangeBox = new QPushButton("📗");
    showGreenChannelChangeBox->setFixedHeight(40);
    showGreenChannelChangeBox->setFixedWidth(30);
    showGreenChannelChangeBox->setToolTip("Change Green Global Channel");

    showBlueChannelChangeBox = new QPushButton("📘");
    showBlueChannelChangeBox->setFixedHeight(40);
    showBlueChannelChangeBox->setFixedWidth(30);
    showBlueChannelChangeBox->setToolTip("Change Blue Global Channel");

    showChangePixelColourBox = new QPushButton("📚");
    showChangePixelColourBox->setFixedHeight(40);
    showChangePixelColourBox->setFixedWidth(30);
    showChangePixelColourBox->setToolTip("Change Pixel Colour");

    revertImageButton = new QPushButton("🔄");
    revertImageButton->setFixedHeight(40);
    revertImageButton->setFixedWidth(30);
    revertImageButton->setToolTip("Revert Image to Original");

    informationButton = new QPushButton("ℹ️");
    informationButton->setFixedHeight(40);
    informationButton->setFixedWidth(30);
    informationButton->setToolTip("Help");

    imageOptionsBarLayout = new QVBoxLayout;
    imageOptionsBarLayout->setAlignment(Qt::AlignCenter);
    imageOptionsBarLayout->addWidget(showRedChannelChangeBox);
    imageOptionsBarLayout->addWidget(showGreenChannelChangeBox);
    imageOptionsBarLayout->addWidget(showBlueChannelChangeBox);
    imageOptionsBarLayout->addWidget(showChangePixelColourBox);
    imageOptionsBarLayout->addWidget(revertImageButton);
    imageOptionsBarLayout->addWidget(informationButton);

    //------------------Image and ColourModel Layout------------------

    decorativeLine1 = new QFrame();
    decorativeLine1->setFrameShape(QFrame::VLine);
    decorativeLine1->setFrameShadow(QFrame::Sunken);

    widgetLayout = new QHBoxLayout();
    widgetLayout->addLayout(imageOptionsBarLayout);
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
    QObject::connect(showRedChannelChangeBox, SIGNAL(clicked()), this, SLOT(on_ShowRedChannelChangeBox_clicked()));
    QObject::connect(changeRedChannelButton, SIGNAL(clicked()), this, SLOT(on_ChangeRedChannelButton_clicked()));
    QObject::connect(showGreenChannelChangeBox, SIGNAL(clicked()), this, SLOT(on_ShowGreenChannelChangeBox_clicked()));
    QObject::connect(changeGreenChannelButton, SIGNAL(clicked()), this, SLOT(on_ChangeGreenChannelButton_clicked()));
    QObject::connect(showBlueChannelChangeBox, SIGNAL(clicked()), this, SLOT(on_ShowBlueChannelChangeBox_clicked()));
    QObject::connect(changeBlueChannelButton, SIGNAL(clicked()), this, SLOT(on_ChangeBlueChannelButton_clicked()));
    QObject::connect(showChangePixelColourBox, SIGNAL(clicked()), this, SLOT(on_ShowSwapPixelColourBox_clicked()));
    QObject::connect(changePixelColourButton, SIGNAL(clicked()), this, SLOT(on_ChangePixelColourButton_clicked()));
    QObject::connect(revertImageButton, SIGNAL(clicked()), this, SLOT(on_RevertImageButton_clicked()));
    QObject::connect(informationButton, SIGNAL(clicked()), this, SLOT(on_Information_clicked()));
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

    //convert image to RGB32 format
    QImage image(fileName);
    image.convertToFormat(QImage::Format_RGB32);

    //get the selected colourmodel and make a copy of the original image
    if(image.isNull()){
        QMessageBox::warning(this, "Error", "Failed to open image.");
    }else{
        //save the image to a temp file
        saveTempImage();
        //display the image and histogram
        colourModelComboBox_CurrentIndexChanged(colourModelComboBox->currentIndex());
    }
}

void MainWindow::on_Save_Clicked(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "ModifiedFile", "PNG Image (*.png);; JPG Image (*.jpg);; BMP Image (*.bmp);; TIFF Image (*.tiff)");
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

void MainWindow::saveTempImage(){

    QImage _originalImage(fileName);

    if(!tempPath.isEmpty()){ //if tempPath is not empty, delete the previously, saved image
        QFile::remove(tempPath);
    }

    QFileInfo fileInfo(fileName);
    tempPath = "tempFiles/temp." + fileInfo.suffix();
    imageViewer->resize(_originalImage.size());
    _originalImage.save(tempPath);
}

void MainWindow::deleteTempImage(){
    if(QFile::exists(tempPath)){
        QFile::remove(tempPath);
    }
}

void MainWindow::setVisiblePixelColourSwapLayout(bool visible){
    swapPixelColourLabel->setVisible(visible);
    getPixelRed->setVisible(visible);
    getPixelGreen->setVisible(visible);
    getPixelBlue->setVisible(visible);
    setPixelRed->setVisible(visible);
    setPixelGreen->setVisible(visible);
    setPixelBlue->setVisible(visible);
    changePixelColourButton->setVisible(visible);
}

void MainWindow::setVisibleRedChannelChangeLayout(bool visible){
    setRedChannel->setVisible(visible);
    changeRedChannelButton->setVisible(visible);
}

void MainWindow::setVisibleGreenChannelChangeLayout(bool visible){
    setGreenChannel->setVisible(visible);
    changeGreenChannelButton->setVisible(visible);
}

void MainWindow::setVisibleBlueChannelChangeLayout(bool visible){
    setBlueChannel->setVisible(visible);
    changeBlueChannelButton->setVisible(visible);
}

void MainWindow::on_ShowRedChannelChangeBox_clicked(){
    //show the red channel change widgets
    setVisibleRedChannelChangeLayout(true);

    //hide other widgets
    setVisiblePixelColourSwapLayout(false);
    setVisibleGreenChannelChangeLayout(false);
    setVisibleBlueChannelChangeLayout(false);
}

void MainWindow::on_ChangeRedChannelButton_clicked(){

    QImage _changedImage(tempPath);
    int rChannelValue = setRedChannel->text().toInt(); // set red channel value

    for (int y = 0; y < _changedImage.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(_changedImage.scanLine(y));
        for (int x = 0; x < _changedImage.width(); ++x) {
            QRgb &rgb = line[x];
            rgb = qRgb(rChannelValue, qGreen(rgb), qBlue(rgb));
        }
    }

    _changedImage.save(tempPath);
    colourModelComboBox_CurrentIndexChanged(colourModelComboBox->currentIndex());
}

void MainWindow::on_ShowGreenChannelChangeBox_clicked(){
    //show green channel change widgets
    setVisibleGreenChannelChangeLayout(true);

    //hide other boxes
    setVisiblePixelColourSwapLayout(false);
    setVisibleRedChannelChangeLayout(false);
    setVisibleBlueChannelChangeLayout(false);
}

void MainWindow::on_ChangeGreenChannelButton_clicked(){

    QImage _changedImage(tempPath);
    int gChannelValue = setGreenChannel->text().toInt(); // set green channel value

    for (int y = 0; y < _changedImage.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(_changedImage.scanLine(y));
        for (int x = 0; x < _changedImage.width(); ++x) {
            QRgb &rgb = line[x];
            rgb = qRgb(qRed(rgb), gChannelValue, qBlue(rgb));
        }
    }

    _changedImage.save(tempPath);
    colourModelComboBox_CurrentIndexChanged(colourModelComboBox->currentIndex());
}

void MainWindow::on_ShowBlueChannelChangeBox_clicked(){
    //show blue channel change widgets
    setVisibleBlueChannelChangeLayout(true);

    //hide other widgets
    setVisiblePixelColourSwapLayout(false);
    setVisibleRedChannelChangeLayout(false);
    setVisibleGreenChannelChangeLayout(false);
}

void MainWindow::on_ChangeBlueChannelButton_clicked(){

    QImage _changedImage(tempPath);
    int bChannelValue = setBlueChannel->text().toInt(); // set blue channel value

    for (int y = 0; y < _changedImage.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(_changedImage.scanLine(y));
        for (int x = 0; x < _changedImage.width(); ++x) {
            QRgb &rgb = line[x];
            rgb = qRgb(qRed(rgb), qGreen(rgb), bChannelValue);
        }
    }

    _changedImage.save(tempPath);
    colourModelComboBox_CurrentIndexChanged(colourModelComboBox->currentIndex());
}

void MainWindow::on_ShowSwapPixelColourBox_clicked(){
    //show pixel swap widgets
    setVisiblePixelColourSwapLayout(true);

    //hide other visible boxes
    setVisibleRedChannelChangeLayout(false);
    setVisibleGreenChannelChangeLayout(false);
    setVisibleBlueChannelChangeLayout(false);
}

void MainWindow::on_ChangePixelColourButton_clicked(){

    QImage _currentImage = imageViewer->pixmap().toImage();

    int getR = getPixelRed->text().toInt();
    int getG = getPixelGreen->text().toInt();
    int getB = getPixelBlue->text().toInt();

    int setR = setPixelRed->text().toInt();
    int setG = setPixelGreen->text().toInt();
    int setB = setPixelBlue->text().toInt();

    for(int row = 0; row < _currentImage.height(); row++){
        for(int col = 0; col < _currentImage.width(); col++){
            QColor _pixelColour = _currentImage.pixelColor(col, row);
            QColor _searchColour(getR, getG, getB);
            QColor _newColour(setR, setG, setB);
            if(_pixelColour == _searchColour){
                _currentImage.setPixelColor(col, row, _newColour);
            }
        }
    }

    imageViewer->setPixmap(QPixmap::fromImage(_currentImage));
}

void MainWindow::on_HideOpenOptions_clicked(){
    setVisiblePixelColourSwapLayout(false);
    setVisibleRedChannelChangeLayout(false);
    setVisibleGreenChannelChangeLayout(false);
    setVisibleBlueChannelChangeLayout(false);
}

void MainWindow::on_RevertImageButton_clicked(){
    saveTempImage();
    colourModelComboBox_CurrentIndexChanged(colourModelComboBox->currentIndex());
}

void MainWindow::on_Information_clicked(){
    QMessageBox shortcutInfo;
    shortcutInfo.setText("Information");
    shortcutInfo.setInformativeText("CTRL+R: Change Red Channel\n"
                                    "CTRL+G: Change Green Channel\n"
                                    "CTRL+B: Change Blue Channel\n"
                                    "CTRL+P: Swap Pixels\n"
                                    "CTRL+H: Hide an Open Colour Option Box\n"
                                    "CTRL+O: Revert Image to Original\n"
                                    "CTRL+I: Open Help Box\n");
    shortcutInfo.setStandardButtons(QMessageBox::Ok);
    shortcutInfo.setDefaultButton(QMessageBox::Ok);
    int ret = shortcutInfo.exec();
}

void MainWindow::colourModelComboBox_CurrentIndexChanged(int index){
    QImage image(tempPath);
    QString colourModel = colourModelComboBox->currentText();
    if (colourModel == "RGB") {
        imageViewer->setPixmap(QPixmap::fromImage(image));
        RGB_histogram->setImageRGB(image);
    } else if (colourModel == "CMY") {
        imageViewer->setPixmap(QPixmap::fromImage(RGB_histogram->setImageCMY(image)));
    } else if (colourModel == "CMYK") {
        imageViewer->setPixmap(QPixmap::fromImage(RGB_histogram->setImageCMYK(image)));
    } else if (colourModel == "HSI") {
        imageViewer->setPixmap(QPixmap::fromImage(RGB_histogram->setImageHSI(image)));
    }
}
