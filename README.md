# My fork of Ryan Fleury's personal 4coder custom layer

1. `cd <wherever you want>`
2. `git clone https://github.com/NicknEma/4coder_nicknema`
3. Go into `build.bat` and `build_lexers.bat` and change `editor_loc` to be the location of 4ed.exe
4. Go into `project.4coder` and change the 2nd of the `load_paths_base` to be the location of 4ed.exe
5. `build`

## Customizing 4coder

# Custom commands

Write a function using the CUSTOM_COMMAND_SIG macro, like this:

```C
CUSTOM_COMMAND_SIG(command_name) {
	// Command implementation
}
```

The macro will expand to a function signature that will be detected by the meta-program, and added into the custom layer.