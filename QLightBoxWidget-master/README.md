QLightBoxWidget
=============

QLightBoxWidget is the Qt desktop widget analog javascript LightBox.

![Screenshot](http://dimkanovikov.pro/img/content/projects/qlightboxwidget/1.png)

Using:
-------------

Use QLightBoxWidget - it's easy. First you need to create instance and configure it:

```cpp
//
// Create instance
//
QLightBoxWidget* lightBox = new QLightBoxWidget(this);

//
// Create widgets that lightBox must contain
//
QLabel* lbTitle = new QLabel(tr("QLightBoxWidget"));
lbTitle->setStyleSheet("font-size: 28px; font-weight: bold; color: white");
// ... 
QPushButton* lbClose = new QPushButton(tr("Close"));
//
// ... layout
//
QGridLayout* lbLayout = new QGridLayout;
lbLayout->addWidget(lbTitle, 1, 1);
// ...
lightBox->setLayout(lbLayout);
//
// ... and configure them
//
connect(lbClose, SIGNAL(clicked()), lightBox, SLOT(hide()));
```

And when you need show it, just do that:

```cpp
QPushButton* showLB = new QPushButton(tr("Show"));
connect(showLB, SIGNAL(clicked()), lightBox, SLOT(show()));

// or

lightBox->show();
```

Build
-------------

Qt 4.6 and greater, or Qt 5.0 and greater

License
-------------

[GNU LGPL v3](http://www.gnu.org/copyleft/lesser.html)