#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
class Widget;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_takePicButton_clicked();

    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::Widget *ui;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mScanningMenu;
    QAction *mScanInAction;
    QAction *mScanOutAction;
};

#endif // WIDGET_H
