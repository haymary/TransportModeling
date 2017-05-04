#include <iostream>
#include <math.h>

class Car{
public:
  double x;
  double v;
  double a;

  void setXV(double newX, double newV){
    x = newX;
    v = newV;
    }

  void setA(double newA){
    a = newA;
  }
};

double newCoordinate(Car car, double d, double l, int j, int i){
  double newX =  car.x + car.v * d + 0.5 * car.a * d * d;
  if(newX > l){
    newX = newX - l;
  }
  return newX;
}

double newSpeed(Car car, double d){
  return car.v + car.a * d;
}

int getNext(int j, int n){
  int next = j + 1;
  if ((j + 1) == n){
    next = 0;
  }
  return next;
}

double newAcceleratio(Car cars[], int j, double h, int n){
  int next = getNext(j, n);
  double v = cars[j].v;
  double v_l = cars[next].v;
  return 1 - pow((v/30),4) - 1/(h*h) * (2+1.5*v-v*(v_l-v)/(2*sqrt(3)))*(2+1.5*v-v*(v_l-v)/(2*sqrt(3)));
}

double distanceFromLeader(Car cars[], int j, int n, double l){
  int next = getNext(j, n);
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
    cars[i] = car;
  }

  for (int i = 0; i < T; i++){
    Car first;
    for (int j = 0; j < n; j++){
      double h = distanceFromLeader(cars, j, n, l);
      double newA = newAcceleratio(cars, j, h, n);
      cars[j].setA(newA);
      double newX = newCoordinate(cars[j], d, l, j, i);
      double newV = newSpeed(cars[j], d);
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
