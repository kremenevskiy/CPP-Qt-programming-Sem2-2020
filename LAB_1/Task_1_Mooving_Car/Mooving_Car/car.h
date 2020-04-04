#ifndef CAR_H
#define CAR_H

#include <rectangle.h>
#include <QDebug>



class Car : public Rectangle
{
public:
    Car(int ySpred);

protected:

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected slots:
    void creating();

};

#endif // CAR_H
