#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtEdad->setValidator(new QIntValidator(1, 150, this));
    ui->tableWidget->setColumnCount(7);
    QStringList titulos = {"ID","Nombre", "Apellido", "Edad", "Adicción", "Meses", "Fecha de ingreso"};
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    loadDataFromCSV("C:\\Users\\ariel\\OneDrive\\Desktop\\Desarrollo de Software\\Segundo Semestre\\Programacion\\Proyecto\\PROYECTO\\Lista de Pacientes\\Pacientes.csv");
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
    p.adiccion = ui->cmbAdiccion->currentText();
    p.diasIngreso = ui->cmbMeses->currentText().toInt();
    p.fechaIngreso = ui->dateIngreso->selectedDate();

    listaPacientes.append(p);

    ui->txtNombre->clear();
    ui->txtApellido->clear();
    ui->txtEdad->clear();
    ui->cmbAdiccion->setCurrentIndex(0);
    ui->cmbMeses->setCurrentIndex(0);

    updateTable();
    //func auxiliar
    QMessageBox::information(this, "Agregado", "Paciente agregado con éxito");
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
            listaPacientes[i].adiccion = ui->cmbAdiccion->currentText();
            listaPacientes[i].diasIngreso = ui->cmbMeses->currentText().toInt();
            listaPacientes[i].fechaIngreso = ui->dateIngreso->selectedDate();
            encontrado = true;
            break;
        }
    }

    ui->txtNombre->clear();
    ui->txtApellido->clear();
    ui->txtEdad->clear();
    ui->cmbAdiccion->setCurrentIndex(0);
    ui->cmbMeses->setCurrentIndex(0);
    ui->txtID->clear();

    if (encontrado) {
        updateTable();
        //tra vez jaja
        QMessageBox::information(this, "Actualizado", "Paciente actualizado correctamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se encontró un paciente con ese ID.");
    }
}


void MainWindow::on_btnBorrar_clicked()
{
    if (ui->txtID_2->text() == "") {
        QMessageBox::warning(this, "Campo vacío", "Por favor ingresa el ID.");
        return;
    }

    int idBuscado = ui->txtID_2->text().toInt();
    bool eliminado = false;

    for (int i = 0; i < listaPacientes.size(); ++i) {
        if (listaPacientes[i].id == idBuscado) {
            listaPacientes.removeAt(i);
            eliminado = true;
            break;
        }
    }
    ui->txtNombre->clear();
    ui->txtApellido->clear();
    ui->txtEdad->clear();
    ui->cmbAdiccion->setCurrentIndex(0);
    ui->cmbMeses->setCurrentIndex(0);
    ui->txtID_2->clear();

    if (eliminado) {
        updateTable();
        QMessageBox::information(this, "Eliminado", "Paciente eliminado correctamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se encontró un paciente con ese ID.");
    }
}


void MainWindow::on_btnGuardarCSV_clicked()
{
    saveDataToCSV("C:\\Users\\ariel\\OneDrive\\Desktop\\Desarrollo de Software\\Segundo Semestre\\Programacion\\Proyecto\\PROYECTO\\Lista de Pacientes\\Pacientes.csv");
}

void MainWindow::updateTable()
{
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
}

void MainWindow::saveDataToCSV(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para escribir.");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "Fundacion Frutos de Amor Registro\n";
    out << "ID;Nombre;Apellido;Edad;Adiccion;Meses;FechaIngreso\n";

    for (const Paciente &p : listaPacientes) {
        out << p.id << ";"
            << p.nombre << ";"
            << p.apellido << ";"
            << p.edad << ";"
            << p.adiccion << ";"
            << p.diasIngreso << ";"
            << p.fechaIngreso.toString("dd/MM/yyyy") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Guardado", "Archivo guardado correctamente.");
}

void MainWindow::loadDataFromCSV(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Información", "No se encontró el archivo de registro. Se creará uno nuevo al guardar.");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    if (!in.atEnd()) {
        in.readLine();
    }
    if (!in.atEnd()) {
        in.readLine();
    }

    listaPacientes.clear();
    contadorid = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(';');

        if (fields.size() == 7) {
            Paciente p;
            p.id = fields[0].toInt();
            p.nombre = fields[1];
            p.apellido = fields[2];
            p.edad = fields[3].toInt();
            p.adiccion = fields[4];
            p.diasIngreso = fields[5].toInt();
            p.fechaIngreso = QDate::fromString(fields[6], "dd/MM/yyyy");
            listaPacientes.append(p);

            if (p.id >= contadorid) {
                contadorid = p.id + 1;
            }
        }
    }

    file.close();
    updateTable();
    QMessageBox::information(this, "Carga Completa", "Datos de pacientes cargados correctamente.");
}
