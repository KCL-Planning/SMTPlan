(define
    (domain car_linear_mt_sc)

    (:predicates
        (engine_running)
        (engine_stopped)
    )

    (:functions
        (d)
        (v)
        (a)
        (max_acceleration)
        (min_acceleration)
        (max_speed)
    )

    (:constraint speed_limit
        :parameters ()
        :condition (and (>= (v) (* -1.0 (max_speed))) (<= (v) (max_speed)))
    )

    (:process displacement
        :parameters ()
        :precondition (engine_running)
        :effect (increase (d) (* #t (v)))
    )

    (:process moving
        :parameters ()
        :precondition (engine_running)
        :effect (and
                    (increase (v) (* #t (a)))  ;; velocity changes because of the acceleration
        )
    )

    (:action accelerate
        :parameters ()
        :precondition (and (< (a) (max_acceleration)) (engine_running) )
        :effect (increase (a) 1.0)  ;;
    )

    (:action stop_car
        :parameters ()
        :precondition (and (> (v) -0.1)(< (v) 0.1) (= (a) 0.0) (engine_running))
        :effect (and
                        (assign (v) 0.0)
                        (engine_stopped)
                        (not (engine_running))
                )

    )

    (:action start_car
        :parameters ()
        :precondition (engine_stopped)
        :effect (and
                    (engine_running)
                    (not (engine_stopped))
                )
    )


    (:action decelerate
        :parameters ()
        :precondition (and (> (a) (min_acceleration)) (engine_running))
        :effect (decrease (a) 1.0) ;;
    )
)
