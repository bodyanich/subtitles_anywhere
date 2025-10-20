#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMouseEvent>

#include "hiding_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void moveToDefaultPos();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QRect calculateDefaultGeometry();
    QFont calculateDefaultFont();

private:
    static constexpr double m_default_width_scaling {0.7};
    static constexpr double m_default_font_scaling {0.04};
    static constexpr double m_default_bot_margin_scaling {0.08};
    static constexpr double m_default_height_scaling {2.2};

    Ui::MainWindow *ui;
    QTextEdit m_subtitle_surface;
    QPoint m_drag_position;
    QRect m_default_geometry;
};
#endif // MAINWINDOW_H
