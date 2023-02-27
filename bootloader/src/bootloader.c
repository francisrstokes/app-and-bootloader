#include <stdint.h>

#define MAIN_APP_START ((uint32_t*)0x08008000)

static void jump_to_main(void) {
	// Try to make this series of casts a little more readable with some types
	typedef void (*jump_fn_t)(void);

	// The first entry in the vector table is the stack pointer, so we need to add
	// 4 bytes to get to the reset handler entry
	const uint32_t main_app_reset_handler = *(MAIN_APP_START + 1);

	// Cast the reset handler address to a jump_fn_t, and call it
	((jump_fn_t)(main_app_reset_handler))();
}

int main(void)
{
	jump_to_main();

	// We'll never reach this point
	while (1) {}
	return 0;
}
