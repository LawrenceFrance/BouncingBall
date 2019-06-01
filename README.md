# BouncingBall
C++ / Bouncing ball simulator

Trajectory Simulator
Lawrence France
Started 25/02/19
Specifies the details of the trajectory of a projectile

Description

		To describe the motion of a ball in 2D when thrown, including:
			Trajectory
			Bouncing
			Final position/range
			
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
			

    Features to add:
    
      Can it clear a wall?
			Enclosed space, bounce around the room?
				Reflection mechanics

    
