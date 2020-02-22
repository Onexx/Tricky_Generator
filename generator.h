#pragma once

#include <QTimer>
#include <QWidget>

namespace Ui {
class Generator;
}

class Generator : public QWidget {
    Q_OBJECT

  public:
    explicit Generator(QWidget *parent = 0);
    ~Generator();
    std::vector<std::vector<int>> possibleTasks;
    int tasksAmount = 0;

  private slots:
    void NextStudentNumber();
    void NextTaskNumber();
    void PossibleTaskNumber();

  private:
    void Generate();
    Ui::Generator *ui;
    std::mt19937 mt_rand;
    int previousNumber = 0;
    int studentNumber = 0;
};
