#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <string>

namespace Ui {
class login_widget;
}

class login_widget : public QWidget
{
    Q_OBJECT

public:
    explicit login_widget(QWidget *parent = nullptr);
    ~login_widget();
	std::string getUsername();
	std::string getPassword();
	QPushButton* getButton();

private:
    Ui::login_widget *ui;
};

#endif // FORM_H
