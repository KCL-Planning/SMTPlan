
(define (problem instance_1_2_40_900_70)
  (:domain generator_linear_duration_mt)
  (:objects
    gen_1 - generator
	tank_1 tank_2 tank_3 tank_4 tank_5 tank_6 tank_7 tank_8 - tank
  )

  (:init
        (= (uptime gen_1) 0.0)
	(= (fuelLevel gen_1) 772)
	(= (capacity gen_1) 1600)
	(not_online gen_1)
	(not_refueling gen_1)
	(= (refuel_running gen_1 tank_1) 0)
	(= (refuel_running gen_1 tank_2) 0)
	(= (refuel_running gen_1 tank_3) 0)
	(= (refuel_running gen_1 tank_4) 0)
	(= (refuel_running gen_1 tank_5) 0)
	(= (refuel_running gen_1 tank_6) 0)
	(= (refuel_running gen_1 tank_7) 0)
	(= (refuel_running gen_1 tank_8) 0)
	(= (generator_running gen_1) 0)
	(available tank_1)
	(available tank_2)
	(available tank_3)
	(available tank_4)
	(available tank_5)
	(available tank_6)
	(available tank_7)
	(available tank_8)
	(= (generator_duration) 1000)
	(= (refuel_duration) 10)
  )

  (:goal
    (and 
	(= (generator_running gen_1) 1000)
    )
  )
)
