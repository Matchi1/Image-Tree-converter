#include "../include/Page.h"
#include "../include/Window.h"

static Page pages[10];

/**
 * Pages information per index:
 * 0 : Menu
 * 1 : Choose Image
 */

/**
 * Initialize the buttons necessary for the menu
 */
void init_menu_page(void){
	int i, x = 200, y = 100;
	Page menu = pages[0];

	for(i = 0; i < 8; i++){
		init_button(
				&(menu.widget[i]),
				x, y + i * 50,
				400, 200,
				i, NULL, MLV_COLOR_WHITE );
	}
}

/**
 * Initialize the buttons necessary for the image selector page
 */
void init_select_page(void){
	int i, j, x = 50, y = 100;
	int img_w = 50, img_h = 50;
	Page select = pages[1];

	for(i = 0; i < 3; i++){
		for (j = 0; j < 3; i++){
			init_button(
					&(select.widget[i]),
					x + (i * 50 + 25), y + (j * 50 + 25),
					img_w, img_h,
					SELECT, NULL, MLV_COLOR_WHITE);
		}
	}
}

void init_image_convert(void){
	int x, y;
	Page p = pages[3];

	x = (WINDOW_W - IMAGE_SIZE) / 2;
	y = (WINDOW_H - IMAGE_SIZE) / 2;
	init_button(
			&(p.widget[0]),
			x, y,
			512, 512,
			SELECT, NULL, MLV_COLOR_WHITE);
}

void init_pages(void){
	init_menu_page();
	init_select_page();
}

/**
 * @brief Verify if a button has been pressed with a mouse click
 * @param x the position of the click in the X axis
 * @param y the position of the click in the Y axis
 * @param buttons an array of Figure structure
 * @ret the associated Action of the button else -1
 */
int click(int x, int y, Figure* buttons){
	int i, x_min, x_max, y_min, y_max;
	for(i = 0; i < NB_BUTTONS; i++){
		x_min = buttons[i].x;
		x_max = buttons[i].x + buttons[i].length_x;
		y_min = buttons[i].y;
		y_max = buttons[i].y + buttons[i].length_y;
		if(x_min <= x && x <= x_max && y_min <= y && y <= y_max)
			return buttons[i].action;
	}
	return -1;
}

void figure_append(Page *page, Figure *wgt){
	(page->elt_nb)++;
	wgt->next = page->widget;
	page->widget = wgt;
}

/**
 * @brief Enter into the menu of the project
 * This menu display the action that can be done by the program
 * @param width width of the window
 * @param height height of the window
 * @ret the action choosen by the user
 */
Action menu(int width, int height){
	Figure arr_buttons[NB_BUTTONS];
	int x, y;
	Action value = -1;

	init_menu_button(arr_buttons);
	align_buttons(width, height, arr_buttons);

	MLV_clear_window(MLV_COLOR_BLACK);
	draw_buttons(arr_buttons);

	while(value == -1){
		MLV_wait_mouse(&x, &y);
		value = click_on_buttons(x, y, arr_buttons);
	}
	MLV_actualise_window();
	return value;
}
