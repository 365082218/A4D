#pragma once
#include "E:\Qt\Qt5.6.3\5.6.3\msvc2015_64\include\QtWidgets\qwidget.h"
class AWidget :
	public QWidget
{
public:
	AWidget(QWidget * parent = NULL);
	QPaintEngine * paintEngine() const;
	void paintEvent(QPaintEvent *event);
	bool event(QEvent *);
};

