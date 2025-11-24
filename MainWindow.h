#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include "TicketSystem.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginClicked();
    void onLogoutClicked();
    void showSearchPage();
    void showBookingPage();
    void showAdminPage();

    void onSearchActionTriggered();
    void onBookActionTriggered();
    void onOrderActionTriggered();
    void onAdminActionTriggered();
    void cancelOrder(int orderId);
    void changeOrder(int orderId);
    void refreshOrderList(QTableWidget* orderTable);
    void showAdminWelcomePage();
    void showUserWelcomePage();
    void onDeleteAccountClicked();
    void onEditProfileClicked();


private:
    void initializeMainInterface();
    void createWelcomePage();
    void createSearchPage();
    void createBookingPage();
    void createAdminPage();
    void updateUIForUser();
    void addOrderToTable(QTableWidget* orderTable, const Order& order, bool isAdmin, bool isHistory);
  

    Ui::MainWindow* ui;
    TicketSystem& m_ticketSystem;
    User* m_currentUser;
};