#include "AboutDlg.h"
#include "ui_QAboutDlg.h"
#include "qlabelclick.h"
// #include <cstring>


QAboutDlg::QAboutDlg(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::QAboutDlg)
{
	ui->setupUi(this);

	// Signals and Slots
    connect(ui->IDOK, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->IDC_OPEN_CONTRIBUTORS, SIGNAL(clicked()), this, SLOT(OnBnClickedOpenContributors()));
	connect(ui->IDC_WWW, SIGNAL(clicked()), this, SLOT(OnClickedWWW()));

    // Set Default Content
    ui->IDC_ABOUTBOX_ICON->setPixmap(QPixmap(QString::fromUtf8(":/res/splash.jpg")));
    ui->IDC_STATIC->setText(m_info.developers);

    QFont font =  ui->IDC_STATIC->font();
    font.setPointSize(10);
    font.setFamily("Tahoma");

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
	#ifdef __linux__
		system(("xdg-open ./../../AUTHORS" ));
	#else
		ShellExecute(nullptr, _T("open"), m_info.website, nullptr, nullptr, SW_SHOWNORMAL );
		//ShellExecute(nullptr, _T("open"), pNMLink->item.szUrl, nullptr, nullptr, SW_SHOWNORMAL);
	#endif
}

void QAboutDlg::OnClickedWWW()
{
	#ifdef __linux__
		system(("xdg-open http://" + m_info.website.toStdString()).c_str());
	#else
		ShellExecute(nullptr, _T("open"), m_info.website, nullptr, nullptr, SW_SHOWNORMAL );
	//ShellExecute(nullptr, _T("open"), pNMLink->item.szUrl, nullptr, nullptr, SW_SHOWNORMAL);
	#endif
}
