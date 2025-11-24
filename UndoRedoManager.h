#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include <QStack>
#include "DatabaseManager.h"
#include "Order.h"

// 抽象基类：可撤销操作
class UndoableAction {
public:
    virtual ~UndoableAction() = default;
    virtual void undo(DatabaseManager& db) = 0; // 撤销操作
    virtual void redo(DatabaseManager& db) = 0; // 重做操作
};

// 添加订单操作
class AddOrderAction : public UndoableAction {
private:
    Order order; // 被添加的订单
public:
    explicit AddOrderAction(const Order& order) : order(order) {}
    void undo(DatabaseManager& db) override;
    void redo(DatabaseManager& db) override;
};

// 修改订单操作
class ModifyOrderAction : public UndoableAction {
private:
    Order oldOrder; // 修改前的订单
    Order newOrder; // 修改后的订单
public:
    ModifyOrderAction(const Order& old, const Order& newOrd)
        : oldOrder(old), newOrder(newOrd) {
    }
    void undo(DatabaseManager& db) override;
    void redo(DatabaseManager& db) override;
};

class UndoRedoManager {
private:
    QStack<UndoableAction*> undoStack; // 撤销栈
    QStack<UndoableAction*> redoStack; // 重做栈
    DatabaseManager& dbManager; // 数据库管理器引用
public:
    explicit UndoRedoManager(DatabaseManager& db) : dbManager(db) {}
    ~UndoRedoManager();

    // 添加新操作（清空重做栈）
    void addAction(UndoableAction* action);

    // 执行撤销
    bool undo();

    // 执行重做
    bool redo();

    // 清空操作栈
    void clear();
};

#endif // UNDOREDOMANAGER_H