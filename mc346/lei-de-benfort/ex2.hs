-- Projeto de Haskell MC346 - 1s2015 - Lei de Benfort
-- Dupla:
-- Rodrigo Nagamine - RA: 137531
-- Vinícius Andrade Frederico - RA: 139223

returnFirst ('R':'$':x) = returnFirst x
returnFirst ('-':x) = returnFirst x
returnFirst x = [head x]

-- count x xs => qtde x em xs
count x = length . filter (x==)

main = do
	-- Lê toda a entrada (lazy)
	contents <- getContents
	let palavras = map returnFirst (words contents)
	putStrLn $ "1 : " ++ (show (count "1" palavras))
	putStrLn $ "2 : " ++ (show (count "2" palavras))
	putStrLn $ "3 : " ++ (show (count "3" palavras))
	putStrLn $ "4 : " ++ (show (count "4" palavras))
	putStrLn $ "5 : " ++ (show (count "5" palavras))
	putStrLn $ "6 : " ++ (show (count "6" palavras))
	putStrLn $ "7 : " ++ (show (count "7" palavras))
	putStrLn $ "8 : " ++ (show (count "8" palavras))
	putStrLn $ "9 : " ++ (show (count "9" palavras))
	putStrLn ""
