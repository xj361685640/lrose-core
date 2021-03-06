
//////////////////////////////////////////////////////////////
//
// Header file for RpCursorDataFormClassUI
//
//    This file is generated by RapidApp 1.2
//
//    This class implements the user interface portion of a class
//    Normally it is not used directly.
//    Instead the subclass, RpCursorDataFormClass is instantiated
//
//    To extend or alter the behavior of this class, you should
//    modify the RpCursorDataFormClass files
//
//    Restrict changes to those sections between
//    the "//--- Start/End editable code block" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//
//////////////////////////////////////////////////////////////
#ifndef RPCURSORDATAFORMCLASSUI_H
#define RPCURSORDATAFORMCLASSUI_H
#include <Vk/VkComponent.h>


//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


class VkOptionMenu;
class VkMenuAction;
class VkMenuToggle;
class VkMenuItem;
class RpCursorDataFormClassUI : public VkComponent
{ 

  public:

    RpCursorDataFormClassUI ( const char *, Widget );
    RpCursorDataFormClassUI ( const char * );
    ~RpCursorDataFormClassUI();
    void create ( Widget );
    const char *  className();

    //---- Start editable code block: RpCursorDataFormClass public


    //---- End editable code block: RpCursorDataFormClass public


  protected:


    // Widgets created by this class

    Widget  _distNELabel;
    Widget  _distnetextfield;
    Widget  _htLabel;
    Widget  _httextfield;
    Widget  _label2;
    Widget  _latLongLabel;
    Widget  _latlongtextfield;
    Widget  _rngBrgLabel;
    Widget  _rngbrgtextfield;
    Widget  _rpCursorDataFormClass;
    Widget  _scantextfield;
    Widget  _speedLabel;
    Widget  _speedtextfield;
    Widget  _tmDiffLabel;
    Widget  _tmdifftextfield;
    Widget  _val1label;
    Widget  _val1textfield;
    Widget  _val2label;
    Widget  _val2textfield;

    VkOptionMenu  *_unitsOptionMenu;

    VkMenuItem *_button19;
    VkMenuItem *_button22;
    VkMenuItem *_button27;
    VkMenuItem *_optionA;
    VkMenuItem *_optionB;


    // These virtual functions are called from the private callbacks (below)
    // Intended to be overriden in derived classes to define actions

    virtual void uifselkmkft ( Widget, XtPointer );
    virtual void uifselkmm ( Widget, XtPointer );
    virtual void uifselmilekft ( Widget, XtPointer );
    virtual void uifselntmilekft ( Widget, XtPointer );

    //---- Start editable code block: RpCursorDataFormClass protected


    //---- End editable code block: RpCursorDataFormClass protected


  private: 

    // Array of default resources

    static String      _defaultRpCursorDataFormClassUIResources[];


    // Callbacks to interface with Motif

    static void uifselkmkftCallback ( Widget, XtPointer, XtPointer );
    static void uifselkmmCallback ( Widget, XtPointer, XtPointer );
    static void uifselmilekftCallback ( Widget, XtPointer, XtPointer );
    static void uifselntmilekftCallback ( Widget, XtPointer, XtPointer );

    //---- Start editable code block: RpCursorDataFormClass private


    //---- End editable code block: RpCursorDataFormClass private
};
//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif

