#include "Root.h"
#include <stdlib.h> 

namespace RootHelper
{
	bool areEqual(std::complex<double> c1, std::complex<double> c2, double precision = 1e-6)
	{
		return !(((abs(c1.imag() - c2.imag()) > precision) || (abs(c1.real() - c2.real()) > precision)));
	}
}

Root::Root(std::complex<double> value)
{
	m_value = value; 
	m_multiplicity = 1; 
}

void Root::increaseMultiplicity()
{
	this->m_multiplicity ++;
}

unsigned int Root::getMultiplicity() const
{
	return m_multiplicity;
}

std::complex<double> Root::getValue() const
{
	return m_value;
}

std::ostream& operator<<(std::ostream& output, const Root& root)
{
	output << root.m_value << " with multiplicity = " << root.m_multiplicity << std::endl;
	return output;
}

bool operator==(const Root& lhs, const Root& rhs)
{
	return RootHelper::areEqual(lhs.m_value, rhs.m_value);
}

bool operator==(const Root& lhs, std::complex<double> rhs)
{
	return RootHelper::areEqual(lhs.m_value, rhs);
}

bool operator==(std::complex<double> lhs, const Root& rhs)
{
	return RootHelper::areEqual(rhs.m_value, lhs);;
}


