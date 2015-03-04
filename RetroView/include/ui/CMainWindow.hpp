/**************************************************************************
**
**************************************************************************/

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui/CGLViewer.hpp"
#include "core/CPakFileModel.hpp"

namespace Ui {
class CMainWindow;
}

class CPakTreeWidget;
class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    virtual ~CMainWindow();

    bool canShow();
signals:
    void closing();
protected:
    bool event(QEvent *event);

private slots:
    void onModeToggled(bool value);
    void onToggled(bool);
    void onViewerInitialized();
    void onExport();
    void onNewPak(CPakTreeWidget* pak);
    void onLoadPak();
    void onTabChanged();
    void updateFPS();
private:
    Ui::CMainWindow *ui;
    QStringList    m_filters;
    QString        m_allSupportedFilter;
    QTimer         m_fpsUpdateTimer;
};

#endif // MAINWINDOW_HPP