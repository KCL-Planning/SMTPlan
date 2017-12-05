;; Domain for Generator, linear version. This formulation is equivalent (in terms of computed plans) to the one using durative actions instead
(define
    (domain generator_linear_mt)

(:types     generator
            tank )

(:predicates
        (online ?g - generator) ;; captures whether the generator is online. Used to trigger the process
        (not_online ?g - generator)
        (available ?t - tank) ;; captures whether the tank is available or not. After being used the tank cannot be used (resources are not unlimited!)
        (not_available ?t - tank)
	    (generator-ran ?g -generator) ;; captures the end of the generation. Used in the goal
	    (using ?t -tank) ;; captures whether a tank is being used. Trigger the refueling process
)

(:functions
            (fuelLevel ?g - generator) ;; level of the fuel in the tank
            (capacity ?g - generator) ;; max capacity of the tank
            (generator_running ?g -generator) ;; timer for the generator
            (refuel_running ?g -generator ?t -tank) ;; timer for the refueling action
            (generator_duration) ;; constant that defines duration of the generator
	        (refuel_duration)    ;; constant that defines duration of the refueling
)


;; constraining the fuel level in the tank for each generator
(:constraint min_generator_fuel
    :parameters (?g - generator)
    :condition (>= (fuelLevel ?g) 0.0)
)

(:constraint max_generator_fuel
    :parameters (?g - generator)
    :condition (<=  (fuelLevel ?g) (capacity ?g))
)


;; the following encodes the durative action "generation" with a fixed duration.

(:constraint generator_duration
    :parameters (?g - generator)
    :condition (<= (generator_running ?g) (generator_duration))
)

(:process generate_power
    :parameters (?g - generator)
    :precondition (and (online ?g) (> (fuelLevel ?g) 0.0))
    :effect (and    (decrease (fuelLevel ?g) (* #t 1.0))
                    (increase (generator_running ?g) (* #t 1.0))
            )
)

(:action turn_on
    :parameters (?g - generator)
    :precondition (and (not_online ?g) (< (generator_running ?g) (generator_duration)))
    :effect (and (online ?g)
                 (not (not_online ?g))
		 (assign (generator_running ?g) 0 )
            )
)

;(:action turn_off
;    :parameters (?g - generator)
;    :precondition (and (online ?g) (= (generator_running ?g) (generator_duration)))
;    :effect (and (not (online ?g))
;                 (not_online ?g)
;                 (assign (generator_running ?g) 0)
;		          (generator-ran ?g)
;            )
;)


;; the following encodes the durative action "refueling" with a fixed duration.

(:constraint refuel_duration
    :parameters (?g - generator ?t -tank)
    :condition (<= (refuel_running ?g ?t) (refuel_duration))
) 

(:process refuel_generator
    :parameters (?g - generator ?t -tank)
    :precondition (and (using ?t) (< (fuelLevel ?g) (capacity ?g))(< (refuel_running ?g ?t) (refuel_duration)))
    :effect (and
                    (increase (fuelLevel ?g) (* #t 2.0))
                    (increase (refuel_running ?g ?t) (* #t 1.0))
            )
)

(:action start_refueling
    :parameters (?g - generator ?t - tank)
    :precondition (and (available ?t))
    :effect (and
                (not (available ?t))
		        (using ?t)
            )
)

;(:action stop_refueling
;    :parameters (?g - generator ?t - tank)
;    :precondition (and (= (refuel_running ?g ?t) (refuel_duration)) (using ?t))
;    :effect (and
;		        (not (using ?t))
;            )
;)
)
