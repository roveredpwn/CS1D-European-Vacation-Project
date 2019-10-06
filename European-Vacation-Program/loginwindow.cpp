#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LoginWindow)
{
	ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::on_moveToMain_clicked()
{
	emit moveToMainClicked();
}

void LoginWindow::on_loginButton_clicked()
{
	// Check username and passwords in SQL to verify a login
	QString username, password;
	username = ui->usernameLineEdit->text();
	password = ui->passwordLineEdit->text();

	checkConnection();
	QSqlQuery query(QSqlDatabase::database());
	query.prepare("select * from login where username='"+username+"' and password='"+password+"'");
	if(query.exec())
	{
		int count = 0;
		while(query.next())
		{
			count++;
		}
		// Move to editwindow on successful login
		if(count >= 1)
		{
			emit moveToEditClicked();
		}
		if(count < 1)
			ui->statusLabel->setText("Invalid Username or Password");
	}
}