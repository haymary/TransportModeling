#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double get_dv(double p){
  double dq = 0;
  if (p >=0 && p < 0.04){
    dq = -250;
  } else if(p >=0.04 && p < 0.07){
    dq = 35.2 - 1.03/(p*p);
  } else{
    dq = -1.39692 /(p*p) ;
  }
  return dq;
}

int main(){
  int m, T = 0;
  double x, t = 0;
  double q_p, q_m, q_par_p, q_par_m, u_p, u_m = 0;
  int prev, nex = 0;

  if (! std::cin.eof ()) {
    std::cin >> m >> x >> T >> t;
  }
  double* p = new double[m];
  double* p_new = new double[m];
  double* v = new double[m];
  double* v_new = new double[m];

  for (int i = 0; i < m; i++) {
    std::cin >> p[i] >> v[i];
  }
  double* temp;
  double alfa = t/x;
  double p_prev, p_next, v_prev, v_next = 0;
  for (int j = 0; j < T; j++){
    for (int i = 0; i < m; i++){
        (i == 0) ? prev = m-1 : prev = i-1;
        (i == m-1) ? nex = 0 : nex = i+1;
        p_prev = p[prev];
        p_next = p[nex];
        v_prev = v[prev];
        v_next = v[nex];

        q_par_p = (v[i] + p[i] * get_dv(p[i]) + v_next + p_next*get_dv(p_next))/2;
        q_par_m = (v[i] + p[i] * get_dv(p[i]) + v_prev + p_prev*get_dv(p_prev))/2;
        q_p = (p[i]*v[i] + p_next*v_next)/2 + (p[i]-p_next)*fabs(q_par_p)/2;
        q_m = (p[i]*v[i] + p_prev*v_prev)/2 - (p[i]-p_prev)*fabs(q_par_m)/2;
        u_p = (v[i] + v_next) * q_par_p/2 + (v[i] - v_next)*fabs(q_par_p)/2;
        u_m = (v[i] + v_prev) * q_par_m/2 - (v[i] - v_prev)*fabs(q_par_m)/2;

        p_new[i] = p[i] + alfa*(q_m - q_p);
        v_new[i] = v[i] + alfa*(u_m - u_p);
    }
    // for(int i = 0; i < m; i++){
    //   p[i] = p_new[i];
    //   v[i] = v_new[i];
    // }
    temp = p;
    p = p_new;
    p_new = temp;

    temp = v;
    v = v_new;
    v_new = temp;
  }

  for (int i = 0; i < m; i++){
    std::cout.precision(15);
    std::cout << std::fixed << p[i] << " " << v[i] << "\n";
  }
  return 0;
}
