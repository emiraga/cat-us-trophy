double gdist
( double a_lat, double b_lat, double a_long, double b_long ) {
	return acos( cos( a_lat ) * cos( b_lat ) * cos( a_long - b_long ) + sin( a_lat ) * sin( b_lat ));
} // don't forget to multiply radius with it! ;)
