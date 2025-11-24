#include "ticket_system_window.h"
#include "ui_ticket_system_window.h"

Ticket_system_Window::Ticket_system_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ticket_system_Window)
{
    ui->setupUi(this);

}

Ticket_system_Window::~Ticket_system_Window()
{
    delete ui;
}
