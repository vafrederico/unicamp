<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1 && $_SESSION['usuario'] = 'admin'))
		header('Location: login.php');


	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;

	$client = new Client();
	$run = "MATCH (c:Person) " . 
			"return c.nome, c.usuario";
	$query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    echo "Pessoas: <br><br>";
    foreach($result as $row) {
    	echo "Nome: " . $row->offsetGet('c.nome') . " - ";
    	echo "<a href='editPersonAdmin.php?usuario=" . $row->offsetGet('c.usuario') . "'>Editar</a><br><br>";
    }

    
?>