#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Paciente {
    int id;
    QString nombre;
    QString apellido;
    int edad;
    QString adiccion;
    int diasIngreso;
    QDate fechaIngreso;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAgregar_clicked();

    void on_btnActualizar_clicked();

    void on_btnBorrar_clicked();

    void on_btnGuardarCSV_clicked();


private:
    Ui::MainWindow *ui;
    QVector<Paciente> listaPacientes;
    int contadorid = 1;
};

#endif
