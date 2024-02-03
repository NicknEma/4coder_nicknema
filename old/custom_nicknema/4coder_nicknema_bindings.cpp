#ifndef FCODER_NICKNEMA_BINDINGS_CPP
#define FCODER_NICKNEMA_BINDINGS_CPP

#if OS_WINDOWS && 0

// #include <windows.h>
#pragma comment(lib, "user32.lib")

// #define GWL_STYLE   -16
#define WS_MAXIMIZE 0x01000000L

struct Window_Dimensions {
    int width;
    int height;
};

struct Window_Area {
    union {
        struct { int x, y; };
        struct { int left, top; };
    };
    int width, height;
};

typedef long LONG;
typedef u32  DWORD;
typedef u8   BOOL;

struct RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
};

typedef RECT *LPRECT;
typedef void *HWND;

#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }

EXTERN_C_BEGIN

HWND GetDesktopWindow();
BOOL GetClientRect   (HWND hWnd, LPRECT lpRect);
BOOL AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu);

HWND GetTopWindow  (HWND hWnd);
LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong);
LONG GetWindowLongA(HWND hWnd, int nIndex);

EXTERN_C_END

function Window_Dimensions
get_client_dimensions(HWND window) {
    RECT client_rect;
    GetClientRect(window, &client_rect);
    
    Window_Dimensions result;
    result.width  = client_rect.right - client_rect.left;
    result.height = client_rect.bottom - client_rect.top;
    return result;
}

function Window_Area
rect_to_window_area(RECT rect) {
    Window_Area result;
    
    result.left   = rect.left;
    result.top    = rect.top;
    result.width  = rect.right - rect.left;
    result.height = rect.bottom - rect.top;
    
    return result;
}

function Window_Area
precompute_window_area(int client_width, int client_height, DWORD window_style) {
    RECT desktop_rect;
    GetClientRect(GetDesktopWindow(), &desktop_rect);
    
    int client_left    = (desktop_rect.right  / 2) - (client_width  / 2);
    int client_top     = (desktop_rect.bottom / 2) - (client_height / 2);
    
    int client_right   = client_left + client_width;
    int client_bottom  = client_top + client_height;
    
    RECT window_rect   = { client_left, client_top, client_right, client_bottom };
    bool adjusted      = AdjustWindowRect(&window_rect, window_style, 0);
    
    adjusted;
    
    Window_Area result = rect_to_window_area(window_rect);
    return result;
}

#endif // OS_WINDOWS

#if 0
function void
system_set_window_dimensions(Application_Links *app) {
    // @Unimplemented(ema).
}
#endif

function void
system_set_maximized(Application_Links *app, bool maximized) {
    
#if OS_WINDOWS && 0
    
    app; // @Todo: Figure out if this is useful for something.
    
    HWND top_window = GetTopWindow(0);
    if (top_window) {
        LONG cur_style = GetWindowLongA(top_window, GWL_STYLE);
        
        if (maximized) {
            cur_style |=  WS_MAXIMIZE;
        } else {
            cur_style &= ~WS_MAXIMIZE;
        }
        
        LONG old_style = SetWindowLongA(top_window, GWL_STYLE, cur_style);
        old_style;
    } else {
        // @Incomplete: Assert/Log.
    }
    
#else
    
    app; maximized;
    
#endif
    
}

CUSTOM_COMMAND_SIG(nicknema_startup)
CUSTOM_DOC("Custom command for responding to a startup event") {
	default_startup(app);
    
    {
        system_set_maximized(app, true);
    }
    
    {
        change_active_panel_send_command(app, close_panel);
    }
}

#endif // FCODER_NICKNEMA_BINDINGS
