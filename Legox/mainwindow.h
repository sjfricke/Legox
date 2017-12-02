#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "core/Legox.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile();

private slots:

private:
    void createMenu();
    void setupStatusBar();

    Ui::MainWindow *mp_ui;

    QMenuBar *mp_menuBar;
    QString m_qFilePath;
    QMenu *mp_fileMenu;
    QMenu *mp_editMenu;
    QMenu *mp_viewMenu;
    QMenu *mp_helpMenu;
    QAction *mp_exitAction;
    QAction *mp_newAction;
    QAction *mp_openAction;
    QAction *mp_saveAction;
    QAction *mp_saveAsAction;
    QAction *mp_zoomAction;
    QAction *mp_undoAction;
    QAction *mp_aboutAction;
    QFileDialog *mp_fileChooser;

    Legox m_legox;
};

#endif // MAINWINDOW_H
