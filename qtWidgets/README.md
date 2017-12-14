# qtWidgets
[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Platform](https://img.shields.io/badge/platform-Qt-green.svg)](http://qt.io)

this is a small collection of custom Qt widgets.  Included here are:

| widget | screenshot |
| --- | :---: |
| The **QAnimatedTimer** provides a "hourglass"-like animation that displays time elapsed and can automatically change its color at predefined time to indicate processes that take longer than expected.  Number of dots is adjustable.  Additionally, it can either switch on/off or fade in/out for smoother transitions. | <img src="https://raw.githubusercontent.com/rom-p/qtWidgets/master/doc/atimer.gif" width="80px" height="80px" /> |
| The **QVUMeter** provides a vertical VU Meter (or volume meter) similar to indicators that can be found on professional or semi-professional audio hardware.  The size of the dots, the range and yellow-red thresholds are adjustable.  It can be dimmed to indicate inactivity.  User can mark a point to indicate, for example, a threshold level. | ![QVUMeter screenshot](https://raw.githubusercontent.com/rom-p/qtWidgets/master/doc/vumeter.gif) |


## using in a project
these controls can be independently added to your project.  Just #include the header and make sure the relevant .cpp file is compiled as part of your project.  There are no external dependencies, other than Qt itself.  The widgets have been tested with Qt 4.x and Qt 5.x.  Linux, Windows and Mac platforms are supported.

## sample app
the sample application is included: look under sampleApp directory

### building the sample app
* make sure Qt and compilers are installed:
** **Ubuntu**: ```sudo apt-get install qt make gcc```
** **CentOS** and **Fedora**: ```sudo yum install qt make gcc```
** **Fedora 23+**: ```sudo dnf install qt make gcc```
** **Windows**: install the dev package from the Qt site
** **Mac**: install the dev package from the Qt site
* cd to the directory with the .pro file
* ```qmake```
* ```make```

