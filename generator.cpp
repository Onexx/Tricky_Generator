#include "generator.h"
#include "ui_generator.h"

Generator::Generator(QWidget *parent) : QWidget(parent), ui(new Ui::Generator) {
    ui->setupUi(this);
    this->hide();

    connect(ui->PbGenerate, &QPushButton::clicked, this, &Generator::Generate);

    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt_rand = std::mt19937(seed);
}

void Generator::NextStudentNumber() {
    if (possibleTasks.size() == 0) return;
    int newNumber = previousNumber;
    while (newNumber == previousNumber) {
        newNumber = mt_rand() % possibleTasks.size() + 1;
    }
    if (newNumber < 10) {
        ui->LblGeneratedStudentNumber->setText(' ' +
                                               QString::number(newNumber));
    } else {
        ui->LblGeneratedStudentNumber->setText(QString::number(newNumber));
    }
    previousNumber = newNumber;
    studentNumber = newNumber - 1;
}

void Generator::NextTaskNumber() {
    if (tasksAmount == 0) return;
    int newNumber = previousNumber;
    while (newNumber == previousNumber) {
        newNumber = mt_rand() % tasksAmount + 1;
    }
    if (newNumber < 10) {
        ui->LblGeneratedTaskNumber->setText(' ' + QString::number(newNumber));
    } else {
        ui->LblGeneratedTaskNumber->setText(QString::number(newNumber));
    }
    previousNumber = newNumber;
}

void Generator::PossibleTaskNumber() {
    if (possibleTasks[studentNumber].size() == 0) return;
    int newNumber = previousNumber;
    while (newNumber == previousNumber) {
        newNumber = mt_rand() % possibleTasks[studentNumber].size();
    }
    if (newNumber < 10) {
        ui->LblGeneratedTaskNumber->setText(
            ' ' + QString::number(possibleTasks[studentNumber][newNumber]));
    } else {
        ui->LblGeneratedTaskNumber->setText(QString::number(newNumber));
    }
    previousNumber = newNumber;
}

void Generator::Generate() {
    for (int i = 1; i <= 17; i++) {
        QTimer::singleShot((i * i) * 10, this, SLOT(NextStudentNumber()));
    }
    for (int i = 1; i <= 17; i++) {
        QTimer::singleShot((i * i) * 10 + 3500, this, SLOT(NextTaskNumber()));
    }
    QTimer::singleShot(7000, this, SLOT(PossibleTaskNumber()));
}

Generator::~Generator() { delete ui; }
