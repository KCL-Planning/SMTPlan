(define
    (problem sample_01)
    (:domain convoys)

    (:objects
        c1 - convoy
        c2 - convoy
        loc_A loc_B - point
    )

    (:init
        (= (speed c1) 10)
        (position c1 loc_A)
        (= (distance_to c1 loc_A) 0)

        (= (speed c2) 20)
        (position c2 loc_A)
        (= (distance_to c2 loc_A) 0)

        (connected loc_A loc_B) (connected loc_B loc_A)
        (= (distance loc_A loc_B) 60)
        (= (distance loc_B loc_A) 60)
        (= (traffic loc_A loc_B) 0.0)
        (= (traffic loc_B loc_A) 0)
        (= (elapsed_time) 0)

    )

    (:goal
        (and
;            (< (elapsed_time) 20)
            (position c1 loc_B)
            (position c2 loc_B)
        )
    )

)
