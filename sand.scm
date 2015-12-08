(define put
  (lambda (l)
    (display (eval l))
    (newline)))

(define puts
  (lambda (l)
    (map put (reverse l))))

(define atom (lambda (x) (not (pair? x))))

(define eq (lambda (x y) (equal? x y)))

(puts '(
  ; (quote arbitrary_thing)
  ; 'arbitrary_thing
  ; (atom 'arbitrary_thing)
  ; (atom (quote ()))
  ; (atom '())

  ; (atom (quote (thingy)))
  ; (car (quote (thing thang thung)))
  ; (cdr (quote (thing thang thung)))
  ; (cons (quote thing) (quote (thang thung)))
  ;
  ; (cond ((eq (quote 2) (quote 2)) (quote first)))
  ; (cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))
  ; (eq '() (cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 1) (quote 2)) (quote second))))

  ; (cond (eq (quote 2) (quote 2)) (quote first)
  ;       ((eq (quote 2) (quote 2)) (quote second))
  ;       )
  ; (cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))
  ; (cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))
  ; (label my_label (quote yayyyy))
  ; (eq my_label (quote yayyyy))
  ; (eq my_label (quote noooo))
  ; (eq my_label (quote noooo))
  ; (cons (quote a) (cons (quote b) (cons (quote c) (quote ()))))


  (define thing ((lambda (x) x) '1))
  ((lambda (x) x) 1)


  ))
