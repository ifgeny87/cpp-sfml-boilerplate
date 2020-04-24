#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Objects {
    CircleShape circle, triangle, penta, octa;
    ConvexShape convex;
    RectangleShape rect, rectLine;
    Sprite smallEarth, middleEarth, bigEarth, coloredEarth;
};

Texture earthTexture, brickwallTexture;
RenderWindow *window;

void sizeSprite(Sprite &sprite, float size) {
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
    float koef = size / sprite.getTexture()->getSize().x;
    sprite.setScale(koef, koef);
}

Objects *init() {
    // круг
    CircleShape circle{70};
    circle.setFillColor(Color(230, 0, 230, 200));
    circle.setOutlineThickness(20);
    circle.setOutlineColor(Color(100, 200, 50, 200));
    circle.setOrigin(75, 75);
    circle.setPosition(100, 100);

    // треугольник
    CircleShape triangle{90, 3};
    triangle.setFillColor(Color::Blue);
    triangle.setOrigin(90, 90);
    triangle.setPosition(300, 115);

    // пентаэдр
    CircleShape penta{90, 5};
    penta.setFillColor(Color::Red);
    penta.setOrigin(90, 90);
    penta.setPosition(500, 105);

    // октаэдр
    CircleShape octa{90, 8};
    octa.setFillColor(Color::Cyan);
    octa.setOrigin(90, 90);
    octa.setPosition(700, 100);

    // многоугольник
    ConvexShape convex{5};
    convex.setPoint(0, Vector2f(0, 0));
    convex.setPoint(1, Vector2f(190, 10));
    convex.setPoint(2, Vector2f(150, 150));
    convex.setPoint(3, Vector2f(30, 120));
    convex.setPoint(4, Vector2f(70, 150));
    convex.setFillColor(Color(90, 150, 60, 200));
    convex.setOrigin(95, 95);
    convex.move(100, 300);

    // прямоугольник
    RectangleShape rect{Vector2f(130, 190)};
    rect.setFillColor(Color(50, 200, 150, 200));
    rect.setOrigin(65, 95);
    rect.move(300, 300);

    // линия как тонкий прямоугольник
    RectangleShape rectLine{Vector2f(190, 5)};
    rectLine.setFillColor(Color(200, 50, 150, 200));
    rectLine.setOrigin(95, 2.5);
    rectLine.rotate(-40);
    rectLine.move(500, 300);

    // текстура
    earthTexture.loadFromFile("images/earth.png");
    brickwallTexture.loadFromFile("images/brickwall.jpg");

    // спрайты
    Sprite smallEarth{earthTexture};
    sizeSprite(smallEarth, 80.f);
    smallEarth.rotate(20);
    smallEarth.move(100, 500);

    Sprite middleEarth{earthTexture};
    sizeSprite(middleEarth, 140.f);
    middleEarth.rotate(40);
    middleEarth.move(300, 500);

    Sprite bigEarth{earthTexture};
    sizeSprite(bigEarth, 190.f);
    bigEarth.rotate(60);
    bigEarth.move(500, 500);

    Sprite coloredEarth{earthTexture};
    sizeSprite(coloredEarth, 190.f);
    coloredEarth.setColor(Color(250, 50, 250, 200));
    coloredEarth.rotate(80);
    coloredEarth.move(700, 500);

    return new Objects{
            circle,
            triangle,
            penta,
            octa,
            convex,
            rect,
            rectLine,
            smallEarth,
            middleEarth,
            bigEarth,
            coloredEarth,
    };
}

Objects *o = init();

// линия как многоугольник
Vertex vertexLine[] = {
        Vertex(Vector2f(620, 380), Color::Magenta),
        Vertex(Vector2f(780, 220), Color::Green),
        Vertex(Vector2f(650, 240), Color::Blue),
        Vertex(Vector2f(750, 360)),
};

void clear() {
    delete o;
    delete window;
}

void changeMode(int mode) {
    std::cout << "Change mode to " << mode << '\n';
    // сглаживание текстуры
    bool smooth = mode % 2 == 0;
    std::cout << " - Earth texture smooth sets to " << smooth << '\n';
    earthTexture.setSmooth(smooth);
}

void handleEvent(Event &event) {
    if (event.type == Event::Closed) {
        window->close();
    }
    if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
            case Keyboard::Escape:
                window->close();
                break;
            default:
                if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num9) {
                    int mode = event.key.code - Keyboard::Num1;
                    changeMode(mode);
                }
        }
    }
}

void updateScene() {

}

void drawGraphics() {
    // Отрисовка фигур
    window->draw(o->circle);
    window->draw(o->triangle);
    window->draw(o->penta);
    window->draw(o->octa);
    window->draw(o->convex);
    window->draw(o->rect);
    window->draw(o->rectLine);
    window->draw(vertexLine, 4, LineStrip);
    window->draw(o->smallEarth);
    window->draw(o->middleEarth);
    window->draw(o->bigEarth);
    window->draw(o->coloredEarth);
}

void presentGraphics() {
    window->display();
}

int main(int argc, char *argv[]) {
    // Установка уровня сглаживания
    ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8;

    window = new RenderWindow(
            VideoMode(800, 600),
            "Hey! Hey! Press numbers to change view",
            Style::Default,
            contextSettings);

    // Цвет фона
    Color backgroundColor{255, 220, 100, 0};

    Event event{};

    while (window->isOpen())
    {
        while (window->pollEvent(event)) {
            handleEvent(event);
        }

        updateScene();
        window->clear(backgroundColor);
        drawGraphics();
        presentGraphics();
    }

    clear();
}