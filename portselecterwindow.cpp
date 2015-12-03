#include "portselecterwindow.h"
#include "ui_portselecterwindow.h"
#include "mainwindow.h"

PortSelecterWindow::PortSelecterWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::PortSelecterWindow)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	refreshPortsList();
}

void PortSelecterWindow::refreshPortsList(){
	ui->boxPorts->clear();
	foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		ui->boxPorts->addItem(info.portName());
	}
}

PortSelecterWindow::~PortSelecterWindow()
{
	delete ui;
}

void PortSelecterWindow::on_btnChoose_clicked()
{
	emit portChoosed(ui->boxPorts->currentText());
}

void PortSelecterWindow::on_btnRefresh_clicked()
{
	refreshPortsList();
}
