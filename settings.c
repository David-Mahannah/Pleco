#include "pleco.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int update(const char * source) {
	// Rename Plect directory to Pleco temp
	// Install newest copy of Pleco
	char cwd [256];
	if (getcwd(cwd, sizeof(cwd)) == 0) {
		printf("Failed to read the current working directory\n");
		return -1;
	}

	printf("Current working directory before move: %s\n", cwd);	

	if (chdir("..") == -1){
		printf("Failed to relocate working directory\n");
		return -1;
	}

	//getcwd(cwd, sizeof(cwd));
	//printf("Current working directory after move: %s\n", cwd);

	char move_buffer [512];
	sprintf(move_buffer, "mv %s temp", cwd);
	if (system(move_buffer) == 0) {
		printf("Failed to rename directory to temp/n");
		//return -1;
	}
	
	// wget("https://github.com/David-Mahannah...");
	char github_link [256];
	if (5 + strlen(source) < 256) {
		sprintf(move_buffer, "wget %s", source);
		if (system(move_buffer) == 0) {
			printf("Failed to fetch the remote repository");
			//return -1;
		}
	} else {
		printf("Source string exceeds string buffer...");
		return -1;
	}

	// tar -xf main
	if (system("tar -xf main") == 0) {
		printf("Failed to unzip the source directory");
	//	return -1;
	}
	
	system("mv David-Mahannah-Pleco* Pleco");

	// delete 
	if (system("rm -rf temp") == 0) {
		printf("Failed to delete old directory\n");
	//	return -1;
	}

	system("rm main*");
	
	if (chdir("Pleco") == -1){
		printf("Failed to relocate working directory\n");
		//return -1;
	}

	system("make");
	execl("pleco", "", NULL);

	return 0;
}

int uninstall() {
	printf("Uninstalling...");

	char cwd [256];
	if (getcwd(cwd, sizeof(cwd)) == 0) {
		printf("Failed to read the current working directory\n");
		return -1;
	}	
	// Delete Pleco directory
	
	if (system("cd ..") == 0){
		printf("Failed to relocate working directory\n");
		return -1;
	}
	
	char buffer [512];
	sprintf(buffer, "rm -rf %s", cwd);
	if (system(buffer) == 0) {
		printf("Failed to delete old directory\n");
		return -1;
	}

	
}


int save_settings(const char * destination, settings_t * settings) {
	// Open file
	FILE * fp = fopen(destination, "w");
	
	if (fp == NULL) {
		printf("Failed to open settings file for writing\n");
		return 1;
	}

	fprintf(fp, "%d\n", settings->num_items);
	
	// Write data to file
	for (int i = 0; i < settings->num_items; i++) {
		fprintf(fp, "%s %s\n", settings->items[i].item, settings->items[i].status);
	}

	fclose(fp);
	
	return 0;
}

settings_t * load_settings(const char * source) {
	
	// Open file
	FILE * fp = fopen(source, "r");
	
	if (fp == NULL) {
		printf("Failed to read settings file: %s\n", source);
		fclose(fp);
		return NULL;
	}
	
	settings_t * settings = malloc(sizeof(settings_t));
			
	// Read data from file
	if (fscanf(fp, "%d", &settings->num_items) == 0) {
		printf("Error while reading %s. File appears to be empty...\n", source);
		free(settings);
		fclose(fp);
		return NULL;
	}
	settings->items = malloc(sizeof(settings_item_t) * settings->num_items);

	for (int i = 0; i < settings->num_items; i++) {
		if (fscanf(fp, "%s : %s\n", settings->items[i].item, 
								settings->items[i].status) == 0) {
			printf("The number of items in your settings is \
					smaller than its header suggests\n");
			settings_cleanup(settings);
			fclose(fp);
			return NULL;
		} 
	}

	fclose(fp);

	return settings;
}

void settings_cleanup(settings_t * settings) {
	free(settings->items);
	free(settings);
}
