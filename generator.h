#pragma once

#include <QDir>
#include <QMediaPlayer>
#include <QTimer>
#include <QUrl>
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
    QMediaPlayer *background;

  private slots:
    void FireworkNextFrame();
    void NextStudentNumber();
    void NextTaskNumber();
    void PossibleTaskNumber();

  private:
    void Generate();
    QMediaPlayer *player1;
    QMediaPlayer *player2;
    QMediaPlayer *player3;
    QMediaPlayer *gong;
    QMovie *movie;
    int nextPlayer = 1;
    int fireworkFrameNumber = 1;
    Ui::Generator *ui;
    std::mt19937 mt_rand;
    int previousNumber = 0;
    int studentNumber = 0;
};
