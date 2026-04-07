#include "raylib.h"

const int screen_width = 800;
const int screen_height = 600;
const int fly_cost = 120;
const float fly_delay = 0.30f;
const int color_count = 6;

Color figure_colors[color_count] = {RED, BLUE, GREEN, ORANGE, MAGENTA, BROWN};

// Базовый абстрактный класс для фигур.
class Shape {
protected:
	int x;
	int y;
	Color color;

public:
	// Инициализирует координаты и цвет фигуры.
	Shape(int x_init, int y_init, Color color_init) : x(x_init), y(y_init), color(color_init) {}

	// Освобождает объект через базовый указатель.
	virtual ~Shape() = default;

	// Рисует фигуру на экране.
	virtual void show(void) const = 0;

	// Скрывает фигуру, в raylib не используется отдельно.
	virtual void hide(void) const {}

	// Возвращает текущие координаты фигуры.
	void locat(int& xl, int& yl) const {
		xl = x;
		yl = y;
	}

	// Обновляет дополнительные эффекты фигуры.
	virtual void update_effects(void) {}

	// Случайно перемещает фигуру внутри окна.
	void fly(int cost, int max_x, int max_y) {
		int xx;
		int yy;

		locat(xx, yy);

		do {
			xx = x + GetRandomValue(-(cost / 2), cost / 2);
		} while (xx <= 0 || xx >= max_x);

		do {
			yy = y + GetRandomValue(-(cost / 2), cost / 2);
		} while (yy <= 0 || yy >= max_y);

		hide();
		x = xx;
		y = yy;
		update_effects();
	}
};

// Класс сплошного круга с вырезанным сектором.
class Circle : public Shape {
protected:
	int radius;
	float sector_size;
	float sector_step;
	int color_index;

	// Переключает цвет фигуры по циклу.
	void change_color(void) {
		color_index++;
		if (color_index >= color_count){
			color_index = 0;
		}
		color = figure_colors[color_index];
	}

public:
	// Инициализирует круг и параметры анимации сектора.
	Circle(int x_init, int y_init, int radius_init, Color color_init)
		: Shape(x_init, y_init, color_init), radius(radius_init), sector_size(40.0f), sector_step(20.0f), color_index(0) {
		for (int i = 0; i < color_count; i++){
			if (figure_colors[i].r == color_init.r &&
				figure_colors[i].g == color_init.g &&
				figure_colors[i].b == color_init.b &&
				figure_colors[i].a == color_init.a){
				color_index = i;
				break;
			}
		}
	}

	// Рисует круг с вырезанным сектором.
	void show(void) const override {
		Vector2 center = {(float)x, (float)y};
		DrawCircleSector(center, (float)radius, sector_size, 360.0f, 100, color);
	}

	// Скрывает круг, отдельное стирание не требуется.
	void hide(void) const override {}

	// Меняет размер сектора и цвет фигуры.
	void update_effects(void) override {
		sector_size += sector_step;
		if (sector_size >= 320.0f || sector_size <= 40.0f){
			sector_step = -sector_step;
			sector_size += sector_step;
		}
		change_color();
	}
};

// Класс кольца с вырезанным сектором.
class Ring : public Circle {
private:
	int width;

public:
	// Инициализирует кольцо с заданной толщиной.
	Ring(int x_init, int y_init, int radius_init, Color color_init, int width_init)
		: Circle(x_init, y_init, radius_init, color_init), width(width_init) {}

	// Рисует кольцо с вырезанным сектором.
	void show(void) const override {
		Vector2 center = {(float)x, (float)y};
		DrawRing(center, (float)(radius - width), (float)radius, sector_size, 360.0f, 100, color);
	}
};

int main(void){
	InitWindow(screen_width, screen_height, "draw");
	if (!IsWindowReady()){
		return 1;
	}

	SetTargetFPS(60);
	SetRandomSeed((unsigned int)GetTime());

	Circle my_circle(200, 200, 30, RED);
	Ring my_ring(400, 300, 50, BLUE, 10);

	bool is_flying = false;
	float fly_timer = 0.0f;

	while (!WindowShouldClose()){
		if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)){
			is_flying = !is_flying;
		}

		if (is_flying){
			fly_timer += GetFrameTime();
			if (fly_timer >= fly_delay){
				my_circle.fly(fly_cost, screen_width, screen_height);
				my_ring.fly(fly_cost, screen_width, screen_height);
				fly_timer = 0.0f;
			}
		} else {
			fly_timer = 0.0f;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		my_circle.show();
		my_ring.show();

		DrawText("Space or Enter - start/stop moving", 20, 20, 20, DARKGRAY);
		DrawText("During movement sector and color change", 20, 50, 20, DARKGRAY);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
