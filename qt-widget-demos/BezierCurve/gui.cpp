#include "gui.h"
#include "SpNode.h"

using namespace std;

gui::gui(QMainWindow *parent) : QMainWindow(parent){
        //Methode, die die erstellte GUI läd und erstellt.
        setupUi(this);

	connect(button_go, SIGNAL(clicked()), this, SLOT(add_point()));
	
	view_canvas->setScene(&scene_bam);
	view_canvas->show();
}

//Destruktor der Klasse "GUI".
gui::~gui(){
}

