namespace Planets
{
	enum Planets
	{
		Mercury = 0,
		Venus,
		Earth,
		EarthSpin,
		Moon,
		Mars,
		Jupiter,
		Saturn,
		Uranus,
		Neptune
	};
};

extern int CalculatePlanets( struct tm *st, double *planet_positions, int planet_count );
