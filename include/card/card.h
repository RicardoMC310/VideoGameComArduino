#ifndef __CARD_H__
#define __CARD_H__

typedef void (*APP_FUNC_SETUP)();
typedef void (*APP_FUNC_UPDATE)();
typedef void (*APP_FUNC_EXIT)();

typedef struct {
    APP_FUNC_SETUP func_setup;
    APP_FUNC_UPDATE func_update;
    APP_FUNC_EXIT func_exit;
} app_vtable_t;

void card_init();
void card_update();
void card_change();

#endif