
//~ TODO FOR SHAWN
//
// [ ] Project File Opener: Ignore directories, recursively list options.
// [X] Ctrl+Arrows: It's still weird... it skips punctuation weridly.
// [ ] Recent Files Menu: this isn't bad!  If it just defaulted to the first one
//     (but still allowed typing), and if the key that opened it continued to cycle
//     the items in the list (rather than closing the lister), that'd be pretty much
//     it!
// [ ] Tabbing: This is really close, the only problem is if the end of the selection
//     isn't at the beginning of a line it does something really weird -- I'm not sure 
//     what.  It shouldn't matter where the caret is, if multiple lines are selected
//     then tab should move the lines
// [ ] Comments: Very close!  The only problem is the multiple selection, single line 
//     comments: instead of putting the // at the start of each line after the whitespace, 
//     the // should be lined up with the shallowest whitespace..
// [ ] Pressing tab on an empty line inside a scope still doesn't do anything.
// [X] If the caret is at the start of the line and you press home, it doesn't take you to 
//     the first non-whitespace character... basically pressing home more than once should 
//     cycle between the first non-whitespace character and column 0
// [X] Token-like movement inside of comments.
// [ ] ctrl E centres the buffer on the current line,  vim has z. There's:
//     zz -> middle, zt-> top, zb->bottom, but also: z5t will centre it 5
//     lines from the top or whatever... is that something that's easy to add? 
//
// ORIGINAL REQUEST:
// [ ] Fix not showing .-lister when cursor is at end of query
// [ ] Cycle overloads, or list them all
// [ ] Ctrl+I but just for the project buffers
// [ ] Vertical edits
//
// DONE:
//

//~ TODO FOR CASEY
//
// [X] Active pane frame color/thickness control in Fleury config options, to allow turning it
//     off entirely or changing the color
//     done: f4_margin_size and f4_margin_use_mode_color
// [X] Inactive pane color cursor differences
// [X] Filenames to disambiguate indexed stuff with the same name
// [X] Way to get to forward decl for an indexed thing too
//     done: use go-to-definition again, at the definition site, and it should cycle between
//     all the definitions
// [ ] Fix clipboard stuff
// [ ] CPM counter shenanigans

//~ TODO PLOTS
// [ ] Un-Bust Histograms
// [ ] Fix plot clip rect bugs when the plot is not 100% in the visible range
//     (caused by 4coder laying out characters off the screen as being at 0, 0)
// [ ] Labels for histogram bins
// [ ] Plots and Calc are so coupled and I hate it, please rewrite or something

//~ TODO META
// [X] Project-wide todo list (by searching for TODO and DONE comments, lister for toggling)
// [ ] Project switcher
// [ ] Plan + do modal input scheme... Identifier-mode, text-mode, semantics mode, search mode...?

/*
* @TODO(ema):

* FEATURES:
* Cursor as a line
* c++ and odin syntax highlighting
  *  recursively walk imports/includes, record types, macros, constants, procedures, global variables.
* Multiline editing
* Peek definition
* Don't auto-indent comments

* COMMANDS:
* build/run command in opposite panel binding
* Numpad ascii codes

* BINDINGS:
* vsplit and hsplit

Tutorial:
https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_
*/
