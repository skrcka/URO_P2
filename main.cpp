#include <QApplication>
#include "gui.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow widget;
	DenRoze3 ui{&widget};
	ui.show();
	ui.update_widgets();
    return app.exec();
}
