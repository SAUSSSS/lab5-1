#include <iostream>
#include <cmath>
#include <fstream>


//integrand
double integrand(double x,double s)
{
  return pow(x,s)/(s+1);
}


double method_trapeze(double a,double b, double h,double s){
  double I = 0; //integral
  double  n = (b - a) / h; //number of steps
      I  +=  h * (integrand(a,s) + integrand(b,s)) / 2.0;
  for(int i = 1; i <= n-1; i++){
      I +=   h * integrand(a + h * i,s);
    }
  return I;
}


double method_simpson(double a,double b, double h,double s){
  double I = 0; //integral
  double  n = (b - a) / h; //number of steps
      I +=  h * (integrand(a,s) + integrand(b,s)) / 6.0;
  for(int i = 1; i <= n; i++){
      I +=  2.0 / 3.0 * h * integrand(a + h * (i - 0.5),s);
    }
  for(int i = 1; i <= n-1; i++){
      I +=  1.0 / 3.0 * h * integrand(a + h * i,s);
    }
  return I;
}

double method_rectangle(double a,double b, double h,double s){
  double I = 0; //integral
  double  n = (b - a) / h; //number of steps
  for(int i = 1; i <= n; i++){
      I +=  h * integrand(a + h * (i - 0.5),s);
    }
  return I;
}

double method_rectangle_left(double a,double b, double h,double s){
  double I = 0; //integral
  double  n = (b - a) / h; //number of steps
  for(int i = 1; i <= n; i++){
      I +=  h * integrand(a + h * (i - 1),s);
    }
  return I;
}

double method_rectangle_right(double a,double b, double h,double s){
  double I = 0; //integral
  double  n = (b - a) / h; //number of steps
  for(int i = 1; i <= n; i++){
      I +=  h * integrand(a + h * i,s);
    }
  return I;
}

double method_simpson_3_8(double a,double b, double h,double s){
    double I = 0; //integral
    double n = (b - a) / (h*3); //number of steps
    I += h *  (integrand(a,s) + integrand(b,s));
    for(int i = 0; i <= 3*n-1; i++){
      if(i % 3 == 0){
         I += 2. * h *  integrand(a + h * i,s);
      } else {
         I += 3. * h *  integrand(a + h * i,s);
      }
    }
    I *= (3./8.);
    return  I;
}


int main(){
    using namespace std;

    double a = 0.0, b = 1.0; // integration segment
    double h = 10E-4; // integration step(accuracy = 10E-4)
    double s = 0.0; // power of numbers
    int r = 100; // number of row elements

    double I_trapeze_1 = 0,I_trapeze_2 = 0;

    double I_simpson_1 = 0,I_simpson_2 = 0;

    double I_simpson_3_8_1 = 0,I_simpson_3_8_2 = 0;

    double I_rectangle_1 = 0,I_rectangle_2 = 0;

    double I_rectangle_L_1 = 0, I_rectangle_L_2 = 0;

    double I_rectangle_R_1 = 0, I_rectangle_R_2 = 0;


    for(int k = 0; k < r; k++){

      I_trapeze_1 += pow(-1,k) * method_trapeze(a,b,h,s);
      I_trapeze_2 += pow(-1,k) * method_trapeze(a,b,2*h,s);

      I_simpson_1 += pow(-1,k) * method_simpson(a,b,h,s);
      I_simpson_2 += pow(-1,k) * method_simpson(a,b,2*h,s);

      I_simpson_3_8_1 += pow(-1,k) * method_simpson_3_8(a,b,h,s);
      I_simpson_3_8_2 += pow(-1,k) * method_simpson_3_8(a,b,2*h,s);

      I_rectangle_1 += pow(-1,k) * method_rectangle(a,b,h,s);
      I_rectangle_2 += pow(-1,k) * method_rectangle(a,b,2*h,s);

      I_rectangle_L_1 += pow(-1,k) * method_rectangle_left(a,b,h,s);
      I_rectangle_L_2 += pow(-1,k) * method_rectangle_left(a,b,2*h,s);

      I_rectangle_R_1 += pow(-1,k) * method_rectangle_right(a,b,h,s);
      I_rectangle_R_2 += pow(-1,k) * method_rectangle_right(a,b,2*h,s);

      s += 2;
    }
    cout << endl;
    cout << "Integral: atan(x)/x from 0 to 1, way to solve -> Taylor series: atan(x)" << endl << endl;

    cout << "Trapeze:     " << I_trapeze_1     << "  Error: " << abs(I_trapeze_2 - I_trapeze_1)  << endl;
    cout << "Simpson:     " << I_simpson_1     << "  Error: " << abs(I_simpson_2  - I_simpson_1 )<< endl;
    cout << "Simpson_3_8: " << I_simpson_3_8_1 << "  Error: " << abs(I_simpson_3_8_2 - I_simpson_3_8_1)  << endl;
    cout << "Rectangle:   " << I_rectangle_1   << "  Error: " << abs(I_rectangle_2 - I_rectangle_1) << endl;
    cout << "Rectangle_L: " << I_rectangle_L_1 << "  Error: " << abs(I_rectangle_L_2 - I_rectangle_L_1) << endl;
    cout << "Rectangle_R: " << I_rectangle_R_1 << "  Error: " << abs(I_rectangle_R_2 - I_rectangle_R_1)  << endl;


    ofstream fout1,fout2,fout3,fout4,fout5,fout6;
    fout1.open("ans/ans1.dat");
    fout2.open("ans/ans2.dat");
    fout3.open("ans/ans3.dat");
    fout4.open("ans/ans4.dat");
    fout5.open("ans/ans5.dat");
    fout6.open("ans/ans6.dat");

    fout1 << "Trapeze:     " << I_trapeze_1     << "  Error: " << abs(I_trapeze_2 - I_trapeze_1) << endl;
    fout2 << "Simpson:     " << I_simpson_1     << "  Error: " << abs(I_simpson_2  - I_simpson_1 ) << endl;
    fout3 << "Simpson_3_8: " << I_simpson_3_8_1 << "  Error: " << abs(I_simpson_3_8_2 - I_simpson_3_8_1)  << endl;
    fout4 << "Rectangle:   " << I_rectangle_1   << "  Error: " << abs(I_rectangle_2 - I_rectangle_1) << endl;
    fout5 << "Rectangle_L: " << I_rectangle_L_1 << "  Error: " << abs(I_rectangle_L_2 - I_rectangle_L_1)  << endl;
    fout6 << "Rectangle_R: " << I_rectangle_R_1 << "  Error: " << abs(I_rectangle_R_2 - I_rectangle_R_1)  << endl;

    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    fout5.close();
    fout6.close();
    return 0;
  }
