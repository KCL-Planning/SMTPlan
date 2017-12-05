(define
    (domain intercept_fn)

    (:types
        vampire bird - object
    )

    (:predicates
        (tackled ?b - vampire)
        (nottackled ?b - vampire)
        (available ?i - bird)
    )

    (:functions
        (x ?o - object) - number
        (y ?o - object) - number
        (v_x ?o - object) - number
        (v_y ?o - object) - number
        (intercept_radius) - number
        (launch_speed) - number
    )

    (:constraint vampire_in_field
        :parameters (?b - vampire)
        :condition (and (>= (x ?b) 0.0 ) )
    )

    (:process vampire_movement
        :parameters (?o - vampire)
        :precondition (nottackled ?o)
        :effect (and    (increase (x ?o) (* #t (v_x ?o)))
                        (increase (y ?o) (* #t (v_y ?o)))
                )
    )

    (:process bird_movement
        :parameters (?i - bird)
        :precondition (available ?i)
        :effect (and    
                        (increase (x ?i) (* #t (v_x ?i)))
                        (increase (y ?i) (* #t (v_y ?i)))
                )
    )


    (:action launch
        :parameters (?i - bird)
        :precondition (= (y ?i) 0.0)
        :effect (assign (v_y ?i) (launch_speed))
    )

    (:action tackle
        :parameters (?b - vampire ?i - bird)
        :precondition (<= (+ (^ (- (x ?b) (x ?i) ) 2.0) (^ (- (y ?b) (y ?i)) 2.0)) (^ (intercept_radius) 2.0) )
        :effect (and
                    (tackled ?b)
                    (not (available ?i))
                    (not (nottackled ?b))
                )

    )

    (:action increase_launch_speed
	:parameters()
	:precondition()
	:effect (increase (launch_speed) 100)
    )

    (:action decrease_launch_speed
	:parameters()
	:precondition()
	:effect (decrease (launch_speed) 100)
    )

)
