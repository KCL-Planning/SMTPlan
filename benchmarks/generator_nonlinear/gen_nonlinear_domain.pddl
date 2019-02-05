(define (domain generator2)
(:requirements :fluents :durative-actions :duration-inequalities :adl :typing)
(:types generator tank)
(:predicates (refueling ?g - generator) (generator-ran) (available ?t - tank))

(:functions (fuelLevel ?g - generator) (capacity ?g - generator) (ptime ?t - tank))

(:durative-action generate
 :parameters (?g - generator)
 :duration (= ?duration  1000)		 
 :condition (over all (>= (fuelLevel ?g) 0))
 :effect (and (decrease (fuelLevel ?g) (* #t 1))
			  (at end (generator-ran))))

(:durative-action refuel
 :parameters (?g - generator ?t - tank)
 :duration  (= ?duration  10) 
 :condition (and  (at start (available ?t))
				  (over all (< (fuelLevel ?g) (capacity ?g)))
				  )				  
 :effect (and (at start (refueling ?g))
			  (increase (ptime ?t) (* #t 1))
              (increase (fuelLevel ?g) (* #t (* 0.1 (* (ptime ?t) (ptime ?t)))))
			  (at start (not (available ?t)))
			  (at end (not (refueling ?g)))
          )
)




)