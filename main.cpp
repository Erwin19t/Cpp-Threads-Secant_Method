#include <iostream>
#include <mutex>
#include <thread>
#include <math.h>

using namespace std;

double Secante(double, double, mutex*);

int main()
{
	mutex m;
	double Paso = 0.5;
	thread t1(Secante, -2.0, Paso, &m);
	thread t2(Secante, -2.0, Paso, &m);
	thread t3(Secante, -1.5, Paso, &m);
	thread t4(Secante, -1.5, Paso, &m);
   thread t5(Secante, 1.0, Paso, &m);				
	thread t6(Secante, 1.0, Paso, &m);	
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	
	return 0;
}

double Secante(double Xi, double Step, mutex *m)
{
	unsigned short int Counter = 0;
	double Xi_aux, h;
	double X_ant = 0.0;
	double Fx, Fx_ant;
	double Error = 100.0;
	double Derivate = 0.0;
	double Derivate_ant = 0.0;
	
	Xi_aux = Xi;
	h = Step;
	while(Error > pow(10,-9))
	{
		Fx = pow(Xi_aux,7) - 2*pow(Xi_aux,5) + 4*pow(Xi_aux,4) - 3*pow(Xi_aux,2) - 1;	//F(X_i)
		Fx_ant = pow(X_ant,7) - 2*pow(X_ant,5) + 4*pow(X_ant,4) - 3*pow(X_ant,2) - 1;	//F(X_(i-1))
		Derivate = (Fx - Fx_ant)/h;		//Se calcula la derivada
		
		//Empieza el parche que no sirve
		if((Derivate == 0.0) && (Derivate_ant > 0.0))
		{
			Derivate = 0.001;
		}
		if((Derivate == 0.0) && (Derivate_ant < 0.0))
		{
			Derivate = -0.001;
		}
		//Termina el parche que no sirve
		
		
		Xi_aux = Xi_aux - (Fx / Derivate);		//Estimamos las raiz
		Error = abs(Xi_aux - X_ant);				//Se calcula el error
						
		X_ant = Xi_aux;			//Se actualiza la raiz anterior
		Derivate_ant = Derivate;//Se actualiza la derivada anterior
		Counter++;					//Se incrementa el contador de iteraciones
	}
	m->lock();
	cout<<"La raiz es: "<<Xi_aux<<endl;
	cout<<"La solucion se encontro en la iteracion: "<<Counter<<endl<<endl;
	m->unlock();
	
	return Xi_aux;
}
