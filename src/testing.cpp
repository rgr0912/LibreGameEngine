#include <testing.h>

Testing::Testing()
{

}
int Testing::miFuncion(int x, int y)
{
    z = x * 10 + y * 5;
    return z;
}
void Testing::miAnalisis()
{
    int z_t = Testing::z;

    if (z_t < 25000)
    std::cout<<" Tus ventas son muy bajas";
    else
    std::cout<<" Bien hecho!!";
}

int main()
{
    Testing test;
    std::cout<<test.miFuncion(2500, 1300);
    test.miAnalisis();
}