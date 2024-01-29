#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END() }

#define Allow_Break() Assert(1)
#define Force_Break() Assert(0)

#define procedure static
#define cast(t) (t)

#pragma warning(disable: 4102) // The label is defined but never referenced. The compiler ignores the label. This is here because of an unreferenced label in the odin generated lexer.
#pragma warning(disable: 4702) // Unreachable code was detected.

//~ For DION team docs server stuff.
// {
#if OS_WINDOWS
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
typedef int socklen_t;
#pragma comment(lib, "Ws2_32.lib")
#endif
// }

//~ Default headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "4coder_default_include.cpp"

//~ Macros and pragmase stuff that have to be put here for various reasons.
#pragma warning(disable: 4706) // Assignment within conditional expression. @Cleanup(ema): Where? If in the custom layer, remove. If in the base editor, explain.
#pragma warning(disable: 4456) // Declaration of 'identifier' hides previous local declaration. @Cleanup(ema): Where? Should probabily be fixed.
#define COMMAND_SERVER_PORT 4041
#define COMMAND_SERVER_UPDATE_PERIOD_MS 200
#define COMMAND_SERVER_AUTO_LAUNCH_IF_FILE_PRESENT "project_namespaces.txt"

//~ Custom layer headers
#include "4coder_custom_ubiquitous.h"
#include "4coder_fleury_audio.h"
#include "4coder_custom_languages.h"
#include "4coder_custom_index.h"
#include "4coder_fleury_colors.h"
#include "4coder_fleury_render_helpers.h"
#include "4coder_fleury_brace.h"
#include "4coder_fleury_error_annotations.h"
#include "4coder_fleury_divider_comments.h"
#include "4coder_fleury_power_mode.h"
#include "4coder_fleury_cursor.h"
#include "4coder_fleury_plot.h"
#include "4coder_fleury_calc.h"
#include "4coder_fleury_lego.h"
#include "4coder_fleury_pos_context_tooltips.h"
#include "4coder_fleury_code_peek.h"
#include "4coder_fleury_recent_files.h"
#include "4coder_custom_bindings.h"
#include "4coder_custom_base_commands.h"
#if OS_WINDOWS
# include "4coder_fleury_command_server.h"
#endif
#include "4coder_custom_hooks.h"

//~ Custom layer implementation
#include "4coder_custom_ubiquitous.cpp"
#include "4coder_fleury_audio.cpp"
#include "4coder_custom_languages.cpp"
#include "4coder_custom_index.cpp"
#include "4coder_fleury_colors.cpp"
#include "4coder_fleury_render_helpers.cpp"
#include "4coder_fleury_brace.cpp"
#include "4coder_fleury_error_annotations.cpp"
#include "4coder_fleury_divider_comments.cpp"
#include "4coder_fleury_power_mode.cpp"
#include "4coder_fleury_cursor.cpp"
#include "4coder_fleury_plot.cpp"
#include "4coder_fleury_calc.cpp"
#include "4coder_fleury_lego.cpp"
#include "4coder_fleury_pos_context_tooltips.cpp"
#include "4coder_fleury_code_peek.cpp"
#include "4coder_fleury_recent_files.cpp"
#include "4coder_custom_bindings.cpp"
#include "4coder_custom_base_commands.cpp"
#if OS_WINDOWS
# include "4coder_fleury_command_server.cpp"
#endif
#include "4coder_fleury_casey.cpp"
#include "4coder_custom_hooks.cpp"

//~ NOTE(rjf): Plots Demo File
#include "4coder_fleury_plots_demo.cpp"

//~ NOTE(rjf): 4coder Stuff
#include "generated/managed_id_metadata.cpp"

//~ Custom layer initialization

void custom_layer_init(Application_Links *app) {
    default_framework_init(app);
    global_frame_arena = make_arena(get_base_allocator_system());
    permanent_arena = make_arena(get_base_allocator_system());
    
    // NOTE(rjf): Set up hooks.
    {
        set_all_default_hooks(app);
        //t $          ($  , $                             , $                     );
        set_custom_hook(app, HookID_Tick,                    nne::F4_Tick);
        set_custom_hook(app, HookID_RenderCaller,            nne::F4_Render);
        set_custom_hook(app, HookID_BeginBuffer,             nne::F4_BeginBuffer);
        set_custom_hook(app, HookID_Layout,                  nne::F4_Layout);
        set_custom_hook(app, HookID_WholeScreenRenderCaller, nne::F4_WholeScreenRender);
        set_custom_hook(app, HookID_DeltaRule,               nne::F4_DeltaRule);
        set_custom_hook(app, HookID_BufferEditRange,         nne::F4_BufferEditRange);
        set_custom_hook_memory_size(app, HookID_DeltaRule, delta_ctx_size(sizeof(Vec2_f32)));
    }
    
    // NOTE(rjf): Set up mapping.
    {
        mapping_init(get_thread_context(app), &framework_mapping);
		
        nne::set_absolutely_necessary_bindings(&framework_mapping);
        if (!dynamic_binding_load_from_file(app, &framework_mapping, Str_U8("bindings.4coder"))) {
            nne::set_default_bindings(&framework_mapping);
        }
		nne::set_absolutely_necessary_bindings(&framework_mapping); // @Todo(ema): Why is this called two times here? If there's a reason, explain.
    }
    
	nne::index__initialize();
	nne::register_languages();
}

NAMESPACE_BEGIN(nne)

// TODO(rjf): This is only being used to check if a font file exists because there's a bug in try_create_new_face that crashes the program if a font is not found. This function is only necessary until that is fixed.
function b32 is_file_readable(String_Const_u8 path) {
    b32 result = false;
    FILE *file = fopen(cast(char *)path.str, "r");
    if (file) {
        result = true;
        fclose(file);
    }
    return result;
}

NAMESPACE_END()

//~ Whenever 4coder's core is ready for the custom layer to start up, this is called.
// In the custom layer entry point above, where the bindings are set, this is passed as a pointer to the editor core. See the bindings.cpp file for more info.
CUSTOM_COMMAND_SIG(fleury_startup)
CUSTOM_DOC("Custom startup event") {
    ProfileScope(app, "default startup");
    
    User_Input input = get_current_input(app);
    if (!match_core_code(&input, CoreCode_Startup)) {
        return;
    }
    
    //~ NOTE(rjf): Default 4coder initialization.
    String_Const_u8_Array file_names = input.event.core.file_names;
    load_themes_default_folder(app);
    default_4coder_initialize(app, file_names);
    
    //~ NOTE(rjf): Open special buffers.
    {
        // NOTE(rjf): Open compilation buffer.
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*compilation*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
            buffer_set_setting(app, buffer, BufferSetting_ReadOnly, true);
        }
        
        // NOTE(rjf): Open lego buffer.
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*lego*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
            buffer_set_setting(app, buffer, BufferSetting_ReadOnly, true);
        }
        
        // NOTE(rjf): Open calc buffer.
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*calc*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
        }
        
        // NOTE(rjf): Open peek buffer.
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*peek*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
        }
        
        // NOTE(rjf): Open LOC buffer.
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*loc*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
        }
    }
    
    //~ NOTE(rjf): Initialize panels
    {
        Buffer_Identifier comp = buffer_identifier(string_u8_litexpr("*compilation*"));
        Buffer_Identifier left  = buffer_identifier(string_u8_litexpr("*calc*"));
        Buffer_Identifier right = buffer_identifier(string_u8_litexpr("*messages*"));
        Buffer_ID comp_id = buffer_identifier_to_id(app, comp);
        Buffer_ID left_id = buffer_identifier_to_id(app, left);
        Buffer_ID right_id = buffer_identifier_to_id(app, right);
        
        // NOTE(rjf): Left Panel
        View_ID view = get_active_view(app, Access_Always);
        new_view_settings(app, view);
        view_set_buffer(app, view, left_id, 0);
        
        // NOTE(rjf): Bottom panel
        View_ID compilation_view = 0;
        {
            compilation_view = open_view(app, view, ViewSplit_Bottom);
            new_view_settings(app, compilation_view);
            Buffer_ID buffer = view_get_buffer(app, compilation_view, Access_Always);
            Face_ID face_id = get_face_id(app, buffer);
            Face_Metrics metrics = get_face_metrics(app, face_id);
            view_set_split_pixel_size(app, compilation_view, (i32)(metrics.line_height*4.f));
            view_set_passive(app, compilation_view, true);
            global_compilation_view = compilation_view;
            view_set_buffer(app, compilation_view, comp_id, 0);
        }
        
        view_set_active(app, view);
        
        // NOTE(rjf): Right Panel
        open_panel_vsplit(app);
        
        View_ID right_view = get_active_view(app, Access_Always);
        view_set_buffer(app, right_view, right_id, 0);
        
        // NOTE(rjf): Restore Active to Left
        view_set_active(app, view);
    }
    
    //~ NOTE(rjf): Auto-Load Project.
    {
        b32 auto_load = def_get_config_b32(vars_save_string_lit("automatically_load_project"));
        if (auto_load) {
            load_project(app);
        }
    }
    
    //~ NOTE(rjf): Set misc options.
    {
        global_battery_saver = def_get_config_b32(vars_save_string_lit("f4_battery_saver"));
    }
    
    //~ NOTE(rjf): Initialize audio.
    {
        def_audio_init();
    }
    
    //~ NOTE(rjf): Initialize stylish fonts.
    {
        Scratch_Block scratch(app);
        String_Const_u8 bin_path = system_get_path(scratch, SystemPath_Binary);
        
        // NOTE(rjf): Fallback font.
        Face_ID face_that_should_totally_be_there = get_face_id(app, 0);
        
        // NOTE(rjf): Title font.
        {
            Face_Description desc = {0};
            {
                desc.font.file_name =  push_u8_stringf(scratch, "%.*sfonts/RobotoCondensed-Regular.ttf", string_expand(bin_path));
                desc.parameters.pt_size = 18;
                desc.parameters.bold = 0;
                desc.parameters.italic = 0;
                desc.parameters.hinting = 0;
            }
            
            if (nne::is_file_readable(desc.font.file_name)) {
                global_styled_title_face = try_create_new_face(app, &desc);
            } else {
                global_styled_title_face = face_that_should_totally_be_there;
            }
        }
        
        // NOTE(rjf): Label font.
        {
            Face_Description desc = {0};
            {
                desc.font.file_name =  push_u8_stringf(scratch, "%.*sfonts/RobotoCondensed-Regular.ttf", string_expand(bin_path));
                desc.parameters.pt_size = 10;
                desc.parameters.bold = 1;
                desc.parameters.italic = 1;
                desc.parameters.hinting = 0;
            }
            
            if (nne::is_file_readable(desc.font.file_name)) {
                global_styled_label_face = try_create_new_face(app, &desc);
            } else {
                global_styled_label_face = face_that_should_totally_be_there;
            }
        }
        
        // NOTE(rjf): Small code font.
        {
            Face_Description normal_code_desc = get_face_description(app, get_face_id(app, 0));
            
            Face_Description desc = {0};
            {
                desc.font.file_name =  push_u8_stringf(scratch, "%.*sfonts/Inconsolata-Regular.ttf", string_expand(bin_path));
                desc.parameters.pt_size = normal_code_desc.parameters.pt_size - 1;
                desc.parameters.bold = 1;
                desc.parameters.italic = 1;
                desc.parameters.hinting = 0;
            }
            
            if (nne::is_file_readable(desc.font.file_name)) {
                global_small_code_face = try_create_new_face(app, &desc);
            } else {
                global_small_code_face = face_that_should_totally_be_there;
            }
        }
    }
    
    //~ NOTE(rjf): Prep virtual whitespace.
    {
        def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
        clear_all_layouts(app);
    }
}

#undef procedure
#undef cast
