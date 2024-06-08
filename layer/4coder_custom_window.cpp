#ifndef FCODER_CUSTOM_WINDOW_CPP
#define FCODER_CUSTOM_WINDOW_CPP

#if OS_WINDOWS
// #include <windows.h>
// @Todo: There's a problem when you include windows.h, that symbols and macros conflict and it's a header file mess (congrats to C++ as the best language ever)
// Probabily define WIN32_LEAN_AND_MEAN and stuff like that
#pragma comment(lib, "user32.lib")
#endif

namespace nne {
	
#if OS_WINDOWS
	
	function b32 set_window_maximized(Application_Links *app, b32 maximized) {
#if 0
		Scratch_Block scratch(app);
		b32 success = false;
		
		HWND top_window = GetTopWindow(0);
		if (top_window) {
			LONG cur_style = GetWindowLongW(top_window, GWL_STYLE);
			
			if (maximized) {
				cur_style |=  WS_MAXIMIZE;
			} else {
				cur_style &= ~WS_MAXIMIZE;
			}
			
			SetLastError(0);
			LONG old_style = SetWindowLongW(top_window, GWL_STYLE, cur_style);
			int last_error = GetLastError();
			if (last_error != 0) {
				String_Const_u8 message = push_u8_stringf(scratch, "The window could not be maximized/de-maximized because the window style could not be set (last error: %d).", last_error);
				print_message(app, message);
				
				// @Bug: This fails with error code 5 (ERROR_ACCESS_DENIED). The docs say nothing more than "Access is denied". What could the problem be?
			} else {
				success = true;
			}
			
			cast(void)old_style;
		} else {
			String_Const_u8 message = push_u8_stringf(scratch, "The window could not be maximized/de-maximized because the window handle could not be retrieved (last error: %d).", GetLastError());
			print_message(app, message);
		}
		
		return success;
#else
		return false;
#endif
	}
	
#else
#define set_window_maximized(...) (cast(b32)false)
#endif
	
}

#endif // FCODER_CUSTOM_WINDOW_CPP
