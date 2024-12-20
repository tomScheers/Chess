#include "platform.h"

void init() {
}

void update(float dt) {

}

void render() {
}

AppDesc chess_main(int argc, char **argv) {
	return (AppDesc){
		.title = "Chess",
		.init_cb = init,
		.update_cb = update,
		.render_cb = render
	};
}