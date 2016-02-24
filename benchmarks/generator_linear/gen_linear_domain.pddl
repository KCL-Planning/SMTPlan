(define (domain generator_linear)
(:requirements :fluents :durative-actions :duration-inequalities :adl :typing)
(:types generator tank)
(:predicates (refueling ?g - generator) (generator-ran) (available ?t - tank))

(:functions (fuelLevel ?g - generator) (capacity ?g - generator) )

(:durative-action generate
 :parameters (?g - generator)
 :duration (= ?duration  1000)		 
 :condition (over all (>= (fuelLevel ?g) 0))
 :effect (and (decrease (fuelLevel ?g) (* #t 1))
			  (at end (generator-ran))))

(:durative-action refuel
 :parameters (?g - generator ?t - tank)
 :duration  (= ?duration  10) 
 :condition (and (at start (available ?t))
				  (over all (< (fuelLevel ?g) (capacity ?g))))
  :effect (and (at start (refueling ?g))
              (increase (fuelLevel ?g) (* #t 2))
			  (at start (not (available ?t)))
			  (at end (not (refueling ?g)))
          )
))
