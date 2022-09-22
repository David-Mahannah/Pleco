typedef struct {
	char item[256];
	char status[256];
} settings_item_t;

typedef struct {
	int num_items;
	settings_item_t * items;
} settings_t;

int update (const char * sources);
int uninstall();
int save_settings(const char * destination, settings_t * settings);
settings_t * load_settings(const char * sources);
