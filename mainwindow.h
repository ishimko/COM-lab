#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "portselecterwindow.h"
#include "types.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QSerialPort chatPort;

	PortSelecterWindow portSelecterWindow;

	ChatState chatState;

	void showConfigWindow();
	void sendMessage(QString messageText);

	void receiveMessage(QByteArray message);
	void enableChat(bool enabled);
public slots:
	void onPortChanged(QString portName);

private slots:
	void onReadyRead();
	void on_btnSend_clicked();

	void on_btnChangePort_clicked();

	void on_rbtnActivate_clicked();

	void on_rbtnDeactivate_clicked();

signals:
	void portOpened();
};

#endif // MAINWINDOW_H
