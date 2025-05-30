#include <SFML/Graphics.hpp> //simple and fast multimedia lib
#include <iostream>

using namespace std;
using namespace sf;


struct Point {
    float x;
    float y;
};

//рекурсивная функция рисует треугольник Серпинского
void drawSierpinski(RenderWindow& window, Point a, Point b, Point c, int depth) {
    //базовый случай если глубина 0
    if (depth == 0) {
        ConvexShape triangle; //создание фигуры с произвальным количеством углов
        triangle.setPointCount(3); //указываем вершины
        triangle.setPoint(0, Vector2f(a.x, a.y)); //координаты первой вершины
        //индекс вершины, двумерный вектор из точки a в b
        triangle.setPoint(1, Vector2f(b.x, b.y));
        triangle.setPoint(2, Vector2f(c.x, c.y));
        triangle.setFillColor(Color::White); //цвет белый
        window.draw(triangle); //рисовка треугольника на окне
        return;
    }

    // Находим середины сторон
    Point ab = {(a.x + b.x) / 2, (a.y + b.y) / 2}; //верхний треугольник
    Point bc = {(b.x + c.x) / 2, (b.y + c.y) / 2}; //правый
    Point ca = {(c.x + a.x) / 2, (c.y + a.y) / 2}; // левый

    // Рекурсивный вызов для трёх внешних треугольников
    drawSierpinski(window, a, ab, ca, depth - 1); //верхний
    drawSierpinski(window, ab, b, bc, depth - 1); //правый нижний
    drawSierpinski(window, ca, bc, c, depth - 1); // левый нижний
    //уменьшаем глубину рекурсии чтобы фрактал завершился
}

int main() {
    // Размер окна
    int width = 900;
    int height = 700;

    // Создание окно (размер окна, заголовок, стиль только с закрытии кнопки)
    RenderWindow window(
        VideoMode(width, height),
        "Треугольник Серпинского",
        Style::Close
        );

    // Установка глубины рекурсии
    int depth;
    cout << "Введите глубину рекурсии (например, 5): ";
    cin >> depth;
    if (depth < 0 || depth > 10) {
        cout << "Ошибка: глубина должна быть от 0 до 10" << endl;
        return 1;
    }

    //Исходные точки большого треугольника
    Point top = {width / 2.0, 50.0}; //верхняя точка по ширине окна
    Point left = {100.0, height - 50.0}; //левая нижняя вершина треугольника
    Point right = {width - 100.0, height - 50.0}; //правее и ниже центра(правая нижняя точка)

    //Главный цикл окна
    while (window.isOpen()) { //проверяет открыто ли окно
        Event event; //структура (объект) который хранит информацию о событий произошедшем с окном
        while (window.pollEvent(event)) { //проверка очереди событий внутри окна
            if (event.type == Event::Closed) //проверяет было ли событие закрытия окна
                window.close();
        }

        //очистка экрана
        window.clear(Color::Black);

        //рисунок фрактала (окно, три вершины и глубина рекурсии)
        drawSierpinski(window, top, left, right, depth);

        //отображение нарисованного
        window.display();
    }

    return 0;
}
