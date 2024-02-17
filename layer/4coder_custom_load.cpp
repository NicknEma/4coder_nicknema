#ifndef FCODER_CUSTOM_LOAD_CPP
#define FCODER_CUSTOM_LOAD_CPP

NAMESPACE_BEGIN(nne)

internal void apply_parsed_config() {
	; // @Unimplemented(ema).
}

internal void parse_config_and_apply() {
	; // @Unimplemented(ema).
}

internal void load_config_and_apply(Application_Links *app, Arena *out_arena, i32 override_font_size, b32 override_hinting) {
    Scratch_Block scratch(app, out_arena);
    
    linalloc_clear(out_arena);
    
	// Load the config file from the "normal" paths.
    Config *parsed = 0;
    FILE *file = def_search_normal_fopen(scratch, "config.4coder", "rb");
    if (file != 0){
        String_Const_u8 data = dump_file_handle(scratch, file);
        fclose(file);
        if (data.str != 0){
            parsed = def_config_from_text(app, scratch, str8_lit("config.4coder"), data);
        }
    } 
    
    if (parsed) {
        // The config file was parsed correctly.
		// Print errors.
        String_Const_u8 error_text = config_stringize_errors(app, scratch, parsed);
        if (error_text.str != 0) {
            print_message(app, string_u8_litexpr("trying to load config file:\n"));
            print_message(app, error_text);
        }
        
        // Save the parsed config file in the variable table, then print the variables.
		// 'Variable_Handle' has a 'next' pointer to allow us to reach the next. A single 'Variable_Handle' could be
		// a handle to multiple variables, as it is in this case.
        if (error_text.str == 0){
            // TODO(allen): this always applies to "def_config". need to get "usr_config" working too.
            Variable_Handle config_vars = def_fill_var_from_config(app, vars_get_root(), vars_save_string_lit("def_config"), parsed);
			vars_print(app, config_vars);
            print_message(app, string_u8_litexpr("\n"));
        }
    } else {
		// The config file was NOT parsed correctly.
        print_message(app, string_u8_litexpr("Using default config:\n"));
        Face_Description description = get_face_description(app, 0);
        if (description.font.file_name.str != 0) {
			// 'vars_save_string_lit' saves the passed string in a table (if it isn't already) and returns the corresponding String_ID.
			// I think 'def_set_config_string' associates the second arg string to the first arg String_ID (that references a string in the variable table).
			
            def_set_config_string(vars_save_string_lit("default_font_name"), description.font.file_name);
        }
    }
    
	// After you saved all the variables in the table, start looking them up
	// and apply their values to the editor.
	
	// Lookup in the variables table the key "default_font_name" and retrieve its value (which in this case is a string).
    String_Const_u8 default_font_name = def_get_config_string(scratch, vars_save_string_lit("default_font_name"));
    if (default_font_name.size == 0) {
        default_font_name = string_u8_litexpr("liberation-mono.ttf");
    }
    
    // TODO(allen): this part seems especially weird now.
    // We want these to be effected by evals of the config system,
    // not by a state that gets evaled and saved *now*!!
    
	// Apply mode.
    String_Const_u8 mode = def_get_config_string(scratch, vars_save_string_lit("mode"));
    change_mode(app, mode); // @Todo: What is mode? Notepad vs emacs?
    
	// Apply lalt_lctrl_is_altgr.
    b32 lalt_lctrl_is_altgr = def_get_config_b32(vars_save_string_lit("lalt_lctrl_is_altgr"));
    global_set_setting(app, GlobalSetting_LAltLCtrlIsAltGr, lalt_lctrl_is_altgr);
    
	// Apply theme.
    String_Const_u8 default_theme_name = def_get_config_string(scratch, vars_save_string_lit("default_theme_name"));
    Color_Table *colors = get_color_table_by_name(default_theme_name);
    set_active_color(colors);
    
	// Apply font.
	// Start with the font size.
    Face_Description description = {};
    if (override_font_size != 0) {
        description.parameters.pt_size = override_font_size;
    } else {
        description.parameters.pt_size = cast(i32)def_get_config_u64(app, vars_save_string_lit("default_font_size"));
    }
    if (description.parameters.pt_size == 0) {
        description.parameters.pt_size = 12;
    }
    
	// Then lookup the hinting mode.
    b32 default_font_hinting = def_get_config_b32(vars_save_string_lit("default_font_hinting"));
    description.parameters.hinting = default_font_hinting || override_hinting;
    
	// Then the anti-aliasing mode.
    Face_Antialiasing_Mode aa_mode = FaceAntialiasingMode_8BitMono;
    String8 aa_mode_string = def_get_config_string(scratch, vars_save_string_lit("default_font_aa_mode"));
    if (string_match(aa_mode_string, str8_lit("8bit"))) {
        aa_mode = FaceAntialiasingMode_8BitMono;
    } else if (string_match(aa_mode_string, str8_lit("1bit"))) {
        aa_mode = FaceAntialiasingMode_1BitMono;
    }
    description.parameters.aa_mode = aa_mode;
    
    description.font.file_name = default_font_name;
    if (!modify_global_face_by_description(app, description)) {
        String8 name_in_fonts_folder = push_u8_stringf(scratch, "fonts/%.*s", string_expand(default_font_name));
        description.font.file_name = def_search_normal_full_path(scratch, name_in_fonts_folder);
        b32 modified = modify_global_face_by_description(app, description);
		cast(void)modified;
    }
    
	// Apply binding mode.
    b32 bind_by_physical_key = def_get_config_b32(vars_save_string_lit("bind_by_physical_key"));
    if (bind_by_physical_key) {
        system_set_key_mode(KeyMode_Physical);
    } else {
        system_set_key_mode(KeyMode_LanguageArranged);
    }
}

NAMESPACE_END()

// @Todo(ema): Reload from the current directory (not project)? Is it possible?
// Probaily use def_search_normal_load_list() to get the executable directory (the so-called BinPath?)

// @Todo(ema): With the same strategy also add a command that goes to the executable directory (sets it as the current directory). It's the parallel to Ctrl+H that goes to the project directory.

CUSTOM_COMMAND_SIG(load_config_from_project_directory)
CUSTOM_DOC("Load and apply the config.4coder file from the project directory.") {
	Face_Description description = get_face_description(app, 0);
	nne::load_config_and_apply(app, &global_config_arena, description.parameters.pt_size, description.parameters.hinting);
}

CUSTOM_COMMAND_SIG(load_config_from_current_buffer)
CUSTOM_DOC("Load and apply the config.4coder file from the current buffer.") {
	; // @Unimplemented(ema).
}

CUSTOM_COMMAND_SIG(load_bindings_from_project_directory)
CUSTOM_DOC("Load and apply the bindings.4coder file from the project directory.") {
	if (!nne::dynamic_binding_load_from_file(app, &framework_mapping, Str_U8("bindings.4coder"))) {
		nne::set_default_bindings(&framework_mapping);
	}
	nne::set_absolutely_necessary_bindings(&framework_mapping);
}

CUSTOM_COMMAND_SIG(load_bindings_from_current_buffer)
CUSTOM_DOC("Load and apply the bindings.4coder file from the current buffer.") {
	; // @Unimplemented(ema).
}


#endif // FCODER_CUSTOM_LOAD_CPP
