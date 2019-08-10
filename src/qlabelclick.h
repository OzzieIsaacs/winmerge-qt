#ifndef qlabelclick_H
#define qlabelclick_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class qlabelclick : public QLabel {
Q_OBJECT

public:
	explicit qlabelclick(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	virtual ~qlabelclick();

signals:
	void clicked();

protected:
	void mousePressEvent(QMouseEvent* event);

};

#endif // qlabelclick_H
