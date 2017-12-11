#include "player.h"
#include "ui_player.h"
#include <QDebug>
Player::Player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Player),
    /* Background ressources */
    a_neuDarkBg(":/Ressources/neudarkbg.png"), a_neuLightBg(":/Ressources/neubackgroundwhite.jpg"), a_neuLightCustombg(":/Ressources/neucustombackgroundwhite.jpg"),
    a_neuDarkCustombg(":/Ressources/neucustombackgroundblack.jpg"),
    /* Volume icons ressources */
    a_volumeIcon(":/Ressources/volumebtn.png"), a_volumeDarkIcon(":/Ressources/volumedarkbtn.png"), a_volumeMutedIcon(":/Ressources/volumebtn_onPressed.png"),
    a_volumeMutedDarkIcon(":/Ressources/volumedarkbtn_onPressed.png"), a_volumeLowIcon(":/Ressources/volumebtn2.png"), a_volumeLowDarkIcon(":/Ressources/volumedarkbtn2.png"),
    /* No CSS controls ressources */
    a_previousIcon(":/Ressources/previousbtn.png"), a_previousDarkIcon(":/Ressources/previousdarkbtn.png"),
    a_forwardIcon(":/Ressources/forwardbtn.png"), a_forwardDarkIcon(":/Ressources/forwarddarkbtn.png"),
    /* Actions */
    a_accessSettings(tr("Paramètres"), this), a_alwaysOnTopHandler(tr("Toujours visible"), this), a_advance(this), a_back(this),
    a_doublerate("2.0x", this), a_halfrate("0.5x", this), a_normalrate("1.0x", this), a_playbackrates(this),
    a_openMedia(tr("Ouvrir des fichiers"), this),  a_showPlaylist(tr("Ouvrir la liste de lecture"), this), a_shuffle(tr("Mélanger la playlist"), this), a_tagViewer(tr("Voir les tags"), this), a_volumeDown(this), a_volumeUp(this),
    /* Menus */
    a_playbackMenu (tr("Vitesse de lecture"), this), a_menu (this),
    /* Settings */
    a_settings ("neuPlayer.ini", QSettings::IniFormat, this)
{
    /*!
                                            2015 Horoneru                                   2.0.1 stable 310515 active
      TODO
      à faire : (/ ordre d'importance)
      > Indexing music infos somehow or another
      - Further skinning options ! (Coming later maybe)
      > UPDATE TRANSLATIONS
      - (Optional) plugin manager musiques osu! << gérer par delete des filenames
      */
    ui->setupUi(this);
    QApplication::setApplicationVersion("2.1.0");
    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_AlwaysShowToolTips);

    setupObjects();

    setupMenus();
    // Bool to control playlist state
    a_isPlaylistOpen = false;

    //Same logic
    a_isSettingsOpen = false;

    //Bool to detect a delete. Used to manage a possible problem after a delete
    a_deleteTriggered = false;

    //Bool to do initial shuffle when selecting random play and forwarding
    a_hasToDoInitialShuffle = false;

    //self-explanatory
    a_hasToStartupPlaylist = false;

    //Bool to control whether we have to set the type of label (Scrolling Label or normal)
    a_hasToSetLabelType = false;

    //Bool to indicate to the playlist if the player is playing
    a_isPlaying = false;

    //Bool to indicate that we were using the previous button. It'll launch the animation when receiving meta-data
    a_wasPrevious = false;

    //Bool to recover progress when needed
    a_recoveredProgress = true;

    //Bool to control if we have to animate the window when closing
    a_canClose = true;

    //Bool to avoid the user to go too fast.
    a_canChangeMusic = true;

    //Bool to avoid the user going too fast again when shuffling the playlist
    a_canDoShuffleAgain = true;

    //Bool that is used to know if we're starting up
    a_isStarting = true;

    //Bool to indicate the playlist needs to be refreshed on the disk
    a_hasToSavePlaylistLater = false;

    ui->a_pausebtn->setVisible(false);

    if(a_settings.value("Additional_Features/framelessWindow", false).toBool() == true)
    {
        a_isFrameless = true;
        setFramelessButtonsVisibility(true);
        a_canClose = false;
    }
    else
    {
        a_isFrameless = false;
        setFramelessButtonsVisibility(false);
    }
    a_audioFade = new QPropertyAnimation(neu, "volume", this);
    a_audioFade->setStartValue(0);
    a_audioFade->setDuration(a_settings.value("fadeValue").toInt());
    if(a_settings.value("Additional_Features/audioFade", false).toBool() == true)
        setAudioFade(true);

    setPlaybackRate();

    setupConnections();

    //Paramètres loadés après car les connexions se chargent de traiter les nouvelles données
    setupPlugins();

    setupPlayMode();

    a_volumeSlider->setValue(a_settings.value("volume", 50).toInt());

    a_alwaysOnTopHandler.setChecked(a_settings.value("visibilite", false).toBool());

    if(a_settings.value("playlistAtStartup").toBool() == true)
        a_hasToStartupPlaylist = true; //Will trigger the playlist startup

    setOpacity();

    a_isStarting = false;    //Done !
}

    /*///////Plugins & Setup Section///////*/

void Player::setupObjects()
{
    /*///////Setup Objects and Data///////*/
    resize(a_settings.value("size", QSize(400, 47) ).toSize());
    move(a_settings.value("pos", QPoint(200,200)).toPoint());
    a_playbackState = a_settings.value("playbackrate", 0).toInt();
    a_isRandomMode = a_settings.value("random", false).toBool();
    a_isLoopPlaylistMode = a_settings.value("loop", false).toBool();

    //Media Player
    neu = new QMediaPlayer(this);

    //Prepare custom Sliders
    a_progressSlider = new Slider(ui->centralWidget);
    a_progressSlider->setGeometry(QRect(132, 26, 110, 20));
    a_progressSlider->setOrientation(Qt::Horizontal);
    a_progressSlider->setInvertedAppearance(false);
    a_progressSlider->setInvertedControls(false);
    a_progressSlider->setTickPosition(QSlider::NoTicks);
    a_progressSlider->setTickInterval(10);
    a_progressSlider->setToolTip(tr("Alt + droite ou gauche pour parcourir"));


    a_volumeSlider = new Slider(ui->centralWidget);
    a_volumeSlider->setGeometry(QRect(310, 28, 60, 16));
    a_volumeSlider->setMaximum(99);
    a_volumeSlider->setValue(50);
    a_volumeSlider->setOrientation(Qt::Horizontal);
    a_volumeSlider->setToolTip(tr("Volume (Ctrl haut ou bas) "));

    //Prepare animation
    a_titleAnimate = new QPropertyAnimation(ui->a_label, "pos", this);
    a_titleAnimate->setDuration(200); //Always 200 ms
    a_infoFadein = new QGraphicsOpacityEffect(this);
    a_infoFadein->setOpacity(1.0);
    ui->a_label->setGraphicsEffect(a_infoFadein);
    a_infoFadeAnim = new QPropertyAnimation(a_infoFadein, "opacity", this);

    //Prepare the sliding text object
    QFont font;
    font.setFamily(QStringLiteral("Segoe UI"));
    font.setPointSize(10);
    a_scrollingLabel.setParent(this);
    a_scrollingLabel.setFont(font);
    a_scrollingLabel.setGeometry(QRect(100, 0, 175, 31));
    a_scrollingLabel.setMinimumSize(QSize(170, 30));

    //Raccourcis clavier pour parcourir les éléments du player
    a_advance.setShortcut(Qt::ALT + Qt::Key_Right);
    a_back.setShortcut(Qt::ALT + Qt::Key_Left);
    ui->a_volumebtn->setCheckable(true);
    a_volumeUp.setShortcut(Qt::CTRL + Qt::Key_Up);
    a_volumeDown.setShortcut(Qt::CTRL + Qt::Key_Down);

    this->addAction(&a_advance);
    this->addAction(&a_back);
    this->addAction(&a_volumeUp);
    this->addAction(&a_volumeDown);

    //Elements du menu :
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    a_openMedia.setShortcut(Qt::CTRL + Qt::Key_O);
    a_showPlaylist.setShortcut(Qt::CTRL + Qt::Key_P); //P comme Playlist ?
    a_alwaysOnTopHandler.setCheckable(true);
    a_alwaysOnTopHandler.setShortcut(Qt::CTRL + Qt::Key_V); // V comme visible :3
    a_accessSettings.setShortcut(Qt::CTRL + Qt::Key_Space);
    a_accessSettings.setShortcutContext(Qt::ApplicationShortcut);
    a_shuffle.setShortcut(Qt::CTRL + Qt::Key_R); // R comme random !
    a_tagViewer.setShortcut(Qt::ALT + Qt::Key_Return);

    //Timer enabling the scrolling of the label info
    Timer.setInterval(1000);
    //Timer that delays the check of which label type to use
    setTypeTimer.setSingleShot(true);
    //Timer that delays When the user can change music again (avoid reading null data when going too fast)
    grantChangeTimer.setSingleShot(true);
    //Timer that delays the time when the user can shuffle again
    grantShuffleAgainTimer.setSingleShot(true);

}

void Player::setupMenus()
{

    //Sous-menu playback rate
    a_normalrate.setCheckable(true);
    a_doublerate.setCheckable(true);
    a_halfrate.setCheckable(true);
    a_playbackrates.addAction(&a_doublerate);
    a_playbackrates.addAction(&a_normalrate);
    a_playbackrates.addAction(&a_halfrate);
    a_playbackrates.setExclusive(true);
    a_playbackMenu.addAction(&a_halfrate);
    a_playbackMenu.addAction(&a_normalrate);
    a_playbackMenu.addAction(&a_doublerate);

    //Setup The menu
    a_menu.addAction(&a_showPlaylist);
    a_menu.addAction(&a_openMedia);
    a_menu.addAction(&a_accessSettings);
    a_menu.addMenu(&a_playbackMenu);
    a_menu.addAction(&a_alwaysOnTopHandler);
    a_menu.addAction(&a_shuffle);
    a_menu.addAction(&a_tagViewer);
    this->addAction(&a_openMedia);
    this->addAction(&a_showPlaylist);
    this->addAction(&a_alwaysOnTopHandler);
    this->addAction(&a_shuffle);
    this->addAction(&a_accessSettings);
    this->addAction(&a_tagViewer);

}

void Player::setupPlayMode()
{
    if(a_isRandomMode)
    {

        a_mediaPlaylist.setPlaybackMode(QMediaPlaylist::Random);
        a_favPlaylist.setPlaybackMode(QMediaPlaylist::Random);
        a_hasToDoInitialShuffle = true;
    }
    else
    {
        a_mediaPlaylist.setPlaybackMode(QMediaPlaylist::Sequential);
        a_favPlaylist.setPlaybackMode(QMediaPlaylist::Sequential);
    }
}


void Player::setupConnections()
{
    /*///////Connexions///////*/
    connect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
    connect(neu, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(errorHandling(QMediaPlayer::Error)));
    connect(neu, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
    connect(neu, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(ui->a_forward, SIGNAL(clicked()), this, SLOT(forwardMedia()));
    connect(ui->a_previous, SIGNAL(clicked()), this, SLOT(previousMedia()));
    connect(ui->a_menubtn, SIGNAL(clicked()), this, SLOT(showMenu()));
    connect(&a_advance, SIGNAL(triggered()), this, SLOT(advanceProgress()));
    connect(&a_back, SIGNAL(triggered()), this, SLOT(backProgress()));
    connect(&a_mediaPlaylist, SIGNAL(loaded()), this, SLOT(finishingUp()));
    connect(neu, SIGNAL(durationChanged(qint64)), this, SLOT(on_durationChanged(qint64)));
    connect(neu, SIGNAL(positionChanged(qint64)), this, SLOT(UpdateProgress(qint64)));
    connect(a_progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(seekProgress(int)));
    connect(a_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(on_volumeChanged(int)));
    connect(ui->a_volumebtn, SIGNAL(clicked()), this, SLOT(setVolumeMuted()));
    connect(&a_volumeUp, SIGNAL(triggered()), this, SLOT(volumeUp()));
    connect(&a_volumeDown, SIGNAL(triggered()), this, SLOT(volumeDown()));
    connect(neu, SIGNAL(metaDataChanged()), this, SLOT(setMeta()));
    connect(&Timer, SIGNAL(timeout()), this, SLOT(update_info()));
    connect(&setTypeTimer, SIGNAL(timeout()), this, SLOT(setType()));
    connect(&grantChangeTimer, SIGNAL(timeout()), this, SLOT(canChangeMusicNow()));
    connect(&grantShuffleAgainTimer, SIGNAL(timeout()), this, SLOT(canShuffleNow()));
    connect(this, SIGNAL(EndOfMedia()), this, SLOT(endOfMediaGuard()));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu()));
    connect(&a_openMedia, SIGNAL(triggered()), this, SLOT(openMedia()));
    connect(&a_alwaysOnTopHandler, SIGNAL(toggled(bool)), this, SLOT(windowFlagsHandler()));
    connect(&a_playbackrates, SIGNAL(triggered(QAction*)), this, SLOT(playbackHandler(QAction*)));
    connect(&a_shuffle, SIGNAL(triggered()), this, SLOT(setShuffle()));
    connect(&a_showPlaylist, SIGNAL(triggered()), this, SLOT(showPlaylist()));
    connect(&a_tagViewer, SIGNAL(triggered()), this, SLOT(showTagViewer()));
    connect(&a_accessSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
    connect(&a_mediaPlaylist, SIGNAL(loaded()), this, SLOT(setupNewLibrary()));
    connect(ui->a_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->a_hideButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

#ifdef Q_OS_WIN
    connect(&a_thumbActionButton, SIGNAL(clicked()), this, SLOT(playMedia())); //Base connect
    connect(&a_thumbForwardButton, SIGNAL(clicked()), this, SLOT(forwardMedia()));
    connect(&a_thumbPreviousButton, SIGNAL(clicked()), this, SLOT(previousMedia()));
#endif
}

void Player::setupPlugins()
{
    loadSkin();
    if(a_settings.value("Additional_Features/libraryAtStartup", false).toBool() == true)
    {
        //Modes de chargement de la librairie

        ui->a_label->setText("<No Media>");
        if(a_settings.value("Additional_Features/refreshWhenNeeded", false).toBool() == true)
        {
            QFile fileHandler(".configdone");
            if(!fileHandler.exists())
            {
                updateLibrary();
                if(a_settings.value("playlistAtStartup", false).toBool() == true)
                    deleteLater();
            }
            else
                checkForNewMedias();
        }

        loadPlaylist(); // We will load the library even if it isn't in refreshWhenNeeded
    }
    QFile fileHandler(".configdone");
    fileHandler.open(QFile::ReadWrite); //Create it and I'm done
    fileHandler.close();
}

void Player::loadPlaylist()
{
    if(a_settings.value("usingFavorites", false).toBool() == true) //Are we on the favorites playlist ?
    {
        a_isUsingFavPlaylist = true;
        disconnect(&a_mediaPlaylist, SIGNAL(loaded()), this, SLOT(setupNewLibrary()));
        connect(&a_favPlaylist, SIGNAL(loaded()), this, SLOT(setupNewLibrary()));

    }
    else
        setUsingFav(false);
    a_mediaPlaylist.load(QUrl::fromLocalFile("neuLibrary.m3u8"), "m3u8");  //We load both anyways
    a_favPlaylist.load(QUrl::fromLocalFile("favorites.m3u8"), "m3u8");
}

void Player::setOpacity(qreal opacityFromSettings)
{
    if(opacityFromSettings != 0) //This is used for live preview from settings. Its default value is 0 and it's an optional parameter
    {
        this->setWindowOpacity(opacityFromSettings);
        if(opacityFromSettings != 1.0)
            a_canClose = false; //Handle the fade out anim
        else
            if(!a_isFrameless) //Frameless also isn't handled by the system anymore
                a_canClose = true;
        return;
    }

    if(a_settings.value("opacity", 1.0).toReal() <= 0) //Because I know someone will somehow set a 0 opacity...
    {
        this->setWindowOpacity(1.0);
        return;
    }
    if(a_settings.value("opacity", 1.0).toReal() < 1.0)
    {
        this->setWindowOpacity(a_settings.value("opacity").toReal());
        a_canClose = false; //Handle the fade out anim
    }
}

void Player::setFramelessButtonsVisibility(bool visible)
{
    ui->a_closeButton->setVisible(visible);
    ui->a_hideButton->setVisible(visible);
}

void Player::loadSkin()
{
    a_idSkin = a_settings.value("skin", 1).toInt();
    if(a_idSkin == 1 || a_idSkin == 3) //Dark skin
    {
        if(!a_isStarting)
            setDarkCSS(); //Because the stylesheet is already set as default
        if(a_idSkin == 1)
        {
            if(!QFile(a_settings.value("customimage").toString()).exists()) //We won't charge something which doesn't exists
                ui->a_image->setPixmap(a_neuDarkBg);
            else
                ui->a_image->setPixmap(QPixmap(a_settings.value("customimage").toString()));
        }
        else //Custom bg
        {
            if(!QFile(a_settings.value("customimage").toString()).exists())
                ui->a_image->setPixmap(a_neuDarkCustombg);
            else
                ui->a_image->setPixmap(QPixmap(a_settings.value("customimage").toString()));
        }
    }

    if(a_idSkin == 0 || a_idSkin == 2) //Light skin
    {
        setLightCSS();
        if(a_idSkin == 0)
        {
            if(!QFile(a_settings.value("customimage").toString()).exists())
                ui->a_image->setPixmap(a_neuLightBg);
            else
                ui->a_image->setPixmap(QPixmap(a_settings.value("customimage").toString()));
        }
        else //Custom bg
        {
            if(!QFile(a_settings.value("customimage").toString()).exists())
                ui->a_image->setPixmap(a_neuLightCustombg);
            else
                ui->a_image->setPixmap(QPixmap(a_settings.value("customimage").toString()));
        }
    }
    if(!a_isStarting)
    {
        if(!a_animManager) //If the pointer is null
            a_animManager = new FadeManager(ui->a_image, 1000, this, FadeManager::FadeIn);
        a_animManager->start();
    }
}

void Player::setLightCSS()
{
    ui->a_playbtn->setStyleSheet("QPushButton#a_playbtn{background-image: url(:/Ressources/Playdarkbtn.png);}"
                                 "QPushButton#a_playbtn:hover{background-image: url(:/Ressources/Playdarkbtn_onHover.png);}");
    ui->a_pausebtn->setStyleSheet("QPushButton#a_pausebtn{background-image: url(:/Ressources/Pausedarkbtn.png);}"
                                  "QPushButton#a_pausebtn:hover{background-image: url(:/Ressources/Pausedarkbtn_onHover.png);}");
    ui->a_menubtn->setStyleSheet("QPushButton#a_menubtn{background-image: url(:/Ressources/roundedmenudarkbtn.png);}"
                                 "QPushButton#a_menubtn:hover{background-image: url(:/Ressources/roundedmenudarkbtn_onHover.png);}");

    a_progressSlider->setStyleSheet("Slider::handle:horizontal {image: url(:/Ressources/handledark.png);}");
    a_volumeSlider->setStyleSheet("Slider::handle:horizontal {image: url(:/Ressources/handledark.png);}");
    if(a_isFrameless)
    {
    ui->a_closeButton->setStyleSheet("QPushButton#a_closeButton{background-image: url(:/Ressources/closeButtonDark.png);}"
                                 "QPushButton#a_closeButton:hover{background-image: url(:/Ressources/closeButton_onHover.png);}");
    ui->a_hideButton->setStyleSheet("QPushButton#a_hideButton{background-image: url(:/Ressources/hideButtonDark.png);}"
                                 "QPushButton#a_hideButton:hover{background-image: url(:/Ressources/hideButtonDark_onHover.png);}");
    }

    //Stylize the rest by putting icons...
    ui->a_forward->setIcon(a_forwardDarkIcon);
    ui->a_previous->setIcon(a_previousDarkIcon);
    on_volumeChanged(neu->volume()); //Will reload the correct icon for volume
}

void Player::setDarkCSS()
{
    ui->a_playbtn->setStyleSheet("QPushButton#a_playbtn{background-image: url(:/Ressources/Playbtn.png);}"
                                 "QPushButton#a_playbtn:hover{background-image: url(:/Ressources/Playbtn_onHover.png);}");
    ui->a_pausebtn->setStyleSheet("QPushButton#a_pausebtn{background-image: url(:/Ressources/Pausebtn.png);}"
                                  "QPushButton#a_pausebtn:hover{background-image: url(:/Ressources/Pausebtn_onHover.png);}");
    ui->a_menubtn->setStyleSheet("QPushButton#a_menubtn{background-image: url(:/Ressources/roundedmenubtn.png);}"
                                 "QPushButton#a_menubtn:hover{background-image: url(:/Ressources/roundedmenubtn_onHover.png);}");

    a_progressSlider->setStyleSheet("Slider::handle:horizontal {image: url(:/Ressources/handle.png);}");
    a_volumeSlider->setStyleSheet("Slider::handle:horizontal {image: url(:/Ressources/handle.png);}");

    if(a_isFrameless)
    {
    ui->a_closeButton->setStyleSheet("QPushButton#a_closeButton{background-image: url(:/Ressources/closeButton.png);}"
                                 "QPushButton#a_closeButton:hover{background-image: url(:/Ressources/closeButton_onHover.png);}");
    ui->a_hideButton->setStyleSheet("QPushButton#a_hideButton{background-image: url(:/Ressources/hideButton.png);}"
                                 "QPushButton#a_hideButton:hover{background-image: url(:/Ressources/hideButton_onHover.png);}");
    }
    //Stylize the rest by putting icons...
    ui->a_forward->setIcon(a_forwardIcon);
    ui->a_previous->setIcon(a_previousIcon);
    on_volumeChanged(neu->volume()); //Will reload the correct icon for volume
}

void Player::checkForNewMedias()
{
    QFileInfo currentInfo (a_settings.value("mediapath").toString());
    if(a_settings.value("libModified").toLongLong() < currentInfo.lastModified().toMSecsSinceEpoch())
    {
        int reponse = QMessageBox::information(this, "neuPlayer", tr("Des changements ont été detectés dans votre base depuis la dernière mise à jour de celle-ci.\nVoulez-vous l'actualiser ?"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Ignore);
        if(reponse == QMessageBox::Yes)
        {
            a_settings.setValue("libModified", currentInfo.lastModified().toMSecsSinceEpoch());
            updateLibrary();
        }
        if(reponse == QMessageBox::Ignore)
            //"Don't bug me for this change"
            a_settings.setValue("libModified", currentInfo.lastModified().toMSecsSinceEpoch());
    }
}

void Player::updateLibrary()
{
    ui->a_label->setText(tr("Mise à jour librairie..."));
    a_mediaPlaylist.save();
    if(a_mediaPlaylist.isEmpty())
        ui->a_label->setText(tr("Aucun média trouvé"));
    else
        a_mediaPlaylist.load(QUrl::fromLocalFile("neuLibrary.m3u8"), "m3u8");
}

//Have to delay it
void Player::finishingUp()
{
    if(a_hasToStartupPlaylist)
    {
        a_hasToStartupPlaylist = false; //No more
        showPlaylist();
    }
#ifdef Q_OS_WIN
    //TODO : Create icons, set them, and link buttons to play/pause/forward/previous slots.
    //prepare buttons
//    a_thumbPlayButton.setDismissOnClick(true);
//    a_thumbPauseButton.setDismissOnClick(true);
    a_thumbActionButton.setIcon(QIcon(":/Ressources/play_thumbnailButton.png"));
    a_thumbForwardButton.setIcon(QIcon(":/Ressources/forward_thumbnailButton.png"));
    a_thumbPreviousButton.setIcon(QIcon(":/Ressources/previous_thumbnailButton.png"));

    //Prepare and set buttons on thumbnailtoolbar
    a_thumbnailToolbar.addButton(&a_thumbPreviousButton);
    a_thumbnailToolbar.addButton(&a_thumbActionButton);
    a_thumbnailToolbar.addButton(&a_thumbForwardButton);

    a_thumbnailToolbar.setWindow(this->windowHandle());
#endif
}

void Player::savePlaylists()
{
    if(a_hasToSaveFavsLater)
        a_favPlaylist.saveFromPlaylist("favorites.m3u8");
    if(a_settings.value("Additional_Features/libraryAtStartup").toBool() == true)
    {
        if(a_hasToSavePlaylistLater)
            a_mediaPlaylist.saveFromPlaylist(); //Defaults to normal library
    }
}

void Player::setupNewLibrary()
{
    if(!a_isUsingFavPlaylist)
        neu->setPlaylist(&a_mediaPlaylist); //The a_isUsingFavPlaylist was already updated before in the loadPlaylist() method
    else
        neu->setPlaylist(&a_favPlaylist); // ^^^^^^^^^
    if(a_settings.value("Additional_Features/saveTrackIndex", false).toBool() == true)
    {
        a_recoveredProgress = false;
        neu->playlist()->setCurrentIndex(a_settings.value("currentTrack").toInt());
    }
}

    /*///////MediaPlayer Controls///////*/

void Player::playMedia()
{
    if(a_isStarting)
        return; // Not ready yet !
    /* Those silly disconnect-reconnect are made so the openMedia(); method isn't called multiple times.
     * For whatever reasons if I don't do it, it will be called about 2 to 4 times ! */

    disconnect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
    if ((neu->media().isNull()))
        openMedia();
    else //On peut play quelque chose
    {
        if(a_audioFadeActivated) //If it was instantiated, it means It's activated
            runAudioFade();
        neu->play();
        ui->a_playbtn->setVisible(false);
        ui->a_pausebtn->setVisible(true);

#ifdef Q_OS_WIN
        a_thumbActionButton.setIcon(QIcon(":/Ressources/pause_thumbnailButton.png"));
        connect(&a_thumbActionButton, SIGNAL(clicked()), this, SLOT(pauseMedia()));
#endif

        connect(ui->a_pausebtn, SIGNAL(clicked()), this, SLOT(pauseMedia()));
        if(a_isPlaylistOpen)
        {
            a_playlist->setToPlaying(neu->playlist()->currentIndex());
        }
        return; //We don't want to go to that last line
    }
    connect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
}

void Player::pauseMedia()
{
    neu->pause();
    disconnect(ui->a_pausebtn, SIGNAL(clicked()), this, SLOT(pauseMedia()));
    ui->a_playbtn->setVisible(true);
    ui->a_pausebtn->setVisible(false);

#ifdef Q_OS_WIN
    a_thumbActionButton.setIcon(QIcon(":/Ressources/play_thumbnailButton.png"));
    connect(&a_thumbActionButton, SIGNAL(clicked()), this, SLOT(playMedia()));
#endif

    connect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
    if(a_isPlaylistOpen)
    {
        a_playlist->setToPaused(neu->playlist()->currentIndex());
    }
}

void Player::forwardMedia()
{
    if(!a_canChangeMusic || a_mediaPlaylist.mediaCount() == 0 )
        return;
    neu->playlist()->next();
    if(a_audioFadeActivated) //If it was instantiated, it means It's activated
        runAudioFade();
    if(neu->playlist()->currentMedia().isNull())
    {
        if(a_isLoopPlaylistMode)
        {
            neu->playlist()->setCurrentIndex(0);
            playMedia();
        }
        else
        {
            emit EndOfMedia();
            return;
        }
    }
    if(a_hasToDoInitialShuffle) //For true randomness
    {
        qsrand(QTime::currentTime().msec());
        neu->playlist()->setCurrentIndex(qrand() % neu->playlist()->mediaCount());
        a_hasToDoInitialShuffle = false;
    }
    a_wasPrevious = false;
}

void Player::forwardAnim()
{
    a_titleAnimate->setStartValue(QPoint(130, 0));
    a_titleAnimate->setEndValue(QPoint(110, 0));
    a_titleAnimate->start();
}

void Player::previousMedia()
{
    if(!a_canChangeMusic || a_mediaPlaylist.mediaCount() == 0)
        return;
    neu->playlist()->previous();
    if(a_audioFadeActivated)
        runAudioFade();
    if(neu->playlist()->currentMedia().isNull())
    {
        emit EndOfMedia();
        return;
    }
    if(a_hasToDoInitialShuffle)
    {
        qsrand(QTime::currentTime().msec());
        neu->playlist()->setCurrentIndex(qrand() % neu->playlist()->mediaCount());
        a_hasToDoInitialShuffle = false;
    }
    a_wasPrevious = true;
}


void Player::previousAnim()
{
    a_titleAnimate->setEndValue(QPoint(110, 0));
    a_titleAnimate->start();
}

void Player::errorHandling(QMediaPlayer::Error error)
{
    int current;
    bool stateBefore = a_isPlaying;
    switch (error) {
    case QMediaPlayer::NoError:
        break;
    case QMediaPlayer::ResourceError:
        ui->a_label->setText(tr("erreur : Unresolved Resource"));
        neu->playlist()->previous();
        current = neu->playlist()->currentIndex();
        qDebug() << neu->playlist()->media(current).canonicalUrl();
        neu->playlist()->removeMedia(current);
        if(a_isPlaylistOpen)
            a_playlist->deleteItem(current);
        neu->setPlaylist(neu->playlist()); // I do this to ensure stability, because we're in a panic case
        if(!a_wasPrevious)
            neu->playlist()->setCurrentIndex(current - 2);
        else
            neu->playlist()->setCurrentIndex(current - 1);
        a_isPlaying = stateBefore;
        if(a_isPlaying)
            playMedia();
        if(!a_isUsingFavPlaylist)
            a_hasToSavePlaylistLater = true; //Prevent error from coming back.
        else
            a_hasToSaveFavsLater = true;
        break;
    case QMediaPlayer::FormatError :
        ui->a_label->setText(tr("erreur : Format non supporté"));
        pauseMedia(); // Total panic
        neu->stop();
        neu->playlist()->clear();// so we have to discard the content
        break;
    case QMediaPlayer::NetworkError :
        ui->a_label->setText(tr("erreur : Network error"));
        break;
    case QMediaPlayer::AccessDeniedError :
        QMessageBox::critical(this, tr("Erreur ! "), tr("Vous n'avez pas les droits pour accéder à ce fichier"));
        break;
    case QMediaPlayer::ServiceMissingError :
        QMessageBox::critical(this, tr("Erreur Critique !"), tr("Le service du player est indisponible. Impossible de lire le fichier !"));
        break;
    }
    a_isPlaying = false;
}

void Player::statusChanged(QMediaPlayer::MediaStatus status)
{
    // handle status message and cursor
    switch (status) {
    case QMediaPlayer::LoadingMedia:
        this->setCursor(Qt::BusyCursor);
        break;
    case QMediaPlayer::StalledMedia:
        ui->a_label->setText("Media stalled");
        a_isPlaying = false;
        break;
    case QMediaPlayer::LoadedMedia:
        this->setCursor(Qt::ArrowCursor);
        if(!a_recoveredProgress && a_settings.value("Additional_Features/saveTrackIndex", false).toBool() == true
                || a_deleteTriggered)
        {
            a_deleteTriggered = false; // no more
            seekProgress(a_settings.value("trackPosition").toInt());
            a_recoveredProgress = true;
        }
        break;
    case QMediaPlayer::EndOfMedia:
        forwardMedia();
    }
}

void Player::stateChanged(QMediaPlayer::State state)
{
    //Handle the update of the bool a_isPlaying
    //Permits an up-to-date icon in the playlist and an info on what is the player's playing state
    switch(state)
    {
    case QMediaPlayer::PlayingState:
        a_isPlaying = true;
        break;
    case QMediaPlayer::PausedState:
        a_isPlaying = false;
        break;
    case QMediaPlayer::StoppedState:
        a_isPlaying = false;
        break;
    }
}

void Player::showMenu()
{
    a_menu.exec(QCursor::pos()); //simplest method pls
}

void Player::openMedia()
{
    QList <QUrl> files = QFileDialog::getOpenFileUrls(this, tr("Sélectionnez des médias à lire"), (QStandardPaths::locate(QStandardPaths::MusicLocation, QString(), QStandardPaths::LocateDirectory)) , tr("Flux audios (*.mp3 *.mp4 *.m4a *.wav)"));
    if(files.isEmpty()) //It was a mistake I guess, so don't do anything
        return;
    //Clear before processing
    a_mediaPlaylist.clear();
    unsigned int const fileNumber = files.size();
    for(unsigned int i (0); i < fileNumber; i++ )
    {
        a_mediaPlaylist.addMedia(files.at(i));
    }
    if(!a_mediaPlaylist.isEmpty())
    {
        changeToDefaultPlaylist();
        playMedia();
        if(a_isPlaylistOpen)
        {
            a_mediaPlaylist.setCurrentIndex(0);
            a_playlist->updateList(&a_mediaPlaylist, true);
        }
    }
}

void Player::setMeta()
{
    //New track, we start at 0 secs !
    a_secondesPasse = 0; //For infos
    // On check pour savoir si les metas sont nulles ou avec une chaine vide pour avoir une donnée correcte à afficher
    if(!neu->metaData("Title").isNull() && !neu->metaData("Title").operator ==(""))
        a_titre = neu->metaData("Title").toString();
    else
        a_titre = neu->currentMedia().canonicalUrl().fileName();
    if(!neu->metaData("ContributingArtist").isNull() && !neu->metaData("ContributingArtist").operator ==(""))
        a_artiste = neu->metaData("ContributingArtist").toString();
    else
        a_artiste = tr("Artiste Inconnu");
    if(!neu->metaData("AlbumTitle").isNull() && !neu->metaData("AlbumTitle").operator ==(""))
        a_album = neu->metaData("AlbumTitle").toString();
    else
        a_album = tr("Album Inconnu");

    //Si c'est une vidéo ou un flux sans header
    if( (neu->metaData("Title").isNull())
         && (neu->metaData("ContributingArtist").isNull())
         && (neu->metaData("AlbumTitle").isNull()) )
    {
        a_artiste = neu->currentMedia().canonicalUrl().fileName();
        a_titre = neu->currentMedia().canonicalUrl().fileName();
        a_album = neu->currentMedia().canonicalUrl().fileName();
        a_no_meta = true;
    }
    else
        a_no_meta = false;

    a_coverArt = QPixmap::fromImage(QImage(neu->metaData("ThumbnailImage").value<QImage>()));
    if(a_coverArt.isNull())
        a_coverArt = QPixmap::fromImage(QImage(neu->metaData("CoverArtImage").value<QImage>()));

    if(!ui->a_label->isVisible())
    {
        a_scrollingLabel.hide();
        ui->a_label->setVisible(true);
    }
    a_hasToSetLabelType = true;
    ui->a_label->setText(a_titre);
    ui->a_label->setToolTip(a_titre);
    if(!a_deleteTriggered) //To avoid animation, because the user wouldn't expect it
    {
        if(a_wasPrevious)
            previousAnim();
        else
            forwardAnim();
    }

    a_canChangeMusic = false;
    setTypeTimer.start(300); //Set the type 300 ms later
    grantChangeTimer.start(200);


    a_previousIndex = neu->playlist()->currentIndex();

    if(a_settings.value("Additional_Features/saveTrackIndex", false).toBool() == true)
        a_settings.setValue("currentTrack", a_previousIndex);
    if(a_isPlaylistOpen)
        a_playlist->setCurrentItem(neu->playlist()->currentIndex(), &a_coverArt, a_titre, a_isPlaying);

    updateFadeinSpeed();
    Timer.start();
}

void Player::setType()
{
        updateLabel(a_titre); //Will set the good type
        a_hasToSetLabelType = false; //It's been done !
        finishingUp();
}

//Update and set type of label
void Player::updateLabel(QString &text)
{
    if(text.size() < 25)
    {
        a_isScrollingText = false;
        if(!ui->a_label->isVisible())
            ui->a_label->show();
        if(a_scrollingLabel.isVisible())
            a_scrollingLabel.hide();

        if(!a_hasToSetLabelType) //Doesn't need to set them if that's the case
        {
            ui->a_label->setText(text);
            ui->a_label->setToolTip(text);
        }
    }
    else
    {
        a_isScrollingText = true;
        if(ui->a_label->isVisible())
            ui->a_label->hide();
        a_scrollingLabel.setText(text);
        a_scrollingLabel.setToolTip(text);
        a_scrollingLabel.show();
    }
}

//This method keeps the fade in speed variable by the info label's length
//It is a workaround for very long info labels that don't have the time to scroll all the way
void Player::updateFadeinSpeed()
{
    /*                                      How it works
     * A case is the number of seconds an info type will be displayed till we switch over to the next info
     * As they're dependent from the previous one, we always add the seconds of the case before
     * ex : if each info is less/equal to 17 chars, it'll be case 3,6,9 so that it switches each 3 seconds
     * */
    if(a_titre.size() <= 17) //17 so it won't go to the else and generate 3 when the default would be 4 (it's an int, it floors)
        a_titleCase = 4;
    else
        a_titleCase = (a_titre.size() / 10) * 3; //3 is a magic number, and /10 is to have seconds

    if(a_artiste.size() <= 17)
        a_artistCase = a_titleCase + 4;
    else
        a_artistCase = a_titleCase + ((a_artiste.size() / 10) * 3);
    if(a_album.size() <= 17)
        a_albumCase = a_artistCase + 4;
    else
        a_albumCase = a_artistCase + ((a_album.size() / 10) * 3);
}

void Player::runAudioFade()
{
    a_audioFade->setEndValue(a_volumeSlider->value());
    if(a_audioFade->state() == QPropertyAnimation::Running)
        a_audioFade->stop();
    a_audioFade->start();
}

//Does the animation between each info
void Player::fadeInLabel()
{
    //This changes the target if we're using the scrolling label
    if(a_isScrollingText)
        a_scrollingLabel.setGraphicsEffect(a_infoFadein);
    else
        ui->a_label->setGraphicsEffect(a_infoFadein);

    a_infoFadeAnim->setTargetObject(a_infoFadein);
    a_infoFadeAnim->setPropertyName("opacity");
    a_infoFadeAnim->setDuration(700);
    a_infoFadeAnim->setStartValue(0);
    a_infoFadeAnim->setEndValue(1.0);
    a_infoFadeAnim->start();
}

void Player::update_info()
{
    //update à chaque seconde
    a_secondesPasse++;

    /*Permet de gérer les informations à afficher en fonction du temps
     * Fades each time
     * The cases are named after the item which is displayed BEFORE going to the specific case
     * It might seems unclear at first but I believe it's better this way
    */

    //Switches over to normal if's because switch case can't evaluate non-constant expression
    if(a_secondesPasse == a_titleCase)
    {
        updateLabel(a_artiste);
        if(!a_no_meta)
            fadeInLabel();
    }
    if(a_secondesPasse == a_artistCase)
    {
        updateLabel(a_album);
        if(!a_no_meta)
            fadeInLabel();
    }
    if(a_secondesPasse == a_albumCase)
    {
        a_secondesPasse = 0;
        updateLabel(a_titre);
        if(!a_no_meta)
            fadeInLabel();
    }
    if(!a_menu.isVisible() &&  a_alwaysOnTopHandler.isChecked()) //If we're always on top, this assure that we're always on top, even if on Windows explorer gets on top
        if(!a_isPlaylistOpen && !a_isSettingsOpen) //Raising also raises over the widgets of these windows... Can be weird if you're using it's context menus...
            this->raise();
}
    /*///////SliderBar Section///////*/
void Player::UpdateProgress(qint64 pos)
{
    if(pos < 0)
        pos = 0; //Will bring back bizarre values to saner levels
    a_progressSlider->setValue(pos);
    updateProgressDisplay(pos, true);

}

//This method updates the seconds and minutes displayed when playing and if isProgress is false it will update the duration (on_durationChanged event)
void Player::updateProgressDisplay(qint64 pos, bool isProgress)
{
    pos /= 1000;
    int minutes = 0;
    // Fait en sorte d'update le label de temps actuel
    while (pos % 60 != pos)
    {
        pos -= 60;
        minutes++;
    }
    //duration vaut maintenant les secondes restantes...
    int secondes = pos;
    if(secondes < 10)
    {
        if(isProgress)
            ui->a_currenttime->setText(QString::number(minutes) + ":0" + QString::number(secondes));
        else
            ui->a_duration->setText(QString::number(minutes) + ":0" + QString::number(secondes));
    }
    else
    {
        if(isProgress)
            ui->a_currenttime->setText(QString::number(minutes) + ":" + QString::number(secondes));
        else
            ui->a_duration->setText(QString::number(minutes) + ":" + QString::number(secondes));
    }
}

//Produit grâce à un signal EndOfMedia();
void Player::endOfMediaGuard()
{
    Timer.stop(); //There should be no more info to display
    ui->a_pausebtn->setVisible(false);
    ui->a_playbtn->setVisible(true);
    disconnect(ui->a_pausebtn, SIGNAL(clicked()), this, SLOT(pauseMedia()));
    connect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
    ui->a_label->setText(tr("Stoppé"));
}
void Player::seekProgress(int pos)
{
    neu->setPosition(pos);
    if(a_recoveredProgress)
    {
        neu->play();
        disconnect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
        ui->a_playbtn->setVisible(false);
        ui->a_pausebtn->setVisible(true);
        connect(ui->a_pausebtn, SIGNAL(clicked()), this, SLOT(pauseMedia()));
    }
    if(a_isPlaylistOpen && !a_playlist->isPlayingState())
        a_playlist->setToPlaying(neu->playlist()->currentIndex());
    if(pos > neu->duration())
        forwardMedia();
}

void Player::on_durationChanged(qint64 pos)
{
    a_progressSlider->setMaximum(pos);
    updateProgressDisplay(pos, false);
}

//Accessible par raccourci clavier ALT + Right
void Player::advanceProgress()
{
    int advanceTo = neu->position() + 15000;
    seekProgress(advanceTo);
}

//Accessible par raccourci clavier ALT + Left
void Player::backProgress()
{
    int goBackTo = neu->position() - 15000;
    seekProgress(goBackTo);
}

//handler du volume
void Player::on_volumeChanged(int pos)
{
    neu->setVolume(pos);
    if(pos == 0)
    {
        ui->a_volumebtn->setChecked(true);
        setVolumeMuted();
        return;
    }
    if(pos <= 50)
    {
        if(a_idSkin == 1 || a_idSkin == 3)
            ui->a_volumebtn->setIcon(a_volumeLowIcon);
        else
            ui->a_volumebtn->setIcon(a_volumeLowDarkIcon);
    }
    else
    {
        if(a_idSkin == 1 || a_idSkin == 3)
            ui->a_volumebtn->setIcon(a_volumeIcon);
        else
            ui->a_volumebtn->setIcon(a_volumeDarkIcon);
    }
    ui->a_volumebtn->setChecked(false);
    neu->setMuted(false);
}

void Player::setVolumeMuted()
{
    if(ui->a_volumebtn->isChecked())
    {
        a_volumeBeforeMute = neu->volume();
        disconnect(a_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(on_volumeChanged(int)));
        neu->setMuted(true);
        a_volumeSlider->setValue(0);
        connect(a_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(on_volumeChanged(int)));
        if(a_idSkin == 1 || a_idSkin == 3)
            ui->a_volumebtn->setIcon(a_volumeMutedIcon);
        if(a_idSkin == 0 ||  a_idSkin == 2)
            ui->a_volumebtn->setIcon(a_volumeMutedDarkIcon);
    }
    else
    {
        neu->setMuted(false);
        a_volumeSlider->setValue(a_volumeBeforeMute); //On laisse le _onvolumeChanged() faire le boulot de remettre les bonnes icones
    }
}

void Player::volumeUp()
{
    a_volumeSlider->setSliderPosition(a_volumeSlider->value() + 10);
}

void Player::volumeDown()
{
    a_volumeSlider->setSliderPosition(a_volumeSlider->value() - 10);
}

    /*///////Menu Actions Section///////*/

void Player::setShuffle()
{
    if(!a_canDoShuffleAgain)
        return;
    if(neu->media().isNull()) //On évite de planter en essayant de play quelque chose qui n'existe pas
    {
        openMedia(); //On demande à l'utilisateur de séléctionner quelque chose
        if(!neu->media().isNull()) //On vérifie qu'il y a maintenant des musiques à jouer
            setShuffle(); //On repasse. Ici il passera donc dans le !isNull(); et procédera au shuffle mode
        }
    else if(!neu->media().isNull())
    {
        /* On seed un générateur de nombres pour avoir un vrai rand
                    généré au moment de l'activation              */
        qsrand(QTime::currentTime().msec());
        QMediaPlaylist *playlist (neu->playlist()); //We retrieve a QMediaPlaylist because we don't want another cast to be done

        int index = qrand() % playlist->mediaCount();
        playlist->setCurrentIndex(index);

        //Plus le shuffle, qui crée un rand en prenant comme valeur le média actuel
        playlist->shuffle();
        playlist->setCurrentIndex(0); //So it looks better this way
        if(!a_isRandomMode)
            playlist->setPlaybackMode(QMediaPlaylist::Sequential); //Default : random. We want it back to Sequential if we were on sequential before
        //On a maintenant un double rand : un rand purement aléatoire, et un rand basé sur le media actuel
        if(a_settings.value("Additional_Features/libraryAtStartup", false).toBool() == true)
            a_hasToSavePlaylistLater = true; // Will update playlist to load the correct one when booting up later on
        if(a_isPlaylistOpen && !a_isUsingFavPlaylist)
            a_playlist->updateList(&a_mediaPlaylist, true);
        else if(a_isPlaylistOpen)
            a_playlist->updateFavs(&a_favPlaylist);
        a_canDoShuffleAgain = false;
        grantShuffleAgainTimer.start(500);
        playlist = nullptr;
    }
}

void Player::windowFlagsHandler()
{
    if(a_alwaysOnTopHandler.isChecked())
        this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    else
        this->setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint);
    QPointer <FadeWindow> fadeIn = new FadeWindow(this, 200, FadeWindow::FadeIn, this);
    fadeIn->start(a_settings.value("opacity").toReal());

    this->show();
}

void Player::playbackHandler(QAction *playbackSelected)
{
    if(playbackSelected->text() == "1.0x")
        a_playbackState = 0;
    else if (playbackSelected->text() == "0.5x")
        a_playbackState = 1;
    else if (playbackSelected->text() == "2.0x")
        a_playbackState = 2;
    setPlaybackRate();
}

void Player::setPlaybackRate()
{
    //Setup playback rate
    //Pause pour forcer de rappuyer sur lecture à nouveau, de façon à ce que le buffer soit déjà à nouveau à peu près rempli
    pauseMedia();
    if(a_playbackState == 0)
    {
        neu->setPlaybackRate(1);
        a_normalrate.setChecked(true);
    }
    else if (a_playbackState == 1)
    {
        neu->setPlaybackRate(0.5);
        a_halfrate.setChecked(true);
    }
    else if (a_playbackState == 2)
    {
        neu->setPlaybackRate(2);
        a_doublerate.setChecked(true);
    }
}

void Player::showPlaylist()
{
    if(!a_isPlaylistOpen)
    {
        a_isPlaylistOpen = true;
        if(a_mediaPlaylist.mediaCount()!= 0)
            a_playlist = new Playlist(a_mediaPlaylist, a_favPlaylist, this, &a_coverArt, a_titre, a_isPlaying, this);
        a_playlist->show();
    }
    else
    {
        a_playlist->showNormal();
        a_playlist->activateWindow();
    }
}

void Player::showSettings()
{
    if(!a_isSettingsOpen)
    {
        a_isSettingsOpen = true;
        a_settingsForm = new Settings(this, this);
        a_settingsForm->show();
    }
    else
    {
        a_settingsForm->show();
        a_settingsForm->activateWindow();
    }
}

void Player::showTagViewer()
{
    if(neu->media().isNull())
        return;

    /* Add meta datas to a list which will be treated by the tagViewer constructor */
    QList<QString> metaDatas;
    metaDatas.append(neu->metaData("TrackNumber").toString());
    metaDatas.append(a_titre);
    metaDatas.append(a_artiste);
    metaDatas.append(a_album);
    metaDatas.append(neu->metaData("Year").toString());
    metaDatas.append(neu->metaData("Genre").toString());
    //Load it now !
    QPointer <TagViewer> TagWindow = new TagViewer(metaDatas, &a_coverArt, this);
    TagWindow->exec();
}

    /*///////Events Section///////*/

void Player::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
            event->acceptProposedAction();
}

void Player::dropEvent(QDropEvent *event)
{
    ui->a_label->setText("Loading...");
    neu->stop();
    Timer.stop(); //We don't want to fade in while we're loading, right ?
    this->setCursor(Qt::BusyCursor);
    unsigned int const numberUrls = event->mimeData()->urls().size();
    QList <QUrl> listUrls;
    for (unsigned int i(0); i < numberUrls; i++)
    {
        listUrls.append(event->mimeData()->urls().at(i));
        //Permet de toujours rendre l'application plus ou moins utilisable
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    updatePlaylistOfThePlayer(listUrls, true);
}

void Player::closeEvent(QCloseEvent *event)
{
    if(a_canClose)
    {
        saveBeforeClosing();
        qApp->closeAllWindows();
    }
    else
    {
        event->ignore();
        Timer.setSingleShot(true);
        //Trigger the delayed close with animation
        Timer.start(400);
        connect(&Timer, SIGNAL(timeout()), this, SLOT(delayedClose()));
        QPointer <FadeWindow> fadeOut = new FadeWindow(this, 200, FadeWindow::FadeOut, this);
        if(a_isPlaying)
        {
            QPointer <QPropertyAnimation> audioFadeOut = new QPropertyAnimation(neu, "volume", this);
            audioFadeOut->setEndValue(0);
            audioFadeOut->setStartValue(a_volumeSlider->value());
            audioFadeOut->setDuration(250);
            audioFadeOut->start(QAbstractAnimation::DeleteWhenStopped);
        }
        fadeOut->start();
    }
}

void Player::saveBeforeClosing()
{
    savePlaylists();
    if(a_settings.value("Additional_Features/framelessWindow").toBool())
        a_settings.setValue("pos", QPoint(this->x() - 8, this->y() - 31)); //Little hack to set the value correctly
    else
        a_settings.setValue("pos", pos());
    a_settings.setValue("size", size());
    a_settings.setValue("volume", a_volumeSlider->value());
    a_settings.setValue("visibilite", a_alwaysOnTopHandler.isChecked());
    a_settings.setValue("playbackrate", a_playbackState);
    a_settings.setValue("random", a_isRandomMode);
    a_settings.setValue("loop", a_isLoopPlaylistMode);
    a_settings.setValue("usingFavorites", a_isUsingFavPlaylist); //If this is on, we're currently using the fav playlist. So it shall be set at next run
    if(a_settings.value("Additional_Features/saveTrackIndex", false).toBool() == true)
        a_settings.setValue("trackPosition", neu->position());
}

void Player::delayedClose()
{
    a_canClose = true;
    close(); //Now the event will be accepted
}

    /*///////Playlist Interface Section///////*/

void Player::setRandomMode(bool mode)
{
    bool prev = a_isRandomMode;
    if(prev != mode) //On change que s'il y a besoin
    {
        a_isRandomMode = mode;
        if(a_isRandomMode)
        {
            neu->playlist()->setPlaybackMode(QMediaPlaylist::Random);
            a_hasToDoInitialShuffle = true;
        }
        else
        {
            neu->playlist()->setPlaybackMode(QMediaPlaylist::Sequential);
            if(a_hasToDoInitialShuffle)
                a_hasToDoInitialShuffle = false;
        }
    }
}

void Player::setLoopMode(bool mode)
{
    bool prev = a_isLoopPlaylistMode;
    if(prev != mode) //On change que s'il y a besoin
    {
        a_isLoopPlaylistMode = mode;
    }
}

//Called when playlist wants to play something
void Player::setIndexOfThePlayer(int index, bool play)
{
    a_wasPrevious = false; //To launch anim
    if(!a_isUsingFavPlaylist)
        a_mediaPlaylist.setCurrentIndex(index);
    else
        a_favPlaylist.setCurrentIndex(index);
    if(play)
        playMedia();
}

//Called when dealing with a drag & drop
void Player::addMediasToThePlayer(QList<QUrl> &medias)
{
    int insertTo = neu->playlist()->currentIndex() + 1;
    unsigned int const mediaNumber = medias.size();
    for(unsigned int i(0); i < mediaNumber; i++, insertTo++)
    {
        neu->playlist()->insertMedia(insertTo, QUrl(medias.at(i)));
    }
    if(a_isPlaylistOpen)
        a_playlist->quickUpdate(&medias, insertTo - 1);
    if(!a_isUsingFavPlaylist)
        if(a_hasToSavePlaylistLater != true)
            a_hasToSavePlaylistLater = true;
    else
        if(a_hasToSaveFavsLater != true)
            a_hasToSaveFavsLater = true;
}

void Player::addFav(int index)
{
    QMediaContent media(a_mediaPlaylist.media(index)); //We copy the media
    a_favPlaylist.addMedia(media);
    QList <QUrl> temp;
    temp.append(media.canonicalUrl());
    bool previousState = a_isUsingFavPlaylist;
    a_isUsingFavPlaylist = true; //So the quickUpdate knows what to update
    a_playlist->quickUpdate(&temp, a_favPlaylist.mediaCount()); //The quick update will place the media at the end of fav without reloading the whole playlist
    if(previousState == false)
        a_isUsingFavPlaylist = false; //We're finished
    if(a_hasToSaveFavsLater != true)
        a_hasToSaveFavsLater = true;

}

void Player::changeToFavPlaylist()
{
    a_shuffle.setVisible(false); // Keep your favorites clean.
    neu->setPlaylist(&a_favPlaylist);
    a_isUsingFavPlaylist = true;
}

void Player::changeToDefaultPlaylist()
{
    a_shuffle.setVisible(true); // We can reload the original from disk anyway
    neu->setPlaylist(&a_mediaPlaylist);
    a_isUsingFavPlaylist = false;
}

//When added to queue
void Player::addToQueue(int index, int currentlyPlaying)
{
    int insertTo = currentlyPlaying + a_playlist->queuedIndex(); //if you add one music, it'll place the next one next to it, ect...
    QMediaContent media(a_mediaPlaylist.media(index)); //We copy the media
    deleteMedia(index);
    if(index < currentlyPlaying)
        insertTo--;
    a_mediaPlaylist.insertMedia(insertTo, media);
    QList <QUrl> temp;
    temp.append(a_mediaPlaylist.media(insertTo).canonicalUrl());
    a_playlist->deleteItem(index);
    a_playlist->quickUpdate(&temp, insertTo); //The quick update will place the media at insertTo index without reloading the whole playlist
    if(a_hasToSavePlaylistLater != true)
        a_hasToSavePlaylistLater = true;
}

//Called when setting a folder from playlist
void Player::updatePlaylistOfThePlayer(const QList<QUrl> &medias, bool play)
{
    a_mediaPlaylist.clear();
    setCursor(Qt::BusyCursor);
    unsigned int const mediaNumber = medias.size();
    for(unsigned int i (0); i < mediaNumber; i++ )
    {
        a_mediaPlaylist.addMedia(medias.at(i));
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    changeToDefaultPlaylist(); //Re-set to update...
    if(a_isPlaylistOpen)
        a_playlist->updateList(&a_mediaPlaylist);
    if(a_hasToSavePlaylistLater != true)
        a_hasToSavePlaylistLater = true;
    if(play)
        playMedia();
    else
    {
        disconnect(ui->a_pausebtn, SIGNAL(clicked()), this, SLOT(pauseMedia()));
        ui->a_playbtn->setVisible(true);
        ui->a_pausebtn->setVisible(false);
        connect(ui->a_playbtn, SIGNAL(clicked()), this, SLOT(playMedia()));
    }
    setCursor(Qt::ArrowCursor);
}

void Player::restart()
{
    saveBeforeClosing();
    qApp->quit();
    QProcess::startDetached("neuPlayer.exe");
}
//Destructor
Player::~Player()
{
    delete ui;
}
