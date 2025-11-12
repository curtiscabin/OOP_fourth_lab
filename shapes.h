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

class Shape : public QWidget {
    Q_OBJECT
protected:
    int sizeX;
    int sizeY;
    QPoint* borders = nullptr;
    bool isSelect = false;
    QString color = "white";
    bool isCreating = false;

public:
    Shape(QWidget* parent = nullptr) : QWidget(parent) {}

    virtual bool isCordBelong(const QPoint &p) = 0;

    void SetSelect(){
        isSelect = true;
        update();
    }

    void SwitchSelect(){
        isSelect = !isSelect;
        update();
    }

    void ClearSelect(){
        isSelect = false;
        update();
    }

    bool isSelect_(){
        return isSelect;
    }

    void PaintShape(){
        show();
    }

    void SetCreating(){
        isCreating = true;
    }

    void ClearCreating(){
        isCreating = false;
    }

    bool isCreating_() {
        return isCreating;
    }

    bool isOutside(const QPoint &p){
        QRect circleRect(p.x() - sizeX/2, p.y() - sizeY/2, sizeX, sizeY);
        return !this->parentWidget()->rect().contains(circleRect);
    }

    virtual void MoveShape(const QPoint &p) = 0;

    virtual void EditColor() = 0;

    void EditSize(const QPoint& b, const QPoint& e){
        sizeX = abs(e.x() - b.x());
        sizeY = abs(e.y()- b.y());
        setFixedSize(sizeX, sizeY);

        if (b.x() < e.x() && b.y() > e.y() ){
            move(b.x(), e.y());
        }
        else if (b.x() > e.x() &&b.y() < e.y()){
            move(e.x(), b.y());
        }
        else if (b.x() > e.x() &&b.y() > e.y()){
            move(e.x(), e.y());
        }
        else move(b.x(), b.y());
        update();
    }

};

class Circle : public Shape {
public:
    Circle(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(parent){
        sizeX = abs(e.x() - b.x());
        sizeY = abs(e.y()- b.y());

    }

    ~Circle(){
        update();
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

        if (isSelect_()) painter.setPen(QPen(Qt::cyan, 3));
        else painter.setPen(QPen(color));

        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawEllipse(0,0,sizeX,sizeY);
    }

    bool isCordBelong(const QPoint& p){
        return this->geometry().contains(p);
    }

    void EditColor(){

    }

    void MoveShape(const QPoint &p){
        if(!isOutside(p)){
            move(p.x() - sizeX/2, p.y() - sizeY/2);
            update();
        }
    }


};


