#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
using namespace std;

class O_maldito : public Objeto{
	private:
		double maldicionVelocidad; //magnitud que cambia este objeto
	public:
		O_maldito(int r); //constructor donde se establece dicha magnitud
        ~O_maldito();
        double getMaldicion();
};