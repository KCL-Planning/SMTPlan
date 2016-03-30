(define (problem run-generatorplus)
    (:domain generatorplus)
    (:objects gen - generator tank1 tank2 tank3 tank4 - tank)
    (:init
		(= (fuelLevel gen) 860)
		(= (capacity gen) 1600)

		(= (fuelInTank tank1) 40)
		(= (fuelInTank tank2) 40)
		(= (fuelInTank tank3) 40)
		(= (fuelInTank tank4) 40)

		(available tank1)
		(available tank2)
		(available tank3)
		(available tank4)

		(safe gen)
     )  
     (:goal (generator-ran))
)
