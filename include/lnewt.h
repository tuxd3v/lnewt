/**
 * @brief  This file contain lnewt declaration for LNewt Library Lua 5.3 Bindings
 * @file   lnewt.h
 * @author Several
 * @date   23 December 2019
 * @see    dhdhd
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <newt.h>

enum type_t {
	TYPE_FORM = -1,
	TYPE_UNKNOWN,
	TYPE_LABEL,
	TYPE_ENTRY,
	TYPE_BUTTON,
	TYPE_CHECKBOX,
	TYPE_RADIOBUTTON,
	TYPE_LISTBOX,
	TYPE_SCALE,
	TYPE_TEXTBOX
} type;
/*
#define TYPE_FORM -1
#define TYPE_UNKNOWN 0
#define TYPE_LABEL 1
#define TYPE_ENTRY 2
#define TYPE_BUTTON 3
#define TYPE_CHECKBOX 4
#define TYPE_RADIOBUTTON 5
#define TYPE_LISTBOX 6
#define TYPE_SCALE 7
#define TYPE_TEXTBOX 8
*/
/**
 * @brief typedef for generic struct pointer component
 */
typedef struct com_t * component;
typedef struct listbox	listbox_t;
/**
 * @brief typedef for generic struct pointer component
 * also, __declared in newt.h_
 * __typedef struct newtComponent_struct * newtComponent;__
*/
typedef struct newtComponent_struct * newtComponent
typedef struct newtComponent_struct * component_t;

/**
 * @brief libnewt internals - very naughty
 * Also declared in __newt_pr.h__... why declaring it twice??
 */
struct newtComponent_struct {
	/* common data */
	int height, width;
	int top, left;
	int takesFocus;
	int isMapped;

	struct componentOps * ops;

	newtCallback callback;
	void * callbackData;

	newtCallback destroyCallback;
	void * destroyCallbackData;

	void * data;

};

/**
 * @brief Holds all the relevant information for this listbox
 */
struct listbox {
	newtComponent sb;		/**< struct newtComponent_struct * newtComponent #sb. */
	int curWidth;			/**< signed integer current collumns width #curWidth */
	int curHeight;			/**< signed integer current collumns height #curHeight */
	int sbAdjust;			/**< signed integer ??? #sbAdjust */
	int bdxAdjust, bdyAdjust;
	int numItems, numSelected;
	int userHasSetWidth;
	int currItem, startShowItem;
	int isActive;
	struct items *boxItems;
	int grow;
	int flags;
};

/**
 * @brief wrapper structs
 */
struct com_t {
	newtComponent p;
	int t;
};

/**
 * @brief module registration
 * @brief open the library - used by require()
 */
LUALIB_API int luaopen_lnewt( lua_State *L );

/**
 * @brief exported functions
 * @brief root functions
 */
static int L_Init( lua_State *L );
static int L_Cls( lua_State *L );
static int L_WaitForKey( lua_State *L );
static int L_ClearKeyBuffer( lua_State *L );
static int L_DrawRootText( lua_State *L );
static int L_OpenWindow( lua_State *L );
static int L_CenteredWindow( lua_State *L );
static int L_PopWindow( lua_State *L );
static int L_PushHelpLine( lua_State *L );
static int L_PopHelpLine( lua_State *L );
static int L_Refresh( lua_State *L );
static int L_Finished( lua_State *L );
/**
 * @brief Creates a Message Window, for information porposes..
 * @brief void newtWinMessage(char * title, char * buttonText, char * text, ...);
 * @param string( L, 1 )
 * @param string( L, 2 )
 * @param string( L, 3 )
 * @return nil
 */
static int L_WinMessage( lua_State *L );
static int L_Suspend( lua_State *L );
static int L_Resume( lua_State *L );
static int L_SetSuspendCallback( lua_State *L );
static int L_Bell( lua_State *L );
static int L_CursorOff( lua_State *L );
static int L_CursorOn( lua_State *L );
static int L_Delay( lua_State *L );
static int L_GetScreenSize( lua_State *L );
static int L_ReflowText( lua_State *L );

/**
 * @brief widgets
 */
static int L_Button( lua_State *L );
static int L_CompactButton( lua_State *L );
static int L_Checkbox( lua_State *L );
static int L_Entry( lua_State *L );
static int L_Form( lua_State *L );
static int L_Label( lua_State *L );
static int L_Textbox( lua_State *L );
static int L_TextboxReflowed( lua_State *L );
static int L_Listbox( lua_State *L );
static int L_Radiobutton( lua_State *L );
static int L_Scale( lua_State *L );
static int L_VerticalScrollbar( lua_State *L );

/**
 * @brief Newt.Component Object
 */
static int L_AddCallback( lua_State *L );
/**
 * @brief Newt.Component object
 * AddComponents(com, ...)
 * @param L 
 * @return 
 * 
 */
static int L_AddComponents( lua_State *L );
/**
 * @brief form:AddHotKey(key)
 * @brief form:AddHotKey({key, ...})
 * @param L 
 * @return 
 * 
 */
static int L_AddHotKey( lua_State *L );
/**
 * @brief listbox:AppendEntry(text, [index])
 * @brief listbox:AppendEntry({text, text}, [startindex])
 * @param L 
 * @return 
 * 
 * 
 */
static int L_AppendEntry( lua_State *L );
/**
 * @brief listbox:Clear()
 * @param L 
 * @return 
 * 
 */
static int L_Clear( lua_State *L );
/**
 * @brief L_ClearSelection
 * @param L 
 * @return 
 * 
 */
static int L_ClearSelection( lua_State *L );
/**
 * @brief L_DeleteEntry
 * @param L 
 * @return 
 * 
 * 
 */
static int L_DeleteEntry( lua_State *L );
/**
 * @brief L_Destroy
 * @param L 
 * @return 
 * 
 */
static int L_Destroy( lua_State *L );
/**
 * @brief form:Draw()
 * @param L 
 * @return 
 * 
 */
static int L_Draw( lua_State *L );
/**
 * @brief Get Curent Component, RADIOBUTTON,LISTBOX, etc
 * @brief com = radiobutton:GetCurrent()
 * @param component( L, 1 )
 * @return integer or RADIOBUTTON Component
 */
static int L_GetCurrent( lua_State *L );
/**
 * @brief L_GetSelection
 * @param L 
 * @return 
 * 
 * 
 */
static int L_GetSelection( lua_State *L );
/**
 * @brief L_GetNumLines
 * @param L 
 * @return 
 * 
 * 
 */
static int L_GetNumLines( lua_State *L );
/**
 * @brief value = entry:GetValue()
 * @brief value = checkbox:GetValue()
 * @param L 
 * @return lua_pushboolean()
 * 
 */
static int L_GetValue( lua_State *L );
/**
 * @brief L_InsertEntry
 * @param L 
 * @return 
 * 
 * 
 */
static int L_InsertEntry( lua_State *L );
/**
 * @brief hex = com:ID()
 * @param L 
 * @return 
 * 
 */
static int L_ID( lua_State *L );
/**
 * @brief reason, value = form:Run()
 * @param L 
 * @return lua_pushcomponent( L, result.u.co, TYPE_UNKNOWN ) or lua_pushinteger( L, result.u.key )
 * 
 */
static int L_Run( lua_State *L );
/**
 * @brief 
 * @param L 
 * @return 
 * 
 * 
 */
static int L_SelectItem( lua_State *L );
/**
 * @brief entry:Set(value, [cursoratend])
 * @brief scale:Set(value)
 * @param L 
 * @return void
 * 
 */
static int L_Set( lua_State *L );
/**
 * @brief L_SetBackground
 * @param L 
 * @return 
 * 
 */
static int L_SetBackground( lua_State *L );
/**
 * @brief L_SetCurrent
 * @param L 
 * @return 
 * 
 */
static int L_SetCurrent( lua_State *L );
/**
 * @brief L_SetCurrentByKey
 * @param L 
 * @return 
 * 
 * 
 */
static int L_SetCurrentByKey( lua_State *L );
/**
 * @brief L_SetEntry
 * @param L 
 * @return 
 * 
 */
static int L_SetEntry( lua_State *L );
/**
 * @brief L_SetHeight
 * @param L 
 * @return 
 * 
 */
static int L_SetHeight( lua_State *L );
/**
 * @brief label:SetText(text)
 * @param L 
 * @return LabelSetText( com->p, text ) or TextboxSetText( com->p, text )
 * 
 */
static int L_SetText( lua_State *L );
/**
 * @brief form:SetTimer(millisecs)
 * @param L 
 * @return FormSetTimer( com->p, period )
 * 
 */
static int L_SetTimer( lua_State *L );
/**
 * @brief com = com:SetType(type)
 * @param L 
 * @return component( L, com->p, type )
 * 
 * 
 */
static int L_SetType( lua_State *L );
/**
 * @brief L_SetValue
 * @param L 
 * @return 
 * 
 * 
 */
static int L_SetValue( lua_State *L );
/**
 * @brief 
 * @param L 
 * @return 
 * 
 * 
 */
static int L_SetWidth( lua_State *L );
/**
 * @brief com:TakesFocus(bool)
 * @param L 
 * @return 
 * 
 */
static int L_TakesFocus( lua_State *L );
/**
 * @brief tag = com:Text()
 * @param component( L, 1 )
 * @return tag
 * 
 */
static int L_Text( lua_State *L );
