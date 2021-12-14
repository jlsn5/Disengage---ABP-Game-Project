#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
using namespace std;

class O_vAtaque : public Objeto{
	private:
		double velAta; //magnitud que cambia este objeto
	public:
		O_vAtaque(int r); //constructor donde se establece dicha magnitud
        ~O_vAtaque();
        double get_velAta();
};