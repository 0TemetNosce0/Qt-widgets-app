/* ---------------------------------- about.cpp ---------------------------------------------------------------------------
      Class to display the about dialog

      ===============================================================================================================================
      ===============================================================================================================================
        This file is part of "luckyBackup" project
        Copyright, Loukas Avgeriou
        luckyBackup is distributed under the terms of the GNU General Public License
        luckyBackup is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.
        
        luckyBackup is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.
        
        You should have received a copy of the GNU General Public License
        along with luckyBackup.  If not, see <http://www.gnu.org/licenses/>.

        project version   : Please see "main.cpp" for project version

        developer         : luckyb 
        last modified     : 04 Mar 2014
      ===============================================================================================================================
      ===============================================================================================================================
*/
#include "about.h"

// class aboutDialog Constructor=================================================================================================
// Displays a simple about dialog
aboutDialog::aboutDialog (QUrl licenseUrl, QDialog *parent) : QDialog (parent)
{
    uiA.setupUi(this);
    //connect okay pushButton SLOTs ----------------
    connect ( uiA.pushButton_ok, SIGNAL( clicked() ), this, SLOT( okay() ) );

    setTop();
    setAbout();
    setAuthor();
    setThanks();
    setLicense(licenseUrl);
    setSupport();
}
// SLOTS-------------------------------------------------------------------------------------
// --------------------------------okay pressed------------------------------------------------
void aboutDialog::okay()
{
    close();
}

// FUNCTIONS-------------------------------------------------------------------------------------
void aboutDialog::setTop()
{
    Text = appName+" "+ appVersionString;
    uiA.label_Top -> setText(Text);
}
void aboutDialog::setAbout()
{
    uiA.textBrowser_About -> setOpenLinks(TRUE);
    uiA.textBrowser_About -> setOpenExternalLinks(TRUE);

    Text = 	"<p align=\"center\"><b>"+appName + " " + appVersionString +"</b> ("+
        tr("using Qt4")+")" + "<br>" +
        tr("Backup & Sync Application")+"<br><br>"

        "(C) 2008-2014,	"+
        tr("Loukas Avgeriou") +"<br><br>"

        "web:<br>"
        "<a href=\"http://luckybackup.sourceforge.net/\" target=\"_blank\">http://luckybackup.sourceforge.net/</a> <br>"
        "<a href=\"http://www.kde-apps.org/content/show.php/luckyBackup?content=94391\" target=\"_blank\">http://www.kde-apps.org/</a> <br><br>"

        "<a href=\"http://www.gnu.org/copyleft/gpl.html\" target=\"_blank\"><img name=\"gpl\""
        " src=\":/luckyPrefix/gplv3-127x51.png\" width=\"60\" height=\"20\" border=\"0\"></a>&nbsp;&nbsp;"+
        tr("luckyBackup is distributed under the terms of the <a href=\"http://www.gnu.org/copyleft/gpl.html\" target=\"_blank\">GNU General Public License</a>","Please leave the tags <a href=\"http://www.gnu.org/copyleft/gpl.html\" target=\"_blank\"> & </a> intact and surrounding the GNU General Public License !!") +".<br><br>" +

        tr("It is <b>free software</b>: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 of the License.","Please leave tags eg <b>, </b> intact and surrounding the words they are suppossed to !!") +"<br>" +
        tr("It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.")+ "<br>" +
        tr("See the 'License Agreement' tab for more details.")+"</p>";

    uiA.textBrowser_About -> setText(Text);
}
void aboutDialog::setAuthor()
{
    uiA.textBrowser_Author -> setOpenLinks(TRUE);
    uiA.textBrowser_Author -> setOpenExternalLinks(TRUE);

    Text =	"<p align=\"center\"><br><img name=\"luckyb\" src=\":/luckyPrefix/luckyb.png\" width=\"80\" height=\"80\" border=\"0\"><b><br><br>"+
        tr("Loukas Avgeriou") +"</b> (luckyb)<br>"+
        tr("Athens, Greece") +
        "<br><br><a href=\"mailto:luckyb69@users.sourceforge.net\">luckyb69@users.sourceforge.net</a></p>";
    uiA.textBrowser_Author -> setText(Text);
}
void aboutDialog::setThanks()
{
    uiA.textBrowser_Thanks -> setOpenLinks(TRUE);
    uiA.textBrowser_Thanks -> setOpenExternalLinks(TRUE);

    Text =	"<p align=\"center\"><b>" + tr("Tom Tryfonidis") + "</b><br>(thanos)<br>" +
        tr("Arch linux package/pkgbuild official maintainer (AUR)") + "<br>" +
        tr("Greek manual translator") + "<br>" +
        tr("Valuable advisor") + "<br><br>"

        "<b>" + tr("Yiorgos Kapellakis") + "</b><br>(slackware)<br>" +
        tr("rpm packager, valuable tester and remote connections advisor") + "<br><br>"

        "<b>" + tr("Patrick Matthaei") + "</b><br>(Debian Developer)<br>" +
        tr("Debian package maintainer") + "<br><br>"
        
        "<b>" + tr("Nikolas Poniros") + "</b><br>(edhunter)<br>" +
        tr("Greek gui translator and valuable tester") + "<br><br>"

        "<b>" + tr("Dimitris Kalamaras") + "</b><br>(dimitris)<br>" +
        tr("If it wasn't him and his tutorials I would never have started this project") + "<br><br>"
        
        "<b><a href=\"http://www.indifex.com/#team\" TARGET=\"_blank\">" + tr("The indifex team") + "</b></a><br>" +
        tr("for developing the wonderful transifex localization platform and providing it for free") + "<br><br>"
    
        "<b>" + tr("Stephan Kleine") + "</b><br>" +
        tr("OpenSUSE package maintainer (KDE4 Community repo) and valuable packing advisor") + "<br><br>"

        "<b>" + tr("Marcos Del Puerto Garcia") + "</b><br>" +
        tr("Mepis package maintainer (Community repo) & Spanish gui translator") + "<br><br>"

        "<b>" + tr("Savvas Radevic") + "</b><br>" +
        tr("ubuntu package maintainer (launchpad PPA)") + "<br><br>"

        "<b>" + tr("Bruce Marriner") + "</b><br>" +
        tr("port to MS Windows") + "<br><br>"
        
        "<b>" + tr("Juan Ramon Alfaro Martinez") + "</b><br>" +
        tr("Code contributor for remote & vss support regarding the windows port") + "<br><br>"
        
        "<b>" + tr("Jack Fink") + "</b><br>" +
        tr("port to Mac OS X") + "<br><br>"
        
        "<b>" + tr("Elbert Pol") + "</b><br>" +
        tr("port to OS/2") + "<br><br>"

        "<b>" + tr("Theo Chatzimichos") + "</b><br>" +
        tr("Gentoo ebuild maintainer") + "<br><br>"
        
        "<b>" + tr("Dimitris Stasinopoulos") + "</b><br>(alfisti)<br>" + 
        tr("Puppy pet & sfs maintainer") + "<br><br>"
        
        "<b>" + tr("Juan Luis Baptiste") + "</b><br>" +
        tr("Mandriva package maintainer (official contrib repo)") + "<br><br>"

        "<b>" + tr("Michael J Gruber") + "</b><br>" +
        tr("Fedora package maintainer (official repo)") + "<br><br>"
        
        "<b>" + tr("Jason E. Hale") + "</b><br>" +
        tr("Free BSD package maintainer") + "<br><br>"
        
        "<b>" + tr("Dimitris Jemos") + "</b><br>" +
        tr("Slackel package maintainer") + "<br><br>"
        
        "<b>" + tr("Thomas Janssen") + "</b><br>" +
        tr("ex Fedora package maintainer") + "<br><br>"

        "<b>" + tr("Pavel Fric") + "</b><br>" +
        tr("Czech gui translator") + "<br><br>"

        "<b>" + tr("Stergios Prosiniklis") + "</b><br>" +
        tr("Greek manual translator") + "<br><br>"
        
        "<b>" + tr("Karsten Jaschultowski") + "</b><br>" +
        tr("German gui translator") + "<br><br>"

        "<b>" + tr("Wilfried Schobel") + "</b><br>" +
        tr("German gui translator") + "<br><br>"
        
        "<b>" + tr("Thomas Glatt") + "</b><br>" +
        tr("German gui translator") + "<br><br>"

        "<b>" + tr("Sergio Gameiro") + "</b><br>" +
        tr("Portuguese gui translator") + "<br><br>"

        "<b>" + tr("Marcio Moraes") + "</b><br>" +
        tr("Portuguese gui translator") + "<br><br>"

        "<b>" + tr("Julien Cynober") + "</b><br>" +
        tr("French gui translator and valuable packing advisor (and not only)") + "<br><br>"
        
        "<b>" + tr("Aurelien Merckel") + "</b><br>" +
        tr("French gui translator") + "<br><br>"

        "<b>" + tr("Sébastien Bourgain") + "</b><br>" +
        tr("French gui translator") + "<br><br>"
        
        "<b>" + tr("Francesco Braile") + "</b><br>" +
        tr("Italian gui translator") + "<br><br>"
        
        "<b>" + tr("Raffaele") + "</b><br>" +
        tr("Italian gui translator") + "<br><br>"
        
        "<b>" + tr("pinguinofurioso") + "</b><br>" +
        tr("Italian gui translator") + "<br><br>"
        
        "<b>" + tr("Alessio Ganci") + "</b><br>" +
        tr("Italian gui translator") + "<br><br>"
        
        "<b>" + tr("Denis Skorski") + "</b><br>" + "<a href=\"http://fripohled.blogspot.com/\" TARGET=\"_blank\">fripohled.blogspot.com</a><br>" +
        tr("Russian gui translator and valuable tester") + "<br><br>"

        "<b>" + tr("Kenny Verstraete") + "</b><br>" +
        tr("Dutch gui translator") + "<br><br>"

        "<b>" + tr("Martin Grashoff (linuxrev)") + "</b><br>" +
        tr("Dutch gui translator") + "<br><br>"
        
        "<b>" + tr("Subhi Honaco") + "</b><br>" +
        tr("Bosnian gui translator & mandriva package maintainer") + "<br><br>"

        "<b>" + tr("Majed Sahli") + "</b><br>" +
        tr("Arabic gui translator") + "<br><br>"

        "<b>" + tr("Adrian Murariu") + "</b><br>" +
        tr("Romanian gui translator") + "<br><br>"

        "<b>" + tr("Andrej Znidarsic") + "</b><br>" +
        tr("Slovenian gui translator") + "<br><br>"
        
        "<b>" + tr("Matej Urbančič") + "</b><br>" +
        tr("Slovenian gui translator") + "<br><br>"
        
        "<b>" + tr("E. Hakan Duran") + "</b><br>" +
        tr("Turkish gui translator") + "<br><br>"
        
        "<b>" + tr("Marvin Gomez") + "</b><br>" +
        tr("Spanish gui translator") + "<br><br>"

        "<b>" + tr("Antonio Jose Molina") + "</b><br>" +
        tr("Spanish gui translator") + "<br><br>"
        
        "<b>" + tr("Fredrik Holmgren") + "</b><br>" +
        tr("Swedish gui translator") + "<br><br>"
        
        "<b>" + tr("Roger Calvo") + "</b><br>" +
        tr("Catalan gui translator") + "<br><br>"
        
        "<b>" + tr("Tomas Vadina") + "</b><br>" +
        tr("Slovak gui translator") + "<br><br>"
        
        "<b>" + tr("Rivo Zangov") + "</b><br>" +
        tr("Estonian gui translator") + "<br><br>"
        
        "<b>" + tr("Nicolay Boychev") + "</b><br>" +
        tr("Bulgarian gui translator") + "<br><br>"
        
        "<b>" + tr("Manuel Meixide") + "</b><br>" +
        tr("Galician gui translator") + "<br><br>"
        
        "<b>" + tr("Roger Foss") + "</b><br>" +
        tr("Norwegian gui translator") + "<br><br>"
        
        "<b>" + tr("Pin-hsien Li") + "</b><br>" +
        tr("Chinese (Taiwan) gui translator") + "<br><br>"
        
        "<b>" + tr("Javi Romero") + "</b><br>" +
        tr("v0.3 gui designer") + "<br><br>"

        "<b>" + tr("fri13") + "</b><br>" +
        tr("v.0.3 gui designer") + "<br><br>" +

        "<b>" + tr("Tito Poquito") + "</b><br>" +
        tr("slackware package maintainer (SlackBuilds Repository)") + "<br><br>" +
        
        "<b>" + tr("Michele Dall'Arno") + "</b><br>" +
        tr("special guest bug killer ;)") + "<br><br>" +
        
        "<b>" + tr("Aphofis Scott") + "</b><br>" +
        tr("valuable tester & brainstorming specialist") + "<br><br>" +

        "<b>" + tr("Yuri Vidal") + "</b><br>" +
        tr("backupwhenidle python script developer") + "<br><br>" +

        "<b>" + tr("Bjorn Rietdijk") + "</b><br>" +
        tr("valuable OS/2 and windows tester") + "<br><br>" +
        
        tr("...to all users of the ")+
        "<br><a href=\"http://www.linuxinside.gr/\" target=\"_blank\">Linux Inside</a>, "
        "<a href=\"http://www.aptosid.com/\" target=\"_blank\">aptosid.com</a>, "
        "<a href=\"http://www.aptosid.gr/\" target=\"_blank\">aptosid.gr</a>, "
        "<a href=\"http://forum.ubuntu-gr.org/\" target=\"_blank\">ubuntu.gr</a>, "
        "<a href=\"http://forum.hellug.gr/\" target=\"_blank\">hellug</a>, "
        "and <a href=\"http://www.kde-apps.org//\" target=\"_blank\">kde-apps.org</a><br>" +
        tr("forums for their support.") + "<br><br>" +
        tr("Especially") + "<br>constantinos, promeneur, grigris, dannys,marios, Regenwald, flo, Ilias Paraponiaris, Takis Vounatsos, Lieven Tytgat, mathetes, Johan Linde, Chris Sylvester, Manos Nikiforakis, Giorgos Katsikatsos, Ray Ambrosi, Barry Jackson, Damien Cassou, Carsten, Daniele Soldati Chris (slam), Paul Chapman, kingfame, Giorgos 'jeff' Finikianakis, Shelby Williams, Felix, skevo, Philipp F, Christian Harms, Paul Hewlett, Tristan Gross, Fabian Muscariello, James Mohr, Julie Pierson, Peter, Michael Daffin and Kate Draven<br>" +
        tr("that contributed to this project one way or another") + "<br><br>" +

        tr("Last but no least") +":<br>"+
        tr("...my other half, <b>Dimitra</b> that bears with me all these times that this project is under development") + " :-)<br></p>";
    uiA.textBrowser_Thanks-> setText(Text);;
}
void aboutDialog::setLicense(QUrl licenseUrl)
{
    uiA.textBrowser_License -> setOpenLinks(TRUE);
    uiA.textBrowser_License -> setOpenExternalLinks(TRUE);

    licenseUrl.setScheme("file");

    if (licenseUrl.toString(QUrl::RemoveScheme) == "Does_not_exist")
        uiA.textBrowser_License -> setText(tr("Could not locate the license file") + "!!");
    else
        uiA.textBrowser_License -> setSource(licenseUrl);

}

void aboutDialog::setSupport()
{
    uiA.textBrowser_Support -> setOpenLinks(TRUE);
    uiA.textBrowser_Support -> setOpenExternalLinks(TRUE);

    Text = 	"<p align=\"left\"><b>" + tr("no money") + "</b><br><br>" +
    tr("If you like this app and would like to donate something to me personally, all you have to do is:") + "<ul><li>" +
    tr("Give a thumbs up at:") +
    " <a href=\"http://sourceforge.net/projects/luckybackup/\" target=\"_blank\">sourceforge.net</a></li><li>" +
    tr("Vote good & become a fan at:") +
    " <a href=\"http://www.kde-apps.org/content/show.php/luckyBackup?content=94391\" target=\"_blank\">kde-apps.org</a></li></ul>" +
    tr("This is my reward :)")
    
    + "<br>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<br><b>" + tr("money") + "</b><br><br>" + 
    tr("I personally never had and never will accept money for this project.") + "<br>" +
    tr("Nevertheless, I decided to use luckyBackup to support people that really need financial help.") + "<br>" +
    tr("So, please consider it seriously to donate money that will eventually be used for a good cause.") + 
    "<br><br><a href=\"http://luckybackup.sourceforge.net/donate.html\" target=\"_blank\"><b>" +
    tr("donation link") + "</b></a></p>";

    uiA.textBrowser_Support -> setText(Text);
}
// end of about.cpp ---------------------------------------------------------------------------

