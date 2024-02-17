// #pragma comment(lib, "custom_4coder_temp.lib")
#pragma comment(lib, "test_2.lib")

// extern "C" void custom_layer_init(struct Application_Links *app);
extern "C" int foo(void);

int main() {
	(void)foo();
	// custom_layer_init(0);
}

namespace test {
	
}

extern "C" {
	
	
}
