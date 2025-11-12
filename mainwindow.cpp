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
    store->clearSelection();
    for (store->first();!store->eol();store->next()){
        if(store->getObject()->isCordBelong(event->pos())){
            store->getObject()->SetSelect();
            return;
        }
    }

    b = event->pos();
    s = new Circle(b,b,this);
    s->PaintShape();
    s->SetCreating();
    store->add(s);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    s->ClearCreating();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){


    if(s->isCreating_()){
        e = event->pos();
        s->EditSize(b,e);
    }
    else{
        for(store->first();!store->eol();store->next()){
            if(store->getObject()->isSelect_()) {
                store->getObject()->MoveShape(event->pos());
            }
        }
    }


}
