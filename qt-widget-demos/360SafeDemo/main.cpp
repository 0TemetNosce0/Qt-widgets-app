#include <QApplication>

#include "src/main_widget/main_widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QFont font("Î¢ÈíÑÅºÚ", 9);
    // app.setFont(font);

    MainWidget main_widget;
    main_widget.showWidget();

    return app.exec();
}
