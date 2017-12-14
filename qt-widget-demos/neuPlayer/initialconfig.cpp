#include "initialconfig.h"
#include "ui_initialconfig.h"
#include <QDebug>

InitialConfig::InitialConfig(QWidget *parent) :
    QDialog(parent), a_page(1), a_willRestart(false),
    a_canClose(false), ui(new Ui::InitialConfig), a_settings ("neuPlayer.ini", QSettings::IniFormat, this)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setupWidgetsInitialVisibility();

    setupConnections();

    entranceAnimations(); //It's time for an appearance ~
}

void InitialConfig::setupWidgetsInitialVisibility()
{
    ui->a_nextBtn->setVisible(false);
    ui->a_finishButton->setVisible(false);
    ui->a_libraryAtStartupCheck->setVisible(false);
    ui->a_playlistAtStartupCheck->setVisible(false);
    ui->a_label->setVisible(false);
    ui->a_opacitySlide->setVisible(false);
    ui->a_opacityLabel->setVisible(false);
    ui->a_libraryAtStartupCheck_2->setVisible(false);
}

void InitialConfig::setupConnections()
{
    connect(ui->a_recommendedBtn, SIGNAL(clicked()), this, SLOT(presetWizard()));
    connect(ui->a_configureBtn, SIGNAL(clicked()), this, SLOT(customWizard()));
    connect(ui->a_nextBtn, SIGNAL(clicked()), this, SLOT(advanceWizard()));
    connect(ui->a_finishButton, SIGNAL(clicked()), this, SLOT(finishWizard()));
}

void InitialConfig::entranceAnimations()
{
    QPointer<MoveAnimation> welcomeMove = new MoveAnimation(ui->a_welcome, MoveAnimation::TopToBottom, MoveAnimation::Normal, this);
    QPointer<MoveAnimation> button1move = new MoveAnimation(ui->a_recommendedBtn, MoveAnimation::TopToBottom, MoveAnimation::Normal, this);
    QPointer<MoveAnimation> button2move = new MoveAnimation(ui->a_configureBtn, MoveAnimation::TopToBottom, MoveAnimation::Normal, this);
    QPointer<MoveAnimation> descriptionMove = new MoveAnimation(ui->a_description, MoveAnimation::TopToBottom, MoveAnimation::Normal, this);
    /* By default this class will make make the target fade in for 300 ms and add it to a parallel animation group */
    a_animManager.setDefaultDuration(400); //The animation will be more visible that way
    a_animManager.addTarget(ui->a_welcome);
    a_animManager.addTarget(ui->a_description);
    a_animManager.addTarget(ui->a_recommendedBtn);
    a_animManager.addTarget(ui->a_configureBtn);
    a_animManager.startGroup(FadeManager::Parallel, false);
    welcomeMove->start();
    descriptionMove->start();
    button1move->start();
    button2move->start();
}

void InitialConfig::customWizard()
{
    ui->a_configureBtn->setVisible(false);
    ui->a_recommendedBtn->setVisible(false);
    //On peut maintenant atteindre la prochaine page
    a_page++;
    advanceWizard();
}

//View that's displayed when selecting the recommended option
void InitialConfig::presetWizard()
{
    this->setCursor(Qt::BusyCursor);
    ui->a_configureBtn->setVisible(false);
    ui->a_recommendedBtn->setText(tr("Chargement..."));
    a_willRestart = true;
    presetConfig();
    ui->a_recommendedBtn->setVisible(false);
    finalPage();
}

//Do the work of configuring the player's data when choosing recommended option
void InitialConfig::presetConfig()
{
    a_settings.beginGroup("Additional_Features");
    a_settings.setValue("libraryAtStartup", true);
    a_settings.setValue("refreshWhenNeeded", true);
    a_settings.setValue("saveTrackIndex", true);
    a_settings.setValue("framelessWindow", true);
    a_settings.endGroup();
    a_settings.setValue("playlistAtStartup", false);
    a_settings.setValue("opacity", 1.0);
    a_settings.setValue("volume", 50);
    a_settings.setValue("mediapath", QStandardPaths::standardLocations(QStandardPaths::MusicLocation));
    QFileInfo info (a_settings.value("mediapath").toString());
    a_settings.setValue("libModified", info.lastModified().toMSecsSinceEpoch());
    neuPlayer = new Player(); //The player will update itself, and write that the config has been done after that
    neuPlayer->hide(); //The update will force-show, but I don't want to show the player to the user yet ;)
}

//Slot that handles the next button action. The master method of the next button
void InitialConfig::advanceWizard()
{
    /* Structure :
     * config with given parameters from previous page
     * visibility
     * others (effects, anims, connections...)
     * */
    if(a_page == 2)
    {
        ui->a_description->setText(tr("Playlist"));
        ui->a_playlistAtStartupCheck->setVisible(true);
        ui->a_nextBtn->setVisible(true);

        a_animManager.setDefaultDuration(300);
        a_animManager.clearGroup(FadeManager::Parallel);
        a_animManager.addTarget(ui->a_description);
        a_animManager.addTarget(ui->a_playlistAtStartupCheck);
        a_animManager.addTarget(ui->a_nextBtn);
        a_animManager.startGroup(FadeManager::Parallel, false);
    }
    if(a_page == 3)
    {
        a_settings.setValue("playlistAtStartup", ui->a_playlistAtStartupCheck->isChecked());
        ui->a_playlistAtStartupCheck->setVisible(false);
        ui->a_description->setText(tr("Opacité"));
        ui->a_label->setText(tr("Laissez à 100% si vous ne souhaitez\npas de transparence"));
        ui->a_label->setVisible(true);
        ui->a_opacityLabel->setVisible(true);
        ui->a_opacitySlide->setVisible(true);
        updateSlideValue(100);

        a_animManager.clearGroup(FadeManager::Parallel);
        a_animManager.addTarget(ui->a_description);
        a_animManager.addTarget(ui->a_label);
        a_animManager.addTarget(ui->a_opacityLabel);
        a_animManager.addTarget(ui->a_opacitySlide);
        a_animManager.startGroup(FadeManager::Parallel, false);

        connect(ui->a_opacitySlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlideValue(int)));
    }

    if(a_page == 4)
    {
        a_settings.setValue("opacity", a_slideValue);
        ui->a_opacityLabel->setVisible(false);
        ui->a_opacitySlide->setVisible(false);
        ui->a_libraryAtStartupCheck->setVisible(true);
        ui->a_libraryAtStartupCheck_2->setVisible(true);
        ui->a_playlistAtStartupCheck->setVisible(false);
        ui->a_label->setVisible(false);
        ui->a_description->setText(tr("Démarrage avec librairie"));

        a_animManager.clearGroup(FadeManager::Parallel);
        a_animManager.addTarget(ui->a_libraryAtStartupCheck);
        a_animManager.addTarget(ui->a_libraryAtStartupCheck_2);
        a_animManager.addTarget(ui->a_description);
        a_animManager.startGroup(FadeManager::Parallel, false);

        connect(ui->a_libraryAtStartupCheck, SIGNAL(clicked(bool)), this, SLOT(setLibrary(bool)));
        connect(ui->a_libraryAtStartupCheck_2, SIGNAL(clicked(bool)), this, SLOT(setDefault(bool)));
    }
    if(a_page == 5)
    {
        this->setCursor(Qt::BusyCursor); //Showing to the user processing is being done
        a_settings.setValue("Additional_Features/libraryAtStartup", ui->a_libraryAtStartupCheck->isChecked());
        a_settings.setValue("Additional_Features/refreshWhenNeeded", ui->a_libraryAtStartupCheck->isChecked());
        a_settings.setValue("saveTrackIndex", true);
        QFileInfo info (a_settings.value("mediapath").toString());
        a_settings.setValue("libModified", info.lastModified().toMSecsSinceEpoch());
        ui->a_libraryAtStartupCheck->setVisible(false);
        ui->a_libraryAtStartupCheck_2->setVisible(false);
        neuPlayer = new Player(); //The player will update itself, and write that the config has been done after that
        neuPlayer->hide(); //The update will force-show, but I don't want to show the player to the user yet ;)
        finalPage();
    }
    a_page++;
}

void InitialConfig::updateSlideValue(int value)
{
    a_slideValue = value /100.0;
    ui->a_opacityLabel->setText(QString::number(value) + "%");
    this->setWindowOpacity(a_slideValue);
}


void InitialConfig::setDefault(bool isActivated)
{
    if(isActivated)
    {
        a_settings.setValue("mediapath", QStandardPaths::standardLocations(QStandardPaths::MusicLocation));
        ui->a_libraryAtStartupCheck->setChecked(true);
    }
}

//Handle les states de la checkbox library
void InitialConfig::setLibrary(bool isActivated)
{
    if(isActivated)
    {
        QString tempPath = QFileDialog::getExistingDirectory(this, tr("Selectionnez votre répertoire de musique"),"", QFileDialog::DontResolveSymlinks);
        if(tempPath.isEmpty())
        {
            ui->a_libraryAtStartupCheck_2->setChecked(true);
            a_settings.setValue("mediapath", QStandardPaths::standardLocations(QStandardPaths::MusicLocation));
            QMessageBox::information(this, tr("Information"), "default folder : " + a_settings.value("mediapath").toString()); //On get depuis le QSettings pour avoir un string normal affichable
        }
        else //Sinon on a de quoi remplir la var
        {
            ui->a_libraryAtStartupCheck_2->setChecked(false);
            a_mediaPath = tempPath;
            a_settings.setValue("mediapath", a_mediaPath);
        }
    }
}

void InitialConfig::finalPage()
{
    a_page = 5;
    ui->a_description->setText(tr("Vous êtes prêt à utiliser le lecteur !"));
    ui->a_welcome->setText(tr("Terminé !"));
    ui->a_label->setVisible(true);
    ui->a_label->setText(tr("Si le lecteur n'affiche pas vos musiques\nconfigurez-le manuellement dans les paramètres"));
    ui->a_finishButton->setVisible(true);
    ui->a_finishButton->setFocus(); //So the user can hit enter and finish right away
    a_animManager.clearGroup(FadeManager::Parallel);
    a_animManager.addTarget(ui->a_welcome);
    a_animManager.addTarget(ui->a_label);
    a_animManager.addTarget(ui->a_description);
    a_animManager.addTarget(ui->a_finishButton);
    a_animManager.startGroup(FadeManager::Parallel); //Will delete the animation. We're done with it !
    this->setCursor(Qt::ArrowCursor);
}

void InitialConfig::finishWizard()
{
    a_page = 10;
    if(a_settings.value("playlistAtStartup").toBool() == true)
        neuPlayer = new Player();
    if(!a_willRestart)
        neuPlayer->show();
    neuPlayer->setIndexOfThePlayer(0, false);
    close(); //Will call closeEvent
}

void InitialConfig::delayedClose()
{
    a_canClose = true;
    close();
}

void InitialConfig::closeEvent(QCloseEvent *event = 0)
{
    if(a_canClose)
    {
        QFile fileHandler(".configdone");
        fileHandler.open(QFile::ReadWrite); //Create it and I'm done
        if(a_page <= 5) //Create it if it hasn't been configured yet
        {
            neuPlayer = new Player();
        }
        if(a_settings.value("Additional_Features/framelessWindow").toBool() == true)
            neuPlayer->restart(); //Didn't find any solution, so we'll go with that. The main will always setup the frameless window nicely

        //else, simply use the object created
        else
            neuPlayer->show();
        event->accept();
    }
    else
    {
        event->ignore();
        QPointer <FadeWindow> fadeOut = new FadeWindow(this, 450, FadeWindow::FadeOut, this);
        fadeOut->start();
        a_timer.start(650);
        connect(&a_timer, SIGNAL(timeout()), this, SLOT(delayedClose()));
    }
}

InitialConfig::~InitialConfig()
{
    delete ui;
}
