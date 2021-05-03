#include <QApplication>
#include "gui.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow widget;
	widget.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	DenRoze3 ui{&widget};
	ui.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.show();
	ui.update_widgets();
    return app.exec();
}
