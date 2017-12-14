

#include <qapplication.h>
#include <qdir.h>
#include <qevent.h>
#include <qfileinfo.h>
#include <qimage.h>
#include <QDebug>

#include <QTime>


#include "pictureflow.h"

QStringList findFiles(const QString& path = QString())
{
  QStringList files;

  QDir dir = QDir::current(); /*返回应用程序当前目录*/
  if(!path.isEmpty())
    dir = QDir(path);
qDebug()<<dir;
  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

  QFileInfoList list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) 
  {
    QFileInfo fileInfo = list.at(i);
    files.append(dir.absoluteFilePath(fileInfo.fileName()));
  }

  return files;
}



class Browser: public PictureFlow
{
public:
  Browser(): PictureFlow()
  {
    setWindowTitle("PictureFlow");
  }

  void keyPressEvent(QKeyEvent* event)
  {
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_Enter || 
		event->key() == Qt::Key_Return)
      {
        event->accept();
        close();
      }

    //// checking the speed of rendering
    //if(event->key() == Qt::Key_F10)
    //if(event->modifiers() == Qt::AltModifier)
    //{
    //  qDebug("benchmarking.... please wait");
    //  const int blit_count = 10;

    //  QTime stopwatch;
    //  stopwatch.start();
    //  for(int i = 0; i < blit_count; i++)
    //  {
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //    render(); repaint(); QApplication::flush(); QApplication::syncX();
    //  }
    //  QString msg;
    //  int elapsed = stopwatch.elapsed();
    //  if( elapsed > 0 )
    //    msg = QString("FPS: %1").arg( blit_count*10*1000.0/elapsed );
    //  else
    //    msg = QString("Too fast. Increase blit_count");
    //  setWindowTitle( msg );
    //  event->accept();
    //  return;
    //}

    // for debugging only: Alt+F11 cycles the reflection effect
    if(event->key() == Qt::Key_F11)
    if(event->modifiers() == Qt::AltModifier)
    {
      qDebug("changing reflection effect...");
      switch(reflectionEffect())
      {
        //case NoReflection:      setReflectionEffect(PlainReflection); break;
        case PlainReflection:   setReflectionEffect(BlurredReflection); break;
        case BlurredReflection: setReflectionEffect(PlainReflection); break;
        default:                setReflectionEffect(PlainReflection); break;
      }
      event->accept();
      return;
    }

    PictureFlow::keyPressEvent(event);  
  }
};  

int main( int argc, char ** argv )
{
  QApplication* app = new QApplication( argc, argv );
  Browser* w = new Browser;

//
  w->setSlideSize(QSize(3*40, 5*40));//设置显示图片的大小
  w->resize(750, 270);//设置程序框架的大小


  QStringList files = (argc > 1) ? findFiles(QString(argv[1])) : findFiles();

  QImage img;
  for(int i = 0; i < (int)files.count(); i++)
    if(img.load(files[i]))
      w->addSlide(img);

  w->setCenterIndex(w->slideCount()/2);
  w->setBackgroundColor(Qt::white);//设置背景颜色
  w->show();

  app->connect( app, SIGNAL(lastWindowClosed()), app, SLOT(quit()) );
  int result = app->exec();

  delete w;
  delete app;

  return result;
}
