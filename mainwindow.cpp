#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    store = new MyStorage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    qDebug()<<"enter to Click";
    store->clearSelection();
    isSelecting = false;
    for (store->first();!store->eol();store->next()){
        if(store->getObject()->isCordBelong(event->pos())){
            store->getObject()->SetSelect();
            isSelecting = true;
            return;
        }
    }

    b = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *){
    s = nullptr;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    e = event->pos();
    if (!isSelecting ){
        if(!s){
            s = new Circle(b,e,this);
            store->add(s);
        }
        s->CreatSize(b,e);
        s->PaintShape();
    }
    else{
        for(store->first();!store->eol();store->next()){
            if(store->getObject()->isSelect_()) {
                    store->getObject()->MoveShape(e);
        }
    }
}
}
