#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QGraphicsRectItem>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <cmath>


class Rectangle : public QGraphicsItem
{

public:
    Rectangle(int ySpred);

protected:
    QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    int OnX = 0;
    int OnY = 0;

protected slots:
    void creating();
    void advance(int phase) override;
};

#endif // RECTANGLE_H
