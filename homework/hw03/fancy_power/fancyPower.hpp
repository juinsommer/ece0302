#ifndef FANCYPOWER_HPP
#define FANCYPOWER_HPP

int fancyPower(int n, int m)
{
	int power = 0;

	if(m == 1) //base case
		power = n;

	else {
			if(m % 2 == 0 ) //if m is even
				power = fancyPower(n * n, m / 2);
		
			else
				power = n * fancyPower(n * n, (m - 1) / 2);
		}
	
		return power;
}

#endif
