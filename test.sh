#!/bin/bash

rm -f in.txt out.txt expected.txt res.txt

# Test 1: archivo de entrada simple, comando cat, comando wc
echo -e "hola\nmundo\npipex\nprueba" > in.txt
./pipex in.txt "cat" "wc -l" out.txt
echo "4" > expected.txt
diff -q out.txt expected.txt || echo "Test 1 FALLÓ"

# Test 2: grep y sort
echo -e "foo\nbar\nbaz\nfoo bar" > in.txt
./pipex in.txt "grep foo" "sort" out.txt
echo -e "foo\nfoo bar" > expected.txt
diff -q out.txt expected.txt || echo "Test 2 FALLÓ"

# Test 3: corte con awk y reversa con rev
echo -e "uno dos tres\ncuatro cinco seis" > in.txt
./pipex in.txt "awk '{print \$2}'" "rev" out.txt
echo -e "sod\nocniv" > expected.txt
diff -q out.txt expected.txt || echo "Test 3 FALLÓ"

# Test 4: comando con comillas
echo -e "alpha beta\ngamma delta" > in.txt
./pipex in.txt "awk '{print \"-\"\$1\"-\"}'" "tr a-z A-Z" out.txt
echo -e "-ALPHA-\n-GAMMA-" > expected.txt
diff -q out.txt expected.txt || echo "Test 4 FALLÓ"

# Test 5: error de archivo de entrada
./pipex noexiste.txt "cat" "cat" out.txt 2> res.txt && echo "Test 5 FALLÓ (no falló como debía)"
grep -qi "Error opening input file" res.txt || echo "Test 5 FALLÓ (mensaje no esperado)"

# Test 6: error de archivo de salida (sin permisos)
touch out.txt
chmod 444 out.txt
./pipex in.txt "cat" "cat" out.txt 2> res.txt && echo "Test 6 FALLÓ (no falló como debía)"
grep -qi "Error opening output file" res.txt || echo "Test 6 FALLÓ (mensaje no esperado)"
chmod 644 out.txt

# Test 7: comandos no existentes
./pipex in.txt "comandoqueNOexiste" "cat" out.txt 2> res.txt && echo "Test 7 FALLÓ (no falló como debía)"
grep -qi "execvp" res.txt || echo "Test 7 FALLÓ (mensaje no esperado)"

# Test 8: argumentos con espacios y escapes
echo -e "foo bar\nbaz" > in.txt
./pipex in.txt "grep \"foo bar\"" "wc -l" out.txt
echo "1" > expected.txt
diff -q out.txt expected.txt || echo "Test 8 FALLÓ"

echo "Todos los tests completados."