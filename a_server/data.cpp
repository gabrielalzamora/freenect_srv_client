#include "data.h"

Data::Data(QWidget *parent) : QWidget(parent)
{
    QGroupBox *gbDepth = new QGroupBox(tr("depth"));//------DEPTH group----
        QLabel *DepthLabelrefresco = new QLabel(tr("refresco"),gbDepth);
        QSlider *DepthSlider = new QSlider(Qt::Horizontal,gbDepth);
        DepthSlider->setTickPosition(QSlider::TicksBelow);
        DepthSlider->setMinimum(0);
        DepthSlider->setMaximum(2000);
        DepthSlider->setSingleStep(200);
        DepthSlider->setValue(1000);
        QLabel *DepthLabelSlider = new QLabel(gbDepth);
        DepthLabelSlider->setFixedWidth(40);
        QString strD;
        DepthLabelSlider->setText(strD.setNum(DepthSlider->sliderPosition()));
        QHBoxLayout *LyDepth1 = new QHBoxLayout;
        LyDepth1->addWidget(DepthLabelrefresco);
        LyDepth1->addWidget(DepthSlider);
        LyDepth1->addWidget(DepthLabelSlider);
        QCheckBox *DepthCBenvio = new QCheckBox("envío",gbDepth);
        DepthCBenvio->setChecked(true);
        QCheckBox *DepthCBcomprimido = new QCheckBox("comprimido",gbDepth);
        DepthCBcomprimido->setChecked(false);
        QHBoxLayout *LyDepth2 = new QHBoxLayout;
        LyDepth2->addWidget(DepthCBenvio);
        LyDepth2->addWidget(DepthCBcomprimido);
        QVBoxLayout *LyDepth = new QVBoxLayout;//depth group layout
        LyDepth->addLayout(LyDepth1);
        LyDepth->addLayout(LyDepth2);
        LyDepth->addStretch(2);
    gbDepth->setLayout(LyDepth);//setting depth group layout //-DEPTH group----

    QGroupBox *gbVideo = new QGroupBox(tr("video"));//------VIDEO group----
        QLabel *VideoLabelrefresco = new QLabel(tr("refresco"));
        QSlider *VideoSlider = new QSlider(Qt::Horizontal);
        VideoSlider->setTickPosition(QSlider::TicksBelow);
        VideoSlider->setMinimum(0);
        VideoSlider->setMaximum(2000);
        VideoSlider->setSingleStep(200);
        VideoSlider->setValue(1000);
        QLabel *VideoLabelSlider = new QLabel;
        VideoLabelSlider->setFixedWidth(40);
        QString strV;
        VideoLabelSlider->setText(strV.setNum(VideoSlider->sliderPosition()));
        QHBoxLayout *LyVideo1 = new QHBoxLayout;
        LyVideo1->addWidget(VideoLabelrefresco);
        LyVideo1->addWidget(VideoSlider);
        LyVideo1->addWidget(VideoLabelSlider);
        QCheckBox *VideoCBenvio = new QCheckBox("envío");
        VideoCBenvio->setChecked(true);
        QCheckBox *VideoCBcomprimido = new QCheckBox("comprimido");
        VideoCBcomprimido->setChecked(false);
        QHBoxLayout *LyVideo2 = new QHBoxLayout;
        LyVideo2->addWidget(VideoCBenvio);
        LyVideo2->addWidget(VideoCBcomprimido);
        QVBoxLayout *LyVideo = new QVBoxLayout;//video group layout
        LyVideo->addLayout(LyVideo1);
        LyVideo->addLayout(LyVideo2);
        LyVideo->addStretch(2);
    gbVideo->setLayout(LyVideo);//setting video group layout //-VIDEO group----

    QGroupBox *gbLimits = new QGroupBox(tr("limits"));//------LIMITS group----
        QLabel *LimitsLabelAltura = new QLabel(tr("altura"));
        QLineEdit *LimitsLineEAltura = new QLineEdit();
        LimitsLineEAltura->setText("0.56");
        QHBoxLayout *LyAltura = new QHBoxLayout;
        LyAltura->addWidget(LimitsLabelAltura);
        LyAltura->addWidget(LimitsLineEAltura);

        QLabel *LimitsLabelAngulo = new QLabel(tr("angulo"));
        QLineEdit *LimitsLineEAngulo = new QLineEdit();
        LimitsLineEAngulo->setText("0.0");
        QHBoxLayout *LyAngulo = new QHBoxLayout;
        LyAngulo->addWidget(LimitsLabelAngulo);
        LyAngulo->addWidget(LimitsLineEAngulo);

        QLabel *LimitsLabelAngK = new QLabel(tr("ang Kinect"));
        QLineEdit *LimitsLineEAngK = new QLineEdit();
        LimitsLineEAngK->setText("0");
        QHBoxLayout *LyAngK = new QHBoxLayout;
        LyAngK->addWidget(LimitsLabelAngK);
        LyAngK->addWidget(LimitsLineEAngK);

        QVBoxLayout *LyColumn1 = new QVBoxLayout;
        LyColumn1->addLayout(LyAltura);
        LyColumn1->addLayout(LyAngulo);
        LyColumn1->addLayout(LyAngK);

        QLabel *LimitsLabelYmin = new QLabel(tr("Y min"));
        QLineEdit *LimitsLineEYmin = new QLineEdit();
        LimitsLineEYmin->setText("0.0");
        QHBoxLayout *LyYmin = new QHBoxLayout;
        LyYmin->addWidget(LimitsLabelYmin);
        LyYmin->addWidget(LimitsLineEYmin);

        QLabel *LimitsLabelYmax = new QLabel(tr("Y max"));
        QLineEdit *LimitsLineEYmax = new QLineEdit();
        LimitsLineEYmax->setText("2000.0");
        QHBoxLayout *LyYmax = new QHBoxLayout;
        LyYmax->addWidget(LimitsLabelYmax);
        LyYmax->addWidget(LimitsLineEYmax);

        QLabel *LimitsLabelZmax = new QLabel(tr("Z max"));
        QLineEdit *LimitsLineEZmax = new QLineEdit();
        LimitsLineEZmax->setText("7000.0");
        QHBoxLayout *LyZmax = new QHBoxLayout;
        LyZmax->addWidget(LimitsLabelZmax);
        LyZmax->addWidget(LimitsLineEZmax);

        QVBoxLayout *LyColumn2 = new QVBoxLayout;
        LyColumn2->addLayout(LyYmin);
        LyColumn2->addLayout(LyYmax);
        LyColumn2->addLayout(LyZmax);

        QHBoxLayout *LyLimits = new QHBoxLayout;//limits group lyout
        LyLimits->addLayout(LyColumn1);
        LyLimits->addLayout(LyColumn2);
        LyLimits->addStretch(2);
    gbLimits->setLayout(LyLimits);//setting limits group lyout //-LIMITS group----

    QGroupBox *gbPoints = new QGroupBox(tr("points 3D"));//-------POINTS group----
        QLabel *PointsLabelrefresco = new QLabel(tr("refresco"));
        QSlider *PointsSlider = new QSlider(Qt::Horizontal);
        PointsSlider->setTickPosition(QSlider::TicksBelow);
        PointsSlider->setMinimum(0);
        PointsSlider->setMaximum(2000);
        PointsSlider->setSingleStep(200);
        PointsSlider->setValue(1000);
        QLabel *PointsLabelSlider = new QLabel;
        PointsLabelSlider->setFixedWidth(40);
        QString strP;
        PointsLabelSlider->setText(strP.setNum(PointsSlider->sliderPosition()));
        QHBoxLayout *LyPoints1 = new QHBoxLayout;
        LyPoints1->addWidget(PointsLabelrefresco);
        LyPoints1->addWidget(PointsSlider);
        LyPoints1->addWidget(PointsLabelSlider);

        QLabel *PointsLabelM = new QLabel(tr("modulo"));
        QSlider *PointsSliderM = new QSlider(Qt::Horizontal);
        PointsSliderM->setTickPosition(QSlider::TicksBelow);
        PointsSliderM->setMinimum(0);
        PointsSliderM->setMaximum(10);
        PointsSliderM->setSingleStep(1);
        PointsSliderM->setValue(1);
        QLabel *PointsLabelSliderM = new QLabel;
        PointsLabelSliderM->setFixedWidth(40);
        QString strPM;
        PointsLabelSliderM->setText(strPM.setNum(PointsSliderM->sliderPosition()));
        QHBoxLayout *LyPoints2 = new QHBoxLayout;
        LyPoints2->addWidget(PointsLabelM);
        LyPoints2->addWidget(PointsSliderM);
        LyPoints2->addWidget(PointsLabelSliderM);

        QCheckBox *PointsCBenvio3D = new QCheckBox("envío 3D");
        PointsCBenvio3D->setChecked(false);
        QCheckBox *PointsCBenvio2 = new QCheckBox("envío 2D");
        PointsCBenvio2->setChecked(false);
        QCheckBox *PointsCBenvioB= new QCheckBox("envío Barrido");
        PointsCBenvioB->setChecked(true);
        QCheckBox *PointsCBcomprimido = new QCheckBox("comprimido");
        PointsCBcomprimido->setChecked(false);
        QVBoxLayout *LyPoints3 = new QVBoxLayout;
        LyPoints3->addWidget(PointsCBenvio3D);
        LyPoints3->addWidget(PointsCBenvio2);
        LyPoints3->addWidget(PointsCBenvioB);
        LyPoints3->addWidget(PointsCBcomprimido);

        QLabel *PointsLabelYmin = new QLabel(tr("Y min"));
        QLineEdit *PointsLineEYmin = new QLineEdit();
        PointsLineEYmin->setText("0");
        QHBoxLayout *LyPointsYmin = new QHBoxLayout;
        LyPointsYmin->addWidget(PointsLabelYmin);
        LyPointsYmin->addWidget(PointsLineEYmin);
        QLabel *PointsLabelYmax = new QLabel(tr("Y max"));
        QLineEdit *PointsLineEYmax = new QLineEdit();
        PointsLineEYmax->setText("2000");
        QHBoxLayout *LyPointsYmax = new QHBoxLayout;
        LyPointsYmax->addWidget(PointsLabelYmax);
        LyPointsYmax->addWidget(PointsLineEYmax);
        QLabel *PointsLabelEcu = new QLabel(tr("Ecu"));
        QLineEdit *PointsLineEEcu = new QLineEdit();
        PointsLineEEcu->setText("7000");
        QHBoxLayout *LyPointsEcu = new QHBoxLayout;
        LyPointsEcu->addWidget(PointsLabelEcu);
        LyPointsEcu->addWidget(PointsLineEEcu);
        QVBoxLayout *LyPoints4 = new QVBoxLayout;
        LyPoints4->addLayout(LyPointsYmin);
        LyPoints4->addLayout(LyPointsYmax);
        LyPoints4->addLayout(LyPointsEcu);

        QHBoxLayout *LyPoints5 = new QHBoxLayout;
        LyPoints5->addLayout(LyPoints3);
        LyPoints5->addLayout(LyPoints4);

        QVBoxLayout *LyPoints = new QVBoxLayout;//points group lyout
        LyPoints->addLayout(LyPoints1);
        LyPoints->addLayout(LyPoints2);
        LyPoints->addLayout(LyPoints5);
        LyPoints->addStretch(2);
    gbPoints->setLayout(LyPoints);//setting points group layout //-POINTS group----



    QHBoxLayout *LyTab1 = new QHBoxLayout;
    LyTab1->addStretch();
    LyTab1->addWidget(gbDepth);
    LyTab1->addStretch();
    LyTab1->addWidget(gbVideo);
    LyTab1->addStretch();

    QHBoxLayout *LyTab2 = new QHBoxLayout;//lower tab lyout limits+points
    LyTab2->addWidget(gbLimits);
    LyTab2->addStretch();
    LyTab2->addWidget(gbPoints);//---------LOWER TAB lyout

    QVBoxLayout *LyTab = new QVBoxLayout;
        LyTab->addStretch();
        LyTab->addLayout(LyTab1);
        LyTab->addStretch();
        LyTab->addLayout(LyTab2);
        LyTab->addStretch();

    setLayout(LyTab);//------------END TAB LAYOUT-----------

    connect(DepthSlider,SIGNAL(sliderMoved(int)),DepthLabelSlider,SLOT(setNum(int)));
    connect(VideoSlider,SIGNAL(sliderMoved(int)),VideoLabelSlider,SLOT(setNum(int)));
    connect(PointsSlider,SIGNAL(sliderMoved(int)),PointsLabelSlider,SLOT(setNum(int)));
    connect(PointsSliderM,SIGNAL(sliderMoved(int)),PointsLabelSliderM,SLOT(setNum(int)));
}

void Data::setTabWidgets()
{

}
