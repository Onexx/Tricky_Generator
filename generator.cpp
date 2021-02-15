#include "generator.h"
#include "ui_generator.h"

#include "QMediaPlaylist"
#include "QMovie"

Generator::Generator(QWidget *parent) : QWidget(parent), ui(new Ui::Generator) {
    ui->setupUi(this);
    this->hide();

    connect(ui->PbGenerate, &QPushButton::clicked, this, &Generator::Generate);

    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt_rand = std::mt19937(seed);

    QString str = QFileInfo("Tricky_Generator").absolutePath();
    QString str2 = str;
    QString str3 = str;
    str += "/Materials/scroll.wav";
    str2 += "/Materials/background.mp3";
    str3 += "/Materials/gong.mp3";

    player1 = new QMediaPlayer;
    player1->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(str)));
    player1->setVolume(5);

    player2 = new QMediaPlayer;
    player2->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(str)));
    player2->setVolume(5);

    player3 = new QMediaPlayer;
    player3->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(str)));
    player3->setVolume(5);

    background = new QMediaPlayer;
    auto playlist = new QMediaPlaylist(background);
    background->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(str2)));
    background->setVolume(30);

    gong = new QMediaPlayer;
    gong->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(str3)));
    gong->setVolume(100);
}

void Generator::FireworkNextFrame() {
    QString str =
        "background-image:url(C:/Users/ilya7/Documents/"
        "build-Tricky_Generator-Desktop_Qt_5_11_1_MinGW_32bit-Release/"
        "Materials/firework";
    str += QString::number(fireworkFrameNumber);
    str += ".jpg);";
    ui->LblGeneratedTaskNumber->setStyleSheet(str);
    fireworkFrameNumber++;
    if (fireworkFrameNumber == 5) fireworkFrameNumber = 1;
}

void Generator::NextStudentNumber() {
    if (possibleTasks.size() == 0) return;
    if (nextPlayer == 1) {
        player1->stop();
        player1->play();
        nextPlayer = 2;
    } else if (nextPlayer == 2) {
        player2->stop();
        player2->play();
        nextPlayer = 3;
    } else {
        player3->stop();
        player3->play();
        nextPlayer = 1;
    }
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
    if (nextPlayer == 1) {
        player1->stop();
        player1->play();
        nextPlayer = 2;
    } else if (nextPlayer == 2) {
        player2->stop();
        player2->play();
        nextPlayer = 3;
    } else {
        player3->stop();
        player3->play();
        nextPlayer = 1;
    }
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
    if (nextPlayer == 1) {
        player1->stop();
        player1->play();
        nextPlayer = 2;
    } else if (nextPlayer == 2) {
        player2->stop();
        player2->play();
        nextPlayer = 3;
    } else {
        player3->stop();
        player3->play();
        nextPlayer = 1;
    }
    gong->play();
    int newNumber = mt_rand() % possibleTasks[studentNumber].size();
    if (possibleTasks[studentNumber].size() > 1) {
        while (possibleTasks[studentNumber][newNumber] == previousNumber) {
            newNumber = mt_rand() % possibleTasks[studentNumber].size();
        }
    }
    ui->LblGeneratedTaskNumber->setText(
        ' ' + QString::number(possibleTasks[studentNumber][newNumber]));
    previousNumber = newNumber;
    QTimer::singleShot(200, this, SLOT(FireworkNextFrame()));
    QTimer::singleShot(400, this, SLOT(FireworkNextFrame()));
    QTimer::singleShot(600, this, SLOT(FireworkNextFrame()));
    QTimer::singleShot(800, this, SLOT(FireworkNextFrame()));
}

void Generator::Generate() {
    int time = 0;
    for (int i = 0; i < 7; i++) {
        time += 150;
        QTimer::singleShot(time, this, SLOT(NextStudentNumber()));
    }
    for (int i = 0; i < 3; i++) {
        time += 250;
        QTimer::singleShot(time, this, SLOT(NextStudentNumber()));
    }
    for (int i = 0; i < 2; i++) {
        time += 350;
        QTimer::singleShot(time, this, SLOT(NextStudentNumber()));
    }
    time += 500;
    QTimer::singleShot(time, this, SLOT(NextStudentNumber()));
    time += 700;
    QTimer::singleShot(time, this, SLOT(NextStudentNumber()));
    time += 1000;
    QTimer::singleShot(time, this, SLOT(NextStudentNumber()));
    time += 500;
    for (int i = 0; i < 7; i++) {
        time += 150;
        QTimer::singleShot(time, this, SLOT(NextTaskNumber()));
    }
    for (int i = 0; i < 3; i++) {
        time += 250;
        QTimer::singleShot(time, this, SLOT(NextTaskNumber()));
    }
    for (int i = 0; i < 2; i++) {
        time += 350;
        QTimer::singleShot(time, this, SLOT(NextTaskNumber()));
    }
    time += 500;
    QTimer::singleShot(time, this, SLOT(NextTaskNumber()));
    time += 700;
    QTimer::singleShot(time, this, SLOT(NextTaskNumber()));
    time += 1000;
    QTimer::singleShot(time, this, SLOT(PossibleTaskNumber()));
}

Generator::~Generator() { delete ui; }
