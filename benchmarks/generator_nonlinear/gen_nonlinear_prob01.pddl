(define (problem run-generator2)
    (:domain generator)
    (:objects gen - generator tank1 - tank)
    (:init 	(= (fuelLevel gen) 967)
		(= (capacity gen)  1600)

		(available tank1)

		(= (ptime tank1) 0)
     )  
     (:goal (generator-ran))
) 