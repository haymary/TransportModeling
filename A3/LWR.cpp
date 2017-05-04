#include <iostream>
#include <stdlib.h>
#include <stdio.h>

double get_q(double p){
  double q = 0;
  if (p < 0.04){
    q = 30*p - 250*p*p;
  } else if(p >=0.04 && p < 0.07){
    q = 35.2*p*p - 7.2*p + 1.03;
  } else{
    q = 9.978 * (0.14-p);
  }
  return q;
}

double get_dq(double p){
  double dq = 0;
  if (p < 0.04){
    dq = 30 - 500*p;
  } else if(p >=0.04 && p < 0.07){
    dq = 70.4*p - 7.2;
  } else{
    dq = -9.978 ;
  }
  return dq;
}

int main(){
  int m, T = 0;
  double x, t = 0;

  if (! std::cin.eof ()) {
    std::cin >> m >> x >> T >> t;
  }
  double p[m] = { };
  for (int i = 0; i < m; i++) {
    std::cin >> p[i];
  }
  double alfa = t/x;
  double first;

  double p_prev = p[m-1];
  for (int j = 0; j < T; j++){
    
    for (int i = 0; i < m; i++){
      double p_next, q_p, q_m, p_new = 0;
      // Find next and prev
      p_next = p[0];
      // p_prev = p[m-1];
      if(i != m-1){
        p_next = p[i+1];
      }
      // if(i != 0){
      //   p_prev = p[i-1];
      // }
      //Find q
      q_p = (get_q(p_next)+get_q(p[i]))/2 + ((p[i]-p_next)/4) * abs(get_dq(p_next) + get_dq(p[i]));
      q_m = (get_q(p_prev)+get_q(p[i]))/2 - ((p[i]-p_prev)/4) * abs(get_dq(p_prev) + get_dq(p[i]));

      p_new = p[i] + alfa * (q_m - q_p);

      p_prev = p[i];
      if(i != 0){
        p[i] = p_new;
      }else{
        first = p_new;
      }
      // p[i] = p_new;
    }
      p[0] = first;
  }

  for (int i = 0; i < m; i++){
    std::cout.precision(15);
    std::cout << std::fixed << p[i] << "\n";
  }
  return 0;
}
