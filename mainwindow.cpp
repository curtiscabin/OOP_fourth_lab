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
    Circle *s = new Circle(event->pos(),this);
    s->PaintShape();
    store->add(s);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    for(store->first();!store->eol();store->next()){
        if(store->getObject()->isSelect_())store->getObject()->MoveShape(event->pos());
}
}
