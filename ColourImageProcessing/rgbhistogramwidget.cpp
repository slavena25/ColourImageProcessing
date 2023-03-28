#include "rgbhistogramwidget.h"
#include <stdlib.h>

RGBHistogramWidget::RGBHistogramWidget(QWidget *parent) : QWidget(parent)
{
    m_redValues.resize(256);
    m_greenValues.resize(256);
    m_blueValues.resize(256);

    _colorConversion = new ColorConversion();
}

void RGBHistogramWidget::setImageCMY(const QImage &image)
{
    m_redValues.fill(0);
    m_greenValues.fill(0);
    m_blueValues.fill(0);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            cmy = new ColourModel_CMY(_colorConversion->RGBtoCMY(new ColourModel_RGB(red,green,blue)));
            rgb_main = new ColourModel_RGB(_colorConversion->CMYtoRGB(cmy));

            red = abs(rgb_main->getRed());
            green = abs(rgb_main->getGreen());
            blue = abs(rgb_main->getBlue());


            ++m_redValues[red];
            ++m_greenValues[green];
            ++m_blueValues[blue];
        }
    }

    update();
}

void RGBHistogramWidget::setImageRGB(const QImage &image)
{
    m_redValues.fill(0);
    m_greenValues.fill(0);
    m_blueValues.fill(0);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);


            ++m_redValues[red];
            ++m_greenValues[green];
            ++m_blueValues[blue];
        }
    }

    update();
}

void RGBHistogramWidget::setImageCMYK(const QImage &image)
{
    m_redValues.fill(0);
    m_greenValues.fill(0);
    m_blueValues.fill(0);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            cmyk = new ColourModel_CMYK(_colorConversion->RGBtoCMYK(new ColourModel_RGB(red,green,blue)));
            rgb_main = new ColourModel_RGB(_colorConversion->CMYKtoRGB(cmyk));

            int r = qRed(rgb_main->getRed());
            int g = qGreen(rgb_main->getGreen());
            int b = qBlue(rgb_main->getBlue());


            ++m_redValues[r];
            ++m_greenValues[g];
            ++m_blueValues[b];
        }
    }

    update();
}

void RGBHistogramWidget::setImageHSI(const QImage &image)
{

    m_redValues.fill(0);
    m_greenValues.fill(0);
    m_blueValues.fill(0);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            hsi = new ColourModel_HSI(_colorConversion->RGBtoHSI(new ColourModel_RGB(red,green,blue)));
            rgb_main = new ColourModel_RGB(_colorConversion->HSItoRGB(hsi));

            int r = qRed(rgb_main->getRed());
            int g = qGreen(rgb_main->getGreen());
            int b = qBlue(rgb_main->getBlue());


            ++m_redValues[r];
            ++m_greenValues[g];
            ++m_blueValues[b];
        }
    }

    update();
}

void RGBHistogramWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

      QPainter painter(this);

      //paint the x and y axes

      int barWidth = width() / 255;
          int barHeight = height() - 20;

          // Draw the x-axis
          painter.drawLine(0, height() - 20, width(), height() - 20);

          // Draw the y-axis
          painter.drawLine(20, 0, 20, height());

                // drawing the labels on the histogram widget
              painter.drawText(0, height(), QString("0"));
              painter.drawText(width() - 20, height(), QString("255"));


              painter.drawText(0, 10, QString("%1").arg(barHeight));
              painter.drawText(0, height() - 20, QString("0"));

          for (int i = 0; i < 255; ++i) {
              int redHeight = m_redValues[i] * height() / (width() * height());
              int greenHeight = m_greenValues[i] * height() / (width() * height());
              int blueHeight = m_blueValues[i] * height() / (width() * height());

              QRect blueBar(i * barWidth + 20, height() - blueHeight - 20, barWidth, blueHeight);
              QRect greenBar(i * barWidth + 20, height() - blueHeight - greenHeight - 20, barWidth, greenHeight);
              QRect redBar(i * barWidth + 20, height() - blueHeight - greenHeight - redHeight - 20, barWidth, redHeight);

              painter.fillRect(redBar, Qt::red);
              painter.fillRect(greenBar, Qt::green);
              painter.fillRect(blueBar, Qt::blue);


      }
  }
