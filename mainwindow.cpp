#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	chatState(ST_NORMAL)
{
	ui->setupUi(this);

	connect(&portSelecterWindow, SIGNAL(portChoosed(QString)), this, SLOT(onPortChanged(QString)));
	connect(this, SIGNAL(portOpened()), &portSelecterWindow, SLOT(hide()));
	connect(&chatPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	showConfigWindow();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showConfigWindow(){
	portSelecterWindow.show();
}

void MainWindow::enableChat(bool enabled){
	ui->grpChatMode->setEnabled(enabled);
	ui->btnSend->setEnabled(enabled);
}

void MainWindow::onPortChanged(QString portName)
{
	if (chatPort.isOpen())
		chatPort.close();

	ui->lblCurrentPort->setText("Текущий порт: не выбран");
	enableChat(false);

	chatPort.setPortName(portName);
	chatPort.setBaudRate(QSerialPort::Baud9600);
	chatPort.setDataBits(QSerialPort::Data8);
	chatPort.setParity(QSerialPort::NoParity);
	chatPort.setStopBits(QSerialPort::OneStop);
	chatPort.setFlowControl(QSerialPort::NoFlowControl);

	if (!chatPort.open(QIODevice::ReadWrite)){
		QMessageBox::critical(&portSelecterWindow, "Ошибка", "Ошибка открытия порта! Выберите другой.");
	} else {
		ui->txtHistory->clear();
		enableChat(true);
		ui->lblCurrentPort->setText("Текущий порт: " + chatPort.portName());
		emit portOpened();
	}
}

void MainWindow::receiveMessage(QByteArray message){
	ui->txtHistory->appendPlainText("Собеседник:");
	ui->txtHistory->appendPlainText(QString::fromLocal8Bit(message));
	ui->txtHistory->appendPlainText("");
}

void MainWindow::onReadyRead(){
	QByteArray data = chatPort.readAll();

	switch (chatState){
		case ST_NORMAL:
			if (data[0] == (char)CONTROL_BLOCK){
				chatState = ST_BLOCK_MSGS;

				QByteArray controlSequence;
				controlSequence[0] = CONTROL_BLOCK;
				chatPort.write(controlSequence);

				ui->rbtnDeactivate->setChecked(true);
			}
			else
				if (data[0] == (char)CONTROL_MSG)
					receiveMessage(data.mid(1));
			break;
		case ST_BLOCK_MSGS:
			if (data[0] == (char)CONTROL_ENABLE){
				chatState = ST_NORMAL;

				QByteArray controlSequence;
				controlSequence[0] = CONTROL_ENABLE;
				chatPort.write(controlSequence);

				ui->rbtnActivate->setChecked(true);
			}
			break;
	}
}

void MainWindow::sendMessage(QString messageText){
	if (messageText.length()){
		QByteArray controlSequence;
		controlSequence[0] = CONTROL_MSG;
		chatPort.write(controlSequence);
		qint64 writtenBytes = chatPort.write(messageText.toLocal8Bit());

		if (writtenBytes != messageText.length())
			QMessageBox::critical(this, "Ошибка", "Ошибка при отправке сообщения!");
		else {
			ui->txtHistory->appendPlainText("Вы:");
			ui->txtHistory->appendPlainText(messageText);
			ui->txtHistory->appendPlainText("");

			ui->txtMessageText->clear();
		}
	}
}

void MainWindow::on_btnSend_clicked()
{
	sendMessage(ui->txtMessageText->toPlainText());
}

void MainWindow::on_btnChangePort_clicked()
{
	showConfigWindow();
}

void MainWindow::on_rbtnActivate_clicked()
{
	QByteArray controlSequence;
	controlSequence[0] = CONTROL_ENABLE;
	chatPort.write(controlSequence);
}

void MainWindow::on_rbtnDeactivate_clicked()
{
	QByteArray controlSequence;
	controlSequence[0] = CONTROL_BLOCK;
	chatPort.write(controlSequence);
}
