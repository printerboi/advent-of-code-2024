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
  std::pair<int, int> initPos;
  DIRECTION dir;
  DIRECTION initDir;

  Character(std::pair<int, int> pos, DIRECTION dir);

  void turnRight();

  void reset();
};