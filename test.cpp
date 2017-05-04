

 int main() {
   int* p1 = new int[20];
   int* p2 = new int[100];

   p1[0] = 5;
   p2[0] = 10;

   int* u = p2;
   p2 = p1;
   p1 = u;

   std::cout << *p1 << std::endl;
   std::cout << *p2 << std::endl;

    return 0;
 }
