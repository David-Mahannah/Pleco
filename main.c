#include <stdio.h>
#include "pleco.h"

int main(int argc, char **argv) {
	// Displau Menu	
	printf("Display Loading bar...\nm");
	printf("PLECO\n");
	
	// Load settings from settings.txt
	settings_t *settings = load_settings("settings.txt");
	if (settings == NULL) {
		printf("Failed to read settings. Exiting\n");
		return 1;
	}

	int success = save_settings("settings_copy.txt", settings);
	if (success == 1) {
		printf("Failed to save the settings...\n");
		return 1;
	}
	
	printf("Ready to update? [y/n] ");
	char c;
	scanf("%c", &c); 
	
	if (update("https://github.com/David-Mahannah/Pleco/tarball/main") == -1) {
		printf("Failed to update... Aborting\n");
		return 1;
	}
	
	return 0;
	// Display main menu
	
}
