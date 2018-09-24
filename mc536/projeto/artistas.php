<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1))
		header('Location: login.php');


	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;

	$client = new Client();
	$run = "MATCH (p:Person)-[r:LIKES]-(c:Artista) " . 
			"WHERE p.usuario = '{$_SESSION['usuario']}' " . 
			"return c.nomeArtistico, c.uri, r.rating";
	$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    echo "Conhecidos: <br><br>";
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('c.nomeArtistico') . " - " . $row->offsetGet('c.uri') . " - Nota: " . $row->offsetGet('r.rating') . " - ";
        echo "<a href='editArtista.php?uri=" . $row->offsetGet('c.uri') . "'>Alterar nota</a> - ";
        echo "<a href='removeArtista.php?uri=" . $row->offsetGet('c.uri') . "'>Remover</a><br><br>";
    }

    echo "<hr><br>Recomendados:<br><br>";
	$run = "MATCH (a:Artista)<-[r:LIKES]-(p2:Person)-[:LIKES]->(a2:Artista)<-[:LIKES]-(p1:Person) " .
"WHERE p1.usuario='{$_SESSION['usuario']}' AND NOT p1-[:LIKES]->a  " .
"with DISTINCT p2, p1, count(distinct a2.uri) as comum, a,r " .
"RETURN a.uri as uri, a.nomeArtistico as nome, avg(r.rating*((0.80)+(0.20)*comum))*(count(r.rating)+SUM(CASE (p2)<-[:KNOWS]-(p1) " .
	"WHEN true THEN 1 " .
	"ELSE 0 " .
"END)) as score " .
"ORDER BY score DESC LIMIT 5";

	$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('nome') . " - " . $row->offsetGet('a.uri') . " - Score: " . $row->offsetGet('score') . " - ";
    	echo "<a href='addArtista.php?uri=" . $row->offsetGet('a.uri') . "'>Eu conheço!</a><br><br>";
    }

    echo "<hr><br>Não conhecidos:<br><br>";
	$run = "MATCH (p:Person), (c:Artista) " .
			"WHERE p.usuario = '{$_SESSION['usuario']}' AND NOT(p-[:LIKES]->c) " . 
			"return c.nomeArtistico, c.uri";
	$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Artista: " . $row->offsetGet('c.nomeArtistico') . " - "   . $row->offsetGet('c.uri') . " - ";
    	echo "<a href='addArtista.php?uri=" . $row->offsetGet('c.uri') . "'>Eu conheço!</a><br><br>";
    }
    echo "<hr><br><a href='novoArtista.php'>Novo artista</a><br><br>";

    
?>