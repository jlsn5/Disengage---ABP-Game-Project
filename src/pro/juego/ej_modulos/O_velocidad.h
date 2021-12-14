#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
using namespace std;

class O_velocidad : public Objeto{
	private:
		double velocidad; //magnitud que cambia este objeto
	public:
		O_velocidad(int r); //constructor donde se establece dicha magnitud
        ~O_velocidad();
        double getVelocidad();
};