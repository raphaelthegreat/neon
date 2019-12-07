#include <application.h>

int main() {
	
	unique_ptr<Application> application;
	application = std::make_unique<Application>();
	
	application->init();

	while (!application->should_close()) {

		application->pre_render();
		application->render();

		application->update();
	}
}