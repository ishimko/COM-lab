#ifndef PORTSELECTERWINDOW_H
#define PORTSELECTERWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>

namespace Ui {
class PortSelecterWindow;
}

class PortSelecterWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit PortSelecterWindow(QWidget *parent = 0);
	~PortSelecterWindow();

private:
	Ui::PortSelecterWindow *ui;

	void refreshPortsList();
signals:
	void portChoosed(QString portName);
private slots:
	void on_btnChoose_clicked();
	void on_btnRefresh_clicked();
};

#endif // PORTSELECTERWINDOW_H
