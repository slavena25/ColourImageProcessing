#include "rgbhistogramwidget.h"

RGBHistogramWidget::RGBHistogramWidget(QWidget *parent) : QWidget(parent)
{
    m_redValues.resize(256);
    m_greenValues.resize(256);
    m_blueValues.resize(256);
}

void RGBHistogramWidget::setImage(const QImage &image)
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

void RGBHistogramWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

      QPainter painter(this);

      int barWidth = width() / 256;

          for (int i = 0; i < 256; ++i) {
              int redHeight = m_redValues[i] * height() / (width() * height());
              int greenHeight = m_greenValues[i] * height() / (width() * height());
              int blueHeight = m_blueValues[i] * height() / (width() * height());

              QRect blueBar(i * barWidth, height() - blueHeight, barWidth, blueHeight);
              QRect greenBar(i * barWidth, height() - blueHeight - greenHeight, barWidth, greenHeight);
              QRect redBar(i * barWidth, height() - blueHeight - greenHeight - redHeight, barWidth, redHeight);

              painter.fillRect(redBar, Qt::red);
              painter.fillRect(greenBar, Qt::green);
              painter.fillRect(blueBar, Qt::blue);


      }
  }
