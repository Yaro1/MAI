;coin19
(define VARIANT 19)
(define LAST-DIGIT-OF-GROUP-NUMBER 6)
(define LARGEST-COIN 50)

(define (implication? x? y?)
  (not (and x? (not y?)))
  )
  
(define (cc amount largest-coin)
  (cond ((or (= amount 0) (= largest-coin 1)) 
     1)
    ((implication? (>= amount 0) (= largest-coin 0))
      0)
       (else (+(cc amount (next-coin largest-coin)) (cc (- amount largest-coin) largest-coin))
       )
   )               
)

(define (count-change amount)
  (cc amount LARGEST-COIN)
 )

(define (next-coin coin)
  (cond ((= coin 50)
    25)
    ((= coin 25)
      20)
       ((= coin 20)
         15)
         ((= coin 15)
           1)
           (else 0)
   )
 )

(define (GR-AMOUNT)
  (remainder (+(* 100 LAST-DIGIT-OF-GROUP-NUMBER) VARIANT) 137)
 )

(display " pys variant")
(display VARIANT) (newline)
(display " 1-15-20-25-50") (newline)
(display "count-change for 100 \t= ")
(display (count-change 100 )) (newline)
(display "count-change for ")
(display (GR-AMOUNT))
(display " \t= ")
(display(count-change (GR-AMOUNT))) (newline)




  
   
           
    
