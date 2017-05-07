#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double Vp(double p){
    double dv = 0;
    if (p >=0 && p < 0.04)
        dv = 30 -250*p;
    else
        if(p >=0.04 && p < 0.07)
            dv = 35.2*p - 7.2 + 1.03/(p);
        else
            if(p >=0.07 && p <= 0.14)
                dv = 9.878*0.14/p - 9.978*0.14 ;
            else dv = 0;
    return dv;

}
double DV(double p){
    double dv = 0;
    if (p >=0 && p < 0.04)
        dv = -250;
    else
        if(p >=0.04 && p < 0.07)
            dv = 35.2 - 1.03/(p*p);
        else
            if(p >=0.07 && p <= 0.14)
                dv = -1.39692 /(p*p) ;
            else dv = 0;
    return dv;
}
double Qp(double p){
    double dv = 0;
    if (p >=0 && p < 0.04)
        dv = 30*p - 250*p*p;
    else
        if(p >=0.04 && p < 0.07)
            dv = 35.2*p*p - 7.2*p + 1.03;
        else
            if(p >=0.07 && p <= 0.14)
                dv = 9.978*(0.14-p);
            else dv = 0;
    return dv;

}
double Qpd(double p){
    double dv = 0;
    if (p >=0 && p < 0.04)
        dv = 30 - 2*250*p;
    else
        if(p >=0.04 && p < 0.07)
            dv = 2*35.2*p - 7.2 ;
        else
            if(p >=0.07 && p <= 0.14)
                dv = -9.978;
            else
                dv = 0;
    return dv;

}

struct Road {
    double p, v, prev_p, prev_v;
};

int m,n, T;
double t, x, tx, alpha, v_ort;
int m1, m2;

double Qp_ort,QwithAlpha;
double prev_v, prev_p;
double next_v, next_p;
double Dv, Dvh, QpM, QpP, QM, QP, UM, UP;
double param = 1;
double temp = 0;
double QpP_hord, QP_hord;

void simulateHord(vector<Road> &road, Road &m1, Road &m2, double QwithAlpha) {
  unsigned int i = 0;

  //hord first el
  // Qp_ort = 0.5 * (v_ort + road[0].v + m1.prev_p * DV( m1.prev_p) +  road[0].p * DV(road[0].p));
  Qp_ort = 0.5 * (v_ort + road[0].v + m1.prev_p * Vp( m1.prev_p) +  road[0].p * Vp(road[0].p));
  v_ort = v_ort - 0.5 * tx * (Qp_ort * (v_ort + road[0].v) + fabs(Qp_ort) * ( v_ort - road[0].v ) );

  next_v = road[i+1].v;
  next_p = road[i+1].p;

  //Qp
  QpM = Qp_ort;
  QpP = (road[i].v + road[i].p * DV(road[i].p) + next_v + next_p * DV(next_p)) / 2;
  //U
  UM = 0.5 * ((road[i].v + prev_v) * QpM - (road[i].v - prev_v) * fabs(QpM));
  UP = 0.5 * ((road[i].v + next_v) * QpP + (road[i].v - next_v) * fabs(QpP));
  //Q
  QM = QwithAlpha;
  QP = (road[i].p * road[i].v + next_p * next_v) / 2 +
           (road[i].p - next_p) / 2 * fabs(QpP);

  road[i].prev_p = road[i].p;
  road[i].prev_v = road[i].v;
  road[i].p += tx * (QM - QP) ;
  road[i].v += tx*( UM - UP);

  // hord elements
  for (unsigned int i = 1; i <= n; i++) {
    prev_v = road[i-1].prev_v;
    prev_p = road[i-1].prev_p;
    if(i != n-1){
      next_v = road[i+1].v;
      next_p = road[i+1].p;
    }else{
      next_p = m2.prev_p;
      next_v = 0;
    }

    //Qp
    temp = road[i].v + road[i].p * DV(road[i].p);
    QpM = 0.5 * (temp + prev_v + prev_p * DV(prev_p));
    QpP = 0.5 * (temp + next_v + next_p * DV(next_p));
    //Q
    temp = road[i].p * road[i].v;
    QM = 0.5 * ((temp + prev_p * prev_v) - (road[i].p - prev_p) * fabs(QpM));
    QP = 0.5 * ((temp + next_p * next_v) + (road[i].p - next_p) * fabs(QpP));
    //U
    UM = 0.5 * ((road[i].v + prev_v) * QpM - (road[i].v - prev_v) * fabs(QpM));
    UP = 0.5 * ((road[i].v + next_v) * QpP + (road[i].v - next_v) * fabs(QpP));

    road[i].prev_p = road[i].p;
    road[i].prev_v = road[i].v;
    road[i].p += tx * (QM - QP) ;
    road[i].v += tx * (UM - UP);

    if(i == n-1){
      QP_hord = QP;
    }
  }
}

void simulate(vector<Road> &road, vector<Road> &hord) {
    for (unsigned int i = 0; i < road.size(); i++) {

        if (i == 0) {
            prev_v = road[road.size()-1].v;
            prev_p = road[road.size()-1].p;
            next_v = road[1].v;
            next_p = road[1].p;
        }
        else if (i == road.size()-1) {
            prev_v = road[i-1].prev_v;
            prev_p = road[i-1].prev_p;
            next_v = road[0].prev_v;
            next_p = road[0].prev_p;
        }
        else {
            prev_v = road[i-1].prev_v;
            prev_p = road[i-1].prev_p;
            next_v = road[i+1].v;
            next_p = road[i+1].p;
        }

        //Qp
        temp = road[i].v + road[i].p * DV(road[i].p);
        QpM = 0.5 * (temp + prev_v + prev_p * DV(prev_p));
        QpP = 0.5 * (temp + next_v + next_p * DV(next_p));
        //Q
        temp = road[i].p * road[i].v;
        QM = 0.5 * ((temp + prev_p * prev_v) - (road[i].p - prev_p) * fabs(QpM));
        QP = 0.5 * ((temp + next_p * next_v) + (road[i].p - next_p) * fabs(QpP));
        if (i == m1) {
            QwithAlpha = alpha * QP;
            QM = (1-alpha)*QP;
        }
        //U
        UM = 0.5 * ((road[i].v + prev_v) * QpM - (road[i].v - prev_v) * fabs(QpM));
        UP = 0.5 * ((road[i].v + next_v) * QpP + (road[i].v - next_v) * fabs(QpP));

        road[i].prev_p = road[i].p;
        road[i].prev_v = road[i].v;

        if (i == m2) {
            road[i].p += tx * (QP + QP_hord - QM) ;
        } else {
            road[i].p += tx * (QM - QP) ;
        }
        road[i].v += tx * (UM - UP);
    }
    simulateHord(hord, road[m1], road[m2], QwithAlpha);
}

int main() {
    scanf("%d %d %lf %d %lf", &m, &n, &x, &T, &t);
    scanf("%d %d %lf", &m1, &m2, &alpha);
    vector<Road> road(m);
    vector<Road> hord(n);
    double p, v;
    for(int i = 0; i < m; i++) {
        scanf("%lf %lf", &p, &v);
        road[i].p = road[i].prev_p = p;
        road[i].v = road[i].prev_v = v;
    }
    for(int i = 0; i < n; i++){
        scanf("%lf %lf", &p, &v);
        hord[i].p = hord[i].prev_p = p;
        hord[i].v = hord[i].prev_v = v;
    }
    scanf("%lf", &v_ort);

    int i = n - 1;
    prev_p = hord[n-1].p;
    next_p = road[m2-1].prev_p;
    QpP_hord = (hord[i].v + hord[i].p * DV(hord[i].p) + next_p * DV(next_p)) / 2;
    QP_hord = ((prev_p * hord[n-1].v)/2 + (prev_p - next_p)/2 * fabs(QpP_hord));


    tx = t/x;

    for (int i = 0; i < T; i++) {
        simulate(road, hord);
    }

    printf("\n");printf("\n");printf("\n");
    for (int i = 0; i < road.size(); i++) {
        printf("%.12f %.12f\n", road[i].p, road[i].v);
    }
    printf("\n");
    for (int i = 0; i < hord.size(); i++) {
        printf("%.12f %.12f\n", hord[i].p, hord[i].v);
    }
    // system("pause");
    return 0;
}
