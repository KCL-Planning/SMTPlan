(define
    (problem 03_chokepoint)
    (:domain convoys)

    (:objects
        c1 c2 c3 - convoy
        loc_A loc_B loc_C loc_D loc_E loc_F loc_G loc_H - point
    )

    (:init
        (= (speed c1) 40.0) (position c1 loc_B)
        (= (distance_to c1 loc_B) 0.0)

        (= (speed c2) 40.0) (position c2 loc_B)
        (= (distance_to c2 loc_B) 0.0)

        (= (speed c3) 40.0) (position c3 loc_B)
        (= (distance_to c3 loc_B) 0.0)

        (= (elapsed_time) 0)

        (connected loc_D loc_B) (connected loc_B loc_D)
        (= (distance loc_D loc_B) 20.0) (= (distance loc_B loc_D) 20.0)
        (= (traffic loc_D loc_B) 0.0) (= (traffic loc_B loc_D) 0.0)

        (connected loc_A loc_B) (connected loc_A loc_D)
        (= (distance loc_D loc_A) 10.0) (= (distance loc_A loc_D) 10.0)
        (= (traffic loc_D loc_A) 0.0) (= (traffic loc_A loc_D) 0.0)

        (connected loc_D loc_C) (connected loc_C loc_D)
        (= (distance loc_D loc_C) 10.0) (= (distance loc_C loc_D) 10.0)
        (= (traffic loc_D loc_C) 0.0) (= (traffic loc_C loc_D) 0.0)

        (connected loc_A loc_F) (connected loc_F loc_A)
        (= (distance loc_A loc_F) 30.0) (= (distance loc_F loc_A) 30.0)
        (= (traffic loc_A loc_F) 0.0) (= (traffic loc_F loc_A) 0.0)

        (connected loc_D loc_E) (connected loc_E loc_D)
        (= (distance loc_D loc_E) 10.0) (= (distance loc_E loc_D) 10.0)
        (= (traffic loc_D loc_E) 0.0) (= (traffic loc_E loc_D) 0.0)

        (connected loc_C loc_H) (connected loc_H loc_C)
        (= (distance loc_C loc_H) 60.0) (= (distance loc_H loc_C) 60.0)
        (= (traffic loc_C loc_H) 0.0) (= (traffic loc_H loc_C) 0.0)

        (connected loc_E loc_F) (connected loc_F loc_E)
        (= (distance loc_E loc_F) 10.0) (= (distance loc_F loc_E) 10.0)
        (= (traffic loc_E loc_F) 0.0) (= (traffic loc_F loc_E) 0.0)

        (connected loc_E loc_G) (connected loc_G loc_E)
        (= (distance loc_E loc_G) 20.0) (= (distance loc_G loc_E) 20.0)
        (= (traffic loc_E loc_G) 0.0) (= (traffic loc_G loc_E) 0.0)

        (connected loc_H loc_E) (connected loc_E loc_H)
        (= (distance loc_H loc_E) 20.0) (= (distance loc_E loc_H) 20.0)
        (= (traffic loc_H loc_E) 0.0) (= (traffic loc_E loc_H) 0.0)


    )

    (:goal
        (and
            (position c1 loc_G) (position c2 loc_G)
            (position c3 loc_G)
        )
    )

    (:metric
        maximize (- 48.0 (elapsed_time))
    )

)
