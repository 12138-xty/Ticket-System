#include "ticket_system_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ticket_system_Window w;
    w.show();
    return a.exec();
}
