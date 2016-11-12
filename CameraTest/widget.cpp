#include "widget.h"
#include "ui_widget.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera, this);
    mLayout = new QVBoxLayout;
    mScanningMenu = new QMenu("Options", this);
    mScanInAction = new QAction("Scan In", this);
    mScanOutAction = new QAction("Scan Out", this);

    mScanningMenu->addActions({ mScanInAction, mScanOutAction});

    ui->scanPushButton->setMenu(mScanningMenu);
    mCamera->setViewfinder(mCameraViewfinder);
    mLayout->addWidget(mCameraViewfinder);
    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);
    connect(mScanInAction, &QAction::triggered, [&]() {
        auto filename = QFileDialog::getSaveFileName(this, "Capture", "/",
                                     "Image (*.jpg *.jpeg)");
        mCameraImageCapture->setCaptureDestination(
                    QCameraImageCapture::CaptureToFile);
        if (filename.isEmpty()) {
            return;
        }
        QImageEncoderSettings imageEncoderSettings;
        imageEncoderSettings.setCodec("image/jpeg");
        imageEncoderSettings.setResolution(1600, 1200);
        mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
        mCamera->setCaptureMode(QCamera::CaptureStillImage);
        mCamera->start();
        mCamera->searchAndLock();
        mCameraImageCapture->capture(filename);
        mCamera->unlock();
    });

    connect(mScanOutAction, &QAction::triggered, [&]() {
        auto filename = QFileDialog::getSaveFileName(this, "Capture", "/",
                                     "Image (*.jpg *.jpeg)");
        mCameraImageCapture->setCaptureDestination(
                    QCameraImageCapture::CaptureToFile);
        if (filename.isEmpty()) {
            return;
        }
        QImageEncoderSettings imageEncoderSettings;
        imageEncoderSettings.setCodec("image/jpeg");
        imageEncoderSettings.setResolution(1600, 1200);
        mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
        mCamera->setCaptureMode(QCamera::CaptureStillImage);
        mCamera->start();
        mCamera->searchAndLock();
        mCameraImageCapture->capture(filename);
        mCamera->unlock();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_takePicButton_clicked()
{
    auto filename = QFileDialog::getSaveFileName(this, "Capture", "/",
                                 "Image (*.jpg *.jpeg)");
    mCameraImageCapture->setCaptureDestination(
                QCameraImageCapture::CaptureToFile);
    if (filename.isEmpty()) {
        return;
    }
    QImageEncoderSettings imageEncoderSettings;
    imageEncoderSettings.setCodec("image/jpeg");
    imageEncoderSettings.setResolution(1600, 1200);
    mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(filename);
    mCamera->unlock();}

void Widget::on_startButton_clicked()
{
    mCamera->start();
}

void Widget::on_stopButton_clicked()
{
    mCamera->stop();
}
