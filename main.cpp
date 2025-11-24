#include "MainWindow.h"
#include "LoginDialog.h"      
#include "RegisterDialog.h"  
#include "AdminPanel.h"     
#include "TicketSystem.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    try {
        // 创建票务系统实例
        TicketSystem ticketSystem;

        // 显示登录对话框
        LoginDialog loginDialog(ticketSystem);

        // 主事件循环
        while (true) {
            if (loginDialog.exec() == QDialog::Accepted) {
                // 登录成功，显示主窗口
                MainWindow mainWindow(ticketSystem);
                mainWindow.show();

                // 运行主窗口事件循环
                int result = app.exec();

                // 主窗口关闭后，重新显示登录对话框
                if (result == QDialog::Accepted) {
                    // 用户选择重新登录，继续循环
                    continue;
                }
                else {
                    // 程序正常退出
                    return result;
                }
            }
            else {
                // 用户取消登录或关闭对话框
                break;
            }
        }

        return 0;
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "启动错误",
            QString("程序启动失败: %1").arg(e.what()));
        return 1;
    }
}