(fn nums_from_line [line_str]
    (let [item_table {}]
        (each [it (string.gmatch line_str "%d*")]
            (table.insert item_table (tonumber it)))
        (values item_table)))

(fn get_times_and_dists [filename] 
    (let [t_t {}]
        (let [f (assert (io.open filename))
            times (nums_from_line (f.read f "*line"))
            dists (nums_from_line (f.read f "*line"))]
            (table.insert t_t times)
            (table.insert t_t dists))
        (values t_t)))

(fn winning [times dists]
    (let [d (- (* times times) (* 4 -1 (- 0 dists)))
          x1 (/ (+ (- 0 times) (math.sqrt d)) -2)
          x2 (/ (- (- 0 times) (math.sqrt d)) -2)]
        (values (- (math.ceil x2) (math.floor x1) 1))))

(let [t_d (get_times_and_dists "input.txt")]
    (var pt_1 1)
    (each [i _ (ipairs (. t_d 1))]
        (let [res (winning (. (. t_d 1) i) (. (. t_d 2) i))]
            (set pt_1 (* pt_1 res))))
    (print (string.format "Part 1: %d" pt_1))
    (print (string.format "Part 2: %d" (winning (table.concat (. t_d 1)) (table.concat (. t_d 2))))))
