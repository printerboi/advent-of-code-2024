#include <utility>


enum class DIRECTION {
  LEFT = '<',
  TOP = '^',
  RIGHT = '>',
  BOTTOM = 'v'
};

class Character {
public:
  std::pair<int, int> pos;
  DIRECTION dir;

  Character(std::pair<int, int> pos, DIRECTION dir);

  void turnRight();
};