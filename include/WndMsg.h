#include <basetsd.h>

typedef unsigned char	BYTE;
typedef unsigned int    UINT;
typedef unsigned long   DWORD;
typedef long			LONG;
typedef UINT_PTR        WPARAM;
typedef LONG_PTR        LPARAM;


typedef struct tagPOINT
{
	LONG  x;
	LONG  y;
} POINT;

typedef struct tagMSG {
	HWND        hwnd;
	UINT        message;
	WPARAM      wParam;
	LPARAM      lParam;
	DWORD       time;
	POINT       pt;

} MSG;

#define		WM_USER		0x0400