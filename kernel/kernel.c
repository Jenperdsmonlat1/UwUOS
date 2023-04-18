#include "../libs/stdio/stdio.h"
#include "../driver/vga/text_mode/vga.h"
#include "../idt/idt.h"
#include "../gdt/gdt.h"
#include "../driver/keyboard/keyboard.h"
#include "../io/pit/pit.h"
#include "../io/rtc/rtc.h"
#include "../driver/vga/graphics_mode/vga_graphics.h"
#include <stdint.h>


char *days[] = {
    "Dimanche",
    "Lundi",
    "Mardi",
    "Mercredi",
    "Jeudi",
    "Vendredi",
    "Samedi",
};

char *months[] = {
    "Janvier",
    "Fevrier",
    "Mars",
    "Avril",
    "Mai",
    "Juin",
    "Juillet",
    "Aout",
    "Septembre",
    "Octobre",
    "Novembre",
    "Decembre"
};


void print_date();

void kernel_main() {

    terminal_init(VGA_WHITE, VGA_BLACK);
    
    init_gdt();
    init_idt();
    init_keyboard();
    init_pit(10);
    setup_rtc();
    printf("[kernel]: Welcome.\n");
    print_date();
    init_vga();
    draw_rect(20, 20, 0, 0, 70);
    draw_rect(20, 20, 25, 25, 71);
}

void print_date() {

    char day[3], year[5];
    uint16_t years, day_, day_get, years_get;
    
    day_ = get_register_infos(DAY_OF_MONTH);
    day_get = (day_ & 0x0F) + ((day_ / 16) * 10);
    itoa(day_get, day, 10);

    years = get_register_infos(YEAR);
    years_get = 2000 + (years & 0x0F) + ((years / 16) * 10);

    itoa(years_get, year, 10);
    
    printf("[kernel]: Date du jour: ");
    printf(days[get_register_infos(WEEKDAY) - 1]);
    printf(" ");
    printf(day);
    printf(" ");
    printf(months[get_register_infos(MONTHS) - 1]);
    printf(" ");
    printf(year);
    printf("\n");
}
