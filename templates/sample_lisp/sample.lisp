(let ((file (open "test.txt" :if-does-not-exist nil)))
  (if file
    (progn
        (loop for line = (read-line file nil)
            while line do (format t "~a~%" line))
        (close file)
        (format t "Done!"))
    (format t "Sorry, something went wrong."))
)

