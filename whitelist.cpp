#include "whitelist.h"
#include "ui_whitelist.h"

Whitelist::Whitelist(QWidget *parent, int studentsAmount_, int tasksAmount_)
    : QWidget(parent), ui(new Ui::Whitelist) {
    ui->setupUi(this);
    this->hide();

    connect(ui->PbNext, &QPushButton::clicked, this, &Whitelist::Next);
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int, int)), this,
            SLOT(CellDoubleClicked(int, int)));
    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this,
            SLOT(CellClicked(int, int)));

    studentsAmount = studentsAmount_;
    tasksAmount = tasksAmount_;
    generator = new class Generator();
    generator->setWindowTitle(QString("Generator V." +
                                      QString::number(Data::version) + "." +
                                      QString::number(Data::build)));
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(studentsAmount);
    for (int it = 0; it < studentsAmount; it++) {
        ui->tableWidget->setItem(
            it, 0, new QTableWidgetItem("Ученик №" + QString::number(it + 1)));
        ui->tableWidget->item(it, 0)->setFlags(Qt::ItemIsSelectable);

        ui->tableWidget->setItem(it, 1, new QTableWidgetItem("Все"));
    }
}

void Whitelist::Parser(std::vector<std::vector<int>> &possibleTasks) {
    for (int student = 0; student < studentsAmount; student++) {
        if (ui->tableWidget->item(student, 1)->text() == "Все") {
            for (int task = 1; task <= tasksAmount; task++) {
                possibleTasks[student].push_back(task);
            }
        } else {
            QString text = ui->tableWidget->item(student, 1)->text();
            for (int it = 0; it < text.size(); it++) {
                if (text[it].isDigit()) {
                    int number = 0;
                    while (it < text.size() && text[it].isDigit()) {
                        number *= 10;
                        number += text[it].digitValue();
                        it++;
                    }
                    possibleTasks[student].push_back(number);
                }
            }
        }
    }
}

void Whitelist::Next() {
    std::vector<std::vector<int>> possibleTasks(studentsAmount);
    CellClicked(0, 1);
    Parser(possibleTasks);
    generator->possibleTasks = possibleTasks;
    generator->tasksAmount = tasksAmount;
    generator->showMaximized();
    generator->background->play();
    this->hide();
}

void Whitelist::CellDoubleClicked(int row, int column) {
    if (column == 1) {
        if (ui->tableWidget->item(row, column)->text() == "Все") {
            ui->tableWidget->item(row, column)->setText("");
        }
    }
}

void Whitelist::CellClicked(int row, int column) {
    if (column == 1) {
        for (int it = 0; it < studentsAmount; it++) {
            if (ui->tableWidget->item(it, column)->text() == "") {
                ui->tableWidget->item(it, column)->setText("Все");
            }
        }
    }
}

Whitelist::~Whitelist() { delete ui; }
