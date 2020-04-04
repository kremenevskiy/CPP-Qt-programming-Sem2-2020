#include "rectangle.h"

Rectangle::Rectangle(int ySpred)
{
    setFlag(ItemIsMovable);
    OnY = ySpred;


}

QRectF Rectangle::boundingRect() const{
    return QRectF(0,0,2560,3000);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    static int i = 1;

    QRectF rect = QRectF(OnX, OnY, 300, 100);
    QBrush brush(Qt::blue);
    QColor color = QColor(rand() & 255, rand() & 255, rand() & 255);
    brush.setColor(color);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);


}

void Rectangle::advance(int phase){
    if (phase){
        moveBy(2, 0);
    }
}




//void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event){
//    delete this;
//}
