# My fork of Ryan Fleury's personal 4coder custom layer

1. `cd <wherever you want>`
2. `git clone https://github.com/NicknEma/4coder_nicknema`
3. Go into `build.bat` and `build_lexers.bat` and change `editor_loc` to be the location of 4ed.exe
4. Go into `project.4coder` and change the 2nd of the `load_paths_base` to be the location of 4ed.exe
5. `build`

_NOTE: On Windows, the path_to.4coder string has to use backslashes (\) instead of forward slashes (/) because the 'copy' utility doesn't accept those._

## Customizing 4coder

# Custom commands

Write a function using the CUSTOM_COMMAND_SIG macro, like this:

```C
CUSTOM_COMMAND_SIG(command_name) {
	// Command implementation
}
```

The macro will expand to a function signature that will be detected by the meta-program and added into the custom layer.

# Using the `config.4coder` file

The `config.4coder` file is parsed as a series of C++ tokens, so it follows the same rules for comments, semicolons, etc. After it is parsed, each variable gets saved in a 'variable table' together with its value. Each piece of code wanting to use a config variable can lookup into that table and use the result. Some variables are looked up immediately after being saved (i.e the font), others only when needed (like when running a command or during an editor tick).

If the code tries to lookup a variable that isn't in the table (for example if the variable is commented out in the `config.4coder` file), it is simply added into the table with a default value.
