(define
  (problem car_max_accel_3)
  (:domain car)

  (:init
    (= (d) 0.0)
	(= (v) 0.0)
	(engine_stopped)
	(= (a) 0.0)
	(= (max_acceleration) 10)
	(= (min_acceleration) -10)
	(= (max_speed) 10)
  )

  (:goal
    (and 
	(>= (d) 999.5 )
	(<= (d) 1010.5 )
	(engine_stopped)
	)
  )
)

