#include "widget.h"
#include<cmath>
#include<QPainter>

Widget::Widget(QWidget *parent)
: QWidget(parent){
    QLabel* lblParametrA= new QLabel("Parametr a:", this);
    lblParametrA->move(10, 10);
    Box_a=new QDoubleSpinBox(this);
    Box_a->setRange(1, Max_a);
    Box_a->setSingleStep(1.0);
    Box_a->setValue(200);
    Box_a->move(10, 30);

    QLabel* lblStep= new QLabel("Step:", this);
    lblStep->move(10, 60);
    Box_step = new QDoubleSpinBox(this);
    Box_step->setRange(0.01, 1);
    Box_step->setSingleStep(0.01);
    Box_step->setValue(0.1);
    Box_step->move(10, 80);

    connect(Box_a, SIGNAL(valueChanged(double)), this, SLOT(redrawOnValueChange(double)));
    connect(Box_step, SIGNAL(valueChanged(double)), this, SLOT(redrawOnValueChange(double)));

    lblOX= new QLabel("X", this);
    lblOY= new QLabel("Y", this);
    lblO0= new QLabel("0,0", this);
    lblOX100= new QLabel("100", this);
    lblOX_100= new QLabel("-100", this);
    lblOY100= new QLabel("100", this);
    lblOY_100= new QLabel("-100", this);
}

Widget::~Widget(){
}

double Widget::curve(const double fi, const double a){
    return sqrt(a*a*abs(cos(2*fi)));
}
void Widget::redrawOnValueChange(double){
    update();
}

void Widget::paintEvent(QPaintEvent*){
    const double step = Box_step->value(),
                 a =Box_a->value()/Max_a* (height()<width()?height():width()) /2,
                 pi(4*atan(1)),
                 end(2*pi + step);

    QPointF p1(curve(0, a)*cos(0), 0);

    QPainter ptr(this);
    double arrow=5.0; //size of arrow and some things
    ptr.setPen(Qt::black);
 // axis OX
    ptr.drawLine(QPointF(0, height()/2),
                 QPointF(width(), height()/2));
    ptr.drawLine(QPointF(width()-arrow, height()/2+arrow),
                 QPointF(width(), height()/2));
    ptr.drawLine(QPointF(width()-arrow, height()/2-arrow),
                 QPointF(width(), height()/2));
// axis OY
    ptr.drawLine(QPointF(width()/2, 0),
                 QPointF(width()/2, height()));
    ptr.drawLine(QPointF(width()/2-arrow, arrow),
                 QPointF(width()/2, 0));
    ptr.drawLine(QPointF(width()/2+arrow, arrow),
                 QPointF(width()/2, 0));
//marking
    //OX
    for(double step_mark=0.0; step_mark<width(); step_mark+=10/Max_a * (height()<width()?height():width())/2){
        ptr.drawLine(QPointF(width()/2 + step_mark , height()/2 + arrow),
                     QPointF(width()/2 + step_mark, height()/2 - arrow));
        ptr.drawLine(QPointF(width()/2 - step_mark, height()/2 + arrow),
                     QPointF(width()/2 - step_mark, height()/2 - arrow));
    }
    //OY
    for(double step_mark=0.0; step_mark < height(); step_mark+=10/Max_a * (height()<width()?height():width())/2){
        ptr.drawLine(QPointF(width()/2 + arrow , height()/2 + step_mark ),
                     QPointF(width()/2 - arrow, height()/2 + step_mark));
        ptr.drawLine(QPointF(width()/2 +arrow, height()/2 - step_mark),
                     QPointF(width()/2 - arrow, height()/2 - step_mark));
    }
//label moves
    lblOX->move(width()-4*arrow, height()/2-4*arrow);
    lblOY->move(width()/2+2*arrow,2*arrow);
    lblO0->move(width()/2 + arrow/2, height()/2);
    lblOX100 ->move(width()/2+100/Max_a * (height()<width()?height():width())/2, height()/2);
    lblOX_100->move(width()/2-100/Max_a * (height()<width()?height():width())/2, height()/2);
    lblOY100 ->move(width()/2, height()/2+100/Max_a * (height()<width()?height():width())/2);
    lblOY_100->move(width()/2, height()/2-100/Max_a * (height()<width()?height():width())/2);
//grafic
    ptr.setPen(Qt::blue);
    const QPointF center (width()/2.0, height() / 2.0);
    for(double fi = step; fi <end; fi+=step){
        QPointF p2(curve(fi, a) * cos(fi), curve(fi, a) * sin(fi));
        ptr.drawLine(p1 + center, p2 + center);
        p1 = p2;
    }
}


