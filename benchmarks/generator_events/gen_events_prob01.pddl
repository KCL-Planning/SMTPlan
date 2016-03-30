(define (problem run-generatorplus)
    (:domain generatorplus)
    (:objects gen - generator tank1 - tank)
    (:init
		(= (fuelLevel gen) 980)
		(= (capacity gen) 1600)

		(= (fuelInTank tank1) 40)

		(available tank1)

		(safe gen)
     )  
     (:goal (generator-ran))
)
