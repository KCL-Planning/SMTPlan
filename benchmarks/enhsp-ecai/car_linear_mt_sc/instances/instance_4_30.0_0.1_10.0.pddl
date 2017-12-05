
(define (problem instance_4_300_01_100)
  (:domain car_linear_mt_sc)
  (:objects
    
  )

  (:init
    (= (d) 0.0)
	(= (v) 0.0)
	(engine_stopped)
	(= (a) 0.0)
	(= (max_acceleration) 4)
	(= (min_acceleration) -4)
	(= (max_speed) 10.0)
  )

  (:goal
    (and 
	(>= (d) 29.5 )
	(<= (d) 30.5 )
	(engine_stopped)
	)
  )
)
