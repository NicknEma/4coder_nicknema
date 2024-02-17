//~ @f4_readme Ryan Fleury's 4coder Custom Layer
//
// Hello! Thank you for checking out my custom layer. This layer is a collection
// of things I've found to be useful, funny, or interesting overtime. It includes
// a few things that makes 4coder feel a bit more like an IDE, a few things that
// are just for kicks and are ridiculous, and a few interesting editor experiments.
// Below is a list of features, along with more information about them and some
// options you can tweak to your liking. To get as much customization as possible,
// you'd obviously have to dig a bit more into the code and probably write your
// own custom layer and just use stuff from this custom layer as a library, but
// the below options are just to allow easy customization of the low-hanging
// fruit.

//~ @f4_features 4coder Fleury Feature/Option List

//- @f4_lang_intro Multi-Language Support
//
// This custom layer has been tweaked to allow for better multi-language support
// in 4coder. It isn't perfect and will not support all languages, but it works
// for more than C/C++ (which historically 4coder has been fairly coupled to). 
//
// List of supported languages (as of 2021/01/29):
// - C
// - C++, partially... if you do a lot of modern C++ (I hope not), nothing
//   me or 4coder do can help you much (in fact, maybe nothing can help you)
// - Jai
// - Metadesk
//
// Adding a language requires a few steps.
//
// 1. Adding a lexer (probably the hardest part)
// 
// 4coder comes bundled with some lexer generation things. They are hard for me
// to understand, but all the languages I've had to deal with have been fairly
// easy to adapt from C++'s lexer. You can take a look at 4coder_cpp_lexer_gen.cpp,
// and copy/paste it into a new file that can generate the lexer for whatever
// language. This is what I did for the Jai lexer. Take a look at build_lexers.bat
// to see what I do to generate the Jai lexing code.
//
// Alternatively, you can hand-roll a lexer. This is a lot simpler (but of course
// gets harder with more complex languages). You can see an example of this in
// the Metadesk language implementation (4coder_fleury_lang_metadesk.cpp).
//
// 2. Implement language hooks
//
// The language system has each language expose a few hooks in v-table-like
// fashion. This allows general editor code to "ask questions" about specific
// language concepts. Here is a list of the hooks:
//
// - IndexFile hook, implement w/ F4_LANGUAGE_INDEXFILE(name) { /* code */ }
//   Used to scan tokens of a file and do heuristic parses to pull out language
//   info, like function/type definitions and stuff.
//
// - LexInit hook, implement w/ F4_LANGUAGE_LEXINIT(name) { /* code */ }
//   A hook that lets you initialize any state you want for your lexer.
//   This is also one of the functions that can be generated for you with
//   the language lexer generator that comes with 4coder. For C++, the name
//   of the function is lex_full_input_cpp_init, so take that and adjust as
//   needed for your language.
//
// - LexFullInput hook, implement w/ F4_LANGUAGE_LEXFULLINPUT(name) { /* code */ }
//   A hook to lex the whole input of a file that is determined to be in a given
//   language. This is also a hook that can be generated with 4coder's lexer
//   generator stuff. For C++, the name of the function is lex_full_input_breaks,
//   so take that and adjust as needed for your language.
//
// - PosContext hook, implement using F4_LANGUAGE_POSCONTEXT(name) { /* code */ }
//   This hook is called into by some rendering features looking for contextual
//   information, usually about the cursor position. For example, figuring out
//   if the cursor is inside some arguments for a function, so a tooltip can be
//   displayed. You can just return 0 if you don't want to deal with this.
//
// - Highlight hook, implement using F4_LANGUAGE_HIGHLIGHT(name) { /* code */ }
//   This hook does any additional syntax highlighting that you want for the
//   language. You don't need to do anything here if you don't want to, in fact
//   you won't need this most of the time probably.
//
// 3. Add the info for your language to the 4coder_fleury_lang_list.h file.
// More information is in that file.

//- @f4_colors_intro Syntax Highlighting and Color Additions
//
// 4coder provides very basic syntax highlighting, but this layer implements
// some more features, particularly ones that rely on the code index. There
// are custom colors that this layer looks for from a theme file so that it
// can use good colors for these. Additionally, many other features (e.g.
// various rendering features that are mentioned elsewhere in here) also need
// custom colors. Here is a list of the colors this layer looks for:
//
// - fleury_color_syntax_crap: Used to change the color of textual syntax stuff
//   that is not really semantically important, but we have to type it anyways,
//   stuff like ;'s and parentheses and stuff.
//
// - fleury_color_operators: The color of operators (+, ?, etc.).
//
// - fleury_color_inactive_pane_overlay: The color of a panel-sized rectangle
//   drawn over panels that are not active, to leave the active panel slightly
//   brighter.
//
// - fleury_color_inactive_pane_background: The color of a panel-sized rectangle
//   drawn *behind* panels that are not active, to leave the active panel slightly
//   brighter.
//
// - fleury_color_file_progress_bar: The color to render the progress bar, drawn
//   over the file bar in a panel.
//
// - fleury_color_brace_highlight: The color used for the brace highlight feature.
//
// - fleury_color_brace_line: The color used for the brace line feature.
//
// - fleury_color_brace_annotation: The color used for the brace annotation
//   feature.
//
// - fleury_color_index_sum_type: The color used for names of sum-types
//   (unions).
//
// - fleury_color_index_product_type: The color used for names of product-
//   types (structs, classes, whatever).
//
// - fleury_color_index_function: The color used for names of functions.
//
// - fleury_color_index_macro: The color used for names of macros.
//
// - fleury_color_index_constant: The color used for names of constants
//   (including enum values).
//
// - fleury_color_index_comment_tag: The color used for comment tags,
//   like this! @example_comment_tag
//
// - fleury_color_cursor_macro: The color used for the cursor when a macro
//   is being recorded.
//
// - fleury_color_cursor_power_mode: The color used for the cursor when
//   Power Mode is activated.
//
// - fleury_color_plot_cycle: The set of colors used for colors in plots.
//
// - fleury_color_token_highlight: The color used to underline/highlight
//   tokens that the cursor is over.
//
// - fleury_color_token_minor_highlight: The Color That is used for minor
//   highlights. i.e. cursor token occurance underlines.
//
// - fleury_color_comment_user_name: The color used to highlight the
//   username in comments.
// 
// - fleury_color_error_annotation: Text color used for the inline error
//   message string with F4_RenderErrorAnnotations


//- @f4_render_intro Rendering Features
//
// Many of the features in this layer are just rendering tweaks/improvements to
// 4coder's defaults. Below is a list of features and some options for them.
//
// - Brace Highlighting: When the cursor is inside of a pair of {}'s, highlight 
//   the brace symbols. Turn it off with "f4_disable_brace_highlight" in your
//   config file.
//
// - Close-Brace Annotations: When the cursor is inside a pair of {}'s, BUT
//   you cannot see the top of the scope, render a little annotation to the
//   right of the }, showing the code that was before the {. Turn it off with
//   "f4_disable_close_brace_annotation" in your config file.
//
// - Brace Lines: In many editors, they will draw a vertical line connecting
//   { and }'s in a file. This feature does that when the cursor inside the
//   scope. Turn it off with "f4_disable_brace_lines" in your config file.
//
// - Progress Bar: Colors the file bar (at the top of a 4coder panel) with
//   a "progress bar", showing you how far your cursor is in a file. Turn it
//   off with "f4_disable_progress_bar" in your config file.
//
// - Divider Comments: Any single-line comments starting with a ~ character
//   (e.g. //~) will render a horizontal line over them, acting as a divider
//   (used as an alternative to gigantic lines of -------'s or whatever).
//   Turn it off with "f4_disable_divider_comments" in your config file.
//
// - Error Annotations: When an error is parsed from compilation output in the
//   *compilation* window, it will display what that error is to the right of
//   the line. Turn it off with "f4_disable_error_annotations" in your config
//   file.
//
// - Cursor Identifier Highlight: The Identifier under the cursor is highlighted
//   with an underline (using the fleury_color_token_highlight color). It also
//   highlights all other occurances of the identifier (by string) that is
//   visible and syntax highlighted (occurances are highlighted using 
//   "fleury_color_token_minor_highlight". Turn the highlight of other occurances
//   off with "f4_disable_cursor_token_occurance" in your config file.

//- @f4_pos_context_intro Language Position-Context Tooltips
//
// This feature shows tooltips relating to the current cursor position, as it
// adheres to the programming language of the buffer in question. For example,
// if a buffer's language has implemented the PosContext hook, then when the
// cursor is inside a function call, it will show a tooltip of the arguments,
// and which one the cursor is over. Same thing with struct listers.
//
// Normally, this renders at the cursor location, but you can make it render
// in a perhaps less-distracting location (at the bottom of the buffer) with
// "f4_poscontext_draw_at_bottom_of_buffer" in your config file.
//
// Alternatively, you can turn the whole thing off with "f4_disable_poscontext"
// in your config file.

//- @f4_commands
//
// There are a lot of commands you can bind in your bindings.4coder file that
// have been helpful for me and others. Here is a list of the most useful ones.
// If you want to check out the code, go look at 4coder_fleury_base_commands.cpp.
//
// - f4_search: Will search forward in a buffer. When in notepad-like mode, will
//   use the current selection as the search query.
//
// - f4_reverse_search: Same thing as f4_search, just goes backwards.
//
// - f4_write_text_input: Use this instead of the default 4coder write_text_input
//   if you want Power Mode features.
//
// - f4_write_text_and_auto_indent: Same thing as above. Use over the default 4coder
//   equivalent if you want Power Mode features.
//
// - f4_write_zero_struct: 4coder provides a helper like this already, which writes
//   a C++-style '= {};' initializer, but this doesn't work for C (which uses '= {0}'),
//   yeah I know why the fuck don't we have a concise way to zero-initialize things
//   in both languages :) Anyways, bind this command to whatever you want if you want
//   to use it.
//
// - f4_home: 4coder obviously provides a default binding for the Home key, but it
//   doesn't move the view back over to the left margin, and that bothers me, so
//   I wrote a command that does exactly that.
//
// - f4_toggle_battery_saver: Some of the rendering features in this custom layer
//   include some animations, because I like animations. This will disable them,
//   so your laptop doesn't get hot. Set its default value with "f4_battery_saver"
//   in your config file.
//
// - f4_disable_cursor_trails: Turns off cursor animation.
//
// - f4_toggle_compilation_expand: Expands/shrinks the *compilation* panel at the
//   bottom of the screen. Bind this to a key that you want to press when you are
//   checking out the output of a build, and be sure to send your build commands
//   here!
//
// - f4_go_to_definition: Uses the identifier that the cursor is currently over
//   as a lookup into the code index. Will open its definition, if it finds one,
//   in the panel that the cursor is not in.
//
// - f4_go_to_definition_same_panel: Same as above except does it in the same
//   panel.
//
// - f4_search_for_definition__project_wide: Opens a lister with all definitions
//   from all the code that is open. You can search by typing into it, and then
//   navigating to the right item, and hitting enter. It will then take you to
//   the location of that definition.
//
// - f4_search_for_definition__current_file: Same as above, except restricts the
//   search to definitions in the file that your cursor is in.
//
// - f4_toggle_enclosure_side: When inside a scope or parentheses, moves the
//   cursor between the starting/ending position of that scope/parentheses.
//
// - f4_open_project: Opens a project file. Navigate to a project file on disk,
//   and when you select it, it will be loaded.
//
// - f4_setup_new_project: Makes a new project file at the location that you
//   specify.
//
// - f4_move_left: Move the cursor left. I have my own to correct for some
//   behavior issues with notepad-like mode. I've tried to converge to VS-like
//   behavior as much as possible with notepad-like mode, so use this if that's
//   what you want.
//
// - f4_move_right: Same as above, except right.
//
// - f4_move_right_token_boundary: Implements the equivalent of your VS-style
//   Ctrl+Right.
//
// - f4_move_left_token_boundary: Implements the equivalent of your VS-style
//   Ctrl+Left.
//
// - f4_backspace_token_boundary: Implements the equivalent of your VS-style
//   Ctrl+Backspace.
//
// - f4_delete_token_boundary: Implements the equivalent of your VS-style
//   Ctrl+Delete.
//
// - f4_backspace_alpha_numeric_or_camel_boundary: Does backspace, but restricts
//   it to camel-case and alphanumeric boundaries. Kind of like Ctrl+Backspace
//   except with different groupings.
//
// - f4_delete_alpha_numeric_or_camel_boundary: Same as above, just does it forward.
//
// - f4_home_first_non_whitespace: Implements VS-style Home key, where it first
//   goes to the first non-whitespace character on the line, then all the way to
//   the left margin, then back again. Bind this to Home if you want VS-like
//   behavior.
//
// - f4_autocomplete_or_indent: Autocompletes an incomplete word at the cursor, or
//   indents the line.
//
// - f4_unindent: Similar to Shift+Tab in VS.
//
// - f4_comment_selection: VS-style selection commenting.
//
// - f4_uncomment_selection: VS-style uncommenting.
