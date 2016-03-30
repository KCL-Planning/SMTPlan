(define (domain generator2 )
(:requirements :fluents :durative-actions :typing :negative-preconditions
:duration-inequalities)
(:types gen tank )
(:predicates ( refueling ?g - gen ?t -
tank)
( generator_ran ?g - gen ))
(:functions ( tank_fuel_level ?t - tank )
( gen_fuel_level ?g - gen )
( flow_constant ?t - tank )
( refuel_time ?t - tank )
( capacity ?g - gen )
( sqrtvolinit ?t - tank )
( sqrtvol ?t - tank)
(runtime)
)
(:durative-action generate
 :parameters (? g - gen )
 :duration (= ? duration (runtime))
 :condition ( over all (> ( gen_fuel_level ?g) 0) )
 :effect (and (decrease ( gen_fuel_level ? g) (* #t 1))
		(at end ( generator_ran ?g))))


(:durative-action refuel
 :parameters (? g - gen ?t - tank )
 :duration ( <= ? duration (* (/ 1 (flow_constant ?t)) ( sqrtvolinit ?t)))
 :condition (and
		(at start (not (refueling ?g ?t )) )
		( over all (< ( gen_fuel_level ?g) (capacity ?g)))
		( over all (> ( tank_fuel_level ?t) 0 )) )
		
 :effect (and
		(at start ( refueling ?g ?t))
		(at start (assign ( refuel_time ?t) 0) )
        (at start (assign ( sqrtvol ?t) (sqrtvolinit ?t)) )
		(increase ( refuel_time ?t) (* #t 1) )
		(decrease ( sqrtvol ?t) (* #t (flow_constant ?t)) )
		(decrease ( tank_fuel_level ?t) (* #t (* (* 2 ( flow_constant ?t)) (- (sqrtvolinit ?t) (* ( flow_constant ?t) (refuel_time ?t)))) ))
		(increase ( gen_fuel_level ?g) (* #t (*(* 2 ( flow_constant ?t)) (- (sqrtvolinit ?t) (* ( flow_constant ?t) (refuel_time ?t)))) ))
		(at end (not ( refueling ?g ?t)))
		(at end (assign ( sqrtvolinit ?t) (sqrtvol ?t)) )))
)


