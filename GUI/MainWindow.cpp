#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
{
    layout = new QHBoxLayout(window);
    table->setRowCount(20);
    table->setColumnCount(20);
    layout->addWidget(table);
    window->show();
}

MainWindow::~MainWindow()
{
}
