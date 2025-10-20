#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_subtitle_surface {this}
    , m_drag_position{}
    , m_default_geometry{}
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
    setWindowOpacity(0.5);

    m_default_geometry = calculateDefaultGeometry();
    setFixedSize(m_default_geometry.width(), m_default_geometry.height());

    m_subtitle_surface.setReadOnly(true);
    m_subtitle_surface.setFocusPolicy(Qt::NoFocus);
    //m_subtitle_surface.setFrameShape(QFrame::NoFrame);
    m_subtitle_surface.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_subtitle_surface.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_subtitle_surface.setGeometry(0, 0, width(), height());
    m_subtitle_surface.setFont(calculateDefaultFont());
    m_subtitle_surface.setAlignment(Qt::AlignCenter);
    //m_subtitle_surface.setAttribute(Qt::WA_TranslucentBackground);
    m_subtitle_surface.insertPlainText("setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);");


    //ui->centralwidget->setLayout(ui->verticalLayout);
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
    m_subtitle_surface.setGeometry(0, 0, width(), height());
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
