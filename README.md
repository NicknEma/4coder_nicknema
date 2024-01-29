# My fork of Ryan Fleury's personal 4coder custom layer

1. `cd path/to/4coder/custom`
2. `git clone https://github.com/NicknEma/4coder_nicknema`
3. `cd 4coder_nicknema && build`

## Customizing 4coder

# Custom commands

Write a function using the CUSTOM_COMMAND_SIG macro, like this:

```C
CUSTOM_COMMAND_SIG(command_name) {
	// Command implementation
}
```

The macro will expand to a function signature that will be detected by the meta-program, and added into the custom layer.