#include <SFML/Graphics.hpp>
#include <vector>
#include <ranges>
#include <tuple>

using namespace sf;
template <typename TLambda>
struct Object : Drawable {
  Object(TLambda onClick) : onClick_(onClick) {}

  static bool isMouseOver(RenderWindow* pWindow, const Shape& shape) {
    Vector2f mousePos = pWindow->mapPixelToCoords(Mouse::getPosition(*pWindow));
    FloatRect buttonRect = shape.getGlobalBounds();
    return buttonRect.contains(mousePos);
  }

  template <typename... T>
  std::optional<Drawable> isClicked(RenderWindow* pWindow, const Shape& shape, T... args) {
    if (isMouseOver(pWindow, shape)) {
      if (Mouse::isButtonPressed(Mouse::Left)) {
        return onClick_(args...);
      }
    }
    else {
      return std::nullopt;
    }
  }

  TLambda onClick_;
};

template <typename TLambda>
struct Wall : Object<TLambda> {
  Wall(Vector2f pos, bool horizontal, TLambda lambda) : Object<TLambda>(lambda) {
    if (horizontal)
      wall = RectangleShape(Vector2f{ 10, 100 });
    else
      wall = RectangleShape(Vector2f{ 100, 10 });
    wall.setFillColor(Color::Black);
    wall.setOrigin(wall.getLocalBounds().width / 2.0f, wall.getLocalBounds().height / 2.0f);
    wall.setPosition(pos);
  }

  void draw(RenderTarget& target, RenderStates states) const {
    target.draw(wall, states);
  }

  void move(Vector2f pos) {
    wall.setPosition(pos);
  }
private:
  RectangleShape wall;
};
