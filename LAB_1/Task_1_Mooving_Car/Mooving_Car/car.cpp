#include "car.h"


Car::Car(int ySpred) : Rectangle(ySpred)
{
    setFlag(ItemIsMovable);
}


QRectF Car::boundingRect() const
{
    return QRectF(-10, 0, 2560, 1600);

}


void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Rectangle::paint(painter, option);

    QRectF circle = QRectF(OnX - 5, OnY + 100, 80, 80);
    QRectF circle_2(OnX + 225, OnY + 100, 80, 80);
    QBrush brush(Qt::red);
    brush.setColor(Qt::blue);

    painter->drawEllipse(circle);
    painter->drawEllipse(circle_2);

}

