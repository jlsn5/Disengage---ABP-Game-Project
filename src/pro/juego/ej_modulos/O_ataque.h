#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
using namespace std;

class O_ataque : public Objeto{
	private:
		double ataque; //magnitud que cambia este objeto
	public:
		O_ataque(int r); //constructor donde se establece dicha magnitud
        ~O_ataque();
        double getAtaque();
};