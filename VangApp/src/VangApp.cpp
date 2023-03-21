#include <iostream>

#include <Vang.h>

int main() {
	VangInst& vangInst = VangInst::Get("VangApp");
	bool running  = true;
	while (running) {
		vangInst.beginFrame();

		vangInst.endFrame();
		if (vangInst.getToClose()) running = false;
	}
}