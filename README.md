# My fork of Ryan Fleury's personal 4coder custom layer

## Build

### Windows

1. Install MSVC and run a developer command prompt.
2. Clone this repository wherever you want.
3. Open `path_to.4coder` and write the exact path to the 4coder editor.

_NOTE: On Windows, the path_to.4coder string has to use backslashes (\\) instead of forward slashes (/) because the 'copy' utility doesn't accept those._

4. Run `scripts\build.bat`.
5. If you want to use the provided config and bindings, , run `scripts\unnamed.bat`.

## Run

- If you want the full codebase to be loaded with the project, go into `project.4coder` and change the 2nd of the `load_paths_base` to be the location of 4ed.exe

## Customizing 4coder

### Themes, bindings and configs

These three file types are parsed by 4coder as a series of C++ tokens; this means they follow the same rules for comments, semicolons, etc; They are loaded by the editor at startup, so make sure they are in the correct directory before you run the program.

After the config file is parsed, each variable gets saved in a 'variable table' together with its value. Each piece of code wanting to use a config variable can lookup into that table and use the result. Some variables are looked up immediately after being saved (i.e the font), others only when needed (like when running a command or during an editor tick).

If the code tries to lookup a variable that isn't in the table (for example if the variable is commented out in the `config.4coder` file), it is simply added into the table with a default value.

### Custom commands

Write a function using the CUSTOM_COMMAND_SIG macro, like this:

```C
CUSTOM_COMMAND_SIG(command_name) {
	// Command implementation
}
```

The macro will expand to a function signature that will be detected by the meta-program and added into the custom layer.
