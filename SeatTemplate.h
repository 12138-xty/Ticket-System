#pragma once

#include <QDialog>
#include "ui_SeatTemplate.h"

class SeatTemplate : public QDialog
{
	Q_OBJECT

public:
	SeatTemplate(QWidget *parent = nullptr);
	~SeatTemplate();

private:
	Ui::SeatTemplateClass ui;
};

