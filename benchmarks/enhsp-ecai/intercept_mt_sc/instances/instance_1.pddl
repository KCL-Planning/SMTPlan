(define
  (problem intercept_sample)
  (:domain intercept_fn)

  (:objects
    vampire_0 - vampire
    bird_0 - bird
  )

  (:init
    (= (x bird_0) 500.0)
    (= (y bird_0) 0.0)
    (= (v_x bird_0) 0.0)
    (= (v_y bird_0) 0.0)

    (= (x vampire_0) 2000.0)
    (= (y vampire_0) 500.0)
    (= (v_x vampire_0) -340.0) ;; Mach 1, goes towards 0.0
    (= (v_y vampire_0) 0.0)

    (= (intercept_radius) 20.0) ;; Approximated
    (= (launch_speed) 1190.0 ) ;; Mach 3.5, max speed of RIM-174

    (available bird_0)
    (nottackled vampire_0)
  )

  (:goal
    (and (tackled vampire_0))
  )

  )
)
