#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
using namespace std;

class O_vida : public Objeto{
	private:
		double vida; //magnitud que cambia este objeto
	public:
		O_vida(int r); //constructor donde se establece dicha magnitud
        ~O_vida();
        double getVida();
};