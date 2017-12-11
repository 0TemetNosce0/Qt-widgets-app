#include "playlist.h"
#include "ui_playlist.h"
#include <QFileDialog>
#include <QDirIterator>

Playlist::Playlist(neuPlaylist &liste, neuPlaylist &favs, Player *player, QPixmap *cover, QString title, bool playingState, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Playlist)
    , a_isReload (false)
    , a_favsNotLoadedYet(true), //These bool can result in unexpected behaviour if it's not initialized
    a_settings("neuPlayer.ini", QSettings::IniFormat, this)
{
    ui->setupUi(this);
    ui->a_searchLine->setHidden(true);
    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_DeleteOnClose);

    resize(a_settings.value("Playlist/size", QSize(265, 300)).toSize());
    ui->a_playlistWidget->setDragEnabled(false); //I can't handle it well as of now :/
    ui->a_playlistFavWidget->setDragEnabled(false);
    a_defaultCover.load(":/Ressources/noCoverHeader.png");
    //On reçoit le player, il faut maintenant le mettre en tant qu'attribut pour l'utiliser partout
    a_player = player;
    //De même, on met la playlist en tant qu'attribut pour l'utiliser plus tard.
    a_playlist = &liste;
    a_favPlaylist = &favs; //Et l'autre
    a_previousIndex = 99999; //Pretty sure nobody would reach that value
    a_queueIndex = 0; //used to determine where to place the song you want to queue
    //Prepare fade manager animations
    a_fadeManager.addTarget(ui->a_cover, FadeManager::FadeIn, 400, FadeManager::Parallel);
    a_fadeManager.addTarget(ui->a_titleHeader, FadeManager::FadeIn, 300, FadeManager::Parallel);
    //Prepare tab animations
    a_moveAnim.setDuration(MoveAnimation::Fast);
    setupActions();
    //Setup list
    updateList(&liste);
    if(!player->isUsingFav())
    {
        if(!liste.isEmpty()) //If it's okay
        {
            if(liste.currentIndex() == -1) //If it's stopped or something weird is going on
                ui->a_titleHeader->setText(tr("Séléctionnez une musique à lire"));
            else //Okay, gogo
            {
                ui->a_playlistWidget->scrollToItem(ui->a_playlistWidget->item(liste.currentIndex()),  QAbstractItemView::PositionAtTop);
                setCurrentItem(liste.currentIndex(), cover, title, playingState);
                //Update the icon if the player is paused or stopped
            }
        }
        else //If not, shows there's nothing
        {
            ui->a_playlistWidget->addItem(tr("Aucune musique"));
            ui->a_playlistWidget->item(0)->setTextAlignment(Qt::AlignCenter);
        }
    }
    else
    {
        updateFavs(&favs);
        if(!favs.isEmpty()) //If it's okay
        {
            if(favs.currentIndex() != -1) //Okay, gogo
            {
                ui->a_playlistFavWidget->scrollToItem(ui->a_playlistFavWidget->item(favs.currentIndex()), QAbstractItemView::PositionAtTop);
                setCurrentItem(favs.currentIndex(), cover, title, playingState);
                //Update the icon if the player is paused or stopped
            }
        }
        setTab(1);
    }

    setupConnections();

    setupMode();
    if(player->y() > 600)
        this->move(player->x() + 60, player->y() - 200);
}

void Playlist::setupActions()
{
    //Actions & Playlist Menu
    a_selectOtherDir = new QAction(tr("Sélectionner un dossier à lire"), this);
    a_selectOtherDir->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    a_reloadLibrary = new QAction(tr("Recharger la bibliothèque"), this);
    a_reloadLibrary->setShortcut(Qt::Key_F5);
    a_playlistMenu = new QMenu(this);
    a_playlistMenu->addAction(a_selectOtherDir);
    a_playlistMenu->addAction(a_reloadLibrary);
    ui->a_tools->setMenu(a_playlistMenu);
    //Actions & Context menu
    ui->a_playlistWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->a_playlistFavWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    a_findItemTrigger = new QAction(this);
    a_findItemTrigger->setShortcut(Qt::CTRL + Qt::Key_F);
    a_findItemTrigger->setCheckable(true);
    a_deleteItemFromQueue = new QAction(tr("Supprimer de la file d'attente"), this);
    a_deleteItemFromQueue->setShortcut(Qt::Key_Delete);
    a_addToQueue = new QAction(tr("Ajouter à la file d'attente"), this);
    a_addToQueue->setShortcut(Qt::CTRL + Qt::Key_Plus);
    a_addToFav = new QAction(tr("Ajouter aux favoris"), this);
    a_addToFav->setShortcut(QKeySequence("CTRL + *"));
    a_viewInfo = new QAction(tr("Voir les informations"), this);
    a_viewInfo->setShortcut(Qt::ALT + Qt::Key_Return);
    a_easyHideFind = new QAction(this);
    a_easyHideFind->setShortcut(Qt::Key_Escape);
    a_validateFind = new QAction(this);
    a_validateFind->setShortcut(Qt::Key_Return); //Action so I don't bother with events to validate

    this->addAction(a_addToQueue);
    this->addAction(a_findItemTrigger);
    this->addAction(a_viewInfo);
    this->addAction(a_deleteItemFromQueue);
    //Setup menu
    a_playlistContextMenu = new QMenu(this);
    a_playlistContextMenu->addAction(a_addToQueue);
    a_playlistContextMenu->addAction(a_deleteItemFromQueue);
    a_playlistContextMenu->addAction(a_viewInfo);
    a_playlistContextMenu->addAction(a_addToFav);
}


void Playlist::setupConnections()
{
    /* Connexions */
    connect(a_selectOtherDir, SIGNAL(triggered()), this, SLOT(setFolder()));
    connect(a_reloadLibrary, SIGNAL(triggered()), this, SLOT(reloadLibrary()));
    connect(ui->a_switchRandomPlay, SIGNAL(clicked()), this, SLOT(randomModeChanger()));
    connect(ui->a_switchLoopPlay, SIGNAL(clicked()), this, SLOT(loopModeChanger()));
    connect(ui->a_playlistWidget, SIGNAL(activated(QModelIndex)), this, SLOT(playItem(QModelIndex)));
    connect(ui->a_playlistFavWidget, SIGNAL(activated(QModelIndex)), this, SLOT(playItem(QModelIndex)));
    //This one below is commented out because it doesn't work yet. Need help as to why it crashes
//    connect(a_findItemTrigger, SIGNAL(triggered()), this, SLOT(findItemVisibilityHandler()));
    connect(ui->a_playlistWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
    connect(ui->a_playlistFavWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
    connect(a_playlistContextMenu, SIGNAL(aboutToShow()), this, SLOT(prepareContextMenu()));
    connect(a_deleteItemFromQueue, SIGNAL(triggered()), this, SLOT(deleteItem()));
    connect(a_addToQueue, SIGNAL(triggered()), this, SLOT(addItemToQueue()));
    connect(a_viewInfo, SIGNAL(triggered()), this, SLOT(viewInfo()));
    connect(a_addToFav, SIGNAL(triggered()), this, SLOT(addToFavContext()));
    connect(ui->a_addFavStar, SIGNAL(clicked()), this, SLOT(on_starClicked()));
    connect(ui->a_titleHeader, SIGNAL(clicked()), this, SLOT(scrollToPlaying()));
    connect(ui->a_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setTab(int)));
    connect(a_validateFind, SIGNAL(triggered()), this, SLOT(validateSearch()));
}

void Playlist::setupMode()
{
    //Random mode setup
    bool isRandomMode = a_player->getRandomState();
    if(isRandomMode)
        ui->a_switchRandomPlay->setChecked(true);
    else
        ui->a_switchRandomPlay->setChecked(false);

    //Loop mode setup
    bool isLoopingPlaylistMode = a_player->getLoopState();
    if(isLoopingPlaylistMode)
        ui->a_switchLoopPlay->setChecked(true);
    else
        ui->a_switchLoopPlay->setChecked(false);
}

        /* Update section */

void Playlist::updateList(neuPlaylist *listeFichiers, bool setZeroIndex)
{
    if(a_currentIndex != 0 && setZeroIndex) //Helps not to crash. Each index is reset to 0 so there isn't any out of bound, but only when we're not starting up
    {
        a_player->setIndexOfThePlayer(0, false);
        ui->a_playlistWidget->setCurrentRow(0);
    }
    if(ui->a_tabWidget->currentIndex() != 0)
        ui->a_tabWidget->setCurrentIndex(0);
    ui->a_playlistWidget->clear();
    int const mediaCount = listeFichiers->mediaCount();
    for(int i(0); i < mediaCount; i++)
    {
        QString filepath = listeFichiers->media(i).canonicalUrl().toString();
        ui->a_playlistWidget->addItem(QFileInfo(filepath).fileName());
    }
}

void Playlist::updateFavs(neuPlaylist *favPlaylist) //Called when the tab is set to favs, and it wasn't initially called
{
    ui->a_playlistFavWidget->clear();
    int const mediaCount = favPlaylist->mediaCount();
    for(int i(0); i < mediaCount; i++)
    {
        QString filepath = favPlaylist->media(i).canonicalUrl().toString();
        ui->a_playlistFavWidget->addItem(QFileInfo(filepath).fileName());
    }
    a_favsNotLoadedYet = false;
}

void Playlist::quickUpdate(QList<QUrl> *items, int currentItemPlusOne) //Updates the list very fast. Used when adding an element
{
    unsigned int const numberItems = items->size();
    if(!a_player->isUsingFav())
    {
        for(unsigned int i(0); i < numberItems; i++, currentItemPlusOne++)
        {
            ui->a_playlistWidget->insertItem(currentItemPlusOne, items->at(i).fileName());
        }
    }
    else
    {
        if(a_favsNotLoadedYet)
            updateFavs(a_favPlaylist); //Load everything
        else //Load only what's necessary, the rest is already there
        {
            for(unsigned int i(0); i < numberItems; i++, currentItemPlusOne++)
            {
                ui->a_playlistFavWidget->insertItem(currentItemPlusOne, items->at(i).fileName());
            }
        }
    }
}
        /* State section */
//Those are handled by the player

void::Playlist::setToPlaying(int index)
{
    if(!a_player->isUsingFav())
        ui->a_playlistWidget->item(index)->setIcon(QIcon(":/Ressources/playingState_icon.png"));
    else
        ui->a_playlistFavWidget->item(index)->setIcon(QIcon(":/Ressources/playingState_icon.png"));
    a_isPlaying = true;
}


void Playlist::setToPaused(int index)
{
    if(!a_player->isUsingFav())
        ui->a_playlistWidget->item(index)->setIcon(QIcon(":/Ressources/pausedState-icon2.png"));
    else
        ui->a_playlistFavWidget->item(index)->setIcon(QIcon(":/Ressources/pausedState-icon2.png"));
    a_isPlaying = false;
}

void Playlist::setCurrentItem(int index, QPixmap *cover, QString title, bool playing)
{
    if(a_previousIndex != 99999) //Default value of a_previousIndex
    {
        if(ui->a_playlistWidget->count() > a_previousIndex) //Then it obviously exists within the list
            ui->a_playlistWidget->item(a_previousIndex)->setIcon(QIcon());
        if(ui->a_playlistFavWidget->count() > a_previousIndex)
            ui->a_playlistFavWidget->item(a_previousIndex)->setIcon(QIcon());
    }
    a_queueIndex = 0;
    a_previousIndex = index;
    if(playing)
        setToPlaying(index);
    else
        setToPaused(index);
    a_currentIndex = index;
    if(!a_player->isUsingFav())
    {
        ui->a_playlistWidget->setCurrentRow(index);
        if(checkIfNotFav(index))
            makeStarFull();
        else
            makeStarEmpty();
    }
    else
    {
        ui->a_playlistFavWidget->setCurrentRow(index);
        makeStarFull();
    }
    scrollToPlaying();
    //Use data received
    updateInfoHeader(title, *cover);
}


void Playlist::updateInfoHeader(QString &title, QPixmap &cover)
{
    ui->a_cover->setPixmap(cover);
    if(ui->a_cover->pixmap()->isNull())
        ui->a_cover->setPixmap(a_defaultCover);
    ui->a_titleHeader->setText(title);
    ui->a_titleHeader->setToolTip(title);
    if(!a_player->deleteTriggered()) //Won't start the animation if we're actually not changing the item played
        a_fadeManager.startGroup(FadeManager::Parallel, false);
}

        /* Playlist functionality */

void Playlist::setFolder()
{
    QString selectDir;
    // On sélectionne le répertoire à partir duquel on va rechercher les fichiers que le player peut lire
    if(!a_isReload)
        selectDir = (QFileDialog::getExistingDirectory (this,tr("Ouvrir un répertoire"), "", QFileDialog::DontResolveSymlinks));
    else if(!a_settings.value("mediapath").toString().isEmpty())
        selectDir =  a_settings.value("mediapath", "").toString();

    if(!selectDir.isEmpty())
    {
        setCursor(Qt::BusyCursor);
        if(a_currentIndex != 0) //Helps not to crash. the index is reset to 0 so there isn't any out of bound.
        {
            a_player->setIndexOfThePlayer(0, false);
            ui->a_playlistWidget->setCurrentRow(0);
        }
        QList <QUrl> urlList = a_playlist->update(selectDir);
        if(!urlList.empty()) //Don't set anything if there wasn't any content
            a_player->updatePlaylistOfThePlayer(urlList, true);
        setCursor(Qt::ArrowCursor);
    }
}

void Playlist::on_starClicked()
{
    if(!a_player->isUsingFav())
    {
        if(!checkIfNotFav(a_currentIndex))
            addToFav();
        else
        {
            deleteFav(a_currentIndex);
            makeStarEmpty();
        }
    }
    else //It's already in favorite, so...
    {
        deleteFav(a_currentIndex);
        makeStarEmpty();
    }
}

//Proxy method that uses setFolder();
void Playlist::reloadLibrary()
{
    a_isReload = true;
    setFolder();
    a_isReload = false;
}

void Playlist::randomModeChanger()
{
    if(ui->a_switchRandomPlay->isChecked())
        setShuffle();
    else
        setSequential();
    this->setFocus(); //évite d'avoir le focus sur le bouton
}

void Playlist::loopModeChanger()
{
    if(ui->a_switchLoopPlay->isChecked())
        a_player->setLoopMode(true);
    else
        a_player->setLoopMode(false);
    this->setFocus();
}

void Playlist::setSequential()
{
    a_player->setRandomMode(false); // 0 = No random = Sequential
}

void Playlist::setShuffle()
{
    a_player->setRandomMode(true); // 1 = random
}

void Playlist::playItem(QModelIndex itemIndex)
{
    if(!a_player->canChangeMusic())
        return;
    if(ui->a_tabWidget->currentIndex() == 0 && ui->a_playlistWidget->currentItem()->textAlignment() == Qt::AlignCenter)
    {
        setFolder();
        return;
    }
    if(ui->a_tabWidget->currentIndex() == 1 && ui->a_playlistFavWidget->currentItem()->textAlignment() == Qt::AlignCenter)
        return;
    if(!a_player->isUsingFav() && ui->a_tabWidget->currentIndex() == 1)
        a_player->changeToFavPlaylist();
    else if(ui->a_tabWidget->currentIndex() == 0 && a_player->isUsingFav())
        a_player->changeToDefaultPlaylist();
    a_player->setIndexOfThePlayer(itemIndex.row(), true);
    a_currentIndex = itemIndex.row();
}

void Playlist::prepareContextMenu()
{
    // 0 : add to queue
    // 1 : delete from queue
    // 2 : view info
    // 3 : add to fav
    if(ui->a_tabWidget->currentIndex() == 0 && a_currentIndex != ui->a_playlistWidget->currentRow())
    {
        a_deleteItemFromQueue->setText(tr("Supprimer de la file d'attente"));
        a_playlistContextMenu->actions().at(3)->setVisible(true);
        a_playlistContextMenu->actions().at(2)->setVisible(true);
        a_playlistContextMenu->actions().at(1)->setVisible(true);
        a_playlistContextMenu->actions().at(0)->setVisible(true);
    }
    else if(ui->a_tabWidget->currentIndex() == 0 && a_currentIndex == ui->a_playlistWidget->currentRow())
    {
        a_playlistContextMenu->actions().at(3)->setVisible(true);
        a_playlistContextMenu->actions().at(2)->setVisible(true);
        a_playlistContextMenu->actions().at(1)->setVisible(false);
        a_playlistContextMenu->actions().at(0)->setVisible(false);
    }
    if(ui->a_tabWidget->currentIndex() == 0 && ui->a_playlistWidget->currentItem()->textAlignment() == Qt::AlignCenter) //if no music on playlist
    {
        a_playlistContextMenu->actions().at(3)->setVisible(false);
        a_playlistContextMenu->actions().at(2)->setVisible(false);
        a_playlistContextMenu->actions().at(1)->setVisible(false);
        a_playlistContextMenu->actions().at(0)->setVisible(false);
    }
    if(a_player->isUsingFav() && a_currentIndex == ui->a_playlistFavWidget->currentRow() && ui->a_tabWidget->currentIndex() == 1)
    {
        a_playlistContextMenu->actions().at(3)->setVisible(false);
        a_playlistContextMenu->actions().at(2)->setVisible(true);
        a_playlistContextMenu->actions().at(1)->setVisible(false);
        a_playlistContextMenu->actions().at(0)->setVisible(false);
    }
}

//Activated by the clicked() signal of the a_titleHeader UI component
void Playlist::scrollToPlaying()
{
    if(!a_player->isUsingFav())
    {
        if(ui->a_tabWidget->currentIndex() != 0)
            ui->a_tabWidget->setCurrentIndex(0);
        ui->a_playlistWidget->setCurrentRow(a_currentIndex);
        ui->a_playlistWidget->scrollTo(ui->a_playlistWidget->currentIndex(), QAbstractItemView::PositionAtTop);
    }
    else
    {
        if(ui->a_tabWidget->currentIndex() != 1)
            ui->a_tabWidget->setCurrentIndex(1);
        ui->a_playlistFavWidget->setCurrentRow(a_currentIndex);
        ui->a_playlistFavWidget->scrollTo(ui->a_playlistFavWidget->currentIndex(), QAbstractItemView::PositionAtTop);
    }
}

void Playlist::setTab(int tabId)
{
    if(tabId == 1) //Favorites
    {
        a_deleteItemFromQueue->setText(tr("Supprimer des favoris"));
        a_playlistContextMenu->actions().at(3)->setVisible(false);
        a_playlistContextMenu->actions().at(2)->setVisible(true);
        a_playlistContextMenu->actions().at(1)->setVisible(true);
        a_playlistContextMenu->actions().at(0)->setVisible(false);
        a_moveAnim.setTarget(ui->a_playlistFavWidget);
        a_moveAnim.setDirection(MoveAnimation::LeftToRight);
        a_moveAnim.start();
        if(a_favsNotLoadedYet)
            updateFavs(a_favPlaylist);
    }
    else
    {
        a_moveAnim.setTarget(ui->a_playlistWidget);
        a_moveAnim.setDirection(MoveAnimation::RightToLeft);
        a_moveAnim.start();
    }
    a_previousTab = tabId;
    if(ui->a_tabWidget->currentIndex() != tabId) //If called
        ui->a_tabWidget->setCurrentIndex(tabId);
}


void Playlist::showContextMenu() const
{
    a_playlistContextMenu->exec(QCursor::pos());
}

void Playlist::addItemToQueue()
{
    a_player->addToQueue(ui->a_playlistWidget->currentRow(), a_currentIndex);
}

void Playlist::addToFavContext()
{
    if(!checkIfNotFav(ui->a_playlistWidget->currentRow()))
        a_player->addFav(ui->a_playlistWidget->currentRow());
    if(ui->a_tabWidget->currentIndex() == 0 && a_currentIndex == ui->a_playlistWidget->currentRow())
        makeStarFull();
}

void Playlist::addToFav()
{
    if(!checkIfNotFav(a_currentIndex)) //If not there already
    {
        a_player->addFav(a_currentIndex);
        makeStarFull();
    }
}

bool Playlist::checkIfNotFav(int index)
{
    QString fileAdded;
    fileAdded = a_playlist->media(index).canonicalUrl().fileName(); //We extract the filename
    unsigned int mediaCount = a_favPlaylist->mediaCount();
    for(unsigned int i(0); i < mediaCount; i++)
    {
        if(a_favPlaylist->media(i).canonicalUrl().fileName() == fileAdded)
            return true; //It already exists, do not add it
    }
    return false;
}

void Playlist::deleteFav(int index)
{
    QString fileAdded;
    if(!a_player->isUsingFav())
        fileAdded = a_playlist->media(index).canonicalUrl().fileName();
    else
        fileAdded = a_favPlaylist->media(index).canonicalUrl().fileName();
    unsigned int mediaCount = a_favPlaylist->mediaCount();
    for(unsigned int i(0); i < mediaCount; i++)
    {
        if(a_favPlaylist->media(i).canonicalUrl().fileName() == fileAdded)
        {
            if(a_player->isUsingFav())
                a_favPlaylist->setCurrentIndex(i - 1);
            a_favPlaylist->removeMedia(i); //Remove media in fav list, index i
            ui->a_playlistFavWidget->takeItem(i);
        }
    }
}

void Playlist::makeStarFull()
{
    ui->a_addFavStar->setIcon(QIcon(":/Ressources/star_full.png"));
    ui->a_addFavStar->setToolTip(tr("Cliquez pour enlever des favoris"));
}

void Playlist::makeStarEmpty()
{
    ui->a_addFavStar->setIcon(QIcon(":/Ressources/star.png"));
    ui->a_addFavStar->setToolTip(tr("Cliquez pour ajouter aux favoris"));
}

void Playlist::deleteItem()
{
    int index;
    /* Protections against the shortcut */
    if(ui->a_tabWidget->currentIndex() == 0)
        index = ui->a_playlistWidget->currentRow();
    else
        index = ui->a_playlistFavWidget->currentRow();

    if(a_player->deleteMedia(index, ui->a_tabWidget->currentIndex()))
    {
        if(index <= a_queueIndex + a_currentIndex) //So if we're deleting something that was added, we update the queue index
            a_queueIndex--;
        if(ui->a_tabWidget->currentIndex() == 0)
            ui->a_playlistWidget->takeItem(index);
        else
        {
            ui->a_playlistFavWidget->takeItem(index);
            a_player->setFavsToBeSaved(true);
        }
    }
}

void Playlist::deleteItem(int index) //For use when the player is in panic mode.
{
    if(a_player->isUsingFav())
        ui->a_playlistFavWidget->takeItem(index);
    else
        ui->a_playlistWidget->takeItem(index);
    //The rest is handled by the errorhandling in player
}

void Playlist::viewInfo()
{
    if(ui->a_tabWidget->currentIndex() == 0 && ui->a_playlistWidget->currentRow() == a_currentIndex) //If you're selecting the currently playing music
        a_player->showTagViewer();
    else if (ui->a_tabWidget->currentIndex() == 1 && ui->a_playlistFavWidget->currentRow() == a_currentIndex)
        a_player->showTagViewer();
    else //Let's find a workaround to give you info Qt shouldn't let me get !
    {
        a_tempPlayer = new QMediaPlayer(this);
        connect(a_tempPlayer, SIGNAL(metaDataChanged()), this, SLOT(sendNewInfos()));
        a_tempPlayer->setMuted(true); //Don't let the user know that this ugly code is happening
        if(ui->a_tabWidget->currentIndex() == 0)
            a_tempPlayer->setMedia(a_playlist->media(ui->a_playlistWidget->currentRow()));
        else
            a_tempPlayer->setMedia(a_favPlaylist->media(ui->a_playlistFavWidget->currentRow()));
        a_tempPlayer->stop();
    }

}

void Playlist::sendNewInfos()
{
    QList<QString> metaDatas;
    metaDatas.append(a_tempPlayer->metaData("TrackNumber").toString());
    metaDatas.append(a_tempPlayer->metaData("Title").toString());
    metaDatas.append(a_tempPlayer->metaData("ContributingArtist").toString());
    metaDatas.append(a_tempPlayer->metaData("AlbumTitle").toString());
    metaDatas.append(a_tempPlayer->metaData("Year").toString());
    metaDatas.append(a_tempPlayer->metaData("Genre").toString());

    //Load it now !
    QPixmap coverArt = QPixmap::fromImage(QImage(a_tempPlayer->metaData("ThumbnailImage").value<QImage>()));
    QPointer<TagViewer> TagWindow = new TagViewer(metaDatas, &coverArt, this);
    TagWindow->show();
    a_tempPlayer->deleteLater();
}

void Playlist::findItemVisibilityHandler()
{
    if(!a_findItemTrigger->isChecked())
    {
        qDebug() << "I leave";
        ui->a_searchLine->setHidden(true);
        this->removeAction(a_validateFind);
        ui->a_playlistWidget->clear();
        for(int i(0); i < a_backupItems.size(); i++)
        {
            ui->a_playlistWidget->addItem(a_backupItems.at(10));

        }
    }

    else
    {
        qDebug() << "I enter";
        ui->a_searchLine->setVisible(true);
        this->addAction(a_validateFind);
    }
}

void Playlist::saveTheItems()
{
    ui->a_playlistWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->a_playlistWidget->selectAll();
    QList <QListWidgetItem *> list = ui->a_playlistWidget->selectedItems();
    for(int i(0); i < list.size(); i++)
    {
        a_backupItems.append(list.at(i));
    }
}

void Playlist::validateSearch()
{
    saveTheItems();
    QList <QListWidgetItem*> itemsReturned = ui->a_playlistWidget->findItems(ui->a_searchLine->text(), Qt::MatchContains);
    ui->a_playlistWidget->clear();
    for(int i(0); i < itemsReturned.size(); i++)
    {
        ui->a_playlistWidget->addItem(itemsReturned.at(i)->text());
        qDebug() << itemsReturned.at(i)->text();
    }
    qDebug() << itemsReturned.size() << a_backupItems.size();
}

void Playlist::closeEvent(QCloseEvent *)
{
    a_player->setPlaylistOpen(false);
    a_settings.setValue("Playlist/size", this->size());
}

Playlist::~Playlist()
{
    delete ui;

    /* Stop the dangling pointers */
    a_player = nullptr;
    a_playlist = nullptr;
    a_favPlaylist = nullptr;
}
