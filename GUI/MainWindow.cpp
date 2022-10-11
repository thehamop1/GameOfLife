#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
{
    MainLayout = new QVBoxLayout(window);
    Grid = new QHBoxLayout();
    ButtonLayout = new QHBoxLayout();

    MainLayout->addLayout(Grid);
    MainLayout->addLayout(ButtonLayout);
    ButtonLayout->addWidget(button);

    table->setRowCount(25);
    table->setColumnCount(25);
    MainLayout->addWidget(table);
    window->show();

    connect(button, &QPushButton::released, this, &MainWindow::HandleButton);
}

MainWindow::~MainWindow() = default;

void MainWindow::HandleButton(){
    std::cout << "HELLO WORLD" << std::endl;
};