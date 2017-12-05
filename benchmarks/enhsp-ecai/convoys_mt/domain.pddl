(define
  (domain convoys)
  ;; Adapted from
  ;; "Reasoning about Autonomous Processes in an Estimated-Regression Planner"
  ;; Drew Mc Dermott, ICAPS 2003

  (:types convoy point - object)

  (:predicates
    (connected ?p1 ?p2 - point)
    (route_assigned ?c -convoy ?p1 ?p2 -point)
    (position ?c -convoy ?p1)
  )

  (:functions
    (distance ?p1 ?p2 - point )
    (traffic ?p1 ?p2 - point )
    (speed ?c - convoy )
    (distance_to ?c -convoy ?p - point) 
    (elapsed_time)
  )

  (:process passage_of_time
    :parameters ()
    :precondition ()
    :effect (increase (elapsed_time) (* #t 1.0))
  )

  (:process rolling
    :parameters (?c - convoy ?p1 ?p2 -point)
    :precondition (and 
                       (route_assigned ?c ?p1 ?p2)
                       (> (distance_to ?c ?p2) 0)
                  )
    :effect (and
                  (decrease (distance_to ?c ?p2) (* #t (/ (speed ?c) (^ (traffic ?p1 ?p2) 2))))
                  (increase (distance_to ?c ?p1) (* #t (/ (speed ?c) (^ (traffic ?p1 ?p2) 2))))
            )
  )

  (:action park
    :parameters (?c - convoy ?p1 ?p2 -point)
    :precondition (and 
                    (<= (distance_to ?c ?p2) 0)
                    (route_assigned ?c ?p1 ?p2)
                  )
    :effect (and
                  (position ?c ?p2)
                  (not (route_assigned ?c ?p1 ?p2))
                  (decrease (traffic ?p1 ?p2) 1)
                  (decrease (traffic ?p2 ?p1) 1)
            )
  )

  (:action assign_route
    :parameters (?c - convoy ?p1 ?p2 - point)
    :precondition (and
                        (connected ?p1 ?p2)
                        (position ?c ?p1)
                  )
    :effect (and
                  (not (position ?c ?p1))
                  (route_assigned ?c ?p1 ?p2)
                  (assign (distance_to ?c ?p2) (distance ?p1 ?p2))
                  (increase (traffic ?p1 ?p2) 1)
                  (increase (traffic ?p2 ?p1) 1)
            )
  )

)
