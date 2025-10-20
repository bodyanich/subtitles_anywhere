#include <QScreen>
#include <QRect>
#include <QDebug>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_expand_timer_button {this}
    , m_expand_menu_button {this}
    , m_subtitle_surface {this}
    , m_drag_position{}
    , m_default_geometry{}
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
    setWindowOpacity(1);

    m_default_geometry = calculateDefaultGeometry();
    //setGeometry(m_default_geometry);
    setFixedSize(m_default_geometry.width(), m_default_geometry.height());

    int default_button_width = m_default_button_width_scaling * width();

    m_subtitle_surface.setReadOnly(true);
    m_subtitle_surface.setFocusPolicy(Qt::NoFocus);
    //m_subtitle_surface.setFrameShape(QFrame::NoFrame);
    m_subtitle_surface.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_subtitle_surface.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_subtitle_surface.setGeometry(0, 0, width() - default_button_width, height());
    m_subtitle_surface.setFont(calculateDefaultFont());
    m_subtitle_surface.setAlignment(Qt::AlignCenter);
    //m_subtitle_surface.setAttribute(Qt::WA_TranslucentBackground);
    m_subtitle_surface.insertPlainText("setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);");

    int button_height = m_default_geometry.height() / 2;
    m_expand_timer_button.setMaximumHeight(button_height);
    m_expand_timer_button.setGeometry(m_subtitle_surface.width(), 0, default_button_width, button_height);
    m_expand_menu_button.setGeometry(m_subtitle_surface.width(),  m_expand_timer_button.height(), default_button_width,  button_height);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QRect MainWindow::calculateDefaultGeometry()
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    int w = screenRect.width();
    int h = screenRect.height();

    int defaultWidth = w * m_default_width_scaling;
    int defaultFont = h * m_default_font_scaling;
    int bottomMargin = h * m_default_bot_margin_scaling;
    int defaultHeight = defaultFont * m_default_height_scaling;
    int defaultX = (w - defaultWidth) / 2;
    int defaultY = h - bottomMargin - defaultHeight;

    qDebug() << "screen width" << screenRect.width();
    qDebug() << "defaultWidth" << defaultWidth;
    qDebug() << "defaultHeight" << defaultHeight;

    return QRect{defaultX, defaultY, defaultWidth, defaultHeight};
}

QFont MainWindow::calculateDefaultFont()
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    int subtitleFont = screenRect.height() * 0.04;

    QFont f("Arial"); // pixel-based scaling
    f.setPixelSize(subtitleFont);

    return f;
}

void MainWindow::moveToDefaultPos()
{
    move(m_default_geometry.x(), m_default_geometry.y());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_subtitle_surface.setGeometry(0, 0, width() - std::max(m_expand_timer_button.width(), m_expand_menu_button.width()), height());

    int default_button_width = m_default_button_width_scaling * width();
    int button_height = m_default_geometry.height() / 2;
    int half_surf_height = m_subtitle_surface.height() / 2;

    m_expand_timer_button.setGeometry(m_subtitle_surface.width(), half_surf_height - button_height, default_button_width, button_height);
    m_expand_menu_button.setGeometry(m_subtitle_surface.width(),  half_surf_height, default_button_width,  button_height);

    QWidget::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_drag_position = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        move(event->globalPosition().toPoint() - m_drag_position);
}
