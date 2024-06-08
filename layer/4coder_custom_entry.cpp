
//~ Default headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "4coder_default_include.cpp"

//~ Macros and pragmase stuff that have to be put here for various reasons.
#pragma warning(disable: 4102) // The label is defined but never referenced. The compiler ignores the label. This is here because of an unreferenced label in the odin generated lexer.
#pragma warning(disable: 4702) // Unreachable code was detected.

// Right now the organization of the code is not very consistent. Some files only contain one or two helper functions (eg. code_peek or divider_comments) while others
// implement entire sybsystems (like calc or index).

//~ Custom layer headers
#include "4coder_custom_ubiquitous.h"            // Macros, variables and utility functions that can be used everywhere
#include "4coder_custom_audio.h"
#include "4coder_custom_languages.h"             // The generic language interface that will be used by the index to communicate to language-specific parsers
#include "4coder_custom_index.h"                 // Dictionary that contains info on every identifier in the loaded project, allowing for syntax highlighting, tooltips, etc.
#include "4coder_custom_colors.h"                // Syntax highlighting and color animations
#include "4coder_custom_render_helpers.h"        // Rendering functions that are used in the render hook
#include "4coder_custom_error_annotations.h"     // A render helper for error annotations.
#include "4coder_custom_divider_comments.h"      // Functions for rendering and jumping between divider comments //~ and //-
#include "4coder_custom_power_mode.h"
#include "4coder_custom_cursor.h"                // Render helpers for the two styles of cursor
#include "4coder_custom_plot.h"
#include "4coder_custom_calc.h"
#include "4coder_custom_lego.h"                  // If I understand correctly, it's a "smart clipboard", a way to copy and paste text that is context-aware. Never tried it though.
#include "4coder_custom_pos_context_tooltips.h"  // Function to render the tooltips at the cursor or at the bottom of the view
#include "4coder_custom_code_peek.h"             // Render helper and commands for code peek
#include "4coder_custom_recent_files.h"          // Command to open the recent files lister and interact with it
#include "4coder_custom_bindings.h"              // Functions to set hardcoded default bindings or to load them from a file
#include "4coder_custom_lines_of_code.h"         // Command for counting and displaying lines of code info
#include "4coder_custom_base_commands.h"         // Generic commands, searchable through the command lister or bindable to an event
#include "4coder_custom_hooks.h"                 // Implementation of custom hooks (callback for various events such as on-render, on-buffer-edit, on-open-file)
#include "4coder_custom_auto_indent.h"           // Slight modification of the default indentation rules to handle languages without semicolons
#include "4coder_custom_window.h"                // Functions that relate to the editor's window

//~ Custom layer implementation
#include "4coder_custom_ubiquitous.cpp"
#include "4coder_custom_audio.cpp"
#include "4coder_custom_languages.cpp"
#include "4coder_custom_index.cpp"
#include "4coder_custom_colors.cpp"
#include "4coder_custom_render_helpers.cpp"
#include "4coder_custom_error_annotations.cpp"
#include "4coder_custom_divider_comments.cpp"
#include "4coder_custom_power_mode.cpp"
#include "4coder_custom_cursor.cpp"
#include "4coder_custom_plot.cpp"
#include "4coder_custom_calc.cpp"
#include "4coder_custom_lego.cpp"
#include "4coder_custom_pos_context_tooltips.cpp"
#include "4coder_custom_code_peek.cpp"
#include "4coder_custom_recent_files.cpp"
#include "4coder_custom_bindings.cpp"
#include "4coder_custom_lines_of_code.cpp"
#include "4coder_custom_base_commands.cpp"
#include "4coder_custom_casey.cpp"
#include "4coder_custom_hooks.cpp"
#include "4coder_custom_load.cpp"
#include "4coder_custom_auto_indent.cpp"
#include "4coder_custom_window.cpp"

//~ Plots Demo File
#include "4coder_custom_plots_demo.cpp"

//~ 4coder Stuff
#include "generated/managed_id_metadata.cpp"

//~ Custom layer initialization

void custom_layer_init(Application_Links *app) {
    default_framework_init(app);
    global_frame_arena            = make_arena(get_base_allocator_system());
    global_custom_permanent_arena = make_arena(get_base_allocator_system());
    
    //- Set up hooks.
    {
        set_all_default_hooks(app);
        //t $          ($  , $                             , $                     );
        set_custom_hook(app, HookID_Tick,                    nne::tick);
        set_custom_hook(app, HookID_RenderCaller,            nne::render);
        set_custom_hook(app, HookID_BeginBuffer,             nne::begin_buffer);
        set_custom_hook(app, HookID_Layout,                  nne::layout);
        set_custom_hook(app, HookID_WholeScreenRenderCaller, nne::whole_screen_render);
        set_custom_hook(app, HookID_DeltaRule,               nne::delta_rule);
        set_custom_hook(app, HookID_BufferEditRange,         nne::buffer_edit_range);
        set_custom_hook_memory_size(app, HookID_DeltaRule,   delta_ctx_size(sizeof(Vec2_f32)));
    }
    
    //- Set up bindings.
    {
        mapping_init(get_thread_context(app), &framework_mapping);
		
        nne::set_absolutely_necessary_bindings(&framework_mapping);
        if (!nne::dynamic_binding_load_from_file(app, &framework_mapping, Str_U8("bindings.4coder"))) {
            nne::set_default_bindings(&framework_mapping);
        }
		
		// We don't want the .4coder file to overwrite some important binding that is necessary
		// for the editor to work, so we set the minimal bindings again to re-overwrite those.
		nne::set_absolutely_necessary_bindings(&framework_mapping);
    }
    
	//- Set up language parsing.
	nne::index__initialize();
	nne::register_languages();
}

//~ Whenever 4coder's core is ready for the custom layer to start up, this is called.
// In the custom layer entry point above, where the bindings are set, this is passed as a pointer to the editor core. See the bindings.cpp file for more info.
CUSTOM_COMMAND_SIG(custom_startup)
CUSTOM_DOC("Custom startup event") {
    ProfileScope(app, "default startup");
    
    User_Input input = get_current_input(app);
    if (!match_core_code(&input, CoreCode_Startup)) {
        return;
    }
    
    //~ Default 4coder initialization.
    String_Const_u8_Array file_names = input.event.core.file_names;
    load_themes_default_folder(app);
    default_4coder_initialize(app, file_names);
	
    {
		//~ Open special buffers.
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*compilation*"), BufferCreate_NeverAttachToFile | BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
            buffer_set_setting(app, buffer, BufferSetting_ReadOnly,    true);
        }
        
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*lego*"), BufferCreate_NeverAttachToFile | BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
            buffer_set_setting(app, buffer, BufferSetting_ReadOnly,    true);
        }
        
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*calc*"), BufferCreate_NeverAttachToFile | BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
        }
        
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*peek*"), BufferCreate_NeverAttachToFile | BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
        }
        
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*loc*"), BufferCreate_NeverAttachToFile | BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
        }
    }
    
    {
		//~ Initialize panels
        Buffer_Identifier  comp = buffer_identifier(string_u8_litexpr("*compilation*"));
        Buffer_Identifier  left = buffer_identifier(string_u8_litexpr("*calc*"));
        Buffer_Identifier right = buffer_identifier(string_u8_litexpr("*messages*"));
        Buffer_ID  comp_id = buffer_identifier_to_id(app, comp);
        Buffer_ID  left_id = buffer_identifier_to_id(app, left);
        Buffer_ID right_id = buffer_identifier_to_id(app, right);
        
        // Left Panel
        View_ID view = get_active_view(app, Access_Always);
        new_view_settings(app, view);
        view_set_buffer(app, view, left_id, 0);
        
        // Bottom panel
        View_ID compilation_view = 0;
        {
            compilation_view = open_view(app, view, ViewSplit_Bottom);
            new_view_settings(app, compilation_view);
            Buffer_ID buffer = view_get_buffer(app, compilation_view, Access_Always);
            Face_ID face_id = get_face_id(app, buffer);
            Face_Metrics metrics = get_face_metrics(app, face_id);
            view_set_split_pixel_size(app, compilation_view, cast(i32)(metrics.line_height*4.f));
            view_set_passive(app, compilation_view, true);
            global_compilation_view = compilation_view;
            view_set_buffer(app, compilation_view, comp_id, 0);
        }
        
        view_set_active(app, view);
        
        // Right Panel
        open_panel_vsplit(app);
        
        View_ID right_view = get_active_view(app, Access_Always);
        view_set_buffer(app, right_view, right_id, 0);
        
        // Restore Active to Left
        view_set_active(app, view);
    }
    
	{
		//~ Maximize window.
		b32 auto_maximize = def_get_config_b32(vars_save_string_lit("maximize_window_on_startup"));
		if (auto_maximize) {
			nne::set_window_maximized(app, true);
		}
	}
	
    {
		//~ Auto-Load Project.
        b32 auto_load = def_get_config_b32(vars_save_string_lit("automatically_load_project"));
        if (auto_load) {
            load_project(app);
        }
    }
    
    {
		//~ Set misc options.
        global_battery_saver = def_get_config_b32(vars_save_string_lit("f4_battery_saver"));
    }
    
    {
		//~ Initialize audio.
        def_audio_init();
    }
    
    //~ Initialize stylish fonts.
    {
        Scratch_Block scratch(app);
        String_Const_u8 bin_path = system_get_path(scratch, SystemPath_Binary);
        
        // Fallback font.
        Face_ID face_that_should_totally_be_there = get_face_id(app, 0);
        
        {
			// Title font.
            Face_Description desc = {};
            {
                desc.font.file_name =  push_u8_stringf(scratch, "%.*sfonts/RobotoCondensed-Regular.ttf", string_expand(bin_path));
                desc.parameters.pt_size = 18;
                desc.parameters.bold    = 0;
                desc.parameters.italic  = 0;
                desc.parameters.hinting = 0;
            }
            
            if (is_file_readable(desc.font.file_name)) {
                global_styled_title_face = try_create_new_face(app, &desc);
            } else {
                global_styled_title_face = face_that_should_totally_be_there;
            }
        }
        
        {
			// Label font.
            Face_Description desc = {};
            {
                desc.font.file_name =  push_u8_stringf(scratch, "%.*sfonts/RobotoCondensed-Regular.ttf", string_expand(bin_path));
                desc.parameters.pt_size = 10;
                desc.parameters.bold    = 1;
                desc.parameters.italic  = 1;
                desc.parameters.hinting = 0;
            }
            
            if (is_file_readable(desc.font.file_name)) {
                global_styled_label_face = try_create_new_face(app, &desc);
            } else {
                global_styled_label_face = face_that_should_totally_be_there;
            }
        }
        
        {
			// Small code font.
            Face_Description normal_code_desc = get_face_description(app, get_face_id(app, 0));
            
            Face_Description desc = {};
            {
                desc.font.file_name =  push_u8_stringf(scratch, "%.*sfonts/Inconsolata-Regular.ttf", string_expand(bin_path));
                desc.parameters.pt_size = normal_code_desc.parameters.pt_size - 1;
                desc.parameters.bold    = 1;
                desc.parameters.italic  = 1;
                desc.parameters.hinting = 0;
            }
            
            if (is_file_readable(desc.font.file_name)) {
                global_small_code_face = try_create_new_face(app, &desc);
            } else {
                global_small_code_face = face_that_should_totally_be_there;
            }
        }
    }
    
    {
		//~ Prep virtual whitespace.
        def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
        clear_all_layouts(app);
    }
}
