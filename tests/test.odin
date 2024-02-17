package test;

main :: proc() {
	if 0 < 1 {
		;
	}
	
	if 1 > 0 {
		;
	}
	
	a := 0
		d := 1
}

odin_foo :: proc() {
	
}

odin_bar :: #force_inline proc() {
	
}

odin_baz :: #force_inline proc "contextless" () {
	
}

odin_bin :: proc "contextless" (a: int, b: f32) -> (res: bool) {
	odin_baz()
}

Point2i32 :: [2]i32;
integer   :: int;
voidstar  :: distinct rawptr;
Product_Type :: struct { }
Sum_Type  :: union { }
PI        :: 3.14;
