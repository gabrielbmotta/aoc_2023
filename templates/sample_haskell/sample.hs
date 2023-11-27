process a = do
    print a

main = do
    file <- readFile "test.txt"
    mapM_ process (lines file)
    return 0 
