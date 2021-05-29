#pragma once
#include<string>
class Pattern
{

		std::string name;
public:
	bool shape[7][7];
	Pattern();
		void Rotate();
		void setShape(bool shapee[7][7]);
		void setName(std::string name);
		std::string getName();
		

	

};

