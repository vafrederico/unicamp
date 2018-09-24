<script src='Chart.min.js'></script>
<?php
	
	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
        $client = new Client();
echo "Qual é a média e desvio padrão dos ratings para artistas musicais?<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) RETURN avg(r.rating) as media, stdev(r.rating) as desvio";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Média: " . $row->offsetGet('media') . " - Desvio: " . $row->offsetGet('desvio') . "<br>";
    }

echo "<br><br>";

echo "Quais são os 20 artistas com o maior rating médio? Ordenados por rating médio.<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) RETURN avg(r.rating) as media, a.uri ORDER BY media DESC LIMIT 20";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('a.uri') . " - Média: " . $row->offsetGet('media') . "<br>";
    }
echo "<br><br>";

echo "Quais são os 20 artistas com o maior rating médio curtidos por pelo menos duas pessoas? Ordenados por rating médio.<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) WITH count(r) as num, avg(r.rating) as media, a.uri as uri WHERE num>1 RETURN num, media, uri ORDER BY media DESC LIMIT 20";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('uri') . " - Média: " . $row->offsetGet('media') . "<br>";
    }
echo "<br><br>";

echo "Quais são os 10 artistas musicais mais populares? Ordenados por popularidade.<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) WITH count(r) as num, a RETURN a.uri, num ORDER BY num DESC LIMIT 10";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('a.uri') . " - Popularidade: " . $row->offsetGet('num') . "<br>";
    }
echo "<br><br>";

echo "Quais são os 10 artistas com o maior variabilidade de ratings? Considere apenas artistas curtidos por pelo menos 2 pessoas. Ordenados por desvio padrão.<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) WITH count(r) as num, stdev(r.rating) as desvio, a.uri as uri WHERE num>1 RETURN num, desvio, uri ORDER BY desvio DESC LIMIT 10";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('uri') . " - Desvio: " . $row->offsetGet('desvio') . "<br>";
    }
echo "<br><br>";

echo "Quais são os 5 gêneros musicais mais populares? Ordenados por popularidade.<br>";
$run = "MATCH (:Person)-[:LIKES]->(:Artista)-[p:PLAYS]->(g:Genero) RETURN g.nome, COUNT(p) as num ORDER by num desc LIMIT 5";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Gênero: " . $row->offsetGet('g.nome') . " - Popularidade: " . $row->offsetGet('num') . "<br>";
    }

echo "<br><br>";
echo "Quais são os 10 conhecidos (duas pessoas ligadas pelo relacionamento 'knows') que compartilham o maior numero de artistas curtidos?<br>";
$run = "MATCH (p1:Person)-[r:LIKES]->(a:Artista)<-[r1:LIKES]-(p2:Person), p1-[:KNOWS]-p2 return p1.nome, p2.nome, count(a) as numero ORDER BY numero LIMIT 10";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Pessoas: " . $row->offsetGet('p1.nome') . "/" . $row->offsetGet('p2.nome') . " - Artistas compartilhados: " . $row->offsetGet('numero') . "<br>";
    }
echo "<br><br>";

echo "Calcule os valores de popularidade (número de pessoas que curtem) de artistas para o primeiro, segundo e terceiro quartis.<br>";
 
 echo "<br><br>";
echo "Construa um gráfico que mostre a popularidade dos artistas. Os artistas devem ser representados no eixo x em ordem decrescente de popularidade. Não é necessário rotular os pontos de x com o nome dos artistas.<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) return count(r) as numero, a.uri ORDER BY numero DESC";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    echo "<canvas id='c1' width=400 height=400></canvas><script>var ctx = document.getElementById('c1').getContext('2d'); var labels = []; var data = []; ";
    foreach($result as $row) {
    	echo "labels.push('". $row->offsetGet('numero') . "');";
    	echo "data.push(". $row->offsetGet('numero') . ");";
    }
    echo "var data = { labels: labels, datasets: [ {data: data}] }; new Chart(ctx).Bar(data,{}); </script>";
echo "<br><br>";

echo "Construa um gráfico para a função f(x) = número de pessoas que curtiram exatamente x artistas.<br>";
$run = "MATCH (p:Person)-[r]->(a:Artista) WITH count(r) as n,p return n, count(n) as vezes ORDER BY vezes DESC, n";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet(); 
    echo "<canvas id='c2' width=400 height=400></canvas><script>var ctx = document.getElementById('c2').getContext('2d'); var labels = []; var data = []; ";
    foreach($result as $row) {
    	echo "labels.push('". $row->offsetGet('n') . "');";
    	echo "data.push(". $row->offsetGet('vezes') . ");";
    }
    echo "var data = { labels: labels, datasets: [ {data: data}] }; new Chart(ctx).Bar(data,{}); </script>";
echo "<br><br>";

echo "Construa um gráfico para a função f(x) = número de artistas curtidos por exatamente x pessoas.<br>";
$run = "MATCH (p:Person)-[r]->(a:Artista) WITH count(r) as n,a return n, count(n) as vezes ORDER BY vezes DESC, n";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
     echo "<canvas id='c3' width=400 height=400></canvas><script>var ctx = document.getElementById('c3').getContext('2d'); var labels = []; var data = []; ";
    foreach($result as $row) {
    	echo "labels.push('". $row->offsetGet('n') . "');";
    	echo "data.push(". $row->offsetGet('vezes') . ");";
    }
    echo "var data = { labels: labels, datasets: [ {data: data}] }; new Chart(ctx).Bar(data,{}); </script>";
echo "<br><br>";

//echo "Aponte (caso existam) tipos de distribuição de probabilidade (normal, geométrica, power law, etc) que mais se aproximam dos grafos definidos nas questões anteriores.";

echo "<br><br>";
echo "Defina duas outras informações (como as anteriores) que seriam úteis para compreender melhor a rede. Agregue estas informações à página de estatísticas.<BR><BR>";


echo "Quais são os 20 artistas com o menor rating médio? Ordenados por rating médio.<br>";
$run = "MATCH (:Person)-[r:LIKES]->(a:Artista) RETURN avg(r.rating) as media, a.uri ORDER BY media ASC LIMIT 20";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('a.uri') . " - Média: " . $row->offsetGet('media') . "<br>";
    }
echo "<br><br>";

echo "Quais são as 10 pessoas mais populares? Ordenados por popularidade.<br>";
$run = "MATCH (:Person)-[r:KNOWS]->(p1:Person) return COUNT(r) as numero, p1.nome ORDER BY numero DESC LIMIT 10";
$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Nome: " . $row->offsetGet('p1.nome') . " - Popularidade: " . $row->offsetGet('numero') . "<br>";
    }
echo "<br><br>";

?>