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

    virtual void EditColor() = 0;

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



private slots:
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


