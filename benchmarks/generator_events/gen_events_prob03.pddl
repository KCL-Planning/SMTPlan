(define (problem run-generatorplus)
    (:domain generatorplus)
    (:objects gen - generator tank1 tank2 tank3 - tank)
    (:init
		(= (fuelLevel gen) 900)
		(= (capacity gen) 1600)

		(= (fuelInTank tank1) 40)
		(= (fuelInTank tank2) 40)
		(= (fuelInTank tank3) 40)

		(available tank1)
		(available tank2)
		(available tank3)

		(safe gen)
     )  
     (:goal (generator-ran))
)
