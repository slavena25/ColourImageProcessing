#ifndef RGBHISTOGRAMWIDGET_H
#define RGBHISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPainter>

class RGBHistogramWidget : public QWidget
{
public:
    RGBHistogramWidget(QWidget *parent = nullptr);
    void setImage(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> m_redValues;
    QVector<int> m_greenValues;
    QVector<int> m_blueValues;

};

#endif // RGBHISTOGRAMWIDGET_H
