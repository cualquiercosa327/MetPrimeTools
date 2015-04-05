#include "ui/CMainWindow.hpp"
#include "core/CTemplateManager.hpp"
#include <QApplication>
#include <QSurfaceFormat>
#include <QMessageBox>
#include <glm/glm.hpp>
#include <CAssetID.hpp>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // initialize settings info so that default QSettings() access works
    a.setWindowIcon(QIcon(":/MPxViewer.png"));
    a.setOrganizationName("MetPrimeTools");
    a.setApplicationName("RetroView");

    CTemplateManager::instance()->initialize("../templates");
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setDepthBufferSize(32);
    fmt.setMajorVersion(3);
    fmt.setMinorVersion(3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    CMainWindow w;
    w.show();

    return a.exec();
}
