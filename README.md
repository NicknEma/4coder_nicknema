# Ryan Fleury's Personal 4coder Custom Layer

1. `cd path/to/4coder/custom`
2. `git clone https://github.com/dion-systems/4coder_fleury`
3. `cd 4coder_fleury && build`

## Customizing 4coder

# Custom commands

Write a function using the CUSTOM_COMMAND_SIG macro, like this:

```C
CUSTOM_COMMAND_SIG(command_name) {
	// Command implementation
}
```

The macro will expand to a function signature that will be detected by the meta-program, and added into the custom layer.