#ifndef SHAPES_H
#define SHAPES_H

#endif // SHAPES_H
#pragma once
#include<QPoint>
#include<QWidget>
#include<QDebug>
#include<QString>
#include<QPainter>

class Shape : public QWidget {
    Q_OBJECT
protected:
    int size = 30;
    QPoint* borders = nullptr;
    bool isSelect = false;
    QString color = "white";

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

    virtual bool isOutside() = 0;

    virtual void MoveShape(const QPoint &p) = 0;

    virtual void EditSize() = 0;

    virtual void EditColor() = 0;

};

class Circle : public Shape {
public:
    Circle(const QPoint& p, QWidget* parent) : Shape(parent){
        setFixedSize(2.2*size, 2.2*size);
        move(p.x() - size, p.y() - size);
    }

    ~Circle(){
        update();
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

        if (isSelect_()) painter.setPen(QPen(Qt::cyan, 3));
        else painter.setPen(QPen(color));

        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawEllipse(0,0,2*size,2*size);
    }

    bool isCordBelong(const QPoint& p){
        return this->geometry().contains(p);
    }

    void EditSize(){

    }

    void EditColor(){

    }

    bool isOutside(){

    }

    void MoveShape(const QPoint &p){
        move(p.x() - size, p.y() - size);
        update();
    }




};


