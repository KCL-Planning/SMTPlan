(define (problem run-generator2)
    (:domain generator)
    (:objects gen - generator tank1 tank2 - tank)
    (:init 	(= (fuelLevel gen) 940)
		(= (capacity gen)  1600)

		(available tank1)
		(available tank2)

		(= (ptime tank1) 0)
		(= (ptime tank2) 0)
     )  
     (:goal (generator-ran))
) 
