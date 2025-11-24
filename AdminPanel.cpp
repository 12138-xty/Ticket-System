#include "AdminPanel.h"
#include "ui_AdminPanel.h" 
#include "TicketSystem.h"
#include "Train.h"
#include "User.h"
#include "Station.h"
#include "TrainSchedule.h"
#include "Order.h"
#include "Seat.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QDebug>
#include <climits>
#include <string>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QTimer>
#include <QLabel>
#include <QCoreApplication>
#include <QGridLayout>
#include <QTimeEdit>
#include <QSpinBox>

using namespace std;

AdminPanel::AdminPanel(TicketSystem& ticketSystem, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanel)
    , m_ticketSystem(ticketSystem)
    , m_stationTable(nullptr)
{
    ui->setupUi(this);

    // 初始化UI组件
    m_usernameEdit = ui->usernameEdit;
    m_passwordEdit = ui->passwordEdit;
    m_captchaEdit = ui->captchaEdit;
    m_captchaDisplay = ui->captchaDisplay;
    m_refreshCaptchaButton = ui->refreshCaptchaButton;
    m_loginButton = ui->loginButton;
    m_registerButton = ui->registerButton;
    m_exitButton = ui->exitButton;
    m_rememberPasswordCheckBox = ui->rememberPasswordCheckBox;

    // 设置验证码
    m_captchaDisplay->setText(generateCaptcha());

    // 连接信号和槽
    connect(m_refreshCaptchaButton, &QPushButton::clicked, this, &AdminPanel::onRefreshCaptchaClicked);
    connect(m_loginButton, &QPushButton::clicked, this, &AdminPanel::onAdminLoginClicked);
    connect(m_registerButton, &QPushButton::clicked, this, &AdminPanel::onAddUserClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &AdminPanel::reject);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::onAddTrainClicked()
{
    QDialog addDialog(this);
    addDialog.setWindowTitle("添加列车");
    addDialog.resize(800, 600);

    QVBoxLayout* mainLayout = new QVBoxLayout(&addDialog);

    // 1. 基本信息
    QGroupBox* basicGroup = new QGroupBox("列车基本信息");
    QFormLayout* basicLayout = new QFormLayout(basicGroup);

    QLineEdit* trainCodeEdit = new QLineEdit();
    QLabel* typeLabel = new QLabel(); // 自动显示类型
    QComboBox* startStationCombo = new QComboBox();
    QComboBox* endStationCombo = new QComboBox();

    // 自动检测类型
    connect(trainCodeEdit, &QLineEdit::textChanged, [typeLabel](const QString& text) {
        if (text.startsWith("G")) typeLabel->setText("高铁");
        else if (text.startsWith("D")) typeLabel->setText("动车");
        else if (text.startsWith("K")) typeLabel->setText("普快");
        else if (text.startsWith("Z")) typeLabel->setText("直达");
        else typeLabel->setText("其他");
        });

    // 填充车站列表
    auto stations = m_ticketSystem.getAllStations();
    for (const auto& station : stations) {
        startStationCombo->addItem(QString::fromStdString(station));
        endStationCombo->addItem(QString::fromStdString(station));
    }

    basicLayout->addRow("车次:", trainCodeEdit);
    basicLayout->addRow("类型:", typeLabel);
    basicLayout->addRow("始发站:", startStationCombo);
    basicLayout->addRow("终点站:", endStationCombo);

    // 2. 经停站信息
    QGroupBox* scheduleGroup = new QGroupBox("经停站信息（请按顺序添加）");
    QVBoxLayout* scheduleLayout = new QVBoxLayout(scheduleGroup);

    QTableWidget* scheduleTable = new QTableWidget();
    scheduleTable->setColumnCount(3);
    scheduleTable->setHorizontalHeaderLabels({ "车站", "到达时间", "发车时间" });
    scheduleTable->horizontalHeader()->setStretchLastSection(true);
    scheduleLayout->addWidget(scheduleTable);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addStopBtn = new QPushButton("添加经停站");
    QPushButton* removeStopBtn = new QPushButton("删除选中");
    buttonLayout->addWidget(addStopBtn);
    buttonLayout->addWidget(removeStopBtn);
    buttonLayout->addStretch();
    scheduleLayout->addLayout(buttonLayout);

    // 3. 座位配置
    QGroupBox* seatGroup = new QGroupBox("座位配置");
    QGridLayout* seatLayout = new QGridLayout(seatGroup);

    QSpinBox* businessSeats = new QSpinBox();
    QSpinBox* firstClassSeats = new QSpinBox();
    QSpinBox* secondClassSeats = new QSpinBox();

    businessSeats->setRange(0, 100);
    firstClassSeats->setRange(0, 100);
    secondClassSeats->setRange(0, 100);

    businessSeats->setValue(10);
    firstClassSeats->setValue(20);
    secondClassSeats->setValue(50);

    seatLayout->addWidget(new QLabel("商务座:"), 0, 0);
    seatLayout->addWidget(businessSeats, 0, 1);
    seatLayout->addWidget(new QLabel("一等座:"), 1, 0);
    seatLayout->addWidget(firstClassSeats, 1, 1);
    seatLayout->addWidget(new QLabel("二等座:"), 2, 0);
    seatLayout->addWidget(secondClassSeats, 2, 1);

    mainLayout->addWidget(basicGroup);
    mainLayout->addWidget(scheduleGroup);
    mainLayout->addWidget(seatGroup);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &addDialog);
    mainLayout->addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &addDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &addDialog, &QDialog::reject);

    // 添加经停站
    connect(addStopBtn, &QPushButton::clicked, [scheduleTable, stations]() {
        int row = scheduleTable->rowCount();
        scheduleTable->insertRow(row);

        QComboBox* stationCombo = new QComboBox();
        for (const auto& station : stations) {
            stationCombo->addItem(QString::fromStdString(station));
        }

        QTimeEdit* arriveTime = new QTimeEdit();
        QTimeEdit* departTime = new QTimeEdit();

        arriveTime->setDisplayFormat("HH:mm");
        departTime->setDisplayFormat("HH:mm");
        arriveTime->setTime(QTime(8, 0).addSecs(row * 1800)); // 每站间隔30分钟
        departTime->setTime(arriveTime->time().addSecs(300)); // 停靠5分钟

        scheduleTable->setCellWidget(row, 0, stationCombo);
        scheduleTable->setCellWidget(row, 1, arriveTime);
        scheduleTable->setCellWidget(row, 2, departTime);
        });

    // 删除经停站
    connect(removeStopBtn, &QPushButton::clicked, [scheduleTable]() {
        int row = scheduleTable->currentRow();
        if (row >= 0) {
            scheduleTable->removeRow(row);
        }
        });

    if (addDialog.exec() == QDialog::Accepted) {
        QString trainCode = trainCodeEdit->text().trimmed();
        QString startStation = startStationCombo->currentText();
        QString endStation = endStationCombo->currentText();

        if (trainCode.isEmpty()) {
            QMessageBox::warning(this, "错误", "车次不能为空");
            return;
        }

        if (startStation == endStation) {
            QMessageBox::warning(this, "错误", "始发站和终点站不能相同");
            return;
        }

        // 自动判断列车类型
        QString type;
        if (trainCode.startsWith("G")) type = "高铁";
        else if (trainCode.startsWith("D")) type = "动车";
        else if (trainCode.startsWith("K")) type = "普快";
        else if (trainCode.startsWith("Z")) type = "直达";
        else type = "其他";

        // 获取车站ID
        int startStationId = -1, endStationId = -1;
        const auto& stationList = m_ticketSystem.getStations();
        for (const auto& station : stationList) {
            if (station.getName() == startStation) startStationId = station.getStationId();
            if (station.getName() == endStation) endStationId = station.getStationId();
        }

        if (startStationId == -1 || endStationId == -1) {
            QMessageBox::warning(this, "错误", "无效的车站名称");
            return;
        }

        // 调用扩展的添加列车方法
        if (m_ticketSystem.addTrainWithSchedulesAndSeats(
            trainCode.toStdString(),
            type.toStdString(),
            startStationId,
            endStationId,
            scheduleTable,
            businessSeats->value(),
            firstClassSeats->value(),
            secondClassSeats->value()
        )) {
            refreshTrainData();
        }
    }
}

void AdminPanel::onEditTrainClicked()
{
    if (!m_trainTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要编辑的列车");
        return;
    }

    int row = m_trainTable->currentRow();
    int trainId = m_trainTable->item(row, 0)->text().toInt();

    // 获取当前列车信息
    Train* train = m_ticketSystem.getTrainById(trainId);
    if (!train) {
        QMessageBox::warning(this, "错误", "未找到指定的列车");
        return;
    }

    // 创建编辑对话框（与添加对话框相同的界面）
    QDialog editDialog(this);
    editDialog.setWindowTitle("编辑列车");
    editDialog.resize(800, 600);

    QVBoxLayout* mainLayout = new QVBoxLayout(&editDialog);

    // 1. 基本信息
    QGroupBox* basicGroup = new QGroupBox("列车基本信息");
    QFormLayout* basicLayout = new QFormLayout(basicGroup);

    QLineEdit* trainCodeEdit = new QLineEdit(QString::fromStdString(train->getTrainCode()));
    QLabel* typeLabel = new QLabel(QString::fromStdString(train->getType()));
    QComboBox* startStationCombo = new QComboBox();
    QComboBox* endStationCombo = new QComboBox();

    // 自动检测类型
    connect(trainCodeEdit, &QLineEdit::textChanged, [typeLabel](const QString& text) {
        if (text.startsWith("G")) typeLabel->setText("高铁");
        else if (text.startsWith("D")) typeLabel->setText("动车");
        else if (text.startsWith("K")) typeLabel->setText("普快");
        else if (text.startsWith("Z")) typeLabel->setText("直达");
        else typeLabel->setText("其他");
        });

    // 填充车站列表
    auto stations = m_ticketSystem.getAllStations();
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < stations.size(); ++i) {
        QString stationName = QString::fromStdString(stations[i]);
        startStationCombo->addItem(stationName);
        endStationCombo->addItem(stationName);

        if (stationName == m_ticketSystem.getStationNameById(train->getStartStationId()))
            startIndex = i;
        if (stationName == m_ticketSystem.getStationNameById(train->getEndStationId()))
            endIndex = i;
    }

    if (startIndex != -1) startStationCombo->setCurrentIndex(startIndex);
    if (endIndex != -1) endStationCombo->setCurrentIndex(endIndex);

    basicLayout->addRow("车次:", trainCodeEdit);
    basicLayout->addRow("类型:", typeLabel);
    basicLayout->addRow("始发站:", startStationCombo);
    basicLayout->addRow("终点站:", endStationCombo);

    // 2. 经停站信息
    QGroupBox* scheduleGroup = new QGroupBox("经停站信息（请按顺序添加）");
    QVBoxLayout* scheduleLayout = new QVBoxLayout(scheduleGroup);

    QTableWidget* scheduleTable = new QTableWidget();
    scheduleTable->setColumnCount(3);
    scheduleTable->setHorizontalHeaderLabels({ "车站", "到达时间", "发车时间" });
    scheduleTable->horizontalHeader()->setStretchLastSection(true);
    scheduleLayout->addWidget(scheduleTable);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addStopBtn = new QPushButton("添加经停站");
    QPushButton* removeStopBtn = new QPushButton("删除选中");
    buttonLayout->addWidget(addStopBtn);
    buttonLayout->addWidget(removeStopBtn);
    buttonLayout->addStretch();
    scheduleLayout->addLayout(buttonLayout);

    // 3. 座位配置
    QGroupBox* seatGroup = new QGroupBox("座位配置");
    QGridLayout* seatLayout = new QGridLayout(seatGroup);

    QSpinBox* businessSeats = new QSpinBox();
    QSpinBox* firstClassSeats = new QSpinBox();
    QSpinBox* secondClassSeats = new QSpinBox();

    businessSeats->setRange(0, 100);
    firstClassSeats->setRange(0, 100);
    secondClassSeats->setRange(0, 100);

    // 加载现有座位配置
    int businessCount = 0, firstClassCount = 0, secondClassCount = 0;
    auto seats = m_ticketSystem.getSeats();
    for (const auto& seat : seats) {
        if (seat.getTrainId() == trainId) {
            if (seat.getSeatType() == "商务") businessCount++;
            else if (seat.getSeatType() == "一等") firstClassCount++;
            else if (seat.getSeatType() == "二等") secondClassCount++;
        }
    }

    businessSeats->setValue(businessCount);
    firstClassSeats->setValue(firstClassCount);
    secondClassSeats->setValue(secondClassCount);

    seatLayout->addWidget(new QLabel("商务座:"), 0, 0);
    seatLayout->addWidget(businessSeats, 0, 1);
    seatLayout->addWidget(new QLabel("一等座:"), 1, 0);
    seatLayout->addWidget(firstClassSeats, 1, 1);
    seatLayout->addWidget(new QLabel("二等座:"), 2, 0);
    seatLayout->addWidget(secondClassSeats, 2, 1);

    mainLayout->addWidget(basicGroup);
    mainLayout->addWidget(scheduleGroup);
    mainLayout->addWidget(seatGroup);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &editDialog);
    mainLayout->addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &editDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &editDialog, &QDialog::reject);

    // 加载现有经停站信息
    auto schedules = m_ticketSystem.getTrainSchedules();
    for (const auto& schedule : schedules) {
        if (schedule.getTrainId() == trainId) {
            int row = scheduleTable->rowCount();
            scheduleTable->insertRow(row);

            QComboBox* stationCombo = new QComboBox();
            for (const auto& station : stations) {
                stationCombo->addItem(QString::fromStdString(station));
            }

            QTimeEdit* arriveTime = new QTimeEdit();
            QTimeEdit* departTime = new QTimeEdit();

            arriveTime->setDisplayFormat("HH:mm");
            departTime->setDisplayFormat("HH:mm");

            // 设置当前值
            QString stationName = m_ticketSystem.getStationNameById(schedule.getStationId());
            int stationIndex = stationCombo->findText(stationName);
            if (stationIndex != -1) {
                stationCombo->setCurrentIndex(stationIndex);
            }

            arriveTime->setTime(QTime::fromString(QString::fromStdString(schedule.getArriveTime()), "HH:mm"));
            departTime->setTime(QTime::fromString(QString::fromStdString(schedule.getDepartTime()), "HH:mm"));

            scheduleTable->setCellWidget(row, 0, stationCombo);
            scheduleTable->setCellWidget(row, 1, arriveTime);
            scheduleTable->setCellWidget(row, 2, departTime);
        }
    }

    // 添加经停站
    connect(addStopBtn, &QPushButton::clicked, [scheduleTable, stations]() {
        int row = scheduleTable->rowCount();
        scheduleTable->insertRow(row);

        QComboBox* stationCombo = new QComboBox();
        for (const auto& station : stations) {
            stationCombo->addItem(QString::fromStdString(station));
        }

        QTimeEdit* arriveTime = new QTimeEdit();
        QTimeEdit* departTime = new QTimeEdit();

        arriveTime->setDisplayFormat("HH:mm");
        departTime->setDisplayFormat("HH:mm");
        arriveTime->setTime(QTime(8, 0).addSecs(row * 1800));
        departTime->setTime(arriveTime->time().addSecs(300));

        scheduleTable->setCellWidget(row, 0, stationCombo);
        scheduleTable->setCellWidget(row, 1, arriveTime);
        scheduleTable->setCellWidget(row, 2, departTime);
        });

    // 删除经停站
    connect(removeStopBtn, &QPushButton::clicked, [scheduleTable]() {
        int row = scheduleTable->currentRow();
        if (row >= 0) {
            scheduleTable->removeRow(row);
        }
        });

    if (editDialog.exec() == QDialog::Accepted) {
        QString trainCode = trainCodeEdit->text().trimmed();
        QString startStation = startStationCombo->currentText();
        QString endStation = endStationCombo->currentText();

        if (trainCode.isEmpty()) {
            QMessageBox::warning(this, "错误", "车次不能为空");
            return;
        }

        if (startStation == endStation) {
            QMessageBox::warning(this, "错误", "始发站和终点站不能相同");
            return;
        }

        // 自动判断列车类型
        QString type;
        if (trainCode.startsWith("G")) type = "高铁";
        else if (trainCode.startsWith("D")) type = "动车";
        else if (trainCode.startsWith("K")) type = "普快";
        else if (trainCode.startsWith("Z")) type = "直达";
        else type = "其他";

        // 获取车站ID
        int startStationId = -1, endStationId = -1;
        const auto& stationList = m_ticketSystem.getStations();
        for (const auto& station : stationList) {
            if (station.getName() == startStation) startStationId = station.getStationId();
            if (station.getName() == endStation) endStationId = station.getStationId();
        }

        if (startStationId == -1 || endStationId == -1) {
            QMessageBox::warning(this, "错误", "无效的车站名称");
            return;
        }

        // 构建新的经停站列表
        std::vector<TrainSchedule> newSchedules;
        int maxScheduleId = 0;
        auto allSchedules = m_ticketSystem.getTrainSchedules();
        for (const auto& s : allSchedules) {
            if (s.getScheduleId() > maxScheduleId) maxScheduleId = s.getScheduleId();
        }

        for (int row = 0; row < scheduleTable->rowCount(); ++row) {
            QComboBox* stationCombo = qobject_cast<QComboBox*>(scheduleTable->cellWidget(row, 0));
            QTimeEdit* arriveTime = qobject_cast<QTimeEdit*>(scheduleTable->cellWidget(row, 1));
            QTimeEdit* departTime = qobject_cast<QTimeEdit*>(scheduleTable->cellWidget(row, 2));

            if (!stationCombo || !arriveTime || !departTime) continue;

            QString stationName = stationCombo->currentText();
            int stationId = -1;
            for (const auto& station : stationList) {
                if (station.getName() == stationName) {
                    stationId = station.getStationId();
                    break;
                }
            }

            if (stationId != -1) {
                newSchedules.emplace_back(
                    ++maxScheduleId,
                    trainId,
                    stationId,
                    row + 1,
                    arriveTime->time().toString("HH:mm").toStdString(),
                    departTime->time().toString("HH:mm").toStdString()
                );
            }
        }

        // 构建新的座位列表
        std::vector<Seat> newSeats;
        int maxSeatId = 0;
        auto allSeats = m_ticketSystem.getSeats();
        for (const auto& s : allSeats) {
            if (s.getSeatId() > maxSeatId) maxSeatId = s.getSeatId();
        }

        // 添加商务座
        for (int i = 1; i <= businessSeats->value(); ++i) {
            newSeats.emplace_back(++maxSeatId, trainId, std::to_string(i) + "A", "商务");
        }

        // 添加一等座
        for (int i = 1; i <= firstClassSeats->value(); ++i) {
            newSeats.emplace_back(++maxSeatId, trainId, std::to_string(i) + "B", "一等");
        }

        // 添加二等座
        for (int i = 1; i <= secondClassSeats->value(); ++i) {
            newSeats.emplace_back(++maxSeatId, trainId, std::to_string(i) + "C", "二等");
        }

        // 调用扩展的编辑列车方法
        if (m_ticketSystem.editTrain(trainId,
            trainCode.toStdString(),
            type.toStdString(),
            startStationId,
            endStationId,
            newSchedules,
            newSeats)) {
            refreshTrainData();
            QMessageBox::information(this, "成功", "列车编辑成功");
        }
        else {
            QMessageBox::warning(this, "失败", "列车编辑失败");
        }
    }
}

void AdminPanel::onDeleteTrainClicked()
{
    if (!m_trainTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要删除的列车");
        return;
    }

    int row = m_trainTable->currentRow();
    int trainId = m_trainTable->item(row, 0)->text().toInt();
    QString trainCode = m_trainTable->item(row, 1)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除列车 %1 (%2) 吗?\n此操作不可撤销！")
        .arg(trainCode).arg(trainId),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 调用TicketSystem的删除列车方法
        if (m_ticketSystem.deleteTrain(trainId)) {
            QMessageBox::information(this, "成功", "列车删除成功");
            refreshTrainData();
        }
        else {
            QMessageBox::warning(this, "失败", "列车删除失败\n可能有未完成的订单关联到此列车");
        }
    }
}

void AdminPanel::onAddUserClicked()
{
    bool ok;
    QString username = QInputDialog::getText(this, "添加用户", "请输入用户名:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) return;

    QString password = QInputDialog::getText(this, "添加用户", "请输入密码:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) return;

    QString displayName = QInputDialog::getText(this, "添加用户", "请输入显示名称:", QLineEdit::Normal, "", &ok);
    if (!ok || displayName.isEmpty()) return;

    QString role = QInputDialog::getItem(this, "添加用户", "选择用户角色:",
        QStringList() << "user" << "admin", 0, false, &ok);
    if (!ok) return;

    QString id_card = QInputDialog::getText(this, "添加用户", "请输入身份证号:", QLineEdit::Normal, "", &ok);
    if (!ok || id_card.isEmpty()) return;

    // 使用TicketSystem的注册用户方法，添加身份证号参数
    if (m_ticketSystem.registerUser(username.toStdString(), password.toStdString(),
        displayName.toStdString(), "", id_card.toStdString(), role.toStdString())) {
        QMessageBox::information(this, "成功", "用户添加成功");
        refreshUserData();
    }
    else {
        QMessageBox::warning(this, "失败", "用户添加失败（用户名可能已存在）");
    }
}

void AdminPanel::onEditUserClicked() {
    if (!m_userTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要编辑的用户");
        return;
    }

    int row = m_userTable->currentRow();
    QString userId = m_userTable->item(row, 0)->text();
    QString currentUsername = m_userTable->item(row, 1)->text();
    QString currentDisplayName = m_userTable->item(row, 2)->text();
    QString currentRole = m_userTable->item(row, 3)->text();
    QString currentPhone = ""; // 需要从用户对象获取，或者添加到表格中

    // 创建编辑对话框
    QDialog editDialog(this);
    editDialog.setWindowTitle("编辑用户信息");
    editDialog.resize(400, 300);

    QFormLayout form(&editDialog);

    QLineEdit* usernameEdit = new QLineEdit(currentUsername);
    QLineEdit* displayNameEdit = new QLineEdit(currentDisplayName);
    QLineEdit* phoneEdit = new QLineEdit(currentPhone);
    QLineEdit* passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("留空则不修改密码");
    passwordEdit->setEchoMode(QLineEdit::Password);

    QComboBox* roleCombo = new QComboBox();
    roleCombo->addItem("user", "user");
    roleCombo->addItem("admin", "admin");
    roleCombo->setCurrentText(currentRole);

    form.addRow("用户名:", usernameEdit);
    form.addRow("显示名称:", displayNameEdit);
    form.addRow("手机号:", phoneEdit);
    form.addRow("新密码:", passwordEdit);
    form.addRow("角色:", roleCombo);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &editDialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &editDialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &editDialog, &QDialog::reject);

    if (editDialog.exec() == QDialog::Accepted) {
        QString newUsername = usernameEdit->text().trimmed();
        QString newDisplayName = displayNameEdit->text().trimmed();
        QString newPhone = phoneEdit->text().trimmed();
        QString newPassword = passwordEdit->text();
        QString newRole = roleCombo->currentData().toString();

        if (newUsername.isEmpty()) {
            QMessageBox::warning(this, "错误", "用户名不能为空");
            return;
        }

        if (m_ticketSystem.editUser(userId.toStdString(),
            newUsername.toStdString(),
            newPhone.toStdString(),
            newPassword.toStdString(),
            newRole.toStdString())) {
            QMessageBox::information(this, "成功", "用户信息修改成功");
            refreshUserData();
        }
        else {
            QMessageBox::warning(this, "失败", "用户信息修改失败（用户名可能已存在）");
        }
    }
}

void AdminPanel::onDeleteUserClicked() {
    if (!m_userTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要删除的用户");
        return;
    }

    int row = m_userTable->currentRow();
    QString userId = m_userTable->item(row, 0)->text();
    QString username = m_userTable->item(row, 1)->text();

    // 防止删除当前登录的管理员
    User* currentUser = m_ticketSystem.getCurrentUser();
    if (currentUser && QString::fromStdString(currentUser->getUserId()) == userId) {
        QMessageBox::warning(this, "错误", "不能删除当前登录的用户");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除用户 %1 吗?").arg(username),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_ticketSystem.deleteUser(userId.toStdString())) {
            QMessageBox::information(this, "成功", "用户删除成功");
            refreshUserData();
        }
        else {
            QMessageBox::warning(this, "失败", "用户删除失败");
        }
    }
}

void AdminPanel::onRefreshCaptchaClicked()
{
    m_captchaDisplay->setText(generateCaptcha());
}

void AdminPanel::onAdminLoginClicked()
{
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();
    QString captcha = m_captchaEdit->text();

    if (username.isEmpty() || password.isEmpty() || captcha.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "请填写完整信息");
        return;
    }

    if (captcha != m_captchaDisplay->text()) {
        QMessageBox::warning(this, "登录失败", "验证码错误");
        onRefreshCaptchaClicked();
        return;
    }

    if (m_ticketSystem.validateLogin(username, password)) {
        User* user = m_ticketSystem.getCurrentUser();

        // 检查是否为管理员
        if (user && m_ticketSystem.isAdminUser(user->getUserId())) {
            QMessageBox::information(this, "登录成功", "管理员登录成功");

            // 创建管理主界面
            QDialog* adminMainDialog = new QDialog(this);
            adminMainDialog->setWindowTitle("管理员控制面板 - " + QString::fromStdString(user->getUsername()));
            adminMainDialog->resize(1200, 800); // 增加宽度以容纳更多内容

            QTabWidget* tabWidget = new QTabWidget(adminMainDialog);
            tabWidget->addTab(createTrainManagementTab(), "列车管理");
            tabWidget->addTab(createUserManagementTab(), "用户管理");
            tabWidget->addTab(createOrderManagementTab(), "订单管理");
            tabWidget->addTab(createStationManagementTab(), "车站管理"); // 新增车站管理选项卡

            QVBoxLayout* layout = new QVBoxLayout(adminMainDialog);
            layout->addWidget(tabWidget);

            adminMainDialog->exec();
            delete adminMainDialog;
        }
        else {
            QMessageBox::warning(this, "登录失败", "非管理员账号无法登录");
        }
    }
    else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
        onRefreshCaptchaClicked();
    }
}

QWidget* AdminPanel::createTrainManagementTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    m_trainTable = new QTableWidget(tab);
    m_trainTable->setColumnCount(6);
    m_trainTable->setHorizontalHeaderLabels({ "车次ID", "车次", "始发站", "终点站", "出发时间", "到达时间" });
    m_trainTable->horizontalHeader()->setStretchLastSection(true);
    m_trainTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_addTrainBtn = new QPushButton("添加列车", tab);
    m_editTrainBtn = new QPushButton("编辑列车", tab);
    m_deleteTrainBtn = new QPushButton("删除列车", tab);

    buttonLayout->addWidget(m_addTrainBtn);
    buttonLayout->addWidget(m_editTrainBtn);
    buttonLayout->addWidget(m_deleteTrainBtn);
    buttonLayout->addStretch();

    layout->addWidget(m_trainTable);
    layout->addLayout(buttonLayout);

    connect(m_addTrainBtn, &QPushButton::clicked, this, &AdminPanel::onAddTrainClicked);
    connect(m_editTrainBtn, &QPushButton::clicked, this, &AdminPanel::onEditTrainClicked);
    connect(m_deleteTrainBtn, &QPushButton::clicked, this, &AdminPanel::onDeleteTrainClicked);

    refreshTrainData();
    return tab;
}

QWidget* AdminPanel::createUserManagementTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    // 创建搜索区域
    QHBoxLayout* searchLayout = new QHBoxLayout();
    QLabel* searchLabel = new QLabel("按姓名搜索:");
    m_searchUserEdit = new QLineEdit();
    m_searchUserEdit->setPlaceholderText("输入用户姓名进行搜索...");
    QPushButton* searchBtn = new QPushButton("搜索");
    QPushButton* clearSearchBtn = new QPushButton("清除");

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(m_searchUserEdit);
    searchLayout->addWidget(searchBtn);
    searchLayout->addWidget(clearSearchBtn);
    searchLayout->addStretch();

    m_userTable = new QTableWidget(tab);
    m_userTable->setColumnCount(4);
    m_userTable->setHorizontalHeaderLabels({ "用户ID", "用户名", "显示名称", "角色" });
    m_userTable->horizontalHeader()->setStretchLastSection(true);
    m_userTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_addUserBtn = new QPushButton("添加用户", tab);
    m_editUserBtn = new QPushButton("编辑用户", tab);
    m_deleteUserBtn = new QPushButton("删除用户", tab);
    m_lockUserBtn = new QPushButton("锁定用户", tab);
    m_unlockUserBtn = new QPushButton("解锁用户", tab);

    buttonLayout->addWidget(m_addUserBtn);
    buttonLayout->addWidget(m_editUserBtn);
    buttonLayout->addWidget(m_deleteUserBtn);
    buttonLayout->addWidget(m_lockUserBtn);
    buttonLayout->addWidget(m_unlockUserBtn);
    buttonLayout->addStretch();

    layout->addLayout(searchLayout);
    layout->addWidget(m_userTable);
    layout->addLayout(buttonLayout);

    connect(m_addUserBtn, &QPushButton::clicked, this, &AdminPanel::onAddUserClicked);
    connect(m_editUserBtn, &QPushButton::clicked, this, &AdminPanel::onEditUserClicked);
    connect(m_deleteUserBtn, &QPushButton::clicked, this, &AdminPanel::onDeleteUserClicked);
    connect(searchBtn, &QPushButton::clicked, this, &AdminPanel::onSearchUserClicked);
    connect(clearSearchBtn, &QPushButton::clicked, this, &AdminPanel::onClearSearchClicked);
    connect(m_searchUserEdit, &QLineEdit::returnPressed, this, &AdminPanel::onSearchUserClicked);
    connect(m_lockUserBtn, &QPushButton::clicked, this, &AdminPanel::onLockUserClicked);
    connect(m_unlockUserBtn, &QPushButton::clicked, this, &AdminPanel::onUnlockUserClicked);

    refreshUserData();
    return tab;
}

QWidget* AdminPanel::createOrderManagementTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    // 创建订单管理区域
    QGroupBox* orderGroup = new QGroupBox("订单管理");
    QVBoxLayout* orderLayout = new QVBoxLayout(orderGroup);

    // 订单表格
    m_orderTable = new QTableWidget();
    m_orderTable->setColumnCount(8);
    m_orderTable->setHorizontalHeaderLabels({ "订单ID", "用户ID", "用户名", "车次", "出发站", "到达站", "旅行日期", "状态" });
    m_orderTable->horizontalHeader()->setStretchLastSection(true);
    m_orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 添加操作按钮
    QHBoxLayout* adminButtonLayout = new QHBoxLayout();
    QPushButton* cancelOrderBtn = new QPushButton("取消订单");
    QPushButton* changeOrderBtn = new QPushButton("改签订单");
    QPushButton* refreshOrdersBtn = new QPushButton("刷新订单列表");

    adminButtonLayout->addWidget(cancelOrderBtn);
    adminButtonLayout->addWidget(changeOrderBtn);
    adminButtonLayout->addWidget(refreshOrdersBtn);
    adminButtonLayout->addStretch();

    orderLayout->addWidget(m_orderTable);
    orderLayout->addLayout(adminButtonLayout);

    layout->addWidget(orderGroup);

    // 连接信号槽
    connect(cancelOrderBtn, &QPushButton::clicked, this, &AdminPanel::onCancelOrderClicked);
    connect(changeOrderBtn, &QPushButton::clicked, this, &AdminPanel::onChangeOrderClicked);
    connect(refreshOrdersBtn, &QPushButton::clicked, this, &AdminPanel::refreshOrderData);

    // 初始刷新订单数据
    refreshOrderData();

    return tab;
}

void AdminPanel::refreshTrainData()
{
    m_trainTable->setRowCount(0);

    // 从TicketSystem获取真实的列车数据
    auto trains = m_ticketSystem.getAllTrains();
    for (const auto* train : trains) {
        if (train) {
            int row = m_trainTable->rowCount();
            m_trainTable->insertRow(row);

            m_trainTable->setItem(row, 0, new QTableWidgetItem(QString::number(train->getTrainId())));
            m_trainTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(train->getTrainCode())));
            m_trainTable->setItem(row, 2, new QTableWidgetItem(m_ticketSystem.getStationNameById(train->getStartStationId())));
            m_trainTable->setItem(row, 3, new QTableWidgetItem(m_ticketSystem.getStationNameById(train->getEndStationId())));
            m_trainTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(m_ticketSystem.getDepartureTimeForTrain(train->getTrainId()))));
            m_trainTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(m_ticketSystem.getArrivalTimeForTrain(train->getTrainId()))));
        }
    }
}

void AdminPanel::refreshUserData() {
    if (!m_userTable) return;

    // 1. 清空表格
    m_userTable->setRowCount(0);

    // 2. 重新获取最新用户数据
    std::vector<User*> users = m_ticketSystem.getAllUsers();

    // 3. 重新填充表格
    for (const auto* user : users) {
        if (!user) continue;

        int row = m_userTable->rowCount();
        m_userTable->insertRow(row);

        m_userTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(user->getUserId())));
        m_userTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user->getUsername())));
        m_userTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(user->getDisplayName())));

        // 显示角色和锁定状态
        QString roleDisplay = QString::fromStdString(user->getRole());
        if (user->isLocked()) {
            roleDisplay += " 🔒"; // 添加锁定图标
        }
        m_userTable->setItem(row, 3, new QTableWidgetItem(roleDisplay));
    }
}

QString AdminPanel::generateCaptcha()
{
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString captcha;
    for (int i = 0; i < 4; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        captcha.append(chars[index]);
    }
    return captcha;
}

void AdminPanel::onSearchUserClicked() {
    QString searchText = m_searchUserEdit->text().trimmed();
    if (searchText.isEmpty()) {
        refreshUserData(); // 如果搜索文本为空，显示所有用户
        return;
    }

    // 清空表格
    m_userTable->setRowCount(0);

    // 获取所有用户并过滤
    std::vector<User*> users = m_ticketSystem.getAllUsers();
    int foundCount = 0;

    for (const auto* user : users) {
        if (!user) continue;

        QString displayName = QString::fromStdString(user->getDisplayName());

        // 使用包含匹配（不区分大小写）
        if (displayName.contains(searchText, Qt::CaseInsensitive)) {
            int row = m_userTable->rowCount();
            m_userTable->insertRow(row);

            m_userTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(user->getUserId())));
            m_userTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user->getUsername())));
            m_userTable->setItem(row, 2, new QTableWidgetItem(displayName));

            // 显示角色和锁定状态
            QString roleDisplay = QString::fromStdString(user->getRole());
            if (user->isLocked()) {
                roleDisplay += " 🔒"; // 添加锁定图标
            }
            m_userTable->setItem(row, 3, new QTableWidgetItem(roleDisplay));

            foundCount++;
        }
    }

    // 显示搜索结果信息
    QMessageBox::information(this, "搜索结果",
        QString("找到 %1 个匹配的用户").arg(foundCount));
}

void AdminPanel::onClearSearchClicked()
{
    m_searchUserEdit->clear();
    refreshUserData();
}

void AdminPanel::onLockUserClicked() {
    if (!m_userTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要锁定的用户");
        return;
    }

    int row = m_userTable->currentRow();
    QString userId = m_userTable->item(row, 0)->text();
    QString username = m_userTable->item(row, 1)->text();
    QString currentRole = m_userTable->item(row, 3)->text();

    // 检查是否已经是锁定状态
    if (currentRole.contains("(lock)")) {
        QMessageBox::information(this, "提示", "该用户已被锁定");
        return;
    }

    // 防止锁定当前登录的管理员
    User* currentUser = m_ticketSystem.getCurrentUser();
    if (currentUser && QString::fromStdString(currentUser->getUserId()) == userId) {
        QMessageBox::warning(this, "错误", "不能锁定当前登录的用户");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认锁定",
        QString("确定要锁定用户 %1 吗?\n锁定后该用户将无法登录系统").arg(username),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 锁定用户
        User* user = m_ticketSystem.getUserById(userId.toStdString());
        if (user) {
            user->setLocked(true);

            // 保存到数据库
            if (m_ticketSystem.saveUsers()) {
                QMessageBox::information(this, "成功", "用户锁定成功");
                refreshUserData();
            }
            else {
                QMessageBox::warning(this, "失败", "用户锁定失败");
            }
        }
    }
}

void AdminPanel::onUnlockUserClicked() {
    if (!m_userTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要解锁的用户");
        return;
    }

    int row = m_userTable->currentRow();
    QString userId = m_userTable->item(row, 0)->text();
    QString username = m_userTable->item(row, 1)->text();
    QString currentRole = m_userTable->item(row, 3)->text();

    // 检查是否已经是解锁状态
    if (!currentRole.contains("(lock)")) {
        QMessageBox::information(this, "提示", "该用户未被锁定");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认解锁",
        QString("确定要解锁用户 %1 吗?\n解锁后该用户可以正常登录系统").arg(username),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 解锁用户
        User* user = m_ticketSystem.getUserById(userId.toStdString());
        if (user) {
            user->setLocked(false);

            // 保存到数据库
            if (m_ticketSystem.saveUsers()) {
                QMessageBox::information(this, "成功", "用户解锁成功");
                refreshUserData();
            }
            else {
                QMessageBox::warning(this, "失败", "用户解锁失败");
            }
        }
    }
}

void AdminPanel::refreshOrderData()
{
    if (!m_orderTable) return;

    m_orderTable->setRowCount(0);

    // 获取所有订单（管理员权限）
    std::vector<Order> orders = m_ticketSystem.getUserOrdersWithDetails("0");

    // 设置表格列
    m_orderTable->setColumnCount(8);
    m_orderTable->setHorizontalHeaderLabels({ "订单ID", "用户ID", "姓名", "车次", "出发站", "到达站", "旅行日期", "状态" });

    for (const auto& order : orders) {
        int row = m_orderTable->rowCount();
        m_orderTable->insertRow(row);

        // 获取用户信息 - 显示display_name而不是username
        User* user = m_ticketSystem.getUserById(QString::number(order.getUserId()).toStdString());
        QString displayName = user ? QString::fromStdString(user->getDisplayName()) : "未知用户";

        std::string trainCode = m_ticketSystem.getTrainCodeByOrder(order);
        QString startStation = m_ticketSystem.getStationNameById(order.getStartStationId());
        QString endStation = m_ticketSystem.getStationNameById(order.getEndStationId());

        // 填充订单信息 - 使用display_name
        m_orderTable->setItem(row, 0, new QTableWidgetItem(QString::number(order.getOrderId())));
        m_orderTable->setItem(row, 1, new QTableWidgetItem(QString::number(order.getUserId())));
        m_orderTable->setItem(row, 2, new QTableWidgetItem(displayName)); // 显示display_name
        m_orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(trainCode)));
        m_orderTable->setItem(row, 4, new QTableWidgetItem(startStation));
        m_orderTable->setItem(row, 5, new QTableWidgetItem(endStation));
        m_orderTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(order.getTravelDate())));
       

        // 状态显示
        QTableWidgetItem* statusItem = new QTableWidgetItem(QString::fromStdString(order.getStatus()));
        if (order.getStatus() == "booked") {
            statusItem->setBackground(Qt::green);
            statusItem->setForeground(Qt::black);
        }
        else if (order.getStatus() == "canceled") {
            statusItem->setBackground(Qt::red);
            statusItem->setForeground(Qt::white);
        }
        else if (order.getStatus() == "changed") {
            statusItem->setBackground(Qt::yellow);
            statusItem->setForeground(Qt::black);
        }
        m_orderTable->setItem(row, 7, statusItem);

        qDebug() << "显示订单:" << order.getOrderId() << "用户:" << order.getUserId()
            << "状态:" << QString::fromStdString(order.getStatus());
    }

    // 调整列宽
    m_orderTable->resizeColumnsToContents();

    if (orders.empty()) {
        qDebug() << "订单列表为空，可能的原因:";
        qDebug() << "1. orders.txt 文件不存在或无法读取";
        qDebug() << "2. 文件格式不正确";
        qDebug() << "3. 数据解析失败";

        // 显示提示信息
        int row = m_orderTable->rowCount();
        m_orderTable->insertRow(row);
        QTableWidgetItem* messageItem = new QTableWidgetItem("没有找到订单数据，请检查数据文件");
        messageItem->setBackground(Qt::lightGray);
        m_orderTable->setItem(row, 0, messageItem);
        m_orderTable->setSpan(row, 0, 1, 8); // 合并单元格
    }
}

void AdminPanel::onAddStationClicked()
{
    bool ok;
    QString stationName = QInputDialog::getText(this, "添加车站",
        "请输入车站名称:", QLineEdit::Normal, "", &ok);

    if (!ok || stationName.isEmpty()) return;

    // 检查车站是否已存在
    auto stations = m_ticketSystem.getAllStations();
    for (const auto& station : stations) {
        if (QString::fromStdString(station) == stationName) {
            QMessageBox::warning(this, "错误", "车站已存在");
            return;
        }
    }

    // 调用 TicketSystem 的添加车站方法
    if (m_ticketSystem.addStation(stationName.toStdString())) {
        QMessageBox::information(this, "成功", "车站添加成功");
        refreshStationData();
    }
    else {
        QMessageBox::warning(this, "失败", "车站添加失败");
    }
}

void AdminPanel::onDeleteStationClicked()
{
    if (!m_stationTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要删除的车站");
        return;
    }

    int row = m_stationTable->currentRow();
    QString stationName = m_stationTable->item(row, 1)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除车站 '%1' 吗?\n注意：删除车站会影响相关列车和订单").arg(stationName),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_ticketSystem.deleteStation(stationName.toStdString())) {
            QMessageBox::information(this, "成功", "车站删除成功");
            refreshStationData();
        }
        else {
            QMessageBox::warning(this, "失败", "车站删除失败\n可能有列车或订单关联到此车站");
        }
    }
}

void AdminPanel::refreshStationData()
{
    if (!m_stationTable) return;

    m_stationTable->setRowCount(0);

    auto stations = m_ticketSystem.getStations();
    for (const auto& station : stations) {
        int row = m_stationTable->rowCount();
        m_stationTable->insertRow(row);

        m_stationTable->setItem(row, 0, new QTableWidgetItem(QString::number(station.getStationId())));
        m_stationTable->setItem(row, 1, new QTableWidgetItem(station.getName()));
    }
}

QWidget* AdminPanel::createStationManagementTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    m_stationTable = new QTableWidget(tab);
    m_stationTable->setColumnCount(2);
    m_stationTable->setHorizontalHeaderLabels({ "车站ID", "车站名称" });
    m_stationTable->horizontalHeader()->setStretchLastSection(true);
    m_stationTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addStationBtn = new QPushButton("添加车站", tab);
    QPushButton* deleteStationBtn = new QPushButton("删除车站", tab);

    buttonLayout->addWidget(addStationBtn);
    buttonLayout->addWidget(deleteStationBtn);
    buttonLayout->addStretch();

    layout->addWidget(m_stationTable);
    layout->addLayout(buttonLayout);

    // 正确的连接语法
    connect(addStationBtn, &QPushButton::clicked, this, &AdminPanel::onAddStationClicked);
    connect(deleteStationBtn, &QPushButton::clicked, this, &AdminPanel::onDeleteStationClicked);

    refreshStationData();
    return tab;
}

void AdminPanel::onCancelOrderClicked()
{
    if (!m_orderTable || !m_orderTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要取消的订单");
        return;
    }

    int row = m_orderTable->currentRow();
    int orderId = m_orderTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认取消",
        QString("确定要取消订单 %1 吗？").arg(orderId),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_ticketSystem.cancelOrder(orderId)) {
            QMessageBox::information(this, "成功", "订单取消成功");
            refreshOrderData();
        }
        else {
            QMessageBox::warning(this, "失败", "订单取消失败");
        }
    }
}

void AdminPanel::onChangeOrderClicked()
{
    if (!m_orderTable || !m_orderTable->currentItem()) {
        QMessageBox::warning(this, "警告", "请选择要改签的订单");
        return;
    }

    int row = m_orderTable->currentRow();
    int orderId = m_orderTable->item(row, 0)->text().toInt();

    // 获取订单信息
    Order* order = m_ticketSystem.getOrderById(orderId);
    if (!order) {
        QMessageBox::warning(this, "错误", "未找到订单信息");
        return;
    }

    // 创建改签对话框
    ChangeOrderDialog changeDialog(m_ticketSystem, orderId, this);
    if (changeDialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "成功", "订单改签成功");
        refreshOrderData();
    }
}