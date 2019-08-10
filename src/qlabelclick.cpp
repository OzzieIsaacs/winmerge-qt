#include "qlabelclick.h"

qlabelclick::qlabelclick(QWidget* parent, Qt::WindowFlags f)
		: QLabel(parent) {

}

qlabelclick::~qlabelclick() {}

void qlabelclick::mousePressEvent(QMouseEvent* event) {
	emit clicked();
}