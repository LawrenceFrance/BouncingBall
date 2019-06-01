// Trajectory Simulator
// Lawrence France
// Started 25/02/19
// Specifies the details of the trajectory of a projectile

/* Description

		To describe the motion of a ball in 2D when thrown, including:
			Trajectory
			Bouncing
			Final position/range
			Can it clear a wall?
			Enclosed space, bounce around the room?
				Reflection mechanics

	Method

		Trajectory equation, leads to:
				x,y position at time t:
						y = v_0y*t + 0.5gt^2
						x = v_0x*t
				y position at position x:
						y = x*(v_0y/v_0x) + 0.5*g*(1/v_0x^2)*x^2
				Range equation:
						R = v0x*v0y/|g|
				Max height equation:
						H = v0y^2/2|g|
				Duration equation:
						t = 2*v0y/|g|
				Velocities after time t:
						v_y(t) = v_0y + gt
						v_x(t) = v_0x
					
		Nested trajectory calculations with each bounce until v~0:
			When y~0, reflect ball
			New trajectory
			Repeat until v=0
		
		Class for balls:
			Mass
			Coefficient of restitution
			Coefficient of friction
			Radius
		Inputs:
			Direction of throw, degrees
			Speed of throw, m/s
		Outputs:
			Duration
			Range
			Max height
			No. of bounces
			If wall present, does it clear wall?


*/

// SETUP ///////////////////////////////////////////////////////

// Includes
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const double pi = 3.14159265358979323846;
const double g  = -9.80665;


class Ball {

private:

	// setup
	bool initialised;

	// invariant parameters
	double mass, radius, COR, COF;

	// flight parameters
	double vx, vy;
	int bounce_count;
	bool flying;

	double x_pos, max_height, range, duration;
	double total_range, total_duration;

	void bounce();
	
	
public:
		
	void initialise(vector<double>&);
	void trajectory();
	void display_results();

};

// replace with constructor
void Ball::initialise(vector<double>& v) {

	/* input structure:			
			( |ball mass|, |ball radius|, |ball COR|,
			  |throw velocity|, |throw direction|    )
	*/

	mass	= v[0];
	radius	= v[1];
	COR		= v[2];
	COF		= v[3];
	vx		= v[4] * cos(v[5] * pi / 180);
	vy		= v[4] * sin(v[5] * pi / 180);

	cout << "Initial energy is " << 0.5*mass*v[4] * v[4] << " J." << endl;

	bounce_count = 0;
	flying = true;
	
	x_pos		= 0;
	max_height	= 0;
	range		= 0;
	duration	= 0;

	total_range		= 0;
	total_duration	= 0;

	initialised = true;
}

void Ball::trajectory() {

	while (flying) {

		cout << "Flying..." << endl;

		/* Find:
				Range
				Max height
				Duration
				vy,vx final

				If range or height are smaller than the diameter of the ball:
					No bounce, end flight
		*/

		// Range equation R = v0x*v0y/|g|
		range = 2 * vx*vy / abs(g);				

		// Duration equation 
		duration = 2 * vy / abs(g);

		// Max height equation H = v0y^2/2|g|	
		double new_height = vy * vy / (2 * abs(g));

		// Test to see if ball flies
		if (range<=2*radius) {
			cout << "Doesn't go far enough." << endl;
			flying = false;
			break;
		}
		else if (new_height<=2*radius){
			cout << "Doesn't go high enough." << endl;
			flying = false;
			break;
		}
		else {
			total_range += range;
			total_duration += duration;
		}

		// Max height equation H = v0y^2/2|g|			
		if (new_height > max_height) {
			max_height = vy * vy / (2 * abs(g));
		}

		// vy final vy = yy0 + gt
		vy = vy + g * duration;
		
		// Display position of contact
		cout << "Contact at x = " << range << " m." << endl;

		// Bounce and find next trajectory
		bounce();
	}

	cout << "Finished flying." << endl;
}

void Ball::bounce() {

	// Evaluate new vy and vx using COR and COF

	// v_f,y = -COR*v_i,y
	double vy_new = -1 * COR*vy;

	// v_f,x = v_i,x - COF(1+COR)*v_i,y
	double vx_new = vx - COF * (1 + COR)*vy;

	// If vx becomes negative, make it equal to 0, end of motion
	if (vx_new <= 0) {
		cout << "x reversed" << endl;
		vx = 0;
		vy = 0;
		flying = false;		
	}
	else {
		bounce_count++;
		vy = vy_new;
		vx = vx_new;
		cout << "Bounce..." << endl;
	}

}

void Ball::display_results() {

	cout << "\n\nResults:\n";
	cout << "Range:\t\t"		<< total_range		<< " m\n";
	cout << "Duration:\t"		<< total_duration	<< " s\n";
	cout << "Max height:\t"		<< max_height		<< " m\n";
	cout << "No. of bounces:\t" << bounce_count		<< "\n";

}

int main() {

	/*READ INPUTS*///////////////////////////////////////////////

	vector<double> inputs{ 0.5, 0.01, 0.8, -0.2, 5, 30 };

	/*INITIATE BALL*////////////////////////////////////////////

	Ball test_ball;
	test_ball.initialise(inputs);
	

	/*EVALUATE THROW*///////////////////////////////////////////

	test_ball.trajectory();

	/*REPORT RESULTS*///////////////////////////////////////////

	test_ball.display_results();

	system("pause");

	return 0;
}



