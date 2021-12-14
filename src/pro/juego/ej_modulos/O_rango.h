#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
using namespace std;

class O_rango : public Objeto{
	private:
		std::string rangoLinterna;
	public:
		O_rango(int rar);
        ~O_rango();
        std::string getRangoLinterna();
};