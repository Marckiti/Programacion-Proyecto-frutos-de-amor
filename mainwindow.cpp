#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtEdad->setValidator(new QIntValidator(1, 150, this));
    ui->tableWidget->setColumnCount(7);
    QStringList titulos = {"ID","Nombre", "Apellido", "Edad", "Adicción", "Meses", "Fecha de ingreso"};
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAgregar_clicked()
{
    if (ui->txtNombre->text() == "" || ui->txtApellido->text() == "" || ui->txtEdad->text() == "") {
        QMessageBox::warning(this, "Campos vacíos", "Completa todos los campos.");
        return;
    }

    Paciente p;
    p.id = contadorid++;
    p.nombre = ui->txtNombre->text();
    p.apellido = ui->txtApellido->text();
    p.edad = ui->txtEdad->text().toInt();
    p.adiccion = ui->cmbAdixion->currentText();
    p.diasIngreso = ui->cmbMeses->currentText().toInt();
    p.fechaIngreso = ui->dateIngreso->selectedDate();

    listaPacientes.append(p);

    ui->txtNombre->clear();
    ui->txtApellido->clear();
    ui->txtEdad->clear();
    ui->cmbAdixion->setCurrentIndex(0);
    ui->cmbMeses->setCurrentIndex(0);

    ui->tableWidget->setRowCount(listaPacientes.size());
    for (int i = 0; i < listaPacientes.size(); ++i) {
        const Paciente &p = listaPacientes[i];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(p.nombre));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(p.apellido));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(p.edad)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(p.adiccion));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(p.diasIngreso)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(p.fechaIngreso.toString("dd/MM/yyyy")));
    }

    QMessageBox::information(this, "Agregado", "Paciente agregado con exito");
}

void MainWindow::on_btnActualizar_clicked()
{
    if (ui->txtID->text() == "") {
        QMessageBox::warning(this, "Campo vacío", "Por favor ingresa el ID.");
        return;
    }

    if (ui->txtNombre->text() == "" || ui->txtApellido->text() == "" || ui->txtEdad->text() == "") {
        QMessageBox::warning(this, "Campos vacíos", "Completa todos los campos.");
        return;
    }

    int idBuscado = ui->txtID->text().toInt();
    bool encontrado = false;

    for (int i = 0; i < listaPacientes.size(); ++i) {
        if (listaPacientes[i].id == idBuscado) {
            listaPacientes[i].nombre = ui->txtNombre->text();
            listaPacientes[i].apellido = ui->txtApellido->text();
            listaPacientes[i].edad = ui->txtEdad->text().toInt();
            listaPacientes[i].adiccion = ui->cmbAdixion->currentText();
            listaPacientes[i].diasIngreso = ui->cmbMeses->currentText().toInt();
            listaPacientes[i].fechaIngreso = ui->dateIngreso->selectedDate();
            encontrado = true;
            break;
        }
    }


