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


    void MoveShape(const QPoint &p) {
        QRect parentRect = this->parentWidget()->rect();
        if(parentRect.x() <= p.x() + sizeX /2 && p.x() + sizeX/2 <= parentRect.x() + parentRect.width()
            &&parentRect.x() <= p.x() - sizeX /2 && p.x() - sizeX/2 <= parentRect.x() + parentRect.width()){
            move(p.x() - sizeX/2, this->y());
        }
        if(parentRect.y() <= p.y() + sizeY/2 && p.y() + sizeY/2 <= parentRect.y() + parentRect.height()
            &&parentRect.y() <= p.y() - sizeY/2 && p.y() - sizeY/2 <= parentRect.y() + parentRect.height()){
            move(this->x(), p.y() - sizeY/2);
        }
        // update();
    }

    virtual void EditColor() = 0;

    void CreatSize(const QPoint& b, const QPoint& e){
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

        if(edit){
            edit->move(sizeX - 20, sizeY - 20);
        }
    }

    void EditSize(const QPoint& b, const QPoint& e){
        sizeX = (e.x() - b.x()) < 10 ? 10 : e.x() - b.x();
        sizeY = (e.y()- b.y()) < 10 ? 10 : e.y() - b.y();

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



private slots:
    void onEditButtonPressed() {
        qDebug()<<"Button is pressed";
        grabMouse();
        isResize = true;
    }

    void mouseMoveEvent(QMouseEvent *event) override{
        if(isResize){
            QPoint b = this->pos();
            QPoint e = parentWidget()->mapFromGlobal(event->globalPos());
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



    void EditColor(){

    }


};


