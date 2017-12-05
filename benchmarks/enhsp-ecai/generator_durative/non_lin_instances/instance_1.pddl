
(define (problem instance_1_2_40_900_70)
  (:domain generator_linear_duration_mt)
  (:objects
    gen_1 - generator
	tank_1 - tank
  )

  (:init
        (= (uptime gen_1) 0.0)
	(= (fuelLevel gen_1) 980)
	(= (capacity gen_1) 1600)
	(not_online gen_1)
	(not_refueling gen_1)
	(= (refuel_running gen_1 tank_1) 0)
	(= (generator_running gen_1) 0)
	(available tank_1)
	(= (generator_duration) 1000)
	(= (refuel_duration) 10)
  )

  (:goal
    (and 
	(= (generator_running gen_1) 1000)
    )
  )
)
