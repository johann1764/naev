/*
 * See Licensing and Copyright notice in naev.h
 */
#pragma once

/** @cond */
#include "naev.h"
#include <SDL3/SDL_keycode.h>
/** @endcond */

#include "tk/widget.h"

/*
 * Colours to use.
 */
extern const glColour *toolkit_colLight;
extern const glColour *toolkit_col;
extern const glColour *toolkit_colDark;

extern const glColour *tab_active;
extern const glColour *tab_activeB;
extern const glColour *tab_inactive;
extern const glColour *tab_inactiveB;
extern const glColour *tab_background;

/**
 * @typedef WidgetType
 *
 * @brief Represents the widget types.
 */
typedef enum WidgetType_ {
   WIDGET_NULL,
   WIDGET_BUTTON,
   WIDGET_TEXT,
   WIDGET_IMAGE,
   WIDGET_LIST,
   WIDGET_RECT,
   WIDGET_CUST,
   WIDGET_INPUT,
   WIDGET_IMAGEARRAY,
   WIDGET_FADER,
   WIDGET_TABBEDWINDOW,
   WIDGET_CHECKBOX
} WidgetType;

/**
 * @typedef WidgetStatus
 *
 * @brief Represents widget status.
 *
 * Only really used by buttons.
 */
typedef enum WidgetStatus_ {
   WIDGET_STATUS_NORMAL,
   WIDGET_STATUS_MOUSEOVER,
   WIDGET_STATUS_MOUSEDOWN,
   WIDGET_STATUS_SCROLLING
} WidgetStatus;

#define WGT_FLAG_CANFOCUS ( 1 << 0 ) /**< Widget can get focus. */
#define WGT_FLAG_RAWINPUT                                                      \
   ( 1 << 1 ) /**< Widget should always get raw input.                         \
               */
#define WGT_FLAG_ALWAYSMMOVE                                                   \
   ( 1 << 2 ) /**< Widget should always get mouse motion events. */
#define WGT_FLAG_FOCUSED ( 1 << 3 ) /**< Widget is focused. */
#define WGT_FLAG_DYNAMIC ( 1 << 4 ) /**< Widget should dynamically render. */
#define WGT_FLAG_KILL ( 1 << 9 )    /**< Widget should die. */
#define wgt_setFlag( w, f )                                                    \
   ( ( w )->flags |= ( f ) ) /**< Sets a widget flag. */
#define wgt_rmFlag( w, f )                                                     \
   ( ( w )->flags &= ~( f ) ) /**< Removes a widget flag. */
#define wgt_isFlag( w, f )                                                     \
   ( ( w )->flags & ( f ) ) /**< Checks if a widget has a fla.g */

/**
 * @struct Widget
 *
 * @brief Represents a widget.
 */
typedef struct Widget_ {
   struct Widget_ *next; /**< Linked list. */

   /* Basic properties. */
   char      *name; /**< Widget's name. */
   WidgetType type; /**< Widget's type. */
   int        id;   /**< Widget ID. */

   /* Inheritance. */
   unsigned int wdw; /**< Widget's parent window. */

   /* Position and dimensions. */
   int x; /**< X position within the window. */
   int y; /**< Y position within the window. */
   int w; /**< Widget width. */
   int h; /**< Widget height. */

   unsigned int flags; /**< Widget flags. */

   /* Event abstraction. */
   int ( *keyevent )(
      struct Widget_ *wgt, SDL_Keycode key, SDL_Keymod mod,
      int isrepeat ); /**< Key event handler function for the widget. */
   int ( *textevent )(
      struct Widget_ *wgt,
      const char *text ); /**< Text event function handler for the widget. */
   int ( *mmoveevent )(
      struct Widget_ *wgt, int x, int y, int rx,
      int ry ); /**< Mouse movement handler function for the widget. */
   int ( *mclickevent )(
      struct Widget_ *wgt, int button, int x,
      int y ); /**< Mouse click event handler function for the widget. */
   int ( *mdoubleclickevent )( struct Widget_ *wgt, int button, int x,
                               int y ); /**< Double-click handler, bypassing the
                                           click handler if provided. */
   int ( *mwheelevent )(
      struct Widget_ *wgt,
      SDL_MouseWheelEvent
         event ); /**< Mouse click event handler function for the widget. */
   void ( *scrolldone )( struct Widget_ *wgt ); /**< Scrolling is over. */
   int ( *rawevent )(
      struct Widget_ *wgt,
      SDL_Event      *event ); /**< Raw event handler function for widget. */
   void ( *exposeevent )( struct Widget_ *wgt,
                          int exposed ); /**< Widget show and hide handler. */

   /* Misc. routines. */
   void ( *render )( struct Widget_ *wgt, double x,
                     double y ); /**< Render function for the widget. */
   void ( *renderDynamic )(
      struct Widget_ *wgt, double x,
      double y ); /**< Dynamic render function for the widget. */
   void ( *renderOverlay )(
      struct Widget_ *wgt, double x,
      double y ); /**< Overlay render fuction for the widget. */
   void ( *cleanup )(
      struct Widget_ *wgt ); /**< Clean up function for the widget. */
   void ( *focusGain )( struct Widget_ *wgt ); /**< Get focus. */
   void ( *focusLose )( struct Widget_ *wgt ); /**< Lose focus. */

   /* Status of the widget. */
   WidgetStatus status; /**< Widget status. */

   /* Type specific data (defined by type). */
   union {
      WidgetButtonData       btn; /**< WIDGET_BUTTON */
      WidgetTextData         txt; /**< WIDGET_TEXT */
      WidgetImageData        img; /**< WIDGET_IMAGE */
      WidgetListData         lst; /**< WIDGET_LIST */
      WidgetRectData         rct; /**< WIDGET_RECT */
      WidgetCustData         cst; /**< WIDGET_CUST */
      WidgetInputData        inp; /**< WIDGET_INPUT */
      WidgetImageArrayData   iar; /**< WIDGET_IMAGEARRAY */
      WidgetFaderData        fad; /**< WIDGET_FADER */
      WidgetTabbedWindowData tab; /**< WIDGET_TABBEDWINDOW */
      WidgetCheckboxData     chk; /**< WIDGET_CHECKBOX */
   } dat;                         /**< Stores the widget specific data. */
} Widget;

#define WINDOW_NOFOCUS ( 1 << 0 ) /**< Window can not be active window. */
#define WINDOW_NOINPUT ( 1 << 1 ) /**< Window receives no input. */
#define WINDOW_NORENDER                                                        \
   ( 1 << 2 ) /**< Window does not render even if it should. */
#define WINDOW_NOBORDER                                                        \
   ( 1 << 3 ) /**< Window does not need border (this is the window background  \
                 and title, only renders widgets). */
#define WINDOW_FULLSCREEN ( 1 << 4 ) /**< Window is fullscreen. */
#define WINDOW_CENTERX ( 1 << 5 )    /**< Window is X-centered. */
#define WINDOW_CENTERY ( 1 << 6 )    /**< Window is Y-centered. */
#define WINDOW_DYNAMIC                                                         \
   ( 1 << 7 )                  /**< Window should be rerendered every frame. */
#define WINDOW_KILL ( 1 << 9 ) /**< Window should die. */
#define window_isFlag( w, f )                                                  \
   ( ( w )->flags & ( f ) ) /**< Checks a window flag. */
#define window_setFlag( w, f )                                                 \
   ( ( w )->flags |= ( f ) ) /**< Sets a window flag. */
#define window_rmFlag( w, f )                                                  \
   ( ( w )->flags &= ~( f ) ) /**< Removes a window flag. */

/**
 * @struct Window
 *
 * @brief Represents a graphical window.
 */
typedef struct Window_ {
   struct Window_ *next; /* Linked list. */

   unsigned int id;          /**< Unique ID. */
   char        *name;        /**< Window name - should be unique. */
   char        *displayname; /**< Display name obtained with gettext. */
   unsigned int flags;       /**< Window flags. */
   int          idgen;       /**< ID generator for widgets. */
   double       timer;       /**< Timer for fancy effects. */
   double       timer_max;   /**< Max timer. */

   unsigned int parent; /**< Parent window, will close if this one closes. */
   void ( *close_fptr )( unsigned int wid,
                         const char  *name ); /**< How to close the window. */

   void ( *accept_fptr )( unsigned int wid, const char *name ); /**< Triggered
                 by hitting 'enter' with no widget that catches the keypress. */
   void ( *cancel_fptr )( unsigned int wid,
                          const char *name ); /**< Triggered by hitting 'escape'
                    with no widget that catches the keypress. */
   void ( *focus_fptr )(
      unsigned int wid ); /**< Triggered when window's focus status changes. */
   int ( *keyevent )( unsigned int wid, SDL_Keycode, SDL_Keymod,
                      int ); /**< User defined custom key event handler. */
   int ( *eventevent )( unsigned int wid,
                        SDL_Event   *evt ); /**< User defined event handler. */

   /* Position and dimensions. */
   int    x;    /**< X position of the window. */
   int    y;    /**< Y position of the window. */
   double xrel; /**< X position relative to screen width. */
   double yrel; /**< Y position relative to screen height. */
   int    w;    /**< Window width. */
   int    h;    /**< Window height. */

   int     exposed; /**< Whether window is visible or hidden. */
   int     focus;   /**< Current focused widget. */
   Widget *widgets; /**< Widget storage. */
   void   *udata;   /**< Custom data of the window. */
} Window;

/* Window stuff. */
Window *toolkit_getActiveWindow( void );
Window *window_wget( const unsigned int wid );
Window *window_wgetW( const unsigned int wid );
Window *window_wgetNameW( const char *name );
void    toolkit_setWindowPos( Window *wdw, int x, int y );
int     toolkit_inputWindow( Window *wdw, SDL_Event *event, int purge );
void    window_render( Window *w, int top );
void    window_renderDynamic( Window *w );
void    window_renderOverlay( Window *w );
void    window_kill( Window *wdw );

/* Widget stuff. */
Widget *window_newWidget( Window *w, const char *name );
void    widget_cleanup( Widget *widget );
void    widget_setStatus( Widget *widget, WidgetStatus sts );
Widget *window_getwgt( const unsigned int wid, const char *name );
void    toolkit_setPos( const Window *wdw, Widget *wgt, int x, int y );
void    toolkit_focusSanitize( Window *wdw );
void    toolkit_focusClear( Window *wdw );
void    toolkit_nextFocus( Window *wdw );
void    toolkit_prevFocus( Window *wdw );
Widget *toolkit_getFocus( Window *wdw );
void    toolkit_focusWidget( Window *wdw, Widget *wgt );
void    toolkit_defocusWidget( Window *wdw, Widget *wgt );

/* Render stuff. */
void toolkit_drawOutline( int x, int y, int w, int h, int b,
                          const glColour *c );
void toolkit_drawOutlineThick( int x, int y, int w, int h, int b, int thick,
                               const glColour *c );
void toolkit_drawScrollbar( int x, int y, int w, int h, double pos );
void toolkit_drawRect( int x, int y, int w, int h, const glColour *c );
void toolkit_drawRectHalf( int x, int y, int w, int h, const glColour *c );
void toolkit_drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3,
                           const glColour *c );
void toolkit_drawAltText( int bx, int by, const char *alt );

/* Input stuff. */
Uint32 toolkit_inputTranslateCoords( const Window *w, SDL_Event *event,
                                     float *x, float *y, float *rx, float *ry );
