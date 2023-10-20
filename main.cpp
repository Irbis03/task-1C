#include <iostream>

enum possible_minotavr_direction{UP, RIGHT, DOWN, LEFT};

void input_coordinates(int& x, int& y, int& x_1, int& y_1) {
  std::cin >> x >> y >> x_1 >> y_1;
}

void input_parameters(int& cost_move, int& cost_rotate, int& cost_check, int& viewing_range) {
  std::cin >> cost_move >> cost_rotate >> cost_check >> viewing_range;
}

int find_minotavr_direction(int cur_x, int cur_y, int next_x, int next_y) {
  int delta_x = next_x - cur_x;
  int delta_y = next_y - cur_y;
  if (delta_x == 0) {
    if (delta_y == -1) {
      return LEFT;
    }
    return RIGHT;
  }
  if (delta_x == -1) {
    return UP;
  }
  return DOWN;
}

int move_in_minotavr_direction() {
  std::cout << "1";
  int result_of_moving;
  std::cin >> result_of_moving;
  return result_of_moving;
}

void move_in_random_direction(int& x, int& y, int& minotavr_direction, int& total_time, int cost_move, int cost_rotate) {
  for (int i = 0; i < 4; ++i) {
    int result_of_moving = move_in_minotavr_direction();
    total_time += cost_move;
    if (result_of_moving == 0) { // если у нас не получилось пройти, то делаем разворот против часовой стрелки
      std::cout << "2 0";
      minotavr_direction = (minotavr_direction + 1) % 4;
      total_time += cost_rotate;
    } else { // иначе обновляем текущую позицию для минотавра
      int delta_x_for_directions[4] = {-1, 0, 1, 0};
      int delta_y_for_directions[4] = {0, 1, 0, -1};
      x += delta_x_for_directions[minotavr_direction];
      y += delta_y_for_directions[minotavr_direction];
      break;
    }
  }
}

int get_distance_from_start(int minotavr_coordinate_x, int minotavr_coordinate_y, int init_x, int init_y) {
  return (minotavr_coordinate_y - init_y) * (minotavr_coordinate_y - init_y) +
      (minotavr_coordinate_x - init_x) * (minotavr_coordinate_x - init_x);
}

void solution() {
  int x, y, x_1, y_1;
  int cost_move, cost_rotate, cost_check, viewing_range;

  input_coordinates(x, y, x_1, y_1);
  input_parameters(cost_move, cost_rotate, cost_check, viewing_range);

  int total_time = 0;
  int minotavr_direction = find_minotavr_direction(x, y, x_1, y_1);
  int minotavr_coordinate_x = x;
  int minotavr_coordinate_y = y;
  bool is_exploring_maze = true;
  while(is_exploring_maze) {
    move_in_random_direction(minotavr_coordinate_x, minotavr_coordinate_y, minotavr_direction, total_time,
                             cost_move, cost_rotate);
    if (get_distance_from_start(minotavr_coordinate_x, minotavr_coordinate_y, x, y) == 0) {
      is_exploring_maze = false;
    }
  }
  
  std::cout << total_time;
}

int main() {
  solution();
  return 0;
}
