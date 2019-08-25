#include "AboutDlg.h"
#include "ui_QAboutDlg.h"
#include "qlabelclick.h"
#include <QPalette>
#include <QPushButton>
#include "Constants.h"
#include <QFile>
#include <QDir>

#ifdef Q_OS_WIN
#include <windows.h>
#include <ShellApi.h>
#endif

QAboutDlg::QAboutDlg(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::QAboutDlg)
{
	ui->setupUi(this);

	// Remove Title bar
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

	// Set background to white
	QPalette pal;
	pal.setColor(QPalette::Background, Qt::white);
	this->setPalette(pal);

	// Signals and Slots
    connect(ui->IDC_OK, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->IDC_OPEN_CONTRIBUTORS, SIGNAL(clicked()), this, SLOT(OnBnClickedOpenContributors()));
	connect(ui->IDC_WWW, SIGNAL(clicked()), this, SLOT(OnClickedWWW()));

    // Set Default Content
    ui->IDC_ABOUTBOX_ICON->setPixmap(QPixmap(QString::fromUtf8(":/res/splash.jpg")));
    ui->IDC_STATIC->setText(m_info.developers);

    QFont font =  ui->IDC_STATIC->font();
    font.setPointSize(10);
    font.setFamily("Tahoma");

    // Set values
    ui->IDC_STATIC->setFont(font);
    ui->IDC_VERSION->setFont(font);
	ui->IDC_VERSION->setText(m_info.version);
	ui->IDC_COMPANY->setText(m_info.copyright);

    QString link = ui->IDC_WWW->text();
    ui->IDC_WWW->setText("<a href=\"" + m_info.website + "\">" + link + "</a>");

}
QAboutDlg::~QAboutDlg()
{
	delete ui;
}
void QAboutDlg::onClickedOk()
{
    this->close();
}

void QAboutDlg::OnBnClickedOpenContributors()
{
	#ifdef Q_OS_LINUX
		QFile spath(QCoreApplication::applicationDirPath() + QDir::separator() + ContributorsPath);
		system(("xdg-open " + spath.fileName().toStdString()).c_str());
	#else
		ShellExecute(nullptr, ("open"), m_info.website.toStdString().c_str(), nullptr, nullptr, SW_SHOWNORMAL );
		//ShellExecute(nullptr, _T("open"), pNMLink->item.szUrl, nullptr, nullptr, SW_SHOWNORMAL);
	#endif
}

void QAboutDlg::OnClickedWWW()
{
	#ifdef Q_OS_LINUX
		system(("xdg-open " + m_info.website.toStdString()).c_str());
	#else
		ShellExecute(nullptr, ("open"), m_info.website.toStdString().c_str(), nullptr, nullptr, SW_SHOWNORMAL );
	#endif
}
