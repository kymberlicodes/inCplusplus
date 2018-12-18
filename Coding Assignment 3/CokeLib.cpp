// Coke Library
#include "CokeLib.h"

bool ParseCokeLine(const std::string& CokeMachineLine, std::vector<std::string>& params)
{
	int x = 0, z = 0, i = 0;

	if (CokeMachineLine.length() == 0)
	{
		return false;
	}
	else
	{
		while (z < CokeMachineLine.length())
		{
			x = CokeMachineLine.find("|", z) - z;
			params[i++] = CokeMachineLine.substr(z, x);
			z += params[i-1].length() + 1;
		}
	}
	return true;
}