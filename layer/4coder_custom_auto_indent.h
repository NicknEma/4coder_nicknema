#ifndef FCODER_CUSTOM_AUTO_INDENT_H
#define FCODER_CUSTOM_AUTO_INDENT_H

NAMESPACE_BEGIN(nne)

typedef u32 Indent_Flag;
enum {
    Indent_ClearLine  = 0x1,
    Indent_UseTab     = 0x2,
    Indent_FullTokens = 0x4,
	
	// New:
	Indent_RequireStatementCloser = 0x8,
};

internal void write_text_and_auto_indent(Application_Links *app);

NAMESPACE_END()

#endif // FCODER_CUSTOM_AUTO_INDENT_H
