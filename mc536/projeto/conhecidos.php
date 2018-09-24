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
	$run = "MATCH (p:Person)-[:KNOWS]-(c:Person) " . 
			"WHERE p.usuario = '{$_SESSION['usuario']}' " . 
			"return c.nome, c.usuario";
	$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    echo "Conhecidos: <br><br>";
    foreach($result as $row) {
    	echo "Nome: " . $row->offsetGet('c.nome') . " - ";
    	echo "<a href='removeConhecido.php?usuario=" . $row->offsetGet('c.usuario') . "'>Remover</a><br><br>";
    }

    echo "<hr><br>Não conhecidos:<br><br>";
	$run = "MATCH (p:Person), (c:Person) " .
			"WHERE p.usuario = '{$_SESSION['usuario']}' AND NOT(p-[:KNOWS]->c) AND NOT (p = c) " . 
			"return c.nome, c.usuario";
	$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    foreach($result as $row) {
    	echo "Nome: " . $row->offsetGet('c.nome') . " - ";
    	echo "<a href='addConhecido.php?usuario=" . $row->offsetGet('c.usuario') . "'>Eu conheço!</a> - <a href='caminho.php?usuario=" . $row->offsetGet('c.usuario') . "'>Caminho</a><br><br>";
    }

    
?>