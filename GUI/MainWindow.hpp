#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>

#include "GameEngine.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void HandleButton();
    ~MainWindow();

    QWidget *window = new QWidget;
    QVBoxLayout *MainLayout;
    QHBoxLayout *Grid;
    QHBoxLayout *ButtonLayout;

    QTableWidget *table = new QTableWidget(this);
    QPushButton *button = new QPushButton("Run Sim", this);

    GameEngine engine;
};