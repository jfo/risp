
(define eq =)
(display 
    (if (cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) #f)) 'thing)
  )
