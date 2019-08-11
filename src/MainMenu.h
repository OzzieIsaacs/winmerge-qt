#ifndef MAINMENU_H
#define MAINMENU_H
#include <QMenuBar>
namespace Ui {
class QMainMenu;
}
class QMainMenu : public QMenuBar
{
	Q_OBJECT

public:
	explicit QMainMenu(QWidget *parent = nullptr);
	~QMainMenu();
private slots:

private:
	Ui::QMainMenu *ui;
	// QWidget *m_parent;
};
#endif // MAINMENU_H
