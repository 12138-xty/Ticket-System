#ifndef TICKET_SYSTEM_WINDOW_H
#define TICKET_SYSTEM_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Ticket_system_Window;
}
QT_END_NAMESPACE

class Ticket_system_Window : public QMainWindow
{
    Q_OBJECT

public:
    Ticket_system_Window(QWidget *parent = nullptr);
    ~Ticket_system_Window();

private:
    Ui::Ticket_system_Window *ui;
};
#endif // TICKET_SYSTEM_WINDOW_H
