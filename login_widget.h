#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>

namespace Ui {
class login_widget;
}

class login_widget : public QWidget
{
    Q_OBJECT

public:
    explicit login_widget(QWidget *parent = nullptr);
    ~login_widget();

private:
    Ui::login_widget *ui;
};

#endif // FORM_H
