// Работа выполнялась на операционной система GNU/Linux Manjaro x86_64
// Для выполнения лабраторной использована библиотека raylib
// Для компилияци нужно использовать make build <prog.cpp> 
// Для компиляции и последующего запуска make run <prog.cpp> 
// В обоих случаях компилируется исполняемы файл bin/prog
// Для данного файла make run draw1.cpp 

#include "raylib.h"

const int screen_width = 800;
const int screen_height = 600;
const int fly_cost = 120;
const float fly_delay = 0.30f;

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
	}
};

// Класс сплошного круга.
class Circle : public Shape {
protected:
	int radius;

public:
	// Инициализирует круг с заданным радиусом.
	Circle(int x_init, int y_init, int radius_init, Color color_init)
		: Shape(x_init, y_init, color_init), radius(radius_init) {}

	// Рисует круг на экране.
	void show(void) const override {
		DrawCircle(x, y, (float)radius, color);
	}

	// Скрывает круг, отдельное стирание не требуется.
	void hide(void) const override {}
};

// Класс кольца.
class Ring : public Circle {
private:
	int width;

public:
	// Инициализирует кольцо с заданной толщиной.
	Ring(int x_init, int y_init, int radius_init, Color color_init, int width_init)
		: Circle(x_init, y_init, radius_init, color_init), width(width_init) {}

	// Рисует кольцо на экране.
	void show(void) const override {
		DrawCircle(x, y, (float)radius, color);
		DrawCircle(x, y, (float)(radius - width), RAYWHITE);
	}
};

int main(void){
	// создание окно
	InitWindow(screen_width, screen_height, "draw1");
	if (!IsWindowReady()){
		return 1;
	}

	SetTargetFPS(60);
	SetRandomSeed((unsigned int)GetTime());

	Circle my_circle(200, 200, 30, RED);
	Ring my_ring(400, 300, 50, BLUE, 10);

	bool is_flying = false;
	float fly_timer = 0.0f;
	
	// основной цикл графического приложения
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
		DrawText("Esc - close window", 20, 50, 20, DARKGRAY);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
