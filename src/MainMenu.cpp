#include "MainMenu.h"
#include "ui_QMainMenu.h"

QMainMenu::QMainMenu(QWidget *parent) :
	QMenuBar(parent),
	ui(new Ui::QMainMenu)
{
	ui->setupUi(this);
	// m_parent = parent;

	connect(ui->ID_APP_ABOUT, SIGNAL(triggered()), parent, SLOT(OnAppAbout()));
	connect(ui->ID_HELP_CONTENTS, SIGNAL(triggered()), parent, SLOT(OnHelp()));
	connect(ui->ID_HELP_GNULICENSE, SIGNAL(triggered()), parent, SLOT(OnHelpGnulicense()));
	connect(ui->ID_HELP_RELEASENOTES, SIGNAL(triggered()), parent, SLOT(OnHelpReleasenotes()));
	connect(ui->ID_HELP_TRANSLATIONS, SIGNAL(triggered()), parent, SLOT(OnHelpTranslations()));
	connect(ui->ID_APP_EXIT, SIGNAL(triggered()), parent, SLOT(close()));
	connect(ui->ID_FILE_OPENPROJECT, SIGNAL(triggered()), parent, SLOT(OnFileOpenProject()));
	connect(ui->ID_OPTIONS, SIGNAL(triggered()), parent, SLOT(OnOptions()));

}
QMainMenu::~QMainMenu()
{
	delete ui;
}


