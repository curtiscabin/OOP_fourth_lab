#ifndef SHAPES_H
#define SHAPES_H

#endif // SHAPES_H
#pragma once
#include<QPoint>
#include<QWidget>
#include<QDebug>
#include<QString>
#include<QPainter>
#include<math.h>
#include<QPushButton>

class Shape : public QWidget {
    Q_OBJECT
protected:
    int sizeX;
    int sizeY;
    QPoint* borders = nullptr;
    bool isSelect = false;
    QString color = "white";
    QPushButton *edit = nullptr;
    bool isResize = false;


public:
    Shape(const QPoint& b, const QPoint& e, QWidget* parent = nullptr) : QWidget(parent) {
        sizeX = abs(e.x() - b.x());
        sizeY = abs(e.y()- b.y());
    }

    ~Shape(){
        update();
    }

    bool isCordBelong(const QPoint& p){
        return this->geometry().contains(p);
    }

    void SetSelect(){
        isSelect = true;
        edit = new QPushButton(this);
        edit->setFixedSize(20,20);
        edit->move(sizeX - 20, sizeY - 20);
        edit->show();

        if (edit && this) {
            connect(edit, &QPushButton::pressed, this, &Shape::onEditButtonPressed);
        }
        update();
    }

    void ClearSelect(){
        isSelect = false;
        delete edit;
        edit = nullptr;
        update();
    }

    bool isSelect_(){
        return isSelect;
    }

    void PaintShape(){
        show();
    }

    bool isXBelongToSection(const int& x){
        QRect parentRect = this->parentWidget()->rect();
        return parentRect.x() <= x + sizeX /2
               && x + sizeX/2 <= parentRect.x() + parentRect.width()
               &&parentRect.x() <= x - sizeX /2
               && x - sizeX/2 <= parentRect.x() + parentRect.width();
    }

    bool isYBelongToSection(const int& y){
        QRect parentRect = this->parentWidget()->rect();
        return parentRect.y() <= y + sizeY/2
               && y + sizeY/2 <= parentRect.y() + parentRect.height()
               &&parentRect.y() <= y - sizeY/2
               && y - sizeY/2 <= parentRect.y() + parentRect.height();
    }

    void MoveShape(const QPoint &p) {
        QRect parentRect = this->parentWidget()->rect();
        if(isXBelongToSection(p.x())){
            move(p.x() - sizeX/2, this->y());
        }
        if(isYBelongToSection(p.y())){
            move(this->x(), p.y() - sizeY/2);
        }
    }

    void EditColor(const QString &c) {
        color = c;
        update();
    }

    void CreatSize(const QPoint& b, const QPoint& e){
        QRect parentRect = this->parentWidget()->rect();

        int ex = e.x();
        int ey = e.y();

        if (ex < parentRect.left()) ex = parentRect.left();
        else if (ex > parentRect.right()) ex = parentRect.right();

        if (ey < parentRect.top()) ey = parentRect.top();
        else if (ey > parentRect.bottom()) ey = parentRect.bottom();

        sizeX = abs(ex - b.x());
        sizeY = abs(ey - b.y());

        setFixedSize(sizeX, sizeY);

        if (b.x() < ex && b.y() > ey){
            move(b.x(), ey);
        }
        else if (b.x() > ex && b.y() < ey){
            move(ex, b.y());
        }
        else if (b.x() > ex && b.y() > ey){
            move(ex, ey);
        }
        else move(b.x(), b.y());

        if(edit){
            edit->move(sizeX - 20, sizeY - 20);
        }
    }

    void EditSize(const QPoint& b, const QPoint& e){
        QRect parentRect = this->parentWidget()->rect();

        if(e.x() <= parentRect.right()) sizeX = (e.x() - b.x()) < 10 ? 10 : e.x() - b.x();
        if(e.y() <= parentRect.bottom()) sizeY = (e.y()- b.y()) < 10 ? 10 : e.y() - b.y();

        setFixedSize(sizeX, sizeY);

        if(edit){
            edit->move(sizeX - 20, sizeY - 20);
        }

    }

protected slots:
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (isResize) {
            isResize = false;
            releaseMouse();
            qDebug() << "Resize finished";
        }
    }

    void onEditButtonPressed() {
        qDebug()<<"Button is pressed";
        grabMouse();
        isResize = true;
    }

    void mouseMoveEvent(QMouseEvent *event) override{
        if(isResize){
            QPoint b = this->pos();
            QPoint e = parentWidget()->mapFromGlobal(event->globalPosition().toPoint());
            EditSize(b,e);
            qDebug()<<"resize object";
        }
        else
        {
            event->ignore();
        }
    }

};

class Circle : public Shape {
public:
    Circle(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(b, e, parent){
        qDebug()<<"Created Circle";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QPen CirclePen;
        painter.setRenderHint(QPainter::Antialiasing);

        if (isSelect_()){
            QPen SelectPen;
            SelectPen.setDashPattern({4,4});
            SelectPen.setColor("cyan");
            SelectPen.setWidth(3);
            painter.setPen(SelectPen);
            painter.drawRect(0,0,sizeX,sizeY);
        }
        CirclePen.setColor(color);
        painter.setBrush(color);

        painter.setPen(CirclePen);
        painter.drawEllipse(0,0,sizeX,sizeY);
    }

};

class Rect : public Shape {
public:
    Rect(const QPoint& b, const QPoint& e, QWidget* parent)
        : Shape(b, e, parent)
    {
        qDebug() << "Created Square";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen rectPen(color);
        painter.setPen(rectPen);
        painter.setBrush(color);
        painter.drawRect(0, 0, sizeX, sizeY);

        if (isSelect_()) {
            QPen selectPen(Qt::cyan);
            selectPen.setDashPattern({4, 4});
            selectPen.setWidth(3);
            painter.setPen(selectPen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(0, 0, sizeX, sizeY);
        }
    }
};


class Triangle : public Shape {
public:
    Triangle(const QPoint& b, const QPoint& e, QWidget* parent)
        : Shape(b, e, parent)
    {
        qDebug() << "Created Triangle";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen trianglePen(color);
        painter.setPen(trianglePen);
        painter.setBrush(color);

        QPolygonF poly;
        poly << QPointF(sizeX / 2.0, 0)
             << QPointF(sizeX,       sizeY)
             << QPointF(0,           sizeY);
        painter.drawPolygon(poly);

        if (isSelect_()) {
            QPen selectPen(Qt::cyan);
            selectPen.setDashPattern({4, 4});
            selectPen.setWidth(3);
            painter.setPen(selectPen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(0, 0, sizeX, sizeY);
        }
    }
};


class Section : public Shape {
public:
    Section(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(b, e, parent){
        qDebug()<<"Created Circle";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QPen SectionPen;
        painter.setRenderHint(QPainter::Antialiasing);

        if (isSelect_()){
            QPen SelectPen;
            SelectPen.setDashPattern({4,4});
            SelectPen.setColor("cyan");
            SelectPen.setWidth(3);
            painter.setPen(SelectPen);
            painter.drawRect(0,0,sizeX,sizeY);
        }
        SectionPen.setColor(color);
        painter.setPen(SectionPen);
        painter.drawLine(0,0,sizeX,sizeY);
    }

};






