#include "MainWindow.h"

#include <dwmapi.h>
#include <windowsx.h>
#include <stdexcept>

#include <QPushButton>
#include <QFile>

HWND winId = 0;

QMainPanel *BorderlessWindow::mainPanel;
QApplication *BorderlessWindow::a;

BorderlessWindow::BorderlessWindow( QApplication *app, HBRUSH windowBackground, const int x, const int y, const int width, const int height ) : hWnd( 0 ),
  hInstance( GetModuleHandle( NULL ) ),
  borderless( false ),
  borderlessResizeable( true ),
  aeroShadow( false ),
  closed( false ),
  visible( false )
{
  WNDCLASSEX wcx = { 0 };
  wcx.cbSize = sizeof( WNDCLASSEX );
  wcx.style = CS_HREDRAW | CS_VREDRAW;
  wcx.hInstance = hInstance;
  wcx.lpfnWndProc = WndProc;
  wcx.cbClsExtra	= 0;
  wcx.cbWndExtra	= 0;
  wcx.lpszClassName = L"WindowClass";
  wcx.hbrBackground = windowBackground;
  wcx.hCursor = LoadCursor( hInstance, IDC_ARROW );
  RegisterClassEx( &wcx );
  if ( FAILED( RegisterClassEx( &wcx ) ) ) throw std::runtime_error( "Couldn't register window class" );

  hWnd = CreateWindow( L"WindowClass", L"BorderlessWindow", static_cast<DWORD>( Style::windowed ), x, y, width, height, 0, 0, hInstance, nullptr );

  if ( !hWnd ) throw std::runtime_error( "Couldn't create window because of reasons" );

  SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( this ) );

  mainPanel = new QMainPanel( hWnd );
  winId = ( HWND )mainPanel->winId();
  
  show();

  toggleBorderless();

  a = app;
}

BorderlessWindow::~BorderlessWindow()
{
  hide();
  DestroyWindow( hWnd );
}

HDC hdc;
PAINTSTRUCT ps;

LRESULT CALLBACK BorderlessWindow::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  BorderlessWindow *window = reinterpret_cast<BorderlessWindow*>( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
  if ( !window ) return DefWindowProc( hWnd, message, wParam, lParam );

  switch ( message ) {
    case WM_KEYDOWN: {
      switch ( wParam ) {
        case VK_F5: {
          window->borderlessResizeable = !window->borderlessResizeable;
          break;
        }
        case VK_F6: {
          window->toggleShadow();
          window->toggleBorderless();
          SetFocus( winId );
          break;
        }
        case VK_F7: {
          window->toggleShadow();
          break;
        }
      }

      if ( wParam != VK_TAB ) return DefWindowProc( hWnd, message, wParam, lParam );

      SetFocus( winId );
      break;
    }

    // ALT + SPACE
    case WM_SYSKEYDOWN: {
      if ( wParam == VK_SPACE) {
        HMENU hMenu = GetSystemMenu( hWnd, FALSE );
        if ( hMenu )
        {
          MENUITEMINFO mii;
          mii.cbSize = sizeof( MENUITEMINFO );
          mii.fMask = MIIM_STATE;
          mii.fType = 0;

          mii.fState = MF_ENABLED;
          SetMenuItemInfo( hMenu, SC_RESTORE, FALSE, &mii );
          SetMenuItemInfo( hMenu, SC_SIZE, FALSE, &mii );
          SetMenuItemInfo( hMenu, SC_MOVE, FALSE, &mii );
          SetMenuItemInfo( hMenu, SC_MAXIMIZE, FALSE, &mii );
          SetMenuItemInfo( hMenu, SC_MINIMIZE, FALSE, &mii );

          mii.fState = MF_GRAYED;

          WINDOWPLACEMENT wp;
          GetWindowPlacement( hWnd, &wp );

          switch ( wp.showCmd ) {
            case SW_SHOWMAXIMIZED:
              SetMenuItemInfo( hMenu, SC_SIZE, FALSE, &mii );
              SetMenuItemInfo( hMenu, SC_MOVE, FALSE, &mii );
              SetMenuItemInfo( hMenu, SC_MAXIMIZE, FALSE, &mii );
              SetMenuDefaultItem( hMenu, SC_CLOSE, FALSE );
              break;
            case SW_SHOWMINIMIZED:
              SetMenuItemInfo( hMenu, SC_MINIMIZE, FALSE, &mii );
              SetMenuDefaultItem( hMenu, SC_RESTORE, FALSE );
              break;
            case SW_SHOWNORMAL:
              SetMenuItemInfo( hMenu, SC_RESTORE, FALSE, &mii );
              SetMenuDefaultItem( hMenu, SC_CLOSE, FALSE );
              break;
            }

            RECT winrect;
            GetWindowRect( hWnd, &winrect );

            LPARAM cmd = TrackPopupMenu( hMenu, (TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD ),
                                        winrect.left, winrect.top, NULL, hWnd, NULL );

            if ( cmd ) PostMessage( hWnd, WM_SYSCOMMAND, cmd, 0 );
        }
        return 0;
      }
      return DefWindowProc( hWnd, message, wParam, lParam );
    }

    case WM_COMMAND: {
      SendMessage( hWnd, WM_SYSCOMMAND, wParam, lParam );
      return DefWindowProc( hWnd, message, wParam, lParam );
    }

    case WM_SETFOCUS: {
      SetFocus( winId );
      break;
    }

    case WM_NCCALCSIZE: {
      //this kills the window frame and title bar we added with
      //WS_THICKFRAME and WS_CAPTION
      if ( window->borderless ) {
          return 0;
      }
      break;
    }

    case WM_DESTROY: {
      delete( mainPanel );
      PostQuitMessage(0);
      break;
    }

    case WM_NCHITTEST: {
      if ( window->borderless )
      {
        if ( window->borderlessResizeable )
        {
          const LONG borderWidth = 8; //in pixels
          RECT winrect;
          GetWindowRect( hWnd, &winrect );
          long x = GET_X_LPARAM( lParam );
          long y = GET_Y_LPARAM( lParam );

          //bottom left corner
          if ( x >= winrect.left && x < winrect.left + borderWidth &&
            y < winrect.bottom && y >= winrect.bottom - borderWidth )
          {
            return HTBOTTOMLEFT;
          }
          //bottom right corner
          if ( x < winrect.right && x >= winrect.right - borderWidth &&
            y < winrect.bottom && y >= winrect.bottom - borderWidth )
          {
            return HTBOTTOMRIGHT;
          }
          //top left corner
          if ( x >= winrect.left && x < winrect.left + borderWidth &&
            y >= winrect.top && y < winrect.top + borderWidth )
          {
            return HTTOPLEFT;
          }
          //top right corner
          if ( x < winrect.right && x >= winrect.right - borderWidth &&
            y >= winrect.top && y < winrect.top + borderWidth )
          {
            return HTTOPRIGHT;
          }
          //left border
          if ( x >= winrect.left && x < winrect.left + borderWidth )
          {
            return HTLEFT;
          }
          //right border
          if ( x < winrect.right && x >= winrect.right - borderWidth )
          {
            return HTRIGHT;
          }
          //bottom border
          if ( y < winrect.bottom && y >= winrect.bottom - borderWidth )
          {
            return HTBOTTOM;
          }
          //top border
          if ( y >= winrect.top && y < winrect.top + borderWidth )
          {
            return HTTOP;
          }
        }

        return HTCAPTION;
      }
      break;
    }

    case WM_SIZE: {
      RECT winrect;
      GetClientRect( hWnd, &winrect );

      WINDOWPLACEMENT wp;
      wp.length = sizeof( WINDOWPLACEMENT );
      GetWindowPlacement( hWnd, &wp );
      if ( wp.showCmd == SW_MAXIMIZE ) {
        QPushButton* pushButtonMaximize = mainPanel->findChild<QPushButton*>( "pushButtonMaximize" );
        pushButtonMaximize->setStyleSheet( "#pushButtonMaximize {image: url(:/SystemMenu/Icons/Restore.png);} #pushButtonMaximize:hover { image: url(:/SystemMenu/Icons/RestoreHover.png); }" );
        mainPanel->setGeometry( 16, 16, winrect.right - 32, winrect.bottom - 32 );
      } else {
        QPushButton* pushButtonMaximize = mainPanel->findChild<QPushButton*>( "pushButtonMaximize" );
        pushButtonMaximize->setStyleSheet( "#pushButtonMaximize {image: url(:/SystemMenu/Icons/Maximize.png);} #pushButtonMaximize:hover { image: url(:/SystemMenu/Icons/MaximizeHover.png); }" );
        mainPanel->setGeometry( 8, 8, winrect.right - 16, winrect.bottom - 16 );
      }
      return DefWindowProc(hWnd, message, wParam, lParam);
    }

    case WM_GETMINMAXINFO: {
      MINMAXINFO* minMaxInfo = ( MINMAXINFO* )lParam;
      if ( window->minimumSize.required ) {
        minMaxInfo->ptMinTrackSize.x = window->getMinimumWidth();;
        minMaxInfo->ptMinTrackSize.y = window->getMinimumHeight();
      }

      if ( window->maximumSize.required ) {
        minMaxInfo->ptMaxTrackSize.x = window->getMaximumWidth();
        minMaxInfo->ptMaxTrackSize.y = window->getMaximumHeight();
      }
      return 0;
    }
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

void BorderlessWindow::toggleBorderless() {
  if ( visible )
  {
    Style newStyle = ( borderless ) ? Style::windowed : Style::aero_borderless;
    SetWindowLongPtr( hWnd, GWL_STYLE, static_cast<LONG>( newStyle ) );

    borderless = !borderless;
    if ( newStyle == Style::aero_borderless ) {
      toggleShadow();
    }
    //redraw frame
    SetWindowPos( hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE );
    show();
  }
}

void BorderlessWindow::toggleShadow() {
  if ( borderless ) {
    aeroShadow = !aeroShadow;
    const MARGINS shadow_on = { 1, 1, 1, 1 };
    const MARGINS shadow_off = { 0, 0, 0, 0 };
    DwmExtendFrameIntoClientArea( hWnd, ( aeroShadow ) ? ( &shadow_on ) : ( &shadow_off ) );
  }
}

void BorderlessWindow::toggleResizeable() {
  borderlessResizeable = borderlessResizeable ? false : true;
}

bool BorderlessWindow::isResizeable() {
  return borderlessResizeable ? true : false;
}

void BorderlessWindow::show() {
  ShowWindow( hWnd, SW_SHOW );
  visible = true;
}

void BorderlessWindow::hide() {
  ShowWindow( hWnd, SW_HIDE );
  visible = false;
}

bool BorderlessWindow::isVisible() {
  return visible ? true : false;
}

// Minimum size
void BorderlessWindow::setMinimumSize( const int width, const int height ) {
  this->minimumSize.required = true;
  this->minimumSize.width = width;
  this->minimumSize.height = height;
}

bool BorderlessWindow::isSetMinimumSize() {
    return this->minimumSize.required;
}

void BorderlessWindow::removeMinimumSize() {
  this->minimumSize.required = false;
  this->minimumSize.width = 0;
  this->minimumSize.height = 0;
}

int BorderlessWindow::getMinimumWidth() {
  return minimumSize.width;
}

int BorderlessWindow::getMinimumHeight() {
  return minimumSize.height;
}

// Maximum size
void BorderlessWindow::setMaximumSize( const int width, const int height ) {
  this->maximumSize.required = true;
  this->maximumSize.width = width;
  this->maximumSize.height = height;
}

bool BorderlessWindow::isSetMaximumSize() {
  return this->maximumSize.required;
}

void BorderlessWindow::removeMaximumSize() {
  this->maximumSize.required = false;
  this->maximumSize.width = 0;
  this->maximumSize.height = 0;
}

int BorderlessWindow::getMaximumWidth() {
  return maximumSize.width;
}

int BorderlessWindow::getMaximumHeight() {
  return maximumSize.height;
}

