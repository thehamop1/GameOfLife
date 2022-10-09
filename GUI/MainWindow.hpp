#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTableWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget *window = new QWidget;
    QHBoxLayout *layout;
    QTableWidget *table = new QTableWidget;
};
