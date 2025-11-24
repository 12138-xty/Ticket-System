#include "UndoRedoManager.h"

using namespace std;

// AddOrderAction 实现
void AddOrderAction::undo(DatabaseManager& db) {
    // 从数据库中移除订单
    auto& orders = const_cast<std::vector<Order>&>(db.getOrders());
    auto it = std::find_if(orders.begin(), orders.end(),
        [this](const Order& o) { return o.getOrderId() == order.getOrderId(); });
    if (it != orders.end()) {
        orders.erase(it);
    }
    db.saveOrders(); // 保存修改
}

void AddOrderAction::redo(DatabaseManager& db) {
    // 重新添加订单
    db.addOrder(order);
    db.saveOrders(); // 保存修改
}

// ModifyOrderAction 实现
void ModifyOrderAction::undo(DatabaseManager& db) {
    // 恢复为旧订单
    auto& orders = const_cast<std::vector<Order>&>(db.getOrders());
    auto it = std::find_if(orders.begin(), orders.end(),
        [this](const Order& o) { return o.getOrderId() == oldOrder.getOrderId(); });
    if (it != orders.end()) {
        *it = oldOrder;
    }
    db.saveOrders();
}

void ModifyOrderAction::redo(DatabaseManager& db) {
    // 应用新订单
    auto& orders = const_cast<std::vector<Order>&>(db.getOrders());
    auto it = std::find_if(orders.begin(), orders.end(),
        [this](const Order& o) { return o.getOrderId() == newOrder.getOrderId(); });
    if (it != orders.end()) {
        *it = newOrder;
    }
    db.saveOrders();
}

// UndoRedoManager 实现
UndoRedoManager::~UndoRedoManager() {
    clear(); // 释放所有操作对象
}

void UndoRedoManager::addAction(UndoableAction* action) {
    if (action) {
        undoStack.push(action);
        // 清空重做栈（新操作后无法重做之前的操作）
        qDeleteAll(redoStack);
        redoStack.clear();
    }
}

bool UndoRedoManager::undo() {
    if (undoStack.isEmpty()) return false;
    UndoableAction* action = undoStack.pop();
    action->undo(dbManager); // 执行撤销
    redoStack.push(action); // 移至重做栈
    return true;
}

bool UndoRedoManager::redo() {
    if (redoStack.isEmpty()) return false;
    UndoableAction* action = redoStack.pop();
    action->redo(dbManager); // 执行重做
    undoStack.push(action); // 移至撤销栈
    return true;
}

void UndoRedoManager::clear() {
    qDeleteAll(undoStack);
    qDeleteAll(redoStack);
    undoStack.clear();
    redoStack.clear();
}