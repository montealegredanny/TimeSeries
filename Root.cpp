#include "Root.h"
#include <stdlib.h> 

double PRECISION = 1e-6; 

namespace RootHelper
{
	bool AreEqual(std::complex<double> c1, std::complex<double> c2)
	{
		bool areEqual = true; 
		if ((abs(c1.imag() - c2.imag()) > PRECISION) || (abs(c1.real() - c2.real()) > PRECISION))
		{
			areEqual = false;
		}

		return areEqual; 
	}
}

Root::Root(std::complex<double> value, unsigned int multiplicity)
{
	m_value = value; 
	m_multiplicity = multiplicity; 
}

Root::Root(std::complex<double> value)
{
	m_value = value; 
	m_multiplicity = 1; 
}

void Root::increaseMultiplicity()
{
	this->m_multiplicity += 1;
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
	return RootHelper::AreEqual(lhs.m_value, rhs.m_value);
}

bool operator==(const Root& lhs, std::complex<double> rhs)
{
	return RootHelper::AreEqual(lhs.m_value, rhs);
}

bool operator==(std::complex<double> lhs, const Root& rhs)
{
	return RootHelper::AreEqual(rhs.m_value, lhs);;
}


