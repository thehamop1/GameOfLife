#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
{
    MainLayout = new QVBoxLayout(window);
    Grid = new QHBoxLayout();
    ButtonLayout = new QHBoxLayout();

    MainLayout->addLayout(Grid);
    MainLayout->addLayout(ButtonLayout);
    ButtonLayout->addWidget(button);

    table->setRowCount(20);
    table->setColumnCount(20);
    MainLayout->addWidget(table);
    window->show();

    connect(button, &QPushButton::released, this, &MainWindow::HandleButton);
    engine.Input();
}

MainWindow::~MainWindow() = default;

void MainWindow::HandleButton(){
};