#include <iostream>
#include <math.h>

class Car{
public:
  double x;
  double v;
  void setX(double newX){
    x = newX;
  }
  void setV(double newV){
    v = newV;
  }
  void setXV(double newX, double newV){
    x = newX;
    v = newV;
    }
};

double nextCoordinate(Car car, double d, double l, int j, int i){
    double newX =  car.x + car.v * d;
    if(newX > l){
      newX = newX - l;
      // std::cout << newX << " " << l << " " << j << " " << i << "\n";
    }
    return newX;
}

double newSpeed(double h){
  // double s1 = h - 7;
  // double s2 = s1 / 30;
  // double s3 = s2 * (-0.8);
  // double e = exp( s3);
  // double s = 1 - e;
  //std::cout << s1 << " " << s2 << " " << s3 << " " << e << " " << s << "\n";
  return 30 * (1 - exp( -0.8 * (h - 7)/30));
}

double distanceFromLeader(Car cars[], int j, int n, double l){
  int next = j + 1;
  if ((j + 1) == n){
    next = 0;
  }
  if(cars[next].x - cars[j].x <= 0){
    return cars[next].x + (l - cars[j].x);
  }
  return cars[next].x - cars[j].x;
}

int main(){

  int n, T = 0;
  double x, v, d, l = 0;

  if (! std::cin.eof ()) {
    std::cin >> n >> l >> T >> d;
  }

  Car cars[n] = { };

  for (int i = 0; i < n; i++) {
    std::cin >> x >> v;
    Car car;
    car.setXV(x, v);
    cars[i] =car;
  }

  for (int i = 0; i < T; i++){
    Car first;
    for (int j = 0; j < n; j++){
      double newX = nextCoordinate(cars[j], d, l, j, i);
      double h = distanceFromLeader(cars, j, n, l);
      double newV = newSpeed(h);
      if(j != 0){
        cars[j].setXV(newX, newV);
      }else{
        first.setXV(newX, newV);
      }
    }
    cars[0] = first;
  }

  for (int i = 0; i < n; i++){
    std::cout.precision(15);
    std::cout << std::fixed << cars[i].x << " " << cars[i].v << "\n";
  }
  return 0;
}
