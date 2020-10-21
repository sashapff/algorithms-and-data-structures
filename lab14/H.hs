

main = do
         a <- getLine
         b <- getLine
         putStr  (show ((read a) * (read b)))
