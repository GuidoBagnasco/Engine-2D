
//---------------------------------------------------------------------------
#ifndef Input_H
#define Input_H
//---------------------------------------------------------------------------
#include "../myEngine_API.h"
#include <stdio.h>
//---------------------------------------------------------------------------
namespace engine
{
//---------------------------------------------------------------------------
	class MYENGINE_API Input
	{
		public:
			enum
			{
				POS_X,
				POS_Y,
				POS_Z
			};

			enum MouseButton
			{
				MB_1,
				MB_2,
				MB_3
			};

			enum KeyState
			{
				KS_NONE,
				KS_DOWN,
				KS_UP
			};

			// copiado de DirectInput
			enum KeyCode
			{
				KEY_ESCAPE       = 0x01,
				KEY_1            = 0x02,
				KEY_2            = 0x03,
				KEY_3            = 0x04,
				KEY_4            = 0x05,
				KEY_5            = 0x06,
				KEY_6            = 0x07,
				KEY_7            = 0x08,
				KEY_8            = 0x09,
				KEY_9            = 0x0A,
				KEY_0            = 0x0B,
				KEY_MINUS        = 0x0C,
				KEY_EQUALS       = 0x0D,
				KEY_BACK         = 0x0E,
				KEY_TAB          = 0x0F,
				KEY_Q            = 0x10,
				KEY_W            = 0x11,
				KEY_E            = 0x12,
				KEY_R            = 0x13,
				KEY_T            = 0x14,
				KEY_Y            = 0x15,
				KEY_U            = 0x16,
				KEY_I            = 0x17,
				KEY_O            = 0x18,
				KEY_P            = 0x19,
				KEY_LBRACKET     = 0x1A,
				KEY_RBRACKET     = 0x1B,
				KEY_RETURN       = 0x1C,
				KEY_LCONTROL     = 0x1D,
				KEY_A            = 0x1E,
				KEY_S            = 0x1F,
				KEY_D            = 0x20,
				KEY_F            = 0x21,
				KEY_G            = 0x22,
				KEY_H            = 0x23,
				KEY_J            = 0x24,
				KEY_K            = 0x25,
				KEY_L            = 0x26,
				KEY_SEMICOLON    = 0x27,
				KEY_APOSTROPHE   = 0x28,
				KEY_GRAVE        = 0x29,
				KEY_LSHIFT       = 0x2A,
				KEY_BACKSLASH    = 0x2B,
				KEY_Z            = 0x2C,
				KEY_X            = 0x2D,
				KEY_C            = 0x2E,
				KEY_V            = 0x2F,
				KEY_B            = 0x30,
				KEY_N            = 0x31,
				KEY_M            = 0x32,
				KEY_COMMA        = 0x33,
				KEY_PERIOD       = 0x34,
				KEY_SLASH        = 0x35,
				KEY_RSHIFT       = 0x36,
				KEY_MULTIPLY     = 0x37,
				KEY_LMENU        = 0x38,
				KEY_SPACE        = 0x39,
				KEY_CAPITAL      = 0x3A,
				KEY_F1           = 0x3B,
				KEY_F2           = 0x3C,
				KEY_F3           = 0x3D,
				KEY_F4           = 0x3E,
				KEY_F5           = 0x3F,
				KEY_F6           = 0x40,
				KEY_F7           = 0x41,
				KEY_F8           = 0x42,
				KEY_F9           = 0x43,
				KEY_F10          = 0x44,
				KEY_NUMLOCK      = 0x45,
				KEY_SCROLL       = 0x46,
				KEY_NUMPAD7      = 0x47,
				KEY_NUMPAD8      = 0x48,
				KEY_NUMPAD9      = 0x49,
				KEY_SUBTRACT     = 0x4A,
				KEY_NUMPAD4      = 0x4B,
				KEY_NUMPAD5      = 0x4C,
				KEY_NUMPAD6      = 0x4D,
				KEY_ADD          = 0x4E,
				KEY_NUMPAD1      = 0x4F,
				KEY_NUMPAD2      = 0x50,
				KEY_NUMPAD3      = 0x51,
				KEY_NUMPAD0      = 0x52,
				KEY_DECIMAL      = 0x53,
				KEY_OEM_102      = 0x56,
				KEY_F11          = 0x57,
				KEY_F12          = 0x58,
				KEY_F13          = 0x64,
				KEY_F14          = 0x65,
				KEY_F15          = 0x66,
				KEY_KANA         = 0x70,
				KEY_ABNT_C1      = 0x73,
				KEY_CONVERT      = 0x79,
				KEY_NOCONVERT    = 0x7B,
				KEY_YEN          = 0x7D,
				KEY_ABNT_C2      = 0x7E,
				KEY_NUMPADEQUALS = 0x8D,
				KEY_PREVTRACK    = 0x90,
				KEY_AT           = 0x91,
				KEY_COLON        = 0x92,
				KEY_UNDERLINE    = 0x93,
				KEY_KANJI        = 0x94,
				KEY_STOP         = 0x95,
				KEY_AX           = 0x96,
				KEY_UNLABELED    = 0x97,
				KEY_NEXTTRACK    = 0x99,
				KEY_NUMPADENTER  = 0x9C,
				KEY_RCONTROL     = 0x9D,
				KEY_MUTE         = 0xA0,
				KEY_CALCULATOR   = 0xA1,
				KEY_PLAYPAUSE    = 0xA2,
				KEY_MEDIASTOP    = 0xA4,
				KEY_VOLUMEDOWN   = 0xAE,
				KEY_VOLUMEUP     = 0xB0,
				KEY_WEBHOME      = 0xB2,
				KEY_NUMPADCOMMA  = 0xB3,
				KEY_DIVIDE       = 0xB5,
				KEY_SYSRQ        = 0xB7,
				KEY_RMENU        = 0xB8,
				KEY_PAUSE        = 0xC5,
				KEY_HOME         = 0xC7,
				KEY_UP           = 0xC8,
				KEY_PRIOR        = 0xC9,
				KEY_LEFT         = 0xCB,
				KEY_RIGHT        = 0xCD,
				KEY_END          = 0xCF,
				KEY_DOWN         = 0xD0,
				KEY_NEXT         = 0xD1,
				KEY_INSERT       = 0xD2,
				KEY_DELETE       = 0xD3,
				KEY_LWIN         = 0xDB,
				KEY_RWIN         = 0xDC,
				KEY_APPS         = 0xDD,
				KEY_POWER        = 0xDE,
				KEY_SLEEP        = 0xDF,
				KEY_WAKE         = 0xE3,
				KEY_WEBSEARCH    = 0xE5,
				KEY_WEBFAVORITES = 0xE6,
				KEY_WEBREFRESH   = 0xE7,
				KEY_WEBSTOP      = 0xE8,
				KEY_WEBFORWARD   = 0xE9,
				KEY_WEBBACK      = 0xEA,
				KEY_MYCOMPUTER   = 0xEB,
				KEY_MAIL         = 0xEC,
				KEY_MEDIASELECT  = 0xED
			};
	

		// constructor/destructor
		public:
			Input ();
			virtual ~Input ();


		// interface
		public:
			virtual void acquire () = 0;
			virtual void reacquire () = 0;
			virtual void unacquire () = 0;


		// input devices state
		public:
			void reset ();

			bool keyDown (KeyCode eKey);
			bool keyUp (KeyCode eKey);

			bool mouseDown (MouseButton eButtonID);
			bool mouseUp (MouseButton eButtonID);

			long mouseRelPosX ();
			long mouseRelPosY ();
			long mouseRelPosZ ();
			long mouseScrAbsPosX ();
			long mouseScrAbsPosY ();
			long mouseScrAbsPosZ ();

		protected:
			unsigned char m_ucKeyBuffer[256];
			unsigned char m_ucMouseButton[3];

			long m_lMouseRelPosition[3];
			long m_lMouseScreenAbsPosition[3];
	};
//---------------------------------------------------------------------------
	#include "Input.inl"
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif // Input_H
//---------------------------------------------------------------------------
