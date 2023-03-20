#include <iostream>

#include <Vang.h>

int main() {
	auto vangInst = VangInst::Get("VangApp");
	bool running  = true;
	while (running) {
		vangInst.beginFrame();



		vangInst.endFrame();
	}
	vangInst.cleanup();
}