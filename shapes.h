#ifndef SHAPES_H
#define SHAPES_H
#include<QPoint>
#include<QWidget>
#include<QDebug>
#include<QString>

class Shape : public QWidget {
    Q_OBJECT

    int rad = 30;
    QPoint* borders = nullptr;
    bool isSelect = false;
    QString color;


public:
    bool isCordBelong() = 0;

    void SetSelect(){
        isSelect = true;
    }

    void ClearSelect(){
        isSelect = false;
    }

    bool isSelect_(){
        return isSelect;
    }

    void PaintShape(){
        show();
    }

    bool isOutside() = 0;

    void MoveShape() = 0;

    void EditSize() = 0;

    void EditColor() = 0;
};

class Circle : public Shape {
public:
    Circle(const QPoint& p){
        setFixedSize(2.2*rad, 2.2*rad);
        move(p.x() - rad, p.y() - rad);
    }

    ~Circle(){
        update();
    }



    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        if (isSelect()) painter.setPen(QPen(Qt::cyan, 3));
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawEllipse(0,0,2*rad,2*rad);

    }

}

#endif // SHAPES_H
