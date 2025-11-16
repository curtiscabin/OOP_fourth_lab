#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    store = new MyStorage();

    connect(ui->radioBlue,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioGreen,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioOrange,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioBlack,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioPink,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioRed,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioWhite,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioYellow,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);

    ui->radioWhite->setChecked(true);
    EditColorByRadioBtton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    qDebug()<<"enter to Click";

    bool ctrl = event->modifiers() & Qt::ControlModifier;

    if(!ctrl){
        store->clearSelection();
        isSelecting = false;
    }

    for (store->first();!store->eol();store->next()){
        if(store->getObject()->isCordBelong(event->pos())){
            store->getObject()->SetSelect();
            isSelecting = true;
            return;
        }
    }
    if(ctrl) store->clearSelection();


    b = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *){
    s = nullptr;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    e = event->pos();
    QPoint delta = e - b;
    qDebug()<<delta;
    if (!isSelecting ){
        if(!s){
            s = new Circle(b,e,this);
            s->EditColor(color);
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

void MainWindow::keyPressEvent(QKeyEvent *event){
    int key = event->key();

    if (key == Qt::Key_Delete){
        qDebug()<<"Key is Delete";
        store->deleteCircles();
    }
}

void MainWindow::EditColorByRadioBtton(){
if (ui->radioBlue->isChecked()){
        color = "blue";
    }
    else if (ui->radioBlack->isChecked()){
        color = "black";
    }
    else if (ui->radioGreen->isChecked()){
        color = "green";
    }
    else if (ui->radioOrange->isChecked()){
        color = "orange";
    }
    else if (ui->radioPink->isChecked()){
        color = "pink";
    }
    else if (ui->radioRed->isChecked()){
        color = "red";
    }
    else if (ui->radioWhite->isChecked()){
        color = "white";
    }
    else if (ui->radioYellow->isChecked()){
        color = "yellow";
    }

    for(store->first();!store->eol();store->next()){
        if(store->getObject()->isSelect_()){
            store->getObject()->EditColor(color);
        }
    }

}
