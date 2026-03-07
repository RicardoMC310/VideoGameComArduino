#include "card/card.h"

extern app_vtable_t app1_vtable;
extern app_vtable_t app2_vtable;

app_vtable_t *apps[] = {
    &app1_vtable,
    &app2_vtable};
app_vtable_t *current_app;
unsigned short current_index_app;

#define APPS_COUNT (sizeof(apps) / sizeof(apps[0]))

void card_init()
{
    current_app = apps[0];
    current_index_app = 0;

    if (current_app && current_app->func_setup)
        current_app->func_setup();
}

void card_update()
{
    if (current_app && current_app->func_update)
        current_app->func_update();
}

void card_change()
{
    if (current_app && current_app->func_exit)
        current_app->func_exit();

    current_index_app = (current_index_app + 1) % APPS_COUNT;

    current_app = apps[current_index_app];

    if (current_app && current_app->func_setup)
        current_app->func_setup();
}