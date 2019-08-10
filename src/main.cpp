#include <QApplication>
#include "MainFrm.h"

// Tests
#include <QDebug>
#include <omp.h>
void testCompilerConfig()
{
    // C++14 Test
    auto testCpp14 = [](auto id) {
        auto binary = 0b1001;
        qDebug() << "Thread" << id << "Binary value" << binary;
        return binary;
    };

    // OpenMp Test
    #pragma omp parallel
    {
        int th_id = omp_get_thread_num();
        testCpp14(th_id);
    }
}

int main(int argc, char *argv[])
{
    testCompilerConfig();

    QApplication app(argc, argv);
    app.setOrganizationName("Thingamahoochie");
    app.setOrganizationDomain("Thingamahoochie");
    app.setApplicationName("WinmergeQt");

    MainWindow window;
    window.show();
    return app.exec();
}
