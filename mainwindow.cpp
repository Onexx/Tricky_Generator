#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->hide();

    connect(ui->PbNext, &QPushButton::clicked, this, &MainWindow::Next);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Close application if 'delete' or 'Esc' button pressed
    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Escape) {
        this->close();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void MainWindow::Next() {
    whitelist = new class Whitelist(0, ui->SbStudentsAmount->value(),
                                    ui->SbTasksAmount->value());
    whitelist->setWindowTitle(QString("Generator V." +
                                      QString::number(Data::version) + "." +
                                      QString::number(Data::build)));
    whitelist->hide();
    this->hide();  // TODO
    whitelist->show();
}

MainWindow::~MainWindow() { delete ui; }
