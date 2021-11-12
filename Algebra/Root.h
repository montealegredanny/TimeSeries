#pragma once 
#include <complex>

class Root
{
	public: 
		Root(std::complex<double> value, unsigned int multiplicity) : m_value(value), m_multiplicity(multiplicity) {};
		Root(std::complex<double> value); 
		friend std::ostream& operator<<(std::ostream& output, const Root& root); 
		friend bool operator== (const Root& lhs, const Root& rhs);
		friend bool operator== (const Root& lhs, std::complex<double> rhs);
		friend bool operator== (std::complex<double> lhs, const Root& rhs);
		void increaseMultiplicity();
		unsigned int getMultiplicity() const; 
		std::complex<double> getValue() const; 
	private:
		std::complex<double> m_value; 
		unsigned int m_multiplicity; 
};